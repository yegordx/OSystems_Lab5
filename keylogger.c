#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

const char *device = "/dev/input/by-id/usb-_HATOR_gaming_keyboard_WKB-F202BENTUB-event-kbd";

char *key_map[256] = { 0 };

void init_key_map() {
    key_map[16] = "q"; key_map[17] = "w"; key_map[18] = "e"; key_map[19] = "r";
    key_map[20] = "t"; key_map[21] = "y"; key_map[22] = "u"; key_map[23] = "i";
    key_map[24] = "o"; key_map[25] = "p";
    key_map[30] = "a"; key_map[31] = "s"; key_map[32] = "d"; key_map[33] = "f";
    key_map[34] = "g"; key_map[35] = "h"; key_map[36] = "j"; key_map[37] = "k";
    key_map[38] = "l";
    key_map[44] = "z"; key_map[45] = "x"; key_map[46] = "c"; key_map[47] = "v";
    key_map[48] = "b"; key_map[49] = "n"; key_map[50] = "m"; key_map[57] = " ";
}

int main() {
    struct input_event ev;
    int shift = 0;

    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        perror("Cannot open device");
        return 1;
    }

    init_key_map();

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == (ssize_t)sizeof(ev) && ev.type == EV_KEY) {
            if (ev.code == 42 || ev.code == 54) {  // Shift Left or Right
                shift = ev.value; // натиснули shift — запам’ятовуємо
                continue;
            }

            if (ev.value == 1) {  // натискання клавіші
                if (key_map[ev.code]) {
                    char letter = key_map[ev.code][0];
                    if (shift) {
                        letter -= 32; // зробити великою (ASCII A=65, a=97)
                    }
                    printf("%c", letter);
                } else {
                    printf("[code %d]", ev.code);
                }
                fflush(stdout);
            }
        }
    }

    close(fd);
    return 0;
}