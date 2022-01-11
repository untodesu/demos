/* Require POSIX.2-1992 */
#define _POSIX_C_SOURCE 2

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define DEF_FORWARD   0
#define DEF_INTEGER   1
#define DEF_UINTEGER  2
#define DEF_XINTEGER  3
#define DEF_STRING    4
#define DEF_BOOLEAN   5

#define DEF_MAX_ID    128
#define DEF_MAX_ARGV  16

struct def_entry {
    struct def_entry *next;
    char name[64];
    char macro[64];
    char description[128];
    unsigned short type;
    unsigned short noedit;
    unsigned short has_value;
    union {
        char s[256];
        intmax_t i;
        uintmax_t u;
        unsigned short b;
    } value;
};

static struct def_entry *entries = NULL;
static const char *argv_0 = "genconfig";
static char print_buffer[4096] = { 0 };
static char gen_prefix[64] = { 0 };
static int suppress_warnings = 0;

static void die(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(print_buffer, sizeof(print_buffer), fmt, va);
    va_end(va);
    fprintf(stderr, "%s: fatal: %s\r\n", argv_0, print_buffer);
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

static void *safe_malloc(size_t n)
{
    void *block = malloc(n);
    if(!block)
        die("out of memory (size: %zu)", n);
    return block;
}

static unsigned short parse_type(const char *s)
{
    if(!strcasecmp(s, "forward"))
        return DEF_FORWARD;
    if(!strcasecmp(s, "integer") || !strcasecmp(s, "int"))
        return DEF_INTEGER;
    if(!strcasecmp(s, "uinteger") || !strcasecmp(s, "unsigned_integer") || !strcasecmp(s, "uint"))
        return DEF_UINTEGER;
    if(!strcasecmp(s, "xinteger") || !strcasecmp(s, "hex_integer") || !strcasecmp(s, "xint"))
        return DEF_XINTEGER;
    if(!strcasecmp(s, "string"))
        return DEF_STRING;
    if(!strcasecmp(s, "boolean") || !strcasecmp(s, "bool"))
        return DEF_BOOLEAN;
    return DEF_FORWARD;
}

static unsigned short parse_boolean(const char *s)
{
    if(!strcasecmp(s, "false") || !strcasecmp(s, "off") || !strcasecmp(s, "no"))
        return 0;
    if(!strcasecmp(s, "true") || !strcasecmp(s, "on") || !strcasecmp(s, "yes"))
        return 1;
    return (unsigned short)strtoul(s, NULL, 10);
}

static int parse_base(const char *s, int *skip)
{
    if(s[0] == '0') {
        switch(s[1]) {
            case 'b':
            case 'B':
                *skip = 2;
                return 2;
            case 'x':
            case 'X':
                *skip = 2;
                return 2;
            default:
                *skip = 0;
                return 8;
        }
    }

    *skip = 0;
    return 10;
}

static struct def_entry *find_entry(const char *name)
{
    struct def_entry *entry;
    for(entry = entries; entry; entry = entry->next) {
        if(strcmp(entry->name, name))
            continue;
        return entry;
    }

    return NULL;
}

static struct def_entry *make_entry(const char *name, const char *type)
{
    int i;
    const char *s;
    struct def_entry *entry = find_entry(name);
    if(entry) {
        lprintf("waning: %s: redefining entries not allowed", name);
        return NULL;
    }

    entry = safe_malloc(sizeof(struct def_entry));
    memset(entry, 0, sizeof(struct def_entry));
    strncpy(entry->name, name, sizeof(entry->name));
    entry->type = parse_type(type);
    entry->noedit = 0;
    entry->has_value = 0;

    for(i = 0, s = entry->name; (size_t)i < (sizeof(entry->macro) - 1) && *s; i++, s++) {
        if(isalpha(*s)) {
            entry->macro[i] = toupper(*s);
            continue;
        }

        if(isdigit(*s)) {
            entry->macro[i] = *s;
            continue;
        }

        entry->macro[i] = '_';
    }

    entry->next = entries;
    entries = entry;

    return entry;
}

static void parse_def_command(const char *cmd, const char *filename, unsigned int line_no)
{
    static char def_argv[DEF_MAX_ARGV][DEF_MAX_ID];
    int i, j;
    struct def_entry *entry;

    memset(def_argv, 0, sizeof(def_argv));

    if(cmd[0] != '$') {
        if(!suppress_warnings)
            lprintf("warning: %s:%u: not a command", filename, line_no);
        return;
    }

    cmd++;

    i = 0;
    while(*cmd && i < DEF_MAX_ARGV) {
        for(j = 0; j < DEF_MAX_ID && *cmd; j++) {
            if(*cmd == '$' || *cmd == '\r' || *cmd == '\n')
                break;
            def_argv[i][j] = *cmd++;
        }

        i++;
        cmd++;
    }

    if(!def_argv[0][0]) {
        if(!suppress_warnings)
            lprintf("warning: %s:%u: empty command", filename, line_no);
        return;
    }

    if(!strcasecmp(def_argv[0], "entry")) {
        make_entry(def_argv[1], def_argv[2]);
        return;
    }

    if(!strcasecmp(def_argv[0], "noedit") && (entry = find_entry(def_argv[1]))) {
        entry->noedit = 1;
        return;
    }

    if(!strcasecmp(def_argv[0], "describe") && (entry = find_entry(def_argv[1]))) {
        strncpy(entry->description, def_argv[2], sizeof(entry->description));
        return;
    }

    if(!strcasecmp(def_argv[0], "set_macro") && (entry = find_entry(def_argv[1]))) {
        memset(entry->macro, 0, sizeof(entry->macro));
        strncpy(entry->macro, def_argv[2], sizeof(entry->macro));
        return;
    }

    if(!strcasecmp(def_argv[0], "set_value") && (entry = find_entry(def_argv[1]))) {
        entry->has_value = 1;
        switch(entry->type) {
            case DEF_INTEGER:
                entry->value.i = strtoimax(def_argv[2], NULL, 10);
                return;
            case DEF_UINTEGER:
                i = parse_base(def_argv[2], &j);
                entry->value.u = strtoumax(def_argv[2] + j, NULL, i);
                return;
            case DEF_XINTEGER:
                entry->value.u = strtoumax(def_argv[2], NULL, 16);
                return;
            case DEF_BOOLEAN:
                entry->value.b = parse_boolean(def_argv[2]);
                return;
            default:
                memset(entry->value.s, 0, sizeof(entry->value.s));
                strncpy(entry->value.s, def_argv[2], sizeof(entry->value.s));
                return;
        }
    }
}

static void parse_deffile(const char *filename)
{
    FILE *fp;
    unsigned int line;
    char s[512] = { 0 };
    const char *sp;

    if(!(fp = fopen(filename, "r"))) {
        if(!suppress_warnings)
            lprintf("warning: %s: %s", filename, strerror(errno));
        return;
    }

    line = 0;
    while((sp = fgets(s, sizeof(s), fp))) {
        parse_def_command(sp, filename, line);
        line++;
    }

    fclose(fp);
}

static void parse_config(const char *filename)
{
    FILE *fp;
    unsigned int line;
    char s[512] = { 0 }, id[64] = { 0 };
    const char *sp;
    char *scratch;
    int i, j;
    struct def_entry *entry;

    if(!(fp = fopen(filename, "r")))
        die("%s: %s", filename, strerror(errno));

    line = 0;
    while((sp = fgets(s, sizeof(s), fp))) {
        if((scratch = strchr(sp, '\r')))
            *scratch = 0;
        if((scratch = strchr(sp, '\n')))
            *scratch = 0;

        if(sscanf(sp, "%63[^= \t\r\n]s", id) <= 0)
            continue;

        while(*sp != '=')
            sp++;
        sp++;
        while(isspace(*sp))
            sp++;

        if((entry = find_entry(id)) && !entry->noedit) {
            entry->has_value = 1;
            switch(entry->type) {
                case DEF_INTEGER:
                    entry->value.i = strtoimax(sp, NULL, 10);
                    return;
                case DEF_UINTEGER:
                    i = parse_base(sp, &j);
                    entry->value.u = strtoumax(sp + j, NULL, i);
                    return;
                case DEF_XINTEGER:
                    entry->value.u = strtoumax(sp, NULL, 16);
                    return;
                case DEF_BOOLEAN:
                    entry->value.b = parse_boolean(sp);
                    return;
                default:
                    memset(entry->value.s, 0, sizeof(entry->value.s));
                    strncpy(entry->value.s, sp, sizeof(entry->value.s));
                    return;
            }
        }

        line++;
    }

    fclose(fp);
}

static void value_to_string(const struct def_entry *entry, char *s, size_t n)
{
    memset(s, 0, n);
    switch(entry->type) {
        case DEF_FORWARD:
            strncpy(s, entry->value.s, n);
            return;
        case DEF_INTEGER:
            snprintf(s, n, "%" PRIdMAX, entry->value.i);
            return;
        case DEF_UINTEGER:
            snprintf(s, n, "%" PRIuMAX, entry->value.u);
            return;
        case DEF_XINTEGER:
            snprintf(s, n, "0x%" PRIXMAX, entry->value.u);
            return;
        case DEF_STRING:
            snprintf(s, n, "\"%s\"", entry->value.s);
            return;
        case DEF_BOOLEAN:
            strncpy(s, entry->value.b ? "1" : "0", n);
            return;
    }
}

static void gen_c_header(const char *filename)
{
    char val_s[512] = { 0 };
    struct def_entry *entry;
    FILE *fp = fopen(filename, "w");
    
    if(!fp) {
        if(!suppress_warnings)
            lprintf("warning: %s: %s", filename, strerror(errno));
        return;
    }

    fprintf(fp, "#ifndef _CONFIG_H_\n");
    fprintf(fp, "#define _CONFIG_H_ 1\n");

    for(entry = entries; entry; entry = entry->next) {
        if(entry->has_value) {
            value_to_string(entry, val_s, sizeof(val_s));
            fprintf(fp, "#define %s%s %s /* %s */\n", gen_prefix, entry->macro, val_s, entry->description);
        }
    }

    fprintf(fp, "#endif\n");

    fclose(fp);
}

static void gen_makefile(const char *filename)
{
    char val_s[512] = { 0 };
    struct def_entry *entry;
    FILE *fp = fopen(filename, "w");
    
    if(!fp) {
        if(!suppress_warnings)
            lprintf("warning: %s: %s", filename, strerror(errno));
        return;
    }

    for(entry = entries; entry; entry = entry->next) {
        if(entry->has_value) {
            value_to_string(entry, val_s, sizeof(val_s));
            fprintf(fp, "%s%s := %s\n", gen_prefix, entry->macro, val_s);
        }
    }

    fclose(fp);
}

static void gen_config(FILE *fp)
{
    char val_s[512] = { 0 };
    struct def_entry *entry;
    
    for(entry = entries; entry; entry = entry->next) {
        value_to_string(entry, val_s, sizeof(val_s));
        fprintf(fp, "%s=%s\n", entry->name, val_s);
    }
}

static void usage(void)
{
    lprintf("usage: %s [options] <config (if no -d)> <definitions...>", argv_0);
    lprintf("options:");
    lprintf("   -C <filename>   : produce a C header");
    lprintf("   -M <filename>   : produce a makefile includable");
    lprintf("   -p <prefix>     : set the generated prefix (default: CONFIG_)");
    lprintf("   -d              : dump editable entries to stdout");
    lprintf("   -s              : suppress all the warnings");
    lprintf("   -h              : print help and exit");
}

#define GETOPT_OPTIONS "C:M:p:dsh"

int main(int argc, char **argv)
{
    int i, opt, nd;
    unsigned short dump_config = 0;
    char input_filename[128] = { 0 };
    struct def_entry *entry, *next_entry;

    memset(gen_prefix, 0, sizeof(gen_prefix));
    strncpy(gen_prefix, "CONFIG_", sizeof(gen_prefix));

    argv_0 = argv[0];

    optind = 1;
    while((opt = getopt(argc, argv, GETOPT_OPTIONS)) != -1) {
        switch(opt) {
            case 'c':
                memset(input_filename, 0, sizeof(input_filename));
                strncpy(input_filename, optarg, sizeof(input_filename));
                break;
            case 'p':
                memset(gen_prefix, 0, sizeof(gen_prefix));
                strncpy(gen_prefix, optarg, sizeof(gen_prefix));
                break;
            case 'd':
                dump_config = 1;
                break;
            case 's':
                suppress_warnings = 1;
                break;
            case 'h':
                usage();
                return 0;
            case '?':
                usage();
                return 1;
        }
    }

    if(optind >= argc)
        die("no input files");

    for(nd = 0, i = optind; i < argc; i++) {
        if(i == optind && !dump_config) {
            memset(input_filename, 0, sizeof(input_filename));
            strncpy(input_filename, argv[i], sizeof(input_filename));
            continue;
        }

        parse_deffile(argv[i]);
        nd++;
    }

    if(!nd)
        die("no definitions");

    if(dump_config) {
        gen_config(stdout);
        goto safe_exit;
    }

    parse_config(input_filename);

    for(entry = entries; entry; entry = entry->next) {
        if(entry->has_value)
            continue;
        die("entry %s requires a value!", entry->name);
    }

    optind = 1;
    while((opt = getopt(argc, argv, GETOPT_OPTIONS)) != -1) {
        switch(opt) {
            case 'C':
                gen_c_header(optarg);
                break;
            case 'M':
                gen_makefile(optarg);
                break;
        }
    }
    
safe_exit:
    for(entry = entries; entry; entry = next_entry) {
        next_entry = entry->next;
        free(entry);
    }

    return 0;
}
