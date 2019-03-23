#include "lib/common_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //Referenced from https://www.geeksforgeeks.org/bool-in-c/

int main()
{

	srand(time(NULL));	
	int physical_memory_size = 65536;
	int data_block_size = randNumGenerator(2048, 20480);
	int process_start_loc = randNumGenerator(512, ((physical_memory_size-1) - data_block_size)); 
	int numOfFrames = physical_memory_size / 256;
	
	char *physicalMemory = malloc(physical_memory_size); //Main Memory with size 65536 (2 ^ 16)


	//Write the memory with unused value "!";
	for(int value = 0; value < physical_memory_size; ++value)
	{
		physicalMemory[value] = '!';
	}

	//Write physical memory with data block with random characters
	for(int x = process_start_loc; x < (process_start_loc + data_block_size); ++x)
	{
		int randChar = randCharGenerator();
		physicalMemory[x] = randChar;
	}

	writePhysicalTable(physical_memory_size, &physicalMemory[512]);


	//Storing all the frame numbers that have Content in it inside the page table.
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
			printf("frameNumber: %d\n",frameNumber);
			physicalMemory[counter] = frameNumber;
			counter++;
		}
		
		frameHasContent = false;
	}

	writePageTable(counter, &physicalMemory[0]);


	return 0;
}
