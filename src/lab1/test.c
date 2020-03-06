#include "utf8.h"

int main() {
    FILE *input = fopen("codex.txt", "r");
    for(int j = 0; j < 8; j++) {
    struct char_utf8 buf = fgetc_utf8(input);
    for(int i = 0; i < buf.size; i++) {
        putc(*(buf.symbol + i), stdout);
    }
    }

    return 0;
}
