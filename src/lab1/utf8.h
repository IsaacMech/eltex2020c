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

int cmpc_utf8(struct char_utf8 *char1, struct char_utf8 *char2);
int cmpl_utf8(struct line_utf8 *line1, struct line_utf8 *line2);

struct char_utf8 fgetc_utf8(FILE *source);
struct line_utf8 * get_line_utf8(FILE *source);

int print_line_utf8(struct line_utf8 *line, FILE *dest);

int free_char_utf8(struct char_utf8 *target);
int free_line_utf8(struct line_utf8 *target);

int free_char_utf8(struct char_utf8 *target) {
    if(target != NULL) {
        free(target);
        return 0;
    } else {
        return -1;
    }
}

int free_line_utf8(struct line_utf8 *target) {
    if(target != NULL) {
        for(int i = 0; i < target->size; i++) {
            if(free_char_utf8(target->text + i))
                return -1;
        }
        free(target);
        return 0;
    } else {
        return -1;
    }
}

int cmpc_utf8(struct char_utf8 *char1, struct char_utf8 *char2) {
    if(char1->size != char2->size) return 0;
    for(int i = 0; i < char1->size; i++) {
        if(*(char1->symbol + i) != *(char2->symbol + i)) 
            return 0;
    }
    return 1;
}

int cmpl_utf8(struct line_utf8 *line1, struct line_utf8 *line2) {
    if(line1->size != line2->size) return 0;
    for(int i = 0; i < line1->size; i++) {
        if(cmpc_utf8(line1->text + i, line2->text + i) != 1) 
            return 0;
    }
    return 1;
}

/*возвращает количество выведенных символов, печатает в dest
строку utf8*/
int print_line_utf8 (struct line_utf8 *line, FILE *dest) {
    int i = 0;
    while(i < line->size) {
        for(int j = 0; j < (line->text + i)->size; j++) {
            putc(*((line->text + i)->symbol + j), dest);
        }
        i++;
    }
    return i + 1;
}

struct line_utf8 * get_line_utf8(FILE *source) {
    struct line_utf8 *line1 = malloc(sizeof(struct line_utf8));
    struct char_utf8 buf = { NULL, 0 };
    buf = fgetc_utf8(source);
    if(buf.size == 0) return NULL;
    for(int i = 0; (*(buf.symbol) != 0x0A) && (*(buf.symbol) != 0x00); i++) {
        if(i == 0) {
            line1->text = malloc(sizeof(struct char_utf8));
        } else
            line1->text = realloc(line1->text, sizeof(struct char_utf8) + i * sizeof(struct char_utf8));
        *(line1->text + i) = buf;
        line1->size++;
        buf = fgetc_utf8(source);
        if(buf.size == 0) break;
    }
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

