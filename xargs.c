#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: build and execute command lines from standard input\n");
        exit(1);
    }
    
    if (argc + 1 > MAXARG) {
        fprintf(2, "too many args\n");
        exit(1);
    }
    
    char* params[MAXARG];
    char buf[512];
    for (int i = 0; i < argc; i++) {
        params[i] = argv[i + 1];
    }

    while (1) {
        int i;
        for (i = 0; ; i++) {
            int n = read(0, buf + i, 1);
            if (n == 0 || buf[i] == '\n') {
                break;
            }
        }

        if(i == 0) {
            break;
        }

        buf[i] = '\0';
        params[argc - 1] = buf;

        if (fork() == 0) {
            exec(params[0], params);
            exit(0);
        } else {
            wait(0);
        }
    }

    exit(0);
}
