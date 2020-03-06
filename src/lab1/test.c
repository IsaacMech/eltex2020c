#include "utf8.h"

int main() {
    FILE *input = fopen("codex.txt", "r");
    
    struct line_utf8 line1 = get_line_utf8(input);
    for(int j = 0; j < line1.size; j++) {
    
    for(int i = 0; i < *(line1.text + j).size; i++) {
        putc(*(*(line1.text + j).symbol + i), stdout);
    }
    }

    return 0;
}
