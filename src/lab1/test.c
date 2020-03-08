#include "utf8.h"

int main() {
    FILE *input = fopen("codex.txt", "r");
    struct line_utf8 *line1 = get_line_utf8(input);
    print_line_utf8(line1, stdout);

    return 0;
}
