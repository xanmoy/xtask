
/*----------------------------------------------------------------------*
 *                              XTask                              *
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ncurses.h>

#define PROC_DIR "/proc"
#define STAT_FILE "stat"

typedef struct
{
    int pid;
    char comm[256];
    char state;
    long unsigned int utime;
    long unsigned int stime;
    long unsigned int vsize;
    long unsigned int rss;
} Process;

void list_processes()
{
    DIR *proc_dir;
    struct dirent *entry;

    proc_dir = opendir(PROC_DIR);
    if (proc_dir == NULL)
    {
        perror("opendir");
        return;
    }

    // Print headers
    printw("%-10s %-20s %-6s %-14s %-10s\n", "PID", "Command", "State", "Memory (KB)", "CPU (s)");

    while ((entry = readdir(proc_dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            char *endptr;
            int pid = strtol(entry->d_name, &endptr, 10);
            if (*endptr == '\0')
            {
                // It's a PID directory
                char stat_path[267];
                snprintf(stat_path, sizeof(stat_path), "%s/%s/%s", PROC_DIR, entry->d_name, STAT_FILE);
                FILE *stat_file = fopen(stat_path, "r");
                if (stat_file)
                {
                    Process process;
                    fscanf(stat_file, "%d %255s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*u %*u %lu %ld",
                           &process.pid, process.comm, &process.state, &process.utime, &process.stime, &process.vsize, &process.rss);
                    fclose(stat_file);

                    // Calculate CPU usage (simplified)
                    double cpu_usage = (double)(process.utime + process.stime) / sysconf(_SC_CLK_TCK);

                    // Print process information
                    printw("%-10d %-20s %-6c %-14lu %-10.2f\n", process.pid, process.comm, process.state, process.vsize / 1024, cpu_usage);

                    // Add a bit of space between entries
                    printw("\n");
                }
            }
        }
    }

    closedir(proc_dir);
}

int main()
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // Non-blocking input
    curs_set(FALSE);       // Hide the cursor

    while (1)
    {
        // Clear the screen
        clear();

        // Print the process list
        list_processes();

        // Refresh the screen
        refresh();

        // Sleep for 2 seconds
        sleep(2);
    }

    // End ncurses mode
    endwin();

    return 0;
}
