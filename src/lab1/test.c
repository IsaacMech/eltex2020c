#include "utf8.h"

int main() {
    FILE *input = fopen("codex.txt", "r");
    char *buf; int size;
    while((size = fgetc_utf8(input, buf)) != -1) {
        *(buf + size) = '\0';
        printf("%s\n", buf);
    }

    return 0;
}
