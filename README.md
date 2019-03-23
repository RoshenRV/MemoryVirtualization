# MemoryVirtualization

After doing a make command. You can run the program by ./dist/simulate.

On run, the program write 3 txt file to ./data.
- physical_memory.txt 
- page_table.txt
- hardrive_memory.txt

The physical_memory.txt shows the contents that inside each index from 512. It also shows the frame number as well. 

The page_table.txt display all the frame numbers that have a random character in it. 

Then it will prompt you to type in an virtual address in Hex. 
After inputing a virtual address it will check if there is page number associated to the virtual address.
If there is page number that associated to the virtual address. It will then check the corresponding frame number and displays it.
If the virtual address is corresponding to a physical address that has no data in it (i.e.'!'). It will the swap the '!' with a random character thats stored in the same address in the hardrive memory array. 

The harddrive memory array is filled with random characters. 