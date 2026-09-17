#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>

#include "errors.h"

#define MAGIC_NUMBER_SIZE 4
#define DOS_MAGIC_NUMBER_SIZE 2
#define E_LFANEW_OFFSET 0X3C

typedef enum {UNSUPPORTED = -1, ELF, PE} Binary_Format;

Error_Code open_binary_r(char *bin_name, FILE **bin);
Error_Code close_binary(FILE **bin);
Error_Code get_binary_size(FILE *bin, long *size);
Error_Code identify_binary(FILE *bin, Binary_Format *file_format);

#endif
