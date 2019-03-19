#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNumGenerator(int randMin, int randMax)
{
    //Referenced from https://devdocs.io/c/numeric/random/rand
    srand(time(NULL));
    int randNum = rand() % randMax + randMin;
    // printf("%d \n", randNum);
    return randNum;
}

void writePhysicalTable()
{
    FILE *file;

    file = fopen("./data/physical_memory.txt", "w");
    fprintf(file, "Address | Frame | Content\n--------|-------|--------\n");
    
    fclose(file);
}

void writePageTable()
{
    FILE *file;

    file = fopen("./data/page_table.txt", "w");
    fprintf(file, "Page | Page Table Entry\n-----| ----------------\n");

    fclose(file);
}