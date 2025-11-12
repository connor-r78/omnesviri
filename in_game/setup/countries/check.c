#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define ARGUMENTS 2
#define TAG_ARG 1

#define SUCCESS 0
#define ERR_INCORRECT_USAGE 1
#define ERR_DIR_NOT_FOUND 2

#define FALSE 0
#define TRUE 1
	
#define DEFAULT_BUFFER 100
#define MUTATION_LENGTH 3
#define TAG_LENGTH 3

int findTag(char *tag, char *countryfileName) 
{
	char mutatedTag[TAG_LENGTH + MUTATION_LENGTH];
    snprintf(mutatedTag, sizeof(mutatedTag), "%s =", tag);

	FILE *countryfile;
	countryfile = fopen(countryfileName, "r");

	char readString[DEFAULT_BUFFER];
	while ( fgets(readString, DEFAULT_BUFFER, countryfile) ) {
		if ( strstr(readString, mutatedTag) ) return TRUE;
	}

	fclose(countryfile);

	return FALSE;
}

int main(int argc, char *argv[])
{
  if ( argc == ARGUMENTS && strlen(argv[TAG_ARG]) == TAG_LENGTH ) {
		DIR *countries;
		struct dirent *dir;

		int found = FALSE;

		countries = opendir("./");
		if ( !countries ) return ERR_DIR_NOT_FOUND;

		while ( (dir = readdir(countries)) ) {
			if ( strstr(dir->d_name, ".txt") && findTag(argv[TAG_ARG], dir->d_name) ) {
				printf("%s is already in use.\n", argv[TAG_ARG]);
				found = TRUE;
			}
		}

		closedir(countries);
		if( !found ) printf("%s is safe to use.\n", argv[TAG_ARG]);
		return SUCCESS;
  }
  else {
		printf("Usage: ./check TAG\n");
		return ERR_INCORRECT_USAGE;
  }
}
