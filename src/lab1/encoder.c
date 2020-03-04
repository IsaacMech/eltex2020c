#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

char no_exit = 1;
void exiting(void) { no_exit = 0; }

int main(int argc, char *argv[]) {
    print_err(fileio_error.unable_to_write, "СЫР.сыр");
    return 0;
}
