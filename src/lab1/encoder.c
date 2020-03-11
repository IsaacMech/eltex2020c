#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utf8.h"

struct coder {
    struct line_utf8 *in;
    struct line_utf8 *out;
    int size;
};

#define SINGLELINE 1
#define TWOLINES 2
int get_coder(FILE *source, unsigned char input_type, struct coder *destination);

void encode(char *target, struct coder dict);

void print_result(char *source);

unsigned char wait_message(void);

int main(int argc, char *argv[]) {
    if(argc == 3) {
        FILE *coder1, *coder2;
       
        if((coder1 = fopen(argv[1], "r")) == NULL) {
            print_err(fileio_error.unable_to_read, argv[1]);
            return -1;
        } else if((coder2 = fopen(argv[2], "r")) == NULL) {
            print_err(fileio_error.unable_to_read, argv[2]);
            return -1;
        }

        struct coder alphabet, punct;

        if(get_coder(coder1, TWOLINES, &alphabet)) {
           print_err(coder_error.incorrect_format, argv[1]);
           return -1;
        } else if(get_coder(coder2, SINGLELINE, &punct)) {
           print_err(coder_error.incorrect_format, argv[2]);
           return -1;
        }
        printf("Alphabet: \n");
        print_line_utf8(alphabet.in, stdout);
        printf("\n");
        print_line_utf8(alphabet.out, stdout);
        printf("\n Punct: \n");
        print_line_utf8(punct.in, stdout);
        printf("\n");
        print_line_utf8(punct.out, stdout);
        //printf("%s %s\n", alphabet.in, alphabet.out);
/*
        char *text;
        do {
            if(get_text(text)) {
            print_err(exec_error.undefined);
            return -1;
            }

            encode(text, alphabet);
            encode(text, punct);
            print_result(text);
            free(text);
        } while(wait_message());
       */ 
    } else if(argc > 3) {
        print_err(exec_error.too_many_args);
        return -1;
    } else {
        print_err(exec_error.not_enough_args);
        return -1;
    }
    
        return 0;
}

int get_coder(FILE *source, unsigned char input_type, struct coder *destination) {
    if(input_type == SINGLELINE) {
        struct line_utf8 *line1 = get_line_utf8(source);
        if(line1->size < 2) {
            return -1;
        }
        destination->in = line1;

        destination->out->size = line1->size;
        destination->out->text = malloc(line1->size * sizeof(struct char_utf8));
        for(int i = 0; i < line1->size; i++) {
            if(i + 1 == line1->size) {
                *(destination->out->text + i) = *(line1->text);
            } else
                *(destination->out->text + i) = *(line1->text + i + 1);
        }
        return 0;
    } else if(input_type == TWOLINES) { 
        struct line_utf8 *line1 = get_line_utf8(source);
        struct line_utf8 *line2 = get_line_utf8(source);
        if(line1->size == 1 || line2->size == 1 || line1->size != line2->size) {
            return -1;
        }
        destination->in = line1;
        destination->out = line2;
        destination->size = line1->size;
        return 0; /*работа в процессе */
    }
}
