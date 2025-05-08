#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pid> <hex_address>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    unsigned long addr = strtoul(argv[2], NULL, 16);

    char mem_path[256];
    sprintf(mem_path, "/proc/%d/mem", pid);
    int fd = open(mem_path, O_RDONLY);
    if (fd < 0) {
        perror("open mem");
        return 1;
    }

    int value, last_value = -1;  // останнє відоме значення

    while (1) {
        lseek(fd, addr, SEEK_SET);
        read(fd, &value, sizeof(int));

        if (value != last_value) {
            printf("Value changed: %d\n", value);
            last_value = value;
        }

        sleep(1);  // або навіть 0.5 чи 0.1 для чутливості
    }

    close(fd);
    return 0;
}
