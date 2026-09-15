#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {UNSUPPORTED = -1, ELF, PE} File_Format;

long get_binary_size(FILE * bin)
{
	int result = fseek(bin, 0, SEEK_END);
	if(result)
	{
		printf("An error occured while accessing the given binary.\n");
		return -1L;
	}

	long size = ftell(bin);
	if(size == -1L)
	{
		printf("An error occured while calculating the size of the given binary.\n");
        return -1L;
	}

	rewind(bin);
	return size;
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
