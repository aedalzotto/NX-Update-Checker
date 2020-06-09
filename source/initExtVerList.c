#include "main.h"

Entry* initExtVerList()
{
	FILE *verListTxt;
	Entry *currExtEntry;
	char *memVerList;
	
	verListTxt = fopen("versions.txt", "r");
	if (verListTxt == NULL)
	{
		printf("\nPlease place a copy of versions.txt in the same directory as this nro.\n");
		printf("You may find a compatible versions.txt this app was tested with on the\n");
		printf("following repository: https://github.com/blawar/titledb/blob/master/versions.txt\n\n");
		printf("Press (+) to exit.");
		consoleUpdate(NULL);
		while (1)
		{
			hidScanInput();
			u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
			if (kDown & KEY_PLUS) return NULL;
		}
	}
	
	/* Have an empty entry at head of list */
	currExtEntry = calloc(1, sizeof(Entry));
	
	// char* selectedTxt = calloc(NAME_MAX, sizeof(char));
	fseek(verListTxt, 0, SEEK_END);
	long fileSize = ftell(verListTxt);
	memVerList = calloc(fileSize, sizeof(char));
	rewind(verListTxt);
	fread(memVerList, 1, fileSize, verListTxt);
	
	/*Close our input file*/
	if (fclose(verListTxt) != 0)
	{
		perror("versions.txt");
		printf("\nPress (+) to exit.");
		consoleUpdate(NULL);
		while (1)
		{
			hidScanInput();
			u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
			if (kDown & KEY_PLUS) return NULL;
		}
	}
	// free(selectedTxt);
	
	return handleVerList(currExtEntry, fileSize, memVerList);
}