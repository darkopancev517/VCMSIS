#ifndef ARGPARS_H
#define ARGPARS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct optmap {
  int lowmap; //lowercase letter option :  bit 0: '-a', bit 1: '-b', ....
  int uppmap; //uppercase letter option : bit 0: '-A', bit 1: '-B', ....
  int nummap; //numeric digit option:     bit 0: '-0', bit 1: '-1', ....
} _optmap;

int argpars_str2intlst(char *args, char rdx, int len, int *ibuf);
int argpars_vars(int argc, char **argv, int *pa1, int *pa2, int *pa3, int *pa4, int *pa5, const char *radix, struct optmap *pom);
int argpars_vars_1(int argc, char **argv, int *pa1, int *pa2, int *pa3, int *pa4, int *pa5, const char *radix, struct optmap *pom);
int argpars_has_opt(char opt, struct optmap *pom);

#ifdef __cplusplus
}
#endif

#endif // ARGPARS_H
