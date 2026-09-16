#include <stdio.h>
#include "myheader.h"
#include MACRO_HEADER

#define MAX 100
#define PI 3.14159
#define GREETING "hello"

#define SQUARE(x) ((x) * (x))
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

#undef MAX

#ifdef DEBUG
    int debug_flag;
#endif

#ifndef HEADER_H
#define HEADER_H
#endif

#if VERSION >= 2
    int v2_feature;
#elif VERSION == 1
    int v1_feature;
#else
    int fallback;
#endif

#if defined(FOO) && !defined(BAR)
    int foo_only;
#endif

#error "unsupported configuration"

#pragma pack(1)
#pragma once

#line 100 "generated.c"

#

#define STR(x) #x
#define CONCAT(a, b) a ## b

#define LONG_MACRO(x) \
    ((x) + 1)

__FILE__
__LINE__
__DATE__
__TIME__
__STDC__
__STDC_VERSION__
__STDC_HOSTED__
__func__

__STDC_IEC_559__
__STDC_IEC_559_COMPLEX__
__STDC_ISO_10646__
