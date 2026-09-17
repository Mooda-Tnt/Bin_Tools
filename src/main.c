#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "binary.h"

int main(int argc, char **argv)
{
	Binary bin;
	bin.bin_file = NULL;
	Error_Code result;

	// TODO: Channel errors to stderr.
	// TODO: You might have to refactor repetative clean-up code.

	if(argc == 1)
	{
		printf("No binary file provided!\n");
		return EXIT_FAILURE;
	}
	
	bin.bin_name = argv[1];
	result = open_binary_r(bin.bin_name, &bin.bin_file);
	if(result)
	{
		printf("%s.\n", get_error_message(result));
		return EXIT_FAILURE;
	}
	
	result = get_binary_size(bin.bin_file, &bin.bin_size);
	if(result)
	{
		printf("%s.\n", get_error_message(result));
		
		result = close_binary(&bin.bin_file);
		if(result)
			printf("%s.\n", get_error_message(result));
		
		return EXIT_FAILURE;
	}

	if(bin.bin_size < 4)
	{
		printf("%s.\n", get_error_message(ERR_BIN_MALFORMED));
		
		result = close_binary(&bin.bin_file);
		if(result)
			printf("%s.\n", get_error_message(result));

		return EXIT_FAILURE;
	}

	result = identify_binary(bin.bin_file, &bin.bin_format);
	if(result)
	{
		printf("%s.\n", get_error_message(result));
		
		result = close_binary(&bin.bin_file);
		if(result)
			printf("%s.\n", get_error_message(result));
		
		return EXIT_FAILURE;
	}
	
	// TODO: Use file_format for printing out the detected binary format.
	printf("File Format: ELF\n");

	result = close_binary(&bin.bin_file);
	if(result)
	{
		printf("%s.\n", get_error_message(result));
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
