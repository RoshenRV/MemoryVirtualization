#include "lib/common_functions.h"
int main()
{

	
	//writePhysicalTable();
	int physical_memory_size = 65536;
	int data_block_size = randNumGenerator(2048, 20480);
	int process_start_loc = randNumGenerator(512, ((physical_memory_size-1) - data_block_size)); 

	


	

	return 0;
}
