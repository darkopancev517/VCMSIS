#ifndef _VC_TYPE_H_
#define _VC_TYPE_H_

#define VC_MS_TICK	1
#define VC_S_TICK	(VC_MS_TICK * 1000)
#define VC_M_TICK	(VC_S_TICK * 60)
#define VC_H_TICK	(VC_M_TICK * 60)
#define VC_D_TICK	(VC_H_TICK * 24)

#define LF			"\r\n"
#define LFLF		"\r\n\r\n"
#define RET_CHAR  	'\n'
#define END_CHAR  	'\r'
#define CTRL_D 		0x04

typedef unsigned char vc_uint8;
typedef signed char vc_int8;
typedef unsigned char vc_char;
typedef unsigned short int vc_uint16;
typedef signed short int vc_int16;
typedef unsigned long int vc_uint32;
typedef signed long int vc_int32;
typedef signed int vc_int;
typedef unsigned int vc_uint;
typedef signed long vc_float;
typedef vc_uint32 vc_ntb32;

#define VC_FALSE 0
#define VC_TRUE 1
typedef unsigned long int vc_bool;

#define CEIL_DIV(a, b) (((a) + (b) - 1) / (b))

#endif
