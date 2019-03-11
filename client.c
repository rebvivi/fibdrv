#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
int main()
{
    int fd;
    long kernel_time;

    int buf;
    char write_buf[] = "testing writing";
    int i = 0;

    fd = open(FIB_DEV, O_RDWR);

    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    struct timespec start, end;

    for (i = 0; i <= 200; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        kernel_time = read(fd, &buf, sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &end);

        printf("%3d\t\t%ld\t\t\t%ld\t\t\t\t%ld ", i,
               end.tv_nsec - start.tv_nsec, kernel_time,
               end.tv_nsec - start.tv_nsec - kernel_time);
        printf("\n");
    }

    close(fd);
    return 0;
}