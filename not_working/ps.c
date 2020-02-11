//#include <sys/procfs.h>

// Might need these for mac
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/kinfo_proc.h>
//#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

// We will implement this for mac

int main()
{
    int i, mib[4];
    size_t len;
    struct kinfo_proc kp;

    len = 4;
    sysctlnametomib("kern.proc.pid", mib, &len);

    for (i = 0; i < 100; i++) {
        mib[3] = i;
        len = sizeof(kp);
        if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1) {
            perror("sysctl");
        } else if (len > 0) {
            printkproc(&kp);
        }
    }
}


