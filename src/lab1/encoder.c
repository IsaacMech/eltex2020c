#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"


struct coder {
    char *in;
    char *out;
    int length;
};
#define SINGLELINE 1
#define TWOLINES 2
unsigned char get_coder(FILE *source, unsigned char input_type, struct coder *destination);
void encode(char *target, struct coder dict);

unsigned char get_text(char *destination);
void print_result(char *source);

unsigned char wait_message(void);

unsigned char file_open(char *name, char *mode, FILE *destination);
/*
    Сделать соответствующие ошибки в errors.h!!!!
*/
int main(int argc, char *argv[]) {
    if(argc == 3) {
        FILE *coder1, *coder2;
       
        if(file_open(argv[1], "r", coder1)) {
            print_err(fileio_error.unable_to_read, argv[1]);
            return -1;
        } else if(file_open(argv[2]), "r", coder2) {
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
        
    } else if(argc > 3) {
        print_err(exec_error.too_many_args);
        return -1;
    } else {
        print_err(exec_error.not_enough_args);
        return -1;
    }
    
        return 0;
}
