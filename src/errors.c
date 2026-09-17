#include "errors.h"

const char *get_error_message(Error_Code err_code)
{
        const char *error_message;

        switch(err_code)
        {
                case ERR_NONE:
                        error_message = "No error encountered";
                        break;
                case ERR_BIN_NOT_FOUND:
                        error_message = "No such binary file";
                        break;
                case ERR_BIN_READ_FAILED:
                        error_message = "Failed to read binary file";
                        break;
                case ERR_BIN_WRITE_FAILED:
                        error_message = "Failed to write to binary file";
                        break;
                case ERR_BIN_ACCESS_FAILED:
                        error_message = "Failed to traverse binary file";
                        break;
                case ERR_BIN_SIZE_CALCULATION_FAILED:
                        error_message = "Failed to get size of binary file";
                        break;
                case ERR_BIN_CLOSING_FAILED:
                        error_message = "Failed to close binary file";
                        break;
                case ERR_BIN_MALFORMED:
                        error_message = "Malformed binary file";
                        break;
                default:
                        error_message = "Unknown error";
        }

        return error_message;
}

