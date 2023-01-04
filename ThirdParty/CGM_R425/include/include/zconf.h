/* zconf.h -- configuration of the zlib compression library
 * Copyright (C) 1995-2010 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
/*
 * DS 01/12/2004
 * Modification of definition of uLong into size_t for 64bits
 * specific prefixes with CAT
 * specific prefixes for minizip
 * Merci spatial pour les symboles dupliques
*/

/* @(#) $Id$ */

#ifndef ZCONF_H
#define ZCONF_H

/* on arrive depuis JS0ZLIB */
#ifdef __JS0ZLIB
#include "CATDataType.h"
#else
#ifndef __CATDataType
/* pour pouvoir linker exterieure a mkmk */
#if !defined(PLATEFORME_DS64)
typedef long CATLONG32 ;
typedef unsigned long CATULONG32 ;
#else
typedef int CATLONG32 ;
typedef unsigned int CATULONG32 ;
#endif
#endif
#endif



#include <stdio.h>
/*
 * If you *really* need a unique prefix for all types and library functions,
 * compile with -DZ_PREFIX. The "standard" zlib should be compiled without it.
 * Even better than compiling with -DZ_PREFIX would be to use configure to set
 * this permanently in zconf.h using "./configure --zprefix".
 */
#ifdef Z_PREFIX     /* may be set to #if 1 by ./configure */

/* all linked symbols */
#  define _dist_code            CAT_dist_code
#  define _length_code          CAT_length_code
#  define _tr_align             CAT_tr_align
#  define _tr_flush_block       CAT_tr_flush_block
#  define _tr_init              CAT_tr_init
#  define _tr_stored_block      CAT_tr_stored_block
#  define _tr_tally             CAT_tr_tally
#  define adler32               CAT_adler32
#  define adler32_combine       CAT_adler32_combine
#  define adler32_combine64     CAT_adler32_combine64
#  define compress              CAT_compress
#  define compress2             CAT_compress2
#  define compressBound         CAT_compressBound
#  define crc32                 CAT_crc32
#  define crc32_combine         CAT_crc32_combine
#  define crc32_combine64       CAT_crc32_combine64
#  define deflate               CAT_deflate
#  define deflateBound          CAT_deflateBound
#  define deflateCopy           CAT_deflateCopy
#  define deflateEnd            CAT_deflateEnd
#  define deflateInit2_         CAT_deflateInit2_
#  define deflateInit_          CAT_deflateInit_
#  define deflateParams         CAT_deflateParams
#  define deflatePrime          CAT_deflatePrime
#  define deflateReset          CAT_deflateReset
#  define deflateSetDictionary  CAT_deflateSetDictionary
#  define deflateSetHeader      CAT_deflateSetHeader
#  define deflateTune           CAT_deflateTune
#  define deflate_copyright     CAT_deflate_copyright
#  define get_crc_table         CAT_get_crc_table
#  define gz_error              CAT_gz_error
#  define gz_intmax             CAT_gz_intmax
#  define gz_strwinerror        CAT_gz_strwinerror
#  define gzbuffer              CAT_gzbuffer
#  define gzclearerr            CAT_gzclearerr
#  define gzclose               CAT_gzclose
#  define gzclose_r             CAT_gzclose_r
#  define gzclose_w             CAT_gzclose_w
#  define gzdirect              CAT_gzdirect
#  define gzdopen               CAT_gzdopen
#  define gzeof                 CAT_gzeof
#  define gzerror               CAT_gzerror
#  define gzflush               CAT_gzflush
#  define gzgetc                CAT_gzgetc
#  define gzgets                CAT_gzgets
#  define gzoffset              CAT_gzoffset
#  define gzoffset64            CAT_gzoffset64
#  define gzopen                CAT_gzopen
#  define gzopen64              CAT_gzopen64
#  define gzprintf              CAT_gzprintf
#  define gzputc                CAT_gzputc
#  define gzputs                CAT_gzputs
#  define gzread                CAT_gzread
#  define gzrewind              CAT_gzrewind
#  define gzseek                CAT_gzseek
#  define gzseek64              CAT_gzseek64
#  define gzsetparams           CAT_gzsetparams
#  define gztell                CAT_gztell
#  define gztell64              CAT_gztell64
#  define gzungetc              CAT_gzungetc
#  define gzwrite               CAT_gzwrite
#  define inflate               CAT_inflate
#  define inflateBack           CAT_inflateBack
#  define inflateBackEnd        CAT_inflateBackEnd
#  define inflateBackInit_      CAT_inflateBackInit_
#  define inflateCopy           CAT_inflateCopy
#  define inflateEnd            CAT_inflateEnd
#  define inflateGetHeader      CAT_inflateGetHeader
#  define inflateInit2_         CAT_inflateInit2_
#  define inflateInit_          CAT_inflateInit_
#  define inflateMark           CAT_inflateMark
#  define inflatePrime          CAT_inflatePrime
#  define inflateReset          CAT_inflateReset
#  define inflateReset2         CAT_inflateReset2
#  define inflateSetDictionary  CAT_inflateSetDictionary
#  define inflateSync           CAT_inflateSync
#  define inflateSyncPoint      CAT_inflateSyncPoint
#  define inflateUndermine      CAT_inflateUndermine
#  define inflate_copyright     CAT_inflate_copyright
#  define inflate_fast          CAT_inflate_fast
#  define inflate_table         CAT_inflate_table
#  define uncompress            CAT_uncompress
#  define zError                CAT_zError
#  define zcalloc               CAT_zcalloc
#  define zcfree                CAT_zcfree
#  define zlibCompileFlags      CAT_zlibCompileFlags
#  define zlibVersion           CAT_zlibVersion

