#include <stdio.h>

int main() {
    long i;
    for (i = 0; i < 2000000000; i++);
    printf("Task completed\n");
    return 0;
}
