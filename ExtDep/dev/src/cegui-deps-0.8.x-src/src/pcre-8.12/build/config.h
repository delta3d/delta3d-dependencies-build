/* config.h for CMake builds */

#define HAVE_DIRENT_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
/* #undef HAVE_WINDOWS_H */

/* #undef HAVE_TYPE_TRAITS_H */
/* #undef HAVE_BITS_TYPE_TRAITS_H */

#define HAVE_BCOPY 1
#define HAVE_MEMMOVE 1
#define HAVE_STRERROR 1
#define HAVE_STRTOLL 1
#define HAVE_STRTOQ 1
/* #undef HAVE__STRTOI64 */

#define PCRE_STATIC 1

/* #undef SUPPORT_UTF8 */
/* #undef SUPPORT_UCP */
/* #undef EBCDIC */
/* #undef BSR_ANYCRLF */
/* #undef NO_RECURSE */

#define HAVE_LONG_LONG 1
#define HAVE_UNSIGNED_LONG_LONG 1

#define SUPPORT_LIBBZ2 1
#define SUPPORT_LIBZ 1
#define SUPPORT_LIBREADLINE 1

#define NEWLINE			10
#define POSIX_MALLOC_THRESHOLD	10
#define LINK_SIZE		2
#define MATCH_LIMIT		10000000
#define MATCH_LIMIT_RECURSION	MATCH_LIMIT


#define MAX_NAME_SIZE	32
#define MAX_NAME_COUNT	10000

/* end config.h for CMake builds */
