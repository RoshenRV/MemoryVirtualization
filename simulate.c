#include "lib/common_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

	srand(time(NULL));	
	//writePhysicalTable();
	int physical_memory_size = 65536;
	int data_block_size = randNumGenerator(2048, 20480);
	int process_start_loc = randNumGenerator(512, ((physical_memory_size-1) - data_block_size)); 
	
	char *physicalMemory = malloc(physical_memory_size);


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

	


	return 0;
}
