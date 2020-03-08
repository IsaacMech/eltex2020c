#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

struct char_utf8 {
    char *symbol;
    int size;
};

struct line_utf8 {
    struct char_utf8 *text;
    int size;
};


struct char_utf8 fgetc_utf8(FILE *source);

struct line_utf8 * get_line_utf8(FILE *source) {
    struct line_utf8 *line1 = malloc(sizeof(struct line_utf8));
    printf("line1\n");
    struct char_utf8 buf = { NULL, 0 };
    printf("line2\n");
    buf = fgetc_utf8(source);
    printf("line3\n");
    if(buf.size == 0) return NULL;
    printf("line4\n");
    for(int i = 0; (*(buf.symbol) != '\n') || (*(buf.symbol) != '\0'); i++) {
        printf("line6\n");
        if(i == 0) {
            line1->text = malloc(sizeof(struct char_utf8));
        } else
            line1->text = realloc(line1->text, sizeof(struct char_utf8) + i * sizeof(struct char_utf8));
        printf("line7\n");
        *(line1->text + i) = buf;
        printf("line8\n");
        line1->size++;
        printf("line9\n");
        printf("size char = %d, size char + char * i = %d\n", sizeof(struct char_utf8), sizeof(struct char_utf8) + i * sizeof(struct char_utf8));
        printf("line10\n");
        buf = fgetc_utf8(source);
        if(buf.size == 0) break;
        printf("line11 buf size = %d\n", buf.size);
    }
    printf("before return\n");
    return line1;
}

struct char_utf8 fgetc_utf8(FILE *source) {
    char buf = 0;
    char size = 0;
    char *dest = NULL;
    struct char_utf8 result = { NULL, 0 };
    if(fread(&buf, 1, 1, source)) {
        if((buf & b11000000) == b11000000) { /*если есть два бита впереди */
            if((buf & b11100000) == b11100000) {
                if((buf & b11110000) == b11110000) {
                    size = 4;
                } else {
                    size = 3;
                }
            } else { /*но нет трёх бит*/
                size = 2; 
            }
        } else {
            size = 1;
        }
        dest = malloc(size);
        *(dest) = buf;
        for(int i = 1; i < size; i++ ){
            if(fread(&buf, 1, 1, source)) {
                *(dest + i) = buf;
            } else {
                return result;
            }
        }
        result.symbol = dest;
        result.size = size;
        return result;
    } else {
        return result;
    }
}

