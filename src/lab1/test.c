#include "utf8.h"

int main() {
    FILE *input = fopen("codex.txt", "r");
    struct line_utf8 *a = get_line_utf8(stdin), *b = get_line_utf8(stdin);
    printf("CMP = %d", cmpl_utf8(a, b));
    return 0;
}
