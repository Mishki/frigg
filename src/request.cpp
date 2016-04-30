#include "request.h"

int parse(char *buf, const int size, ...) {
    int seek = 0;
    va_list args;
    va_start(args, size);

    *((int *) (buf + seek)) = size;
    seek += INT_SZ;

    for (int i = 0; i < size; i++) {
        char *str = va_arg(args, char *);
        size_t len = (int) std::string(str).length();
        *((int *) (buf + seek)) = (int) len;
        seek += INT_SZ;
        strncpy(buf + seek, str, len + 1);
        seek += len + 1;
    }
    va_end(args);

    return std::min(seek, MSG_SIZE);
};

std::vector<std::string> unparse(char *args) {
    std::vector<std::string> vec;

    int seek = 0;
    int size = *((int *) (args + seek));
    seek += INT_SZ;

    for (int i = 0; i < size; i++) {
        int len = *((int *) (args + seek));
        seek += INT_SZ;
        vec.push_back(std::string(args + seek));
        seek += len + 1;
    }

    return vec;
};