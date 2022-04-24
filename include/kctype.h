/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:14 */
#ifndef _KCTYPE_H_
#define _KCTYPE_H_ 1

int kisalnum(int c);
int kisalpha(int c);
int kisascii(int c);
int kisblank(int c);
int kiscntrl(int c);
int kisdigit(int c);
int kisgraph(int c);
int kislower(int c);
int kisprint(int c);
int kispunct(int c);
int kisspace(int c);
int kisupper(int c);
int kisxdigit(int c);

int ktoascii(int c);
int ktolower(int c);
int ktoupper(int c);

#endif
