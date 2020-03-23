#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utf8.h"
#include "coding.h"

void decode(struct line_utf8 *target, struct coder dict);

void print_result(char *source);

unsigned char wait_message(void);

int main(int argc, char *argv[]) {
    if(argc == 2) {
        FILE *coder1;
       
        if((coder1 = fopen(argv[1], "r")) == NULL) {
            print_err(fileio_error.unable_to_read, argv[1]);
            return -1;
        }

        struct coder alphabet;

        if(get_coder(coder1, TWOLINES, &alphabet)) {
           print_err(coder_error.incorrect_format, argv[1]);
           return -1;
        }

        printf("Здравствуйте! Введите свой текст для декодирования:\n[нажмите Ctrl+D, чтобы завершить ввод]\n");
        struct line_utf8 *text = get_text_utf8(stdin);
        printf("Текст для декодирования:\n");
        print_line_utf8(text, stdout);
        printf("\nСловарь:\n");
        print_line_utf8(alphabet.in, stdout);
        printf("\n");
        print_line_utf8(alphabet.out, stdout);
        printf("\n");
        decode(text, alphabet);
        printf("Результат:\n");
        print_line_utf8(text, stdout);
        printf("\n");
    } else if(argc > 2) {
        print_err(exec_error.too_many_args);
        return -1;
    } else {
        print_err(exec_error.not_enough_args);
        return -1;
    }
    
        return 0;
}

void decode(struct line_utf8 *target, struct coder dict) {
    for(int i = 0; i < target->size; i++) {
        for(int j = 0; j < dict.size; j++) {
            if(cmpc_utf8(target->text + i, dict.out->text + j)) {
                *(target->text + i) = *(dict.in->text + j);
                break;
            }
        }
    }
}
