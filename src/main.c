#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAGIC_NUMBER_SIZE 4
#define DOS_MAGIC_NUMBER_SIZE 2
#define E_LFANEW_OFFSET 0X3C

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

Error_Code identify_file(FILE *bin, File_Format *file_format)
{
	const unsigned char Elf_Magic_Number[MAGIC_NUMBER_SIZE] = {'\x7f', '\x45', '\x4c', '\x46'};
	const unsigned char Dos_Magic_Number[DOS_MAGIC_NUMBER_SIZE] = {'\x4d', '\x5a'};
	const unsigned char Pe_Magic_Number[MAGIC_NUMBER_SIZE] = {'\x50', '\x45', '\x00', '\x00'};

    unsigned char magic_number[MAGIC_NUMBER_SIZE];
    if(fread(magic_number, sizeof(*magic_number), MAGIC_NUMBER_SIZE, bin) != MAGIC_NUMBER_SIZE)
		return ERR_FILE_READ_FAILED;

	if(!memcmp(Elf_Magic_Number, magic_number, MAGIC_NUMBER_SIZE))
		*file_format = ELF;
	
	else if(!memcmp(Dos_Magic_Number, magic_number, DOS_MAGIC_NUMBER_SIZE))
	{
		uint32_t e_lfanew;
		size_t object_count = sizeof(uint32_t) / sizeof(uint32_t);
		
		// Access e_lfanew to learn where the PE signature begins.
		if(fseek(bin, E_LFANEW_OFFSET - MAGIC_NUMBER_SIZE, SEEK_CUR) != 0)
			return ERR_FILE_ACCESS_FAILED;
		
		// TODO: Wory about endianness later.   
		// Read e_lfanew.
		if(fread(&e_lfanew, sizeof(uint32_t), object_count, bin) != object_count)
			return ERR_FILE_READ_FAILED;
		
		// Access magic number of PE.
		if(fseek(bin, e_lfanew - (E_LFANEW_OFFSET + sizeof(uint32_t)), SEEK_CUR) != 0)
			return ERR_FILE_ACCESS_FAILED;
		
		// Read magic number of PE.
		if(fread(magic_number, sizeof(*magic_number), MAGIC_NUMBER_SIZE, bin) != MAGIC_NUMBER_SIZE)
			return ERR_FILE_READ_FAILED;
		
		if(!memcmp(Pe_Magic_Number, magic_number, MAGIC_NUMBER_SIZE))
			*file_format = PE;
		else
			*file_format = UNSUPPORTED;
	}

	else
		*file_format = UNSUPPORTED;

    rewind(bin);

    return ERR_NONE;
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