#  define z_errmsg              CAT_z_errmsg


/* all zlib typedefs in zlib.h and zconf.h */
#  define Byte                  CAT_Byte
#  define Bytef                 CAT_Bytef
#  define alloc_func            CAT_alloc_func
#  define charf                 CAT_charf
#  define free_func             CAT_free_func
#  define gzFile                CAT_gzFile
#  define gz_header             CAT_gz_header
#  define gz_headerp            CAT_gz_headerp
#  define in_func               CAT_in_func
#  define intf                  CAT_intf
#  define out_func              CAT_out_func
#  define uInt                  CAT_uInt
#  define uIntf                 CAT_uIntf
#  define uLong                 CAT_uLong
#  define uLongf                CAT_uLongf
#  define voidp                 CAT_voidp
#  define voidpc                CAT_voidpc
#  define voidpf                CAT_voidpf

/* all zlib structs in zlib.h and zconf.h */
#  define gz_header_s           CAT_gz_header_s
#  define internal_state        CAT_internal_state

#endif

#if defined(__MSDOS__) && !defined(MSDOS)
#  define MSDOS
#endif
#if (defined(OS_2) || defined(__OS2__)) && !defined(OS2)
#  define OS2
#endif
#if defined(_WINDOWS) && !defined(WINDOWS)
#  define WINDOWS
#endif
#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
#  ifndef WIN32
#    define WIN32
#  endif
#endif
#if (defined(MSDOS) || defined(OS2) || defined(WINDOWS)) && !defined(WIN32)
#  if !defined(__GNUC__) && !defined(__FLAT__) && !defined(__386__)
#    ifndef SYS16BIT
#      define SYS16BIT
#    endif
#  endif
#endif

/*
 * Compile with -DMAXSEG_64K if the alloc function cannot allocate more
 * than 64k bytes at a time (needed on systems with 16-bit int).
 */
#ifdef SYS16BIT
#  define MAXSEG_64K
#endif
#ifdef MSDOS
#  define UNALIGNED_OK
#endif

#ifdef __STDC_VERSION__
#  ifndef STDC
#    define STDC
#  endif
#  if __STDC_VERSION__ >= 199901L
#    ifndef STDC99
#      define STDC99
#    endif
#  endif
#endif
#if !defined(STDC) && (defined(__STDC__) || defined(__cplusplus))
#  define STDC
#endif
#if !defined(STDC) && (defined(__GNUC__) || defined(__BORLANDC__))
#  define STDC
#endif
#if !defined(STDC) && (defined(MSDOS) || defined(WINDOWS) || defined(WIN32))
#  define STDC
#endif
#if !defined(STDC) && (defined(OS2) || defined(__HOS_AIX__))
#  define STDC
#endif

#if defined(__OS400__) && !defined(STDC)    /* iSeries (formerly AS/400). */
#  define STDC
#endif

