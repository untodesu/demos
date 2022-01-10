/* Require POSIX.2-1992 */
#define _POSIX_C_SOURCE 2

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ini.h"

#define DEFCON_VERSION "0.0.1"

#define VALUE_TYPE_STRING           0
#define VALUE_TYPE_INTEGER          1
#define VALUE_TYPE_HEX_INTEGER      2
#define VALUE_TYPE_UNSIGNED_INTEGER 3
#define VALUE_TYPE_BOOLEAN          4

struct defcon_value {
    unsigned int type;
    union {
        char string[128];
        intmax_t integer;
        uintmax_t unsigned_integer;
        bool boolean;
    } u;
};

struct defcon_def {
    char name[128];
    char macro[64];
    bool has_value;
    bool value_required;
    struct defcon_value value;
    struct defcon_def *next;
};

static char print_buffer[4096] = { 0 };
static const char *argv_0 = "defcon";
static struct defcon_def *def_begin = NULL;
static bool suppress_undefined_warnings = false;
static char config_key_prefix[64] = "";

static void die(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(print_buffer, sizeof(print_buffer), fmt, va);
    va_end(va);
    fprintf(stderr, "%s: fatal: %s\n", argv_0, print_buffer);
    exit(1);
}

static void lprintf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(print_buffer, sizeof(print_buffer), fmt, va);
    va_end(va);
    fputs(print_buffer, stderr);
    fputs("\r\n", stderr);
}

static void *safe_malloc(size_t size)
{
    void *block = malloc(size);
    if(!block)
        die("out of memory (size: %zu)", size);
    return block;
}

static bool parse_boolean(const char *s)
{
    return atoi(s) || !strcmp(s, "true");
}

static unsigned int parse_type(const char *s)
{
    if(!strcmp(s, "string"))
        return VALUE_TYPE_STRING;
    if(!strcmp(s, "integer"))
        return VALUE_TYPE_INTEGER;
    if(!strcmp(s, "hex_integer"))
        return VALUE_TYPE_HEX_INTEGER;
    if(!strcmp(s, "unsigned_integer"))
        return VALUE_TYPE_UNSIGNED_INTEGER;
    if(!strcmp(s, "boolean"))
        return VALUE_TYPE_BOOLEAN;
    return VALUE_TYPE_STRING;
}

static void parse_value(const char *s, struct defcon_value *v, bool *success)
{
    bool result = false;
    switch(v->type) {
        case VALUE_TYPE_INTEGER:
            result = sscanf(s, "%" SCNdMAX, &v->u.integer) == 1;
            break;
        case VALUE_TYPE_HEX_INTEGER:
            result = sscanf(s, "0x%" SCNxMAX, &v->u.unsigned_integer) == 1;
            break;
        case VALUE_TYPE_UNSIGNED_INTEGER:
            result = sscanf(s, "%" SCNuMAX, &v->u.unsigned_integer) == 1;
            break;
        case VALUE_TYPE_BOOLEAN:
            v->u.boolean = parse_boolean(s);
            result = true;
            break;
        default:
            strncpy(v->u.string, s, sizeof(v->u.string));
            result = v->type == VALUE_TYPE_STRING;
            break;
    }

    if(!success)
        return;
    *success = result;
}

static struct defcon_def *get_def(const char *name)
{
    struct defcon_def *def = NULL;

    for(def = def_begin; def; def = def->next) {
        if(strcmp(def->name, name))
            continue;
        return def;
    }

    def = safe_malloc(sizeof(struct defcon_def));
    memset(def, 0, sizeof(struct defcon_def));
    strncpy(def->name, name, sizeof(def->name));
    def->value.type = VALUE_TYPE_STRING;

    def->next = def_begin;
    def_begin = def;

    return def;
}

static struct defcon_def *find_def(const char *name)
{
    struct defcon_def *def = NULL;

    for(def = def_begin; def; def = def->next) {
        if(strcmp(def->name, name))
            continue;
        return def;
    }

    return NULL;
}

static int ini_callback_def(void *data, const char *section, const char *name, const char *value)
{
    struct defcon_def *def = get_def(section);

    if(!strcmp(name, "macro")) {
        strncpy(def->macro, value, sizeof(def->macro));
        return 1;
    }

    if(!strcmp(name, "type")) {
        def->value.type = parse_type(value);
        return 1;
    }

    if(!strcmp(name, "value")) {
        parse_value(value, &def->value, &def->has_value);
        return 1;
    }

    if(!strcmp(name, "required")) {
        def->value_required = parse_boolean(value);
        return 1;
    }

    lprintf("%s: %s: warning: unknown key: %s", data, section, name);
    return 0;
}

static int init_callback_conf(void *data, const char *section, const char *name, const char *value)
{
    struct defcon_def *def = NULL;

    if(!(def = find_def(name))) {
        if(!suppress_undefined_warnings)
            lprintf("%s: warning: undefined key: %s", data, name);
        return 0;
    }

    parse_value(value, &def->value, &def->has_value);
    if(!def->has_value) {
        lprintf("%s: %s: warning: unable to parse: %s", data, name, value);
        return 0;
    }

    return 1;
}

static void make_config_key(const char *name, const char *macro, char *s, size_t n)
{
    size_t i;

    if(macro[0]) {
        strncpy(s, macro, n);
        return;
    }

    for(i = 0; i < n && *name; i++, name++) {
        if(isalpha(*name)) {
            s[i] = toupper(*name);
            continue;
        }

        if(isdigit(*name)) {
            s[i] = *name;
            continue;
        }

        s[i] = '_';
    }

    s[(i < n) ? i : (n - 1)] = 0;
}

