/*
 * Copyright (c) 2015 Ambroz Bizjak
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <aprinter/base/Preprocessor.h>

#define PACK_STRUCT_STRUCT __attribute__((packed))

#ifdef __cplusplus
extern "C"
#endif
void aprinter_lwip_platform_diag (char const *fmt, ...);

// Tell lwip how to print diagnostic messages.
#define LWIP_PLATFORM_DIAG(x) do { aprinter_lwip_platform_diag x; } while (0)

// Tell lwip what to do on assertion failure.
// TBD: Improve this to use Assert.h.
#define LWIP_PLATFORM_ASSERT(x) do { puts(__FILE__ ":" AMBRO_STRINGIFY(__LINE__) x); while (1); } while (0)

// Enable/disable lwip assertions.
#if !APRINTER_LWIP_ASSERTIONS
#define LWIP_NOASSERT
#endif

// Lwip defaults to using PRIuPTR for printing size_t which is a good guess
// but we know we have %zu available so let's use this.
#define SZT_F "zu"

// Rely on GCC's byte order macros to inform lwip of the byte order.
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LWIP_BYTE_ORDER LWIP_LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define LWIP_BYTE_ORDER LWIP_BIG_ENDIAN
#else
#error Unknown byte order
#endif

// Give GCC's bswap builtins to lwip.
#define LWIP_PLATFORM_BYTESWAP 1
#define LWIP_PLATFORM_BSWAP16(x) __builtin_bswap16(x)
#define LWIP_PLATFORM_BSWAP32(x) __builtin_bswap32(x)
