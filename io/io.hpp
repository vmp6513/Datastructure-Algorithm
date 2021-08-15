#include <errno.h>
#include <unistd.h>

ssize_t rio_read(int fd, void* buf, size_t n) {
    size_t leftn = n;
    ssize_t readn = 0;
    char* bufc = (char*)buf;

    while (leftn > 0) {
        readn = read(fd, bufc, leftn);
        if (readn < 0) {
            if (errno == EINTR) {  // SIGINT
                readn = 0;
            } else {  // other error
                return -1;
            }
        } else if (readn == 0) {
            break;  // EOF
        }
        leftn -= readn;
        bufc += readn;
    }

    return n - leftn;
}

ssize_t rio_write(int fd, void* buf, size_t n) {
    size_t leftn = n;
    ssize_t writen = 0;
    char* bufc = (char*)buf;

    while (leftn > 0) {
        writen = write(fd, bufc, leftn);
        if (writen < 0) {
            if (errno == EINTR) {
                writen = 0;
            } else {
                return -1;
            }
        }
        leftn -= writen;
        bufc += writen;
    }

    return n - leftn;
}
