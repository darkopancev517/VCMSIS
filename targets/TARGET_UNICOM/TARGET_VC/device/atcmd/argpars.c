#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "argpars.h"
//
//_argargs_chk_opt:
//    fst 
//    las
//    argvi
//  *pmap : updated
// return value: 
//    -1:  -h option
//     0:  an option other than -h
//     1:  not an option
static int _argargs_chk_opt1(char fst, char las, const char *argvi, int *pmap)
{
  if (strlen(argvi)==2&&argvi[0]=='-'){
    if (argvi[1]>=fst&&argvi[1]<=las){
      *pmap|=(1<<(argvi[1]-fst));
      if (argvi[1]=='h') return -1; //for convenience to the caller, return value indicates '-h' is there
      return 0;
    }
  }
  return 1;
}
//
//_argargs_chk_opt:
//    argvi
//  *pmap : updated
// return value: 
//    -1: 
static int _argargs_chk_opt(const char *argvi, struct optmap *pom)
{
  int res;
  if ((res=_argargs_chk_opt1('a','z',argvi,&(pom->lowmap)))<=0)
    return res;
  if ((res=_argargs_chk_opt1('A','Z',argvi,&(pom->uppmap)))<=0)
    return res;
  if ((res=_argargs_chk_opt1('0','9',argvi,&(pom->nummap)))<=0)
    return res;
  return 1;
}

static int _str2int(const char *s, char rdx)
{
  switch (rdx){
    case 'x': return strtoul(s, NULL, 16);
    default : return atoi(s); //'i'
  }
}

int _str2intlst(const char *s0, int rdx, int len ,int *buf)
{
  char s2[23];//2^31: max 10 digits, 10(begin)+2(dots)+10(end)+1(null)
  int i;
  for (i=0; i<sizeof(s2)/sizeof(char)&&s0[i]!=','&&s0[i]!=0; i++){
    s2[i]=s0[i];
  }
  if (i>=sizeof(s2)/sizeof(char)&&s2[i-1]!=0){
    return -1; //string range too long
  }
  if (i==0){
    return -1; //null string
  }
  s2[i]=0;//terminate the string
  char *pd;
  int bx,ex;
  if ((pd=strstr(s2,".."))==NULL){
    //single integer
    bx=_str2int(s2,rdx);
    ex=bx;
  }else{
    //integer range: x..y 
    *pd=0; pd+=2;
    bx=_str2int(s2,rdx);
    ex=_str2int(pd,rdx);
    if (ex<bx ||(ex-bx+1)>len){
      return -1; //range error
    }
  }
  i=0;
  for (int x=bx; x<=ex; x++){
    buf[i++]=x;
  }
  return i;
}

int argpars_str2intlst(char *args, char rdx, int len, int *ibuf)
{
  char *tkn;
  // get the first token
  tkn = strtok(args, ",");
  // walk through other tokens
  int i=0,d;
  while (tkn!=NULL && i<len){
    if ((d=_str2intlst(tkn,rdx,len-i,&ibuf[i]))<0){
      return -1; //string format error
    }
    i+=d;
    tkn = strtok(NULL, ",");
  }
  return i;
}

//
// 0 <= idx < sizeof(pas)/sizeof(int*)
// 0 <= idx < sizeof(radix)/sizeof(radix*)
//
static int _cnvt_arg(int idx, const char *argvi, int **pas, const char *radix)
{
  if (pas[idx]==NULL) return 0;
  if (radix==NULL||idx>=strlen(radix)){
    *pas[idx]=_str2int(argvi,'i');//integer is assumed if not supplied
  }else if (radix[idx]=='s'){
    *pas[idx]=(int)(int *)argvi;
  }else{
    *pas[idx]=_str2int(argvi,radix[idx]);//integer 
  }
  return 1;
}

// _argpars_vars: 
// argstart: arguments start index, eg. if argstart=2,  that means the 1st argument is argv[2]
// *pa1, *pa2, *pa3, *pa4, and *pa5 may or may not gets its value, depending on the supplied command-line **argv
// for string type argument, the caller needs to cast its type
// the caller may supply default values to *pa1, *pa2, *pa3, and *pa4 before calling this function
// if the caller has less argument, it should supply all the rest arguments as NULLs
//
static int _argpars_vars(int argc, char **argv, int argstart, int *pa1, int *pa2, int *pa3, int *pa4, int *pa5, const char *radix, struct optmap *pom)
{
  int res=0;
  int posidx=0;
  int *pas[]={pa1,pa2,pa3,pa4,pa5,NULL};//must end with NULL
  pom->lowmap=0;
  pom->uppmap=0;
  pom->nummap=0;
  for (int i=argstart; i<argc; i++){
    if ((res=_argargs_chk_opt(argv[i],pom))<0) {
        return res;//-h help , just print help
    }else if (res>0) {
      if (!_cnvt_arg(posidx,argv[i],pas,radix)){
        return posidx;
      }
      posidx++;
      if (posidx>=sizeof(pas)/sizeof(int *)-1)
        return posidx;
    }
  }
  return posidx;
}

// argpars_vars: 
// assumption: arguments start at index 2
// *pa1, *pa2, *pa3, *pa4, and *pa5 may or may not gets its value, depending on the supplied command-line **argv
// for string type argument, the caller needs to cast its type
// the caller may supply default values to *pa1, *pa2, *pa3, and *pa4 before calling this function
// if the caller has less argument, it should supply all the rest arguments as NULLs
//
int argpars_vars(int argc, char **argv, int *pa1, int *pa2, int *pa3, int *pa4, int *pa5, const char *radix, struct optmap *pom)
{
  return _argpars_vars(argc, argv, 2, pa1, pa2, pa3, pa4, pa5, radix, pom);
}

// argpars_vars_1: 
// assumption: arguments start at index 1
int argpars_vars_1(int argc, char **argv, int *pa1, int *pa2, int *pa3, int *pa4, int *pa5, const char *radix, struct optmap *pom)
{
  return _argpars_vars(argc, argv, 1, pa1, pa2, pa3, pa4, pa5, radix, pom);
}

int argpars_has_opt(char opt, struct optmap *pom)
{
  if (opt>='a' && opt <='z')
    return pom->lowmap&(1<<(opt-'a'))? 1:0;
  if (opt>='A' && opt <='Z')
    return pom->uppmap&(1<<(opt-'A'))? 1:0;
  if (opt>='0' && opt <='9')
    return pom->nummap&(1<<(opt-'0'))? 1:0;
  return 0;
}
