// Code Author: Hafiz Hassaan Saeed

#include "stdafx.h"
#include <windows.h>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("hello world\n");

	BYTE sector[512];
	DWORD bytesRead;
	HANDLE handledisk = NULL;
	int numSector = 0;
	int totalSectors = 976768002;
	printf("Total Sectors are: %d\n", totalSectors);

	//DWORD dataheader[16] = { 0xEB, 0x52, 0x90, 0x4E, 0x54, 0x46, 0x53, 0x20, 0x20, 0x20, 0x20, 0x00, 0x02, 0x08, 0x00, 0x00 };
	DWORD dataheader[12] = { 0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x06, 0x00, 0x08, 0x00, 0x00, 0x00 };
	DWORD buf[512];

	handledisk = CreateFile(L"\\\\.\\G:", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (handledisk == INVALID_HANDLE_VALUE)
	{
		printf("Error in CreateFile: %u\n", GetLastError());
		return 1;
	}

	int countmatches = 0;
	
	int countSectors = 0;
	
	while (countSectors < totalSectors)
	{
		SetFilePointer(handledisk, countSectors * 512, NULL, FILE_BEGIN);

		if (!ReadFile(handledisk, sector, 512, &bytesRead, NULL))
		{
			printf("ReadFile: %u\n", GetLastError());
		}
		else
		{
			//printf("Success and Reading!\n");
			memcpy(buf, sector, 512);
			int r = memcmp(buf, dataheader, sizeof(dataheader));
			/*for (int i = 0; i < sizeof(dataheader); i++)
			{
				printf("%d \t %x \t %x \n", i, buf[i], dataheader[i]);
			}
			printf("\n\n");*/
			//printf("memcmp:%d\n", r);
			if (r == 0)
			{
				countmatches++;
				printf("\t\tFirst found:%d\n", countSectors);
				break;
			}
		}
		printf("Sectors checked:%d\n", countSectors);
		countSectors++;
	}

	CloseHandle(handledisk);
	//system("PAUSE");
	return 0;
}