#ifndef STDC
#  ifndef const /* cannot use !defined(STDC) && !defined(const) on Mac */
#    define const       /* note: need a more gentle solution here */
#  endif
#endif

/* Some Mac compilers merge all .h files incorrectly: */
#if defined(__MWERKS__)||defined(applec)||defined(THINK_C)||defined(__SC__)
#  define NO_DUMMY_DECL
#endif

/* Maximum value for memLevel in deflateInit2 */
#ifndef MAX_MEM_LEVEL
#  ifdef MAXSEG_64K
#    define MAX_MEM_LEVEL 8
#  else
#    define MAX_MEM_LEVEL 9
#  endif
#endif

/* Maximum value for windowBits in deflateInit2 and inflateInit2.
 * WARNING: reducing MAX_WBITS makes minigzip unable to extract .gz files
 * created by gzip. (Files created by minigzip can still be extracted by
 * gzip.)
 */
#ifndef MAX_WBITS
#  define MAX_WBITS   15 /* 32K LZ77 window */
#endif

/* The memory requirements for deflate are (in bytes):
            (1 << (windowBits+2)) +  (1 << (memLevel+9))
 that is: 128K for windowBits=15  +  128K for memLevel = 8  (default values)
 plus a few kilobytes for small objects. For example, if you want to reduce
 the default memory requirements from 256K to 128K, compile with
     make CFLAGS="-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7"
 Of course this will generally degrade compression (there's no free lunch).

   The memory requirements for inflate are (in bytes) 1 << windowBits
 that is, 32K for windowBits=15 (default value) plus a few kilobytes
 for small objects.
*/

                        /* Type declarations */

#ifndef OF /* function prototypes */
#  ifdef STDC
#    define OF(args)  args
#  else
#    define OF(args)  ()
#  endif
#endif

/* The following definitions for FAR are needed only for MSDOS mixed
 * model programming (small or medium model with some far allocations).
 * This was tested only with MSC; for other MSDOS compilers you may have
 * to define NO_MEMCPY in zutil.h.  If you don't need the mixed model,
 * just define FAR to be empty.
 */
#ifdef SYS16BIT
#  if defined(M_I86SM) || defined(M_I86MM)
     /* MSC small or medium model */
#    define SMALL_MEDIUM
#    ifdef _MSC_VER
#      define FAR _far
#    else
#      define FAR far
#    endif
#  endif
#  if (defined(__SMALL__) || defined(__MEDIUM__))
     /* Turbo C small or medium model */
#    define SMALL_MEDIUM
#    ifdef __BORLANDC__
#      define FAR _far
#    else
#      define FAR far
#    endif
#  endif
#endif

#if defined(WINDOWS) || defined(WIN32)
   /* If building or using zlib as a DLL, define ZLIB_DLL.
    * This is not mandatory, but it offers a little performance increase.
    */
#  ifdef ZLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
/*#      ifdef ZLIB_INTERNAL*/
#        define ZEXTERN extern __declspec(dllexport)
#      else
#        define ZEXTERN extern __declspec(dllimport)
/*#      endif*/
#    endif
#  endif  /* ZLIB_DLL */
   /* If building or using zlib with the WINAPI/WINAPIV calling convention,
    * define ZLIB_WINAPI.
    * Caution: the standard ZLIB1.DLL is NOT compiled using ZLIB_WINAPI.
    */
#  ifdef ZLIB_WINAPI
#    ifdef FAR
#      undef FAR
#    endif
#    include <windows.h>
     /* No need for _export, use ZLIB.DEF instead. */
     /* For complete Windows compatibility, use WINAPI, not __stdcall. */
#    define ZEXPORT WINAPI
#    ifdef WIN32
#      define ZEXPORTVA WINAPIV
#    else
#      define ZEXPORTVA FAR CDECL
#    endif
#  endif
#endif

#if defined (__BEOS__)
#  ifdef ZLIB_DLL
#    ifdef ZLIB_INTERNAL
#      define ZEXPORT   __declspec(dllexport)
#      define ZEXPORTVA __declspec(dllexport)
#    else
#      define ZEXPORT   __declspec(dllimport)
#      define ZEXPORTVA __declspec(dllimport)
#    endif
#  endif
#endif
 


