#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char no_exit = 1;
void exiting(void) { no_exit = 0; }

struct codex {
    char *in;
    char *out;
};

struct codex get_codex(char *name);

int main(int argc, char *argv[]) {
    struct codex code;
    if(argc) {
        code = get_codex(argv[1]);
    } else {
        printf("Не указан файл с шифром!\n");
        exiting();
    }
    if(no_exit) {
         printf("CODEX:\n%s\n%s\n", code.in, code.out);
         return 0;
    } 
    return -1;
}
/*Функция возвращает указатель на пары символов*/
struct codex get_codex(char *name) {
    FILE *codex_file;
    struct codex code = { NULL, NULL };
    char buf = '\0';
    if((codex_file = fopen(name, "r")) == NULL) {
        printf("Файл %s не найден!", name);
        exiting();
    }
    if(no_exit) {
        code.in = malloc(sizeof(char));
        for(int i = 0; no_exit; i++) {
            if(fscanf(codex_file, "%c", buf) != NULL) {
                if(buf == '\n') {  /* первая строка считана */
                    buf = '\0';
                    *(code.in + i) = '\0';
                    break;
                }
                code.in = realloc(code.in, sizeof(char) + i * sizeof(char));
                *(code.in + i) = buf;
            } else if(buf != '\0') {
                printf("Ошибка! Неправильный формат файла %s!", name);
                exiting();
                break;
            } else if(buf == '\0') {
                printf("Файл %s пуст!", name);
                exiting();
                break;
            }
        }

        code.out = malloc(sizeof(char));
        for(int i = 0; no_exit; i++) {
            if(fscanf(codex_file, "%c", buf) != NULL) {
                if(buf == '\n') {  /* первая строка считана */
                    printf("Ошибка! Неправильный формат файла %s!", name);
                    exiting();
                    break;
                }
                code.out = realloc(code.out, sizeof(char) + i * sizeof(char));
                *(code.out + i) = buf;
            } else if(buf != '\0') {
                *(code.out + i) = '\0';
                break;
            }
        }
        if(strlen(code.in) != strlen(code.out)) {
            printf("Ошибка! Неправильный формат файла %s!", name);
            exiting();
        }
    }
    return code;
}
