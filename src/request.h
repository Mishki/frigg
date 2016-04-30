#ifndef FRIGG_REQUESTS_H
#define FRIGG_REQUESTS_H

#include <cstdarg>
#include <string>
#include <cstring>
#include <vector>


#define MSG_SIZE 8192
#define INT_SZ 4

#define QUIT        1
#define SESSION     2
#define HTML        3
#define JS          4

typedef struct request {
    char uid[37];
    int method;
    long shmem;
    char args[0];
} request;

int parse(char *buf, const int size, ...);
std::vector<std::string> unparse(char *args);

#endif //FRIGG_REQUESTS_H