/* Dassault Systemes adt */
#if defined (_LINUX_SOURCE) || defined(_DARWIN_SOURCE) || defined (_MACOSX_SOURCE) || defined (_ANDROID_SOURCE)
#define ZEXTERN __attribute__((visibility("default")))
#define ZEXPORT   
#define ZEXPORTVA 
#endif



#ifndef ZEXTERN
#  define ZEXTERN extern
#endif
#ifndef ZEXPORT
#  define ZEXPORT
#endif
#ifndef ZEXPORTVA
#  define ZEXPORTVA
#endif

#ifndef FAR
#  define FAR
#endif

#if !defined(__MACTYPES__)
typedef unsigned char  Byte;  /* 8 bits */
#endif
typedef unsigned int   uInt;  /* 16 bits or more */
/*+NUF Change uLong type to I4 for all plateforms.*/
/*  typedef unsigned long uLong;  32 bits or more */
#if !defined(PLATEFORME_DS64)
  typedef unsigned long uLong ;
#else
 typedef unsigned int uLong ;
#endif
/*-NUF*/

#ifdef SMALL_MEDIUM
   /* Borland C/C++ and some old MSC versions ignore FAR inside typedef */
#  define Bytef Byte FAR
#else
   typedef Byte  FAR Bytef;
#endif
typedef char  FAR charf;
typedef int   FAR intf;
typedef uInt  FAR uIntf;
typedef uLong FAR uLongf;

#ifdef STDC
   typedef void const *voidpc;
   typedef void FAR   *voidpf;
   typedef void       *voidp;
#else
   typedef Byte const *voidpc;
   typedef Byte FAR   *voidpf;
   typedef Byte       *voidp;
#endif

#ifdef HAVE_UNISTD_H    /* may be set to #if 1 by ./configure */
#  define Z_HAVE_UNISTD_H
#endif

#ifdef STDC
#  include <sys/types.h>    /* for off_t */
#endif

/* a little trick to accommodate both "#define _LARGEFILE64_SOURCE" and
 * "#define _LARGEFILE64_SOURCE 1" as requesting 64-bit operations, (even
 * though the former does not conform to the LFS document), but considering
 * both "#undef _LARGEFILE64_SOURCE" and "#define _LARGEFILE64_SOURCE 0" as
 * equivalently requesting no 64-bit operations
 */
#if -_LARGEFILE64_SOURCE - -1 == 1
#  undef _LARGEFILE64_SOURCE
#endif

#if defined(Z_HAVE_UNISTD_H) || defined(_LARGEFILE64_SOURCE)
#  include <unistd.h>       /* for SEEK_* and off_t */
#  ifdef VMS
#    include <unixio.h>     /* for off_t */
#  endif
#  ifndef z_off_t
#    define z_off_t off_t
#  endif
#endif

#ifndef SEEK_SET
#  define SEEK_SET        0       /* Seek from beginning of file.  */
#  define SEEK_CUR        1       /* Seek from current position.  */
#  define SEEK_END        2       /* Set file pointer to EOF plus "offset" */
#endif

#ifndef z_off_t
#  define z_off_t long
#endif

#if defined(_LARGEFILE64_SOURCE) && _LFS64_LARGEFILE-0
#  define z_off64_t off64_t
#else
#  define z_off64_t z_off_t
#endif

#if defined(__OS400__)
#  define NO_vsnprintf
#endif

#if defined(__MVS__)
#  define NO_vsnprintf
#endif

/* MVS linker does not support external names larger than 8 bytes */
#if defined(__MVS__)
  #pragma map(deflateInit_,"DEIN")
  #pragma map(deflateInit2_,"DEIN2")
  #pragma map(deflateEnd,"DEEND")
  #pragma map(deflateBound,"DEBND")
  #pragma map(inflateInit_,"ININ")
  #pragma map(inflateInit2_,"ININ2")
  #pragma map(inflateEnd,"INEND")
  #pragma map(inflateSync,"INSY")
  #pragma map(inflateSetDictionary,"INSEDI")
  #pragma map(compressBound,"CMBND")
  #pragma map(inflate_table,"INTABL")
  #pragma map(inflate_fast,"INFA")
  #pragma map(inflate_copyright,"INCOPY")
#endif

#endif /* ZCONF_H */
