#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char** argv){
    if(argc != 4){
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "-a") == 0){
        int len = 0;
        long *arr = Array_Load_From_File(argv[2], &len);
        if(len == -1) {
            fprintf(stderr, "Can not open input file.\n");
            return EXIT_FAILURE;
        }
        long n_comp = 0;
        Array_Shellsort(arr, len, &n_comp);
	    printf("%ld\n", n_comp);
        long saved = Array_Save_To_File(argv[3], arr, len);
        free(arr);
        if(saved == -1) {
            fprintf(stderr, "Can not open output file.\n");
            return EXIT_FAILURE;
        } else if(saved == -2) {
            return EXIT_FAILURE;
        }
        
        return EXIT_SUCCESS;
    }
    
    if(strcmp(argv[1], "-l") == 0){
        long n_comp = 0;
        Node *head = List_Load_From_File(argv[2]);
        Node *temp = head;
        Node *prev = NULL;

        head = List_Shellsort(head, &n_comp);
        printf("%ld\n", n_comp);
        List_Save_To_File(argv[3], head);
	    if(List_Save_To_File(argv[3], head) == -1) {
            fprintf(stderr, "Can not open output file.\n");
            return EXIT_FAILURE;
        }
        /*for (Node* curr = head; curr != NULL; curr = curr -> next) 
        {
            printf("%ld\n", curr -> value);
        }*/
        for(temp = head;temp != NULL;)
        {
            prev = temp;
            temp = temp -> next;
            free(prev);
        }
        return EXIT_SUCCESS;
    }


    return EXIT_FAILURE;
}