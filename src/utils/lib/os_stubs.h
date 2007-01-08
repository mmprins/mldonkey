
#include "../../../config/config.h"

/*******************************************************************


                         MINGW specific


*******************************************************************/

#ifdef __MINGW32__

#ifndef PTW32_STATIC_LIB
#define PTW32_STATIC_LIB
#endif

#define FD_SETSIZE 1024

#include <winsock.h>

struct filedescr {
  union {
    HANDLE handle;
    SOCKET socket;
  } fd;
  enum { KIND_HANDLE, KIND_SOCKET } kind;
};

#define Fd_val(v) (((struct filedescr *) Data_custom_val(v))->fd.handle)
#define Socket_val(v) (((struct filedescr *) Data_custom_val(v))->fd.socket)

typedef HANDLE OS_FD;
typedef SOCKET OS_SOCKET;
typedef unsigned int uint;
extern void win32_maperr(unsigned long errcode);
unsigned char * utf8_to_utf16(const char * str);

/*******************************************************************


                         UNIX specific


*******************************************************************/

#else  /* __MINGW32__ */

#define Fd_val(v) Int_val(v)
#define Socket_val(v) Int_val(v)

typedef int OS_FD;
typedef int OS_SOCKET;

#if defined(__OpenBSD__) || defined(__FreeBSD__)
#include <string.h>
#endif


#endif  /* __MINGW32__ */

/*******************************************************************


                         COMMON used 


*******************************************************************/

#include <caml/config.h>
#include <caml/signals.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/custom.h>
#include <caml/callback.h>

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef HAS_SIGNALS_H
#include <signals.h>
#endif

#ifdef HAS_SYS_SELECT_H
#include <sys/select.h>
#endif


/* off_t is long on mingw, long long everywhere else */
#ifdef _OFF64_T_
typedef off64_t OFF_T;
#else
typedef off_t OFF_T;
#endif

#if !defined(__MINGW32__) && !defined(__BEOS__)
#include <sys/mman.h>
#endif

#ifdef HAS_UNISTD
#include <unistd.h>
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif



#define Nothing ((value) 0)

extern void unix_error (int errcode, char * cmdname, value arg) Noreturn;
extern void uerror (char * cmdname, value arg) Noreturn;

extern OFF_T os_lseek(OS_FD fd, OFF_T pos, int dir);
extern void os_ftruncate(OS_FD fd, OFF_T len, int sparse);
extern ssize_t os_read(OS_FD fd, char *buf, size_t len);
extern int os_getdtablesize();
extern int64 os_getfdsize(OS_FD fd);
extern int64 os_getfilesize(char *path);
extern void os_set_nonblock(OS_SOCKET fd);
extern void os_uname(char buf[]);
extern int os_os_supported();


#define HASH_BUFFER_LEN 131072
extern unsigned char hash_buffer[HASH_BUFFER_LEN];


