#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int shared_value = 0;

int main() {
    printf("Writer PID: %d\n", getpid());
    while (1) {
        printf("Enter new value: ");
        scanf("%d", &shared_value);
        sleep(1);
    }
}
