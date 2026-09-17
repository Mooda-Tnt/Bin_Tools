#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
    ERR_NONE = 0,

    ERR_BIN_NOT_FOUND = 1,
    ERR_BIN_READ_FAILED = 2,
    ERR_BIN_WRITE_FAILED = 3,
    ERR_BIN_ACCESS_FAILED = 4,
    ERR_BIN_SIZE_CALCULATION_FAILED = 5,
    ERR_BIN_CLOSING_FAILED = 6,
    ERR_BIN_MALFORMED = 7

} Error_Code;

const char *get_error_message(Error_Code err_code);

#endif
