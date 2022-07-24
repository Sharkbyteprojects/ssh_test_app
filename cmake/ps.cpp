#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <ctype.h>
#include "sar.hpp"

// Helper function to check if a struct dirent from /proc is a PID directory.
int is_pid_dir(const struct dirent *entry) {
    const char *p;

    for (p = entry->d_name; *p; p++) {
        if (!isdigit(*p))
            return 0;
    }

    return 1;
}

void _ps(){
    DIR *procdir;
    FILE *fp;
    struct dirent *entry;
    char path[256 + 5 + 5]; // d_name + /proc + /stat
    int pid;
    unsigned long maj_faults;

    // Open /proc directory.
    procdir = opendir("/proc");
    if (!procdir) {
        err("opendir failed");
        return;
    }

    printf("  PID: process              Faults\n"
        "------------------------------------\n");
    // Iterate through all files and directories of /proc.
    while ((entry = readdir(procdir))) {
        // Skip anything that is not a PID directory.
        if (!is_pid_dir(entry))
            continue;

        // Try to open /proc/<PID>/stat.
        snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
        fp = fopen(path, "r");

        if (!fp) {
            perror(path);
            continue;
        }

        // Get PID, process name and number of faults.
        fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %lu",
            &pid, &path, &maj_faults
        );

        // Pretty print.
        printf("%5d %-20s: %lu\n", pid, path, maj_faults);
        fclose(fp);
    }

    closedir(procdir);
}