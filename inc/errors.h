#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
    ERR_NONE = 0,

    ERR_FILE_NOT_FOUND = 1,
    ERR_FILE_READ_FAILED = 2,
    ERR_FILE_WRITE_FAILED = 3,
    ERR_FILE_ACCESS_FAILED = 4,
    ERR_FILE_SIZE_CALCULATION_FAILED = 5

} Error_Code;

const char *get_error_message(Error_Code err_code);

#endif
