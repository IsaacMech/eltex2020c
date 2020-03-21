#include <stdio.h>
#include <stdlib.h>

struct coder {
    struct line_utf8 *in;
    struct line_utf8 *out;
    int size;
};
#define SINGLELINE 1
#define TWOLINES 2
int get_coder(FILE *source, unsigned char input_type, struct coder *destination);

int get_coder(FILE *source, unsigned char input_type, struct coder *destination) {
    if(input_type == SINGLELINE) {
        struct line_utf8 *line1 = get_line_utf8(source);
        if(line1->size < 2) return -1;
        destination->in = line1;
        destination->size = line1->size;
        destination->out->size = line1->size;
        destination->out->text = malloc(destination->out->size * sizeof(struct char_utf8));
        *(destination->out->text + destination->size - 1) = *(destination->in->text);
        for(int i = 0; i < destination->size - 1; i++) {
            *(destination->out->text + i) = *(destination->in->text + i + 1);
        }
        return 0;
    } else if(input_type == TWOLINES) {
        struct line_utf8 *line1 = get_line_utf8(source);
        struct line_utf8 *line2 = get_line_utf8(source);
        if((line1->size != line2->size) || (line1->size == 0)) return -1;
        destination->in = line1;
        destination->out = line2;
        destination->size = line1->size;
        return 0;
    } else {
        return -1;
    }
}
