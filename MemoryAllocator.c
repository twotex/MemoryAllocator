/*
Eric Lee
CECS 424
3/8/2020
*/

#include <stdio.h>
#include <conio.h>

struct Block {
	int block_size;
	struct Block *next_block;
};

void my_initialize_heap(int size);

const int OVERHEAD_SIZE = sizeof(struct Block);
const int VOID_PTR_SIZE = sizeof(void*);
struct Block *free_head;


int main()
{
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(void*));
	printf("%d\n", sizeof(struct Block));
	

	_getch();
	_getch();
	return 0;
}

void my_initialize_heap(int size)
{
	void* allocated_storage = malloc(size);
	free_head = allocated_storage;
	free_head->block_size = size - OVERHEAD_SIZE;
	free_head->next_block = NULL;
}

void* my_malloc(int size)
{
	struct Block *tempHead;
	tempHead = free_head;

	while (tempHead != NULL)
	{
		if (tempHead->block_size % VOID_PTR_SIZE == 0 && tempHead->block_size >= size)
		{
			if (tempHead->block_size > size)
			{
				int extraSpace = tempHead->block_size - size;
				struct Block *proceedingBlock = tempHead->next_block;
				proceedingBlock->block_size = extraSpace;
				proceedingBlock->next_block = NULL;
			}

			else
			{
				free_head = free_head->next_block;
			}
		}

		else
		{
			tempHead = tempHead->next_block;
		}
	}
	
}

void my_free(void *data)
{
	struct Block *tempBlock = data;
	struct Block *blockToFree = tempBlock - OVERHEAD_SIZE;

	(*blockToFree).next_block = free_head;
	(*blockToFree).block_size = 0;
	free_head = blockToFree;
}