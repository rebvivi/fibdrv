#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
struct U64 {
    unsigned long long msl;
    unsigned long long lsl;
};
static int diff_in_ns(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec - t1.tv_nsec < 0) {
        diff.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }

    return (diff.tv_sec * 1000000000 + diff.tv_nsec);
}

int main()
{
    int fd;


    struct U64 buf;
    char write_buf[] = "testing writing";
    int offset = 184;  // TODO: test something bigger than the limit
    int i = 0;

    // FILE *fp = fopen("time.txt", "wb+");
    fd = open(FIB_DEV, O_RDWR);

    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (i = 0; i <= offset; i++) {
        struct timespec start, end;
        lseek(fd, i, SEEK_SET);
        clock_gettime(CLOCK_REALTIME, &start);
        read(fd, &buf, sizeof(struct U64));
        clock_gettime(CLOCK_REALTIME, &end);
        // fprintf(fp, "%d %d %lld %lld\n",i, diff_in_ns(start, end),
        // atoll(buf),diff_in_ns(start, end) - atoll(buf));
        if (buf.lsl < 1000000000000000000 && buf.lsl > 100000000000000000) {
            printf("Reading from " FIB_DEV
                   " at offset %d, returned the sequence "
                   "%llu0%llu\n",
                   i, buf.msl, buf.lsl);
        } else if (buf.lsl < 100000000000000000 &&
                   buf.lsl > 10000000000000000) {
            printf("Reading from " FIB_DEV
                   " at offset %d, returned the sequence "
                   "%llu00%llu\n",
                   i, buf.msl, buf.lsl);
        } else {
            printf("Reading from " FIB_DEV
                   " at offset %d, returned the sequence "
                   "%llu%llu\n",
                   i, buf.msl, buf.lsl);
        }
    }

    // fclose(fp);
    close(fd);
    return 0;
}