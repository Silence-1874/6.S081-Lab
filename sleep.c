#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(2, "Usage: sleep TIME(tenth of a sencond)\n");
        exit(1);
    }

    int time = atoi(argv[1]);
    // in fact, this if statement won't work, for the given function atoi() didn't achieve nagative trasformation :(
    if (time < 0) {
        fprintf(2, "TIME must be positive!\n");
        exit(1);
    }
    sleep(time);

    exit(0);
}
