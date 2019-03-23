#include "lib/common_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //Referenced from https://www.geeksforgeeks.org/bool-in-c/

void swap(char *physicalMemoryContent, char *hardDriveMemoryContent);

int main()
{

	srand(time(NULL));	
	int physical_memory_size = 65536;
	int data_block_size = randNumGenerator(2048, 20480);
	int process_start_loc = randNumGenerator(512, ((physical_memory_size-1) - data_block_size)); 
	int numOfFrames = physical_memory_size / 256;
	
	char *physicalMemory = malloc(physical_memory_size); //Main Memory with size 65536 (2 ^ 16)
	char *hardDriveMemory = malloc(physical_memory_size); //Simulated HardDrive Memory


	//Write the memory with unused value "!";
	for(int value = 0; value < physical_memory_size; ++value)
	{
		physicalMemory[value] = '!';
		hardDriveMemory[value] = randCharGenerator();
	}

	//Write physical memory with data block with random characters
	for(int x = process_start_loc; x < (process_start_loc + data_block_size); ++x)
	{
		int randChar = randCharGenerator();
		physicalMemory[x] = randChar;
		hardDriveMemory[x] = '!';
	}

	writePhysicalTable(physical_memory_size, &physicalMemory[512]);
	writeHardDriveMemoryTable(physical_memory_size, &hardDriveMemory[0]);


	//Stores all the frame numbers that have Random character in it inside the page table.
	int counter = 0;
	for(int a = 512; a < physical_memory_size; a += 256)
	{
		bool frameHasContent = false;
		for(int b = a; b < a+256; ++b)
		{
			if(physicalMemory[b] != '!')
			{
				frameHasContent = true;
			}
		}
		if(frameHasContent == true)
		{
			int frameNumber = a/numOfFrames;
			physicalMemory[counter] = frameNumber;
			counter++;
		}
		
		frameHasContent = false;
	}

	writePageTable(counter, &physicalMemory[0]); //Write the page table to txt file


	//Looks up the content in virtual address.
	int userInputVirtualAddress = 0; //Store the hex value that user enter as Decimal
	do{
		printf("\nPlease Enter a Virtual Address in Hex or -1 to exit program: ");
		scanf("%x", &userInputVirtualAddress);

		if(userInputVirtualAddress != -1) //Runs if the user hasnt choosen to Exit
		{
			int correspondingPageNum = userInputVirtualAddress /256; //Divdes the Decimal value by total number of pages the page table can hold
			printf("The Virtual Address you entered is in Page: %d\n", correspondingPageNum); // And checks what page number hold that address

			if(correspondingPageNum > counter)
			{
				printf("No Page exist for that Address - Not Being Used\n"); 
				//Fails if there is no page in the page table that has the data.
			}
			else
			{
				//Get the Frame number associated with the Page Number
				int correspondingFrameNum = physicalMemory[correspondingPageNum];

				if(correspondingFrameNum < 0)
				{
					correspondingFrameNum = correspondingFrameNum + 256;
				}

				int pageOffSet = userInputVirtualAddress - ((correspondingPageNum * 256) -1);
				int correspondingPhysicalAddress = pageOffSet + (correspondingFrameNum * 256);
				
				printf("Page: %d\t --->\tFrame: %d\n", correspondingPageNum, correspondingFrameNum);
				printf("OffSet: %d\n", pageOffSet);
				printf("Virtual Address: 0x%x\t---->\tPhysical Address: 0x%x\n", userInputVirtualAddress, correspondingPhysicalAddress);
				if(physicalMemory[correspondingPhysicalAddress] == '!')
				{
					//After Address translation. If the address correspond to an index that contains no data i.e. "!.
					//It will swap the '!' with a value from the 
					printf("No Content at Physical Memory: 0x%x\n Swapping with Content from HardDisk\n", correspondingPhysicalAddress);
					swap(&physicalMemory[correspondingPhysicalAddress], &hardDriveMemory[correspondingPhysicalAddress]);
					printf("Current Content at Physical Address 0x%x: %c\n", correspondingPhysicalAddress, physicalMemory[correspondingPhysicalAddress]);
				}
			}
		}
	}while(userInputVirtualAddress != -1);

	return 0;
}

//Referenced from LAB 3 of Operating Systems
void swap(char *physicalMemoryContent, char *hardDriveMemoryContent)
{
	int tempHolder = *physicalMemoryContent;
	*physicalMemoryContent = *hardDriveMemoryContent;
	printf("Swapped %c from Physical Memory with %c from Hard Drive\n", tempHolder, *physicalMemoryContent);
}