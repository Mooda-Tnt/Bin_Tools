#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    ERR_NONE = 0,

    ERR_FILE_NOT_FOUND = 1,
    ERR_FILE_READ_FAILED = 2,
    ERR_FILE_WRITE_FAILED = 3,
    ERR_FILE_ACCESS_FAILED = 4,
    ERR_FILE_SIZE_CALCULATION_FAILED = 5

} Error_Code;

typedef enum {UNSUPPORTED = -1, ELF, PE} File_Format;

Error_Code get_binary_size(FILE *bin, long *size)
{
    if(fseek(bin, 0, SEEK_END) != 0)
        return ERR_FILE_ACCESS_FAILED;

    long result = ftell(bin);
    if(result == -1L)
        return ERR_FILE_SIZE_CALCULATION_FAILED;

    *size = result;

    rewind(bin);

    return ERR_NONE;
}

File_Format identify_file(FILE * binary_file)
{
	const unsigned char elf_magic_number[4] = {'\x7f', '\x45', '\x4c', '\x46'};
	
	unsigned char magic_number[4];
	fread(magic_number, sizeof(*magic_number), sizeof(magic_number) / sizeof(*magic_number), binary_file);

	int result = memcmp(elf_magic_number, magic_number, 4);
	if(result == 0)
		return ELF;

	return UNSUPPORTED;
}

int main(int argc, char **argv)
{
	if(argc == 1)
    {
    	printf("No binary file provided!\n");
		return EXIT_FAILURE;
	}

	char *bin_name = argv[1];
	
	FILE *bin = fopen(bin_name, "rb");
	if(!bin)
	{
		printf("Binary file does not exist!\n");
		return EXIT_FAILURE;
	}
	
	long bin_size = get_binary_size(bin);
	if(bin_size == -1L)
    	return EXIT_FAILURE;

	if(bin_size < 4)
	{
		printf("Malformed binary file\n");
		return EXIT_FAILURE;
	}

	// Debugging line.
	printf("%ld\n", bin_size);

	File_Format ff = identify_file(bin);
	if(ff)
	{
			printf("Unsupported binary format!\n");
			return EXIT_FAILURE;
	}

	printf("File Format: ELF\n");

	fclose(bin);
	return 0;
}
