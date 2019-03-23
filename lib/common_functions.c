#include <stdio.h>
#include <stdlib.h>

int randNumGenerator(int randMin, int randMax)
{
    //Referenced from https://devdocs.io/c/numeric/random/rand
    // srand(time(NULL));
    int randNum = rand() % randMax + randMin;
    // printf("%d \n", randNum);
    return randNum;
}

int randCharGenerator()
{
    int randNum = rand() % (126 -34 + 1) + 34;
    return randNum;
}

void writePhysicalTable(int physicalMemorySize, char *physicalMemory)
{
    FILE *file;

    file = fopen("./data/physical_memory.txt", "w");
    fprintf(file, "Address | Frame | Content\n");
    fprintf(file, "--------|-------|--------\n");

    for(int x = 512; x < physicalMemorySize; ++x) //pass in Address Size
    {
        fprintf(file, "0x%x\t|\t%d\t|\t%c\n", x , x/256, *physicalMemory);
        physicalMemory++;
        // printf("Function Value: %c\n", *physicalMemory);
    }
    
    fclose(file);
}

void writePageTable(int counter, char *physicalMemory)
{
    FILE *file;

    file = fopen("./data/page_table.txt", "w");
    fprintf(file, "Page\t|\t Page Table Entry\n");
    fprintf(file, "-----\t|\t ----------------\n");

    for(int x = 0; x < counter; ++x) //pass in Address Size
    {
        int value = *physicalMemory;
        if(value < 0)
        {
            value = value + 256;
        }
        fprintf(file, "0x%x\t\t|\t\t%d\n", x, value);
        physicalMemory++;
        // printf("Function Value: %c\n", *physicalMemory);
    }

    fclose(file);
}

void writeHardDriveMemoryTable(int physicalMemorySize, char *hardDriveMemory)
{
    FILE *file;

    file = fopen("./data/hardrive_memory.txt", "w");
    fprintf(file, "Address | Frame | Content\n");
    fprintf(file, "--------|-------|--------\n");

    for(int x = 0; x < physicalMemorySize; ++x) //pass in Address Size
    {
        fprintf(file, "0x%x\t|\t%d\t|\t%c\n", x , x/256, *hardDriveMemory);
        hardDriveMemory++;
        // printf("Function Value: %c\n", *physicalMemory);
    }
    
    fclose(file);
}