static void value_string(const struct defcon_value *src, char *s, size_t n)
{
    switch(src->type) {
        case VALUE_TYPE_STRING:
            snprintf(s, n, "\"%s\"", src->u.string);
            break;
        case VALUE_TYPE_INTEGER:
            snprintf(s, n, "%" PRIdMAX, src->u.integer);
            break;
        case VALUE_TYPE_HEX_INTEGER:
            snprintf(s, n, "0x%" PRIXMAX, src->u.unsigned_integer);
            break;
        case VALUE_TYPE_UNSIGNED_INTEGER:
            snprintf(s, n, "%" PRIuMAX, src->u.unsigned_integer);
            break;
        case VALUE_TYPE_BOOLEAN:
            snprintf(s, n, "%d", src->u.boolean ? 1 : 0);
            break;
        default:
            strncpy(s, src->u.string, n);
            break;
    }
}

static bool generate_c_header(const char *filename)
{
    FILE *fp = NULL;
    struct defcon_def *def = NULL;
    char config_key[64], value[128] = { 0 };

    if(!(fp = fopen(filename, "w"))) {
        lprintf("%s: warning: unable to open file", filename);
        return false;
    }

    fprintf(fp, "#ifndef _CONFIG_H_\n");
    fprintf(fp, "#define _CONFIG_H_ 1\n");

    for(def = def_begin; def; def = def->next) {
        make_config_key(def->name, def->macro, config_key, sizeof(config_key));
        value_string(&def->value, value, sizeof(value));
        fprintf(fp, "#define %s%s %s\n", config_key_prefix, config_key, value);
    }

    fprintf(fp, "#endif\n");

    fclose(fp);
    return true;
}

static bool generate_makefile(const char *filename)
{
    FILE *fp = NULL;
    struct defcon_def *def = NULL;
    char config_key[64], value[128] = { 0 };

    if(!(fp = fopen(filename, "w"))) {
        lprintf("%s: warning: unable to open file", filename);
        return false;
    }

    for(def = def_begin; def; def = def->next) {
        make_config_key(def->name, def->macro, config_key, sizeof(config_key));
        value_string(&def->value, value, sizeof(value));
        fprintf(fp, "%s%s := %s\n", config_key_prefix, config_key, value);
    }

    fclose(fp);
    return true;
}

static void usage(void)
{
    lprintf("Usage: %s [options] <definition files>...", argv_0);
    lprintf("Options:");
    lprintf("   -C <filename>   : generate a C header");
    lprintf("   -M <filename>   : generate a makefile");
    lprintf("   -c <filename>   : set the input file (default: defcon.conf)");
    lprintf("   -p <prefix>     : set the prefix for generated key-value pairs");
    lprintf("   -d              : dump all the keys to stdout in a parsable format");
    lprintf("   -s              : suppress \"undefined key\" warnings during parsing");
    lprintf("   -h              : print this message and exit");
    lprintf("   -v              : print version and exit");
    lprintf("   <definitions>   : set the definition files");
}

static void version(void)
{
    lprintf("%s (DefCon) %s", argv_0, DEFCON_VERSION);
    lprintf("Copyright (c) 2021, Kirill GPRB.");
}

int main(int argc, char **argv)
{
    int opt, i;
    const char *opt_string = "C:M:c:p:dshv";
    char input_filename[64] = "defcon.conf", value[128] = { 0 };
    bool dump_keys = false;
    FILE *fp;
    struct defcon_def *def = NULL, *next_def = NULL;

    argv_0 = argv[0];

    strncpy(config_key_prefix, "CONFIG_", sizeof(config_key_prefix));

    optind = 1;
    while((opt = getopt(argc, argv, opt_string)) != -1) {
        switch(opt) {
            case 'c':
                strncpy(input_filename, optarg, sizeof(input_filename));
                break;
            case 'p':
                strncpy(config_key_prefix, optarg, sizeof(config_key_prefix));
                break;
            case 'd':
                dump_keys = true;
                break;
            case 's':
                suppress_undefined_warnings = true;
                break;
            case 'h':
                usage();
                return 0;
            case 'v':
                version();
                return 0;
            case '?':
                usage();
                return 1;
        }
    }

    if(optind >= argc)
        die("no definition files");

    for(i = optind; i < argc; i++) {
        if(!(fp = fopen(argv[i], "r"))) {
            lprintf("%s: warning: %s", argv[i], strerror(errno));
            continue;
        }

        if(ini_parse_file(fp, &ini_callback_def, argv[i]) < 0) {
            lprintf("%s: warning: parse error", argv[i]);
            continue;
        }

        fclose(fp);
    }

    if(dump_keys) {
        fprintf(stdout, "# This config will be parsed by defcon\n");
        fprintf(stdout, "# without any serious problems but I'd\n");
        fprintf(stdout, "# recommend editing it to make it readable\n");

        for(def = def_begin; def; def = def->next) {
            value_string(&def->value, value, sizeof(value));
            fprintf(stdout, "%s = %s\n", def->name, value);
        }
        
        goto safe_exit;
    }

    fp = fopen(input_filename, "r");
    if(!fp)
        die("%s", strerror(errno));
    if(ini_parse_file(fp, &init_callback_conf, input_filename) < 0)
        die("parse error");
    fclose(fp);

    for(def = def_begin; def; def = def->next) {
        if(def->has_value || !def->value_required)
            continue;
        die("key %s requires a value!", def->name);
    }

    optind = 1;
    while((opt = getopt(argc, argv, opt_string)) != -1) {
        switch(opt) {
            case 'C':
                generate_c_header(optarg);
                break;
            case 'M':
                generate_makefile(optarg);
                break;
        }
    }

safe_exit:
    for(def = def_begin; def; def = next_def) {
        next_def = def->next;
        free(def);
    }

    return 0;
}
