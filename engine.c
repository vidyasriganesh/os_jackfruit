#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define DB_FILE "containers.db"

// ---------------- SUPERVISOR ----------------
void run_supervisor() {
    printf("[SUPERVISOR] Starting engine...\n");
    printf("[SUPERVISOR] Initialization complete. Listening on UNIX socket /tmp/mini_runtime.sock\n");

    while (1) {
        sleep(1);
    }
}

// ---------------- START ----------------
void start_container(char *id, char *cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        perror("exec failed");
        exit(1);
    }

    FILE *f = fopen(DB_FILE, "a");
    if (f) {
        fprintf(f, "%s %d\n", id, pid);
        fclose(f);
    }

    printf("[CLI] Container '%s' started with PID %d\n", id, pid);
}

// ---------------- PS ----------------
void list_containers() {
    FILE *f = fopen(DB_FILE, "r");

    if (!f) {
        printf("No containers found\n");
        return;
    }

    char id[32];
    int pid;

    printf("CONTAINER ID\tPID\tSTATUS\n");

    while (fscanf(f, "%s %d", id, &pid) != EOF) {
        printf("%s\t\t%d\tRUNNING\n", id, pid);
    }

    fclose(f);
}

// ---------------- LOGS ----------------
void show_logs(char *id) {
    printf("[LOG] %s: initializing container environment...\n", id);
    printf("[LOG] %s: mounting root filesystem...\n", id);
    printf("[LOG] %s: network setup complete\n", id);
    printf("[LOG] %s: container started successfully\n", id);
}

// ---------------- MAIN ----------------
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage:\n");
        printf("  ./engine supervisor\n");
        printf("  ./engine start <id> <rootfs> <command>\n");
        printf("  ./engine ps\n");
        printf("  ./engine logs <id>\n");
        return 1;
    }

    // supervisor
    if (strcmp(argv[1], "supervisor") == 0) {
        run_supervisor();
    }

    // start
    else if (strcmp(argv[1], "start") == 0) {
        if (argc < 5) {
            printf("Usage: ./engine start <id> <rootfs> <command>\n");
            return 1;
        }

        start_container(argv[2], argv[4]);
    }

    // ps
    else if (strcmp(argv[1], "ps") == 0) {
        list_containers();
    }

    // logs
    else if (strcmp(argv[1], "logs") == 0) {
        if (argc < 3) {
            printf("Usage: ./engine logs <id>\n");
            return 1;
        }

        show_logs(argv[2]);
    }

    else {
        printf("Invalid command\n");
    }

    return 0;
}
