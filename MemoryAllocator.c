/*
Eric Lee
CECS 424
3/8/2020
*/

#include <stdio.h>
#include <conio.h>
#include <math.h>

struct Block {
	int block_size;
	struct Block *next_block;
};

void my_initialize_heap(int size);
void* my_malloc(int size);
void my_free(void *data);

const int OVERHEAD_SIZE = sizeof(struct Block);
const int VOID_PTR_SIZE = sizeof(void*);
struct Block *free_head;


int main()
{
	printf("Size of int: %d\n", sizeof(int));
	printf("Size of char: %d\n", sizeof(char));
	printf("Void Pointer Size: %d\n", sizeof(void*));
	printf("Overhead Size: %d\n", sizeof(struct Block));
	
	
	//my_initialize_heap(1048576 + OVERHEAD_SIZE);
	
	my_initialize_heap(1028 + OVERHEAD_SIZE);

	/*
	void* result1 = my_malloc(sizeof(int));
	printf("%d\n", result1);
	my_free(result1);
	void* result2 = my_malloc(sizeof(int));
	printf("%d\n", result2);
	my_free(result2);

	void* result3 = my_malloc(sizeof(int));
	void* result4 = my_malloc(sizeof(int));
	printf("%d\n", result3);
	printf("%d\n", result4);
	my_free(result3);
	my_free(result4);
	*/

	/*
	void* result5 = my_malloc(sizeof(int));
	void* result6 = my_malloc(sizeof(int));
	void* result7 = my_malloc(sizeof(int));
	printf("%d\n", result5);
	printf("%d\n", result6);
	printf("%d\n", result7);
	printf("\nBreak\n");

	my_free(result6);

	void* result8 = my_malloc(sizeof(double));
	printf("%d\n", result5);
	printf("%d\n", result8);
	printf("%d\n", result7);
	*/

	
	void* result9 = my_malloc(sizeof(char));
	void* result10 = my_malloc(sizeof(int));
	printf("%d\n", result9);
	printf("%d\n", result10);
	

	/*
	void* result11 = my_malloc(sizeof(int[100]));
	void* result12 = my_malloc(sizeof(int));
	printf("%d\n", result11);
	printf("%d\n", result12);
	*/

	/*
	int numOfInts;
	int dummyInt;
	printf("How many integers would you like to allocate? ");
	scanf_s("%d", &numOfInts);

	void* startOfArray = my_malloc(sizeof(int[100]));
	int* intArrayPtr = (int*) startOfArray;

	for (int count = 0; count < numOfInts; count++)
	{
		printf("Integer %d: ", count + 1);
		scanf_s("%d", &dummyInt);
		intArrayPtr[count] = dummyInt;
	}
	
	double sum = 0;
	double oneOverN = 1.0 / (double)numOfInts;
	double arithmeticMean;

	for (int count = 0; count < numOfInts; count++)
	{
		sum = sum + (double)intArrayPtr[count];
	}

	arithmeticMean = sum / numOfInts;

	double partialResult = 0;

	for (int count = 0; count < numOfInts; count++)
	{
		partialResult = partialResult + (pow((double)intArrayPtr[count] - arithmeticMean, 2.0));
	}

	partialResult = oneOverN * partialResult;
	partialResult = sqrt(partialResult);

	printf("\n\nStandard Deviation: %f\n\n", partialResult);

	*/

	_getch();
	return 0;
}

void my_initialize_heap(int size)
{
	void* allocated_storage = malloc(size);
	free_head = (struct Block*)allocated_storage;
	free_head->block_size = size - OVERHEAD_SIZE;
	free_head->next_block = NULL;
}

void* my_malloc(int size)
{
	struct Block* traversal_ptr;
	traversal_ptr = free_head;

	while (traversal_ptr != NULL)
	{
		//traversal_ptr->block_size % VOID_PTR_SIZE == 0 && 
		if (traversal_ptr->block_size >= size)
		{
			if (traversal_ptr->block_size > (size + OVERHEAD_SIZE + VOID_PTR_SIZE)) //Block needs to be split
			{
				int sizeOfNewBlock = traversal_ptr->block_size - size - OVERHEAD_SIZE;
				struct Block* newlyFormedBlock = traversal_ptr + 1;
				newlyFormedBlock = ((char*)newlyFormedBlock) + size;

				newlyFormedBlock->block_size = sizeOfNewBlock;
				newlyFormedBlock->next_block = traversal_ptr->next_block;

				traversal_ptr->block_size = size;
				traversal_ptr->next_block = NULL;

				
				if (traversal_ptr == free_head) //We're splitting the first block of free_head
				{
					free_head = newlyFormedBlock;
				}

				
				else //We're splitting a block that is not the first element of free_head
				{
					struct Block* previousBlock = free_head;

					while (previousBlock->next_block != traversal_ptr)
					{
						previousBlock = previousBlock->next_block;
					}

					previousBlock->next_block = newlyFormedBlock;
				}

				return traversal_ptr + 1;
			}

			else //Block does not need to be split
			{
				if (traversal_ptr == free_head) //The first element of free_head exactly fits our allocation needs
				{
					struct Block* temp = free_head;
					free_head = free_head->next_block;
					temp->next_block = NULL;
				}

				else //An element that is not the first element of free_head exactly fits our allocation needs
				{
					struct Block* previousBlock = free_head;

					while (previousBlock->next_block != traversal_ptr)
					{
						previousBlock = previousBlock->next_block;
					}

					previousBlock->next_block = previousBlock->next_block->next_block;
					traversal_ptr->next_block = NULL;
				}

				return traversal_ptr + 1;
			}
		}

		
		else
		{
			traversal_ptr = traversal_ptr->next_block;
		}
	}
	
	return NULL;
}

void my_free(void *data)
{
	struct Block *tempBlock = (struct Block*) data;
	struct Block *blockToFree = tempBlock - 1;
	blockToFree->next_block = free_head;
	free_head = blockToFree;
}

/*
		else if (traversal_ptr->block_size % VOID_PTR_SIZE != 0 && traversal_ptr->next_block == NULL && traversal_ptr->block_size > (size + OVERHEAD_SIZE + VOID_PTR_SIZE))
		{
			int originalSize = traversal_ptr->block_size;
			struct Block* fourByteBlock = traversal_ptr;
			struct Block* tempBlock = fourByteBlock + 1;
			tempBlock = (int*)tempBlock + 4;
			fourByteBlock->next_block = tempBlock;
			fourByteBlock->block_size = 4;
			tempBlock->block_size = originalSize - (OVERHEAD_SIZE + 4);
			tempBlock->next_block = NULL;
		}
		*/