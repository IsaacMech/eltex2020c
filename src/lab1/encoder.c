#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"


struct line {
    char *text;
    int length;
};

struct coder {
    char *in;
    char *out;
    int length;
};
#define SINGLELINE 1
#define TWOLINES 2
unsigned char get_coder(FILE *source, unsigned char input_type, struct coder *destination);
struct line get_line(FILE *source);
void encode(char *target, struct coder dict);

unsigned char get_text(char *destination);
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

        if(get_coder(coder1, SINGLELINE, &alphabet)) {
           print_err(coder_error.incorrect_format, argv[1]);
           return -1;
        } else if(get_coder(coder2, SINGLELINE, &punct)) {
           print_err(coder_error.incorrect_format, argv[2]);
           return -1;
        }
        printf("%.10s %.10s\n", alphabet.in, alphabet.out;
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

struct line get_line(FILE *source) {
    struct line input;
    input.text = malloc(sizeof(char));
    input.length = sizeof(char);
    char buf = '\0';
    for(; fscanf(source, "%c", &buf); input.length++) {
        if(buf == '\n') {
            *(input.text + input.length - 1) = '\0';
            return input;
        }
        input.text = realloc(input.text, sizeof(char) + (input.length - 1) * sizeof(char));
        *(input.text + (input.length - 1)) = buf;
    }
    if(input.length - 1 != 0) {
        *(input.text + input.length - 1) = '\0';
    } else {
        free(input.text);
    }
    return input;
}

unsigned char get_coder(FILE *source, unsigned char input_type, struct coder *destination) {
    if(input_type == SINGLELINE) {
        struct line line1 = get_line(source);
        if(line1.length < 3) {
            return -1;
        }
        destination->in = malloc(line1.length * sizeof(char));
        destination->out = malloc(line1.length * sizeof(char));
        for(int i = 0; i < line1.length - 1; i++) {
            *(destination->in + i) = *(line1.text + i);
            if(i + 1 == line1.length - 1) {
                *(destination->out + i) = *(line1.text);
                destination->length = ++i;
            } else
                *(destination->out + i) = *(line1.text + i + 1);
        }
        return 0;
    } else if(input_type == TWOLINES) { 
        struct line line1 = get_line(source);
        struct line line2 = get_line(source);
        if(line1.length == 1 || line2.length == 2 || line1.length != line2.length) {
            return -1;
        } 
        return -1; /*работа в процессе */
    }
}
