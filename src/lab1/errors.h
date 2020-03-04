#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define WITH_ARG 1
#define WITHOUT_ARG 0
/*В этом заголовочном файле определена структурная переменная error,
которая содержит в себе указатели на строки, содержащие текст ошибок
в работе программы ввода/вывода.*/
/*simple_error - простая ошибка, у которой есть текст и флаг аргумента*/
struct simple_error {
    char *text;
    unsigned char arg_flag;
};
/*структурная переменная exec_error, в которой содержатся все возможные
ошибки, связанные с запуском программы*/
const struct {
    struct simple_error not_enough_args;
    struct simple_error too_many_args;
} exec_error  = {
    "Программа запущена с недостаточным количеством аргументов!", WITHOUT_ARG,
    "Программа запущена со слишком большим количеством аргументов!", WITHOUT_ARG,
};
/*структурная переменная fileio_error, в котором содержатся все 
возможные ошибки связанные с использование функции fopen()*/
const struct {
    struct simple_error unable_to_read;
    struct simple_error unable_to_write;
} fileio_error = {
    "Невозможно прочитать файл %s!", WITH_ARG,
    "Невозможно записать в файл %s!", WITH_ARG
};

const struct {
    struct simple_error unable_to_alloc;
} mem_error = {
    "Невозможно выделить память для %s!", WITH_ARG
};
/*
int static debug_print_text(char *text, FILE *target) {
    for(int i = 0; *(text + i) != '\0'; i++) { 
        fputc(*(text + i), target);
        printf("\n");
    }
    return 0;
}
*/
int static print_text(char *text, FILE *target) {
    if(fprintf(target, "%s\n", text)) {
        return 0;
    } else
        return -1;
}

char* combine_str(char *fstr, char *astr) {
    char *text = malloc(strlen(fstr) + strlen(astr));
    sprintf(text, fstr, astr);
    return text;
}

int print_err(struct simple_error name, ...) {
    if(name.arg_flag == WITH_ARG) {
        char *arg, *text = name.text;
        va_list param;
        va_start(param, name);
        arg = va_arg(param, char*);
        va_end(param);
        text = combine_str(text, arg);
        if(print_text(text, stdout))
            return -1;
        else {
            free(text);
            return 0;
        }
    } else {
        if(print_text(name.text, stdout))
            return -1;
        else
            return 0;
    }
}

/*напечатать simple_error ошибку в stdout
int print_serr(struct simple_error name){
    if(print_err(name.text, stdout))
        return -1;
    else
        return 0;
}

int fprint_serr(struct simple_error name, FILE *target){
    if(print_err(name.text, target))
        return -1;
    else
        return 0;
}


int print_cerr(struct simple_error name, char *arg){
    char *text = malloc(sizeof(name.text) + sizeof(arg));
    unsigned short rtr = 0;
    sprintf(text, name.text, arg);
    if(print_err(text, stdout))
        rtr = -1;
    free(text);
    return rtr;
}

int fprint_cerr(struct complex_error name, FILE *target){
    char *text = malloc(sizeof(name.text) + sizeof(name.arg));
    unsigned short rtr = 0;
    sprintf(text, name.text, name.arg);
    if(print_err(text, target))
        rtr = -1;
    free(text);
    return rtr;
}*/
