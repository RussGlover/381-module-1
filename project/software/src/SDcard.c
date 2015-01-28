
#include <../Module1/Definitions.h>
#include <../Module1/SDcard.h>

alt_up_sd_card_dev *device_reference = NULL;
void sdcard_Init(void)
{
	//alt_up_sd_card_dev *device_reference = NULL;
			device_reference = alt_up_sd_card_open_dev("/dev/sdcard");
				int connected = 0;
				if (device_reference != NULL) {
						if ((connected == 0) && (alt_up_sd_card_is_Present())) {
							printf("Card connected.\n");
							if (alt_up_sd_card_is_FAT16()) {
								printf("FAT16 file system detected.\n");
							} else {
								printf("Unknown file system.\n");
							}
							connected = 1;
						} else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)) {
							printf("Card disconnected.\n");
							connected = 0;
						}
				}

}


/**
 * Looks for an SD Card
 * Return: True if SD Card present. False otherwise.
 */
int sdcard_isPresent(void)
{
	int is_present = alt_up_sd_card_is_Present();
	return is_present;
}

/**
 * Looks for a FAT16 partition
 * Return: True if FAT16 partition exists. False otherwise.
 */
int sdcard_isFAT16(void)
{
	int is_fat16 = alt_up_sd_card_is_FAT16();
	return is_fat16;
}

/**
 * Finds the first file in the directory, stores it into file_name
 * Return: 0 (success), 1 (invalid directory), 2 (no sd card/fat16 partition), -1 (no files found)
*/
short int sdcard_FirstFile(char *directory, char *file_name)
{
	short int result = alt_up_sd_card_find_first(directory, file_name);
	return result;
}

/**
 * Uses the directory used in sdcard_get_first_file.
 * Return: Same as sdcard_FirstFile, with the addition of 3, which means that sdcard_FirstFile must be called first
 */
short int sdcard_NextFile(char *file_name)
{
	short int result = alt_up_sd_card_find_next(file_name);
	return result;
}

/**
 * Prints out a list of files in the given directory
 */
void sdcard_ListFiles(char *directory)
{
	char *file_name = NULL;
		if (!alt_up_sd_card_find_first(directory, file_name))
			{
				printf(file_name); printf("\n");
				while(!alt_up_sd_card_find_next(file_name))
				{
					printf(file_name); printf("\n");
				}
		}
}

/**
* Opens a file for use
* Parameters: name (file name, including the directory), create_new_if_not_exist (set to True to create a file if it doesn't exist already)
* Result: Index to file record. -1 if file not opened. -2 if file has already been opened
*/
short int sdcard_fopen(char *file_name, bool create_new_if_not_exist)
{
	short int handle = alt_up_sd_card_fopen(file_name,false);
	return handle;
}


/*
 * Returns a byte from given file
 */
short int sdcard_ReadByte(short int file_handle)
{
	short int byte = alt_up_sd_card_read(file_handle);
	return byte;
}

/*
 * Returns file size
 */
int sdcard_FileSize(short int file_handle)
{
	int size = 0;
	for(size = 0; sdcard_ReadByte(file_handle) != -1; size++);

	sdcard_fclose(file_handle);

	return size;
}

/*
 * Reads file into a int buffer
 */
void sdcard_ReadFile(int read_data[], short int file_handle)
{
	short int byte = 0;
	int val=0;
	int size = 0;
	char string[10];
	int string_index;
	while(byte !=-1){
		string_index = 0;
		while(1){
			byte = sdcard_ReadByte(file_handle);
			if(byte >=47 &&byte <= 58){
				string[string_index] =(char)(((int)'0')+byte-48);
				printf("%s",string);
				string_index ++;
			}
			else {
				string[string_index]='\0';
				break;
			}
		}
		val = atoi(string);
		read_data[size]=val;
		size++;
		if (size ==16){
			break;
		}
	}
}
	/*
	short int byte = 0;
	int size = 0;
	while(byte != -1)
	{
		byte = sdcard_ReadByte(file_handle);
		if ( byte != -1) read_data[size] = byte;

		size++;
	}

	read_data[size - 1] = '/';
}
*/
/*
 *	Debug method for printing char buffer
 */
void printArray(int a[])
{
	printf("Print array called \n");
	int h = 0;
	for (h=0; h<16; h++){
		printf("Print parameter %d : %d \n",h, a[h]);
	}
}


/*
 *	Writes char buffer to file
 *	Stops when end of file character '/' detected
 */
void sdcard_WriteFile(int write_data [], short int file_handle)
{
	int byte_index = 0;
	bool result;
	char temp;
	while(byte_index != 16)
	{
		temp=(char)(((int)'0')+write_data[byte_index]);
		result = alt_up_sd_card_write(file_handle, temp);
		byte_index++;
	}
}

/* Return: File attributes. -1 if invalid file.
 */
short int sdcard_getFattributes(short int file_handle)
{
	short int att = alt_up_sd_card_get_attributes(file_handle);
	return att;
}

/*
 * Closes the file
 */
void sdcard_fclose(int short file_handle)
{
	alt_up_sd_card_fclose(file_handle);
}
