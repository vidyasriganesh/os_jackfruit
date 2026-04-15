#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "monitor_ioctl.h"

int main() {
    int fd;
    struct monitor_request req;

    fd = open("/dev/container_monitor", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    req.pid = 33033;  // 🔥 CHANGE THIS EVERY TIME
    strcpy(req.container_id, "test_container");
    req.soft_limit_bytes = 50 * 1024 * 1024;   // 50MB
    req.hard_limit_bytes = 100 * 1024 * 1024;  // 100MB

    if (ioctl(fd, MONITOR_REGISTER, &req) < 0) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    printf("Registered successfully\n");

    close(fd);
    return 0;
}
