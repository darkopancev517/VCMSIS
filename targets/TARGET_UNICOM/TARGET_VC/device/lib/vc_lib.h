#ifndef VC_LIB_H
#define VC_LIB_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

extern long vc_strtol(const char *str, char **ep);
extern unsigned long vc_strtoul(const char *str, char **ep);
extern unsigned long vc_strtox(const char *str, char **ep);
extern void vc_ltoa(char *a, unsigned long *len, long l, bool w_sign);
extern void vc_ultoa(char *a, unsigned long *len, unsigned long u);
extern unsigned long vc_strtoux(const char *str);
extern void vc_xtoa(char *a, unsigned long *len, unsigned long x, bool capitalized);

#ifdef __cplusplus
}
#endif

#endif  // VC_LIB_H
