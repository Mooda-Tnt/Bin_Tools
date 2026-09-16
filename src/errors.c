const char *get_error_message(Error_Code err_code)
{
        const char *error_message;

        switch(err_code)
        {
                case ERR_NONE:
                        error_message = "No error encountered";
                        break;
                case ERR_FILE_NOT_FOUND:
                        error_message = "No such binary file";
                        break;
                case ERR_FILE_READ_FAILED:
                        error_message = "Failed to read binary file";
                        break;
                case ERR_FILE_WRITE_FAILED:
                        error_message = "Failed to write to binary file";
                        break;
                case ERR_FILE_ACCESS_FAILED:
                        error_message = "Failed to traverse binary file";
                        break;
                case ERR_FILE_SIZE_CALCULATION_FAILED:
                        error_message = "Failed to get size of binary file";
                        break;
                default:
                        error_message = "Unknown error";
        }

        return error_message;
}

