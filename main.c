#include <stdlib.h>
#include <string.h>
#include "kernel/calls.h"
#include "kernel/task.h"
#include "xX_main_Xx.h"

int main(int argc, char *const argv[]) {
    char envp[100] = {0};
    if (getenv("TERM"))
        strcpy(envp, getenv("TERM") - strlen("TERM") - 1);
    int err = xX_main_Xx(argc, argv, envp);
    if (err < 0) {
        fprintf(stderr, "%s\n", strerror(-err));
        return err;
    }
    do_mount(&procfs, "proc", "/proc");
    do_mount(&devptsfs, "devpts", "/dev/pts");
    cpu_run(&current->cpu);
}
