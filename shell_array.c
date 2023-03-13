#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char *filename, int *size)
{
    FILE *fptr;
    long *numArray = NULL;

	fptr = fopen(filename, "rb");
    if (fptr == NULL)
        {
            *size = 0;
            return NULL;
        }
    else
        {
            fseek(fptr, 0, SEEK_END);
	        int byte_size = ftell(fptr);
            *size = byte_size / (sizeof(long));
        }

	numArray = (long*) malloc(*size * sizeof(long));
    fseek(fptr,0, SEEK_SET);
    fread(numArray, sizeof(long), *size, fptr);
    /* for debug
    for(int i = 0; i < *size; i++)
    {
        printf("unsorted%ld\n", numArray[i]);
    }
    */
    fclose(fptr);

	return numArray;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *fptr;

    int i = 0;
    fptr = fopen(filename, "wb");

    while(i < size)
    {
        fwrite(array+i, sizeof(long), 1, fptr);
        //printf("%ld\n", array[i]);
        i++;
    }
    //free(array);
    fclose(fptr);
    return size;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    //Rearrange elements at 3×h(i) +1 intervals
    int bigest_numinter;
    bigest_numinter = 0;

    while ((bigest_numinter * 3 + 1) < size)
    {
        bigest_numinter = bigest_numinter * 3 + 1;
    }

    for (int k = bigest_numinter; k > 0; k = (k - 1) / 3)
    {
        for (int i = k; i < size; i++)
        {
            long temp = array[i];
            int j;
            //change the position
            for (j = i; j >= k && array[j - k] > temp; j -= k)
            {
                array[j] = array[j - k];
                *n_comp += 1;
            }
            array[j] = temp;
        }
    }

}
