
#ifndef LOGGING_HPP
#define LOGGING_HPP
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <unistd.h>
#include <fcntl.h>

FILE *logfd = NULL;

void mds_fuse_log_enable()
{
    if (logfd == NULL) {
        logfd = fopen("fuse.log", "wb+");
        if (logfd == NULL) {
            perror("fopen");
            exit(1);
        }
    }
}

void mds_fuse_log(const char *what, ...)
    __attribute__((format(printf, 1, 2)))
{
    va_list vl;
    va_start(vl, what);

    if (logfd == NULL) {
        return;
    }

    vfprintf(logfd, what, vl);

#ifdef DEBUG
    fflush(logfd);
#endif
}

#if defined(DEBUG)
#define FUSE_LOG(fmt, ...) mds_fuse_log(fmt "\n", ##__VA_ARGS__)
#define FUSE_PLOG(fmt, ...) mds_fuse_log(fmt "\n", ##__VA_ARGS__)
#elif defined(ORI_PERF)
#define FUSE_LOG(fmt, ...)
#define FUSE_PLOG(fmt, ...) mds_fuse_log(fmt "\n", ##__VA_ARGS__)
#else
#define FUSE_LOG(fmt, ...)
#define FUSE_PLOG(fmt, ...)
#endif

#endif

