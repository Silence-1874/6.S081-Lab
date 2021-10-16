#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int pipe_left[]){
    close(pipe_left[1]);

    int p = 0;
    int r = read(pipe_left[0], &p, sizeof(p));
    if (r > 0) {
        printf("prime %d\n", p);

        int pipe_right[2];
        pipe(pipe_right);

        if (fork() == 0) {
            close(pipe_left[0]);
            child(pipe_right);
        } else {
            close(pipe_right[0]);
            int n = p + 1;
            while (read(pipe_left[0], &n, sizeof(n))) {
                if (n % p != 0) {
                    write(pipe_right[1], &n, sizeof(n));
                }
            }
            close(pipe_left[0]);
            close(pipe_right[1]);
            wait(0);
        }
    }
    close(pipe_left[0]);
    exit(0);
}

int main(int argc, char*argv[])
{
    int pip[2];
    pipe(pip);

    if (fork() == 0) {
        child(pip);
    } else {
        close(pip[0]);
        for (int i = 2; i <= 35; i++) {
            write(pip[1], &i, sizeof(i));
        }
        close(pip[1]);
        wait(0);
    }
    exit(0);
}

