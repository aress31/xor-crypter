#include <stdio.h>
#include <stdlib.h>
#include "../headers/check_key.h"

int get_position(char* argv[], int argc, char* string) {
	/** Return the position of an argument.
	Arguments:
	argv 	-- the list of arguments
	argc 	-- the number of arguments
	string 	-- the string that we desire the position
	Returns:
	The position of the argument
	*/
	int i = 0;
  
	while(i<argc) {
		if((strcmp(argv[i], string))==0)
			return i;

		else
	  		i++;
	}
	return -1; 
}
  
bool parseArgs(int argc, char* argv[]) {
	/** Parse command line arguments.
	Returns:
	Command line argument object
	*/
	int i = 0;
  
	if(argc == 2 && (strcmp(argv[1], "-h")==0)) {
		printf("examples:\n");
		printf("to encrypt/decrypt a text file:\n");
		printf("$ xor -i my_input_text_file -o my_output_text_file.\n\n");
		printf("-i -- your input text file.\n");
		printf("-o -- your output text file.\n");
		printf("-h -- help.\n");
		exit(EXIT_SUCCESS);
	}
	else if(argc == 7) {
		while (i<argc) {  
	  		if(((i % 2) != 0) && ((strcmp(argv[i], "-i")!=0) && (strcmp(argv[i], "-o")!=0) && (strcmp(argv[i], "-k")!=0)))
				return false;
			else 
				i++;
		}
		return true;
	}
	else
		return false;
}

int main (int argc, char* argv[]) {
	printf("XOR-crypter 0.1\n");
	printf("by Ares\n\n");
	
	FILE* input; FILE* output;
	char* key;
	char crypted_char = 0, c = 0;
	int  i = 0, key_length = 0;

	if(parseArgs(argc, argv)==false) {
		printf("Error: You need to specify an input file, output file and a key string. See -h for more info.\n");
		exit(EXIT_FAILURE);
	}

	input = fopen(argv[get_position(argv, argc,"-i") + 1], "r");
	if(input == NULL || get_position(argv, argc,"-i") == -1) {
		fprintf(stderr,"Error: Impossible to read the input file.\n");
		exit(EXIT_FAILURE); 
	}

	output = fopen(argv[get_position(argv, argc,"-o") + 1], "w");
	if(output == NULL || get_position(argv, argc,"-i") == -1) {
		fprintf(stderr,"Error: Impossible to write in the output file.\n");
		exit(EXIT_FAILURE); 
	}

	//Check the key
	key_length = strlen(argv[get_position(argv, argc,"-k") + 1]);
	key = malloc(sizeof(char)*key_length);
	strcpy(key, argv[get_position(argv, argc,"-k") + 1]); 

	if (check_key(key, key_length)==false) {
		printf("Error: use characters from ISO/IEC 8859-1(Latin1) for the key.\n");
		exit(EXIT_FAILURE); 
	}

	//Encryption/decryption 
	while(!feof(input)) {
		c = fgetc(input);
		if(feof(input)) 
			break;
		crypted_char = (c ^ (key[i % key_length]));
		fputc(crypted_char,output);
		i++; 
	}

	fclose(input);
	fclose(output);
	return(EXIT_SUCCESS); 
}
