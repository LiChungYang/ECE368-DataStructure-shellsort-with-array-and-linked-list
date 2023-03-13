#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
/*
void prindebuglist(Node *head)
{
   for (Node* curr = head; curr != NULL; curr = curr -> next) 
    {
        printf("debug%ld\n", curr -> value);
    } 
}*/

static int bubbleSort(Node **start, Node **contrl_inter, Node **prestart, Node **precontrl, Node **initial) 
{ 
    int confirm = 0;
    /* Checking for empty list */
    /*if (start == NULL) 
    {
        return 0;
    }*/

    if (((*start)->value) > ((*contrl_inter)->value))
    {
        /*printf("beforeswap\n");
        printf("start%ld\n", ((*start) -> value));
        printf("contrl_inter%ld\n", (*contrl_inter) -> value);
        printf("prestart%ld\n", (*prestart) -> value);
        printf("precontrlt%ld\n", (*precontrl) -> value);*/

        if((*start) -> next == (*contrl_inter))
        {
            (*prestart) -> next = (*contrl_inter);
            (*start) -> next = (*contrl_inter) -> next;
            (*contrl_inter) -> next = (*start);
        }
        else
        {
            Node *temptemp = (*start) -> next;
            (*start) -> next = (*contrl_inter) -> next;
            (*contrl_inter) -> next = temptemp;
            (*prestart) -> next = (*contrl_inter);
            (*precontrl) -> next = (*start);
        }

        Node *tempfinal = (*start);
        (*start) = (*contrl_inter);
        (*contrl_inter) = tempfinal;

        if((*prestart) -> value == 0)
        {
            (*initial) = (*start);
        }

        confirm = 1;
    }
    return confirm;
}
  

Node *List_Load_From_File(char *filename)
{
    int size;
    FILE *fptr;
    Node *head = NULL;
    Node *temp = NULL;
    // which conect the nodes to create a linked list
    Node *conect_p = NULL;

    fptr = fopen(filename, "rb");

    if (fptr == NULL)
        {
            size = 0;
            return NULL;
        }
    else
        {
            fseek(fptr, 0, SEEK_END);
	        int byte_size = ftell(fptr);
            rewind(fptr);
            size = byte_size / (sizeof(long));
        }

    //create same number of nodes as the number of long in the file
    long readtemp;
    
    for(int i = 0; i < size; i++)
    {
        temp = (Node*)malloc(sizeof(Node));
        fread(&readtemp, sizeof(long), 1, fptr);

        temp -> value =  readtemp;
        temp -> next = NULL;

        //first time when the linked list is empty
        if (head == NULL)
        {
            head = temp;
        }
        //conect the nodes to create linked list
        else
        {
            conect_p = head;
            while (conect_p -> next != NULL)
            {
                conect_p = conect_p -> next;
            }
            conect_p -> next = temp;
        }
    }
    fclose(fptr);
    return head;
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE *fptr;
    int size;
    Node *temp = list;
    fptr = fopen(filename, "wb");

    if (fptr == NULL)
        {
            size = 0;
            return 0;
        }
    else
        {
            fseek(fptr, 0, SEEK_END);
	        int byte_size = ftell(fptr);
            rewind(fptr);
            size = byte_size / (sizeof(long));
        }

    while (temp != NULL)
    {
        fwrite(temp, sizeof(Node*), 1, fptr);
        temp = temp->next;
    }
    fclose(fptr);
    //printf("%d", size);
    return size;
}

Node *List_Shellsort(Node *list, long *n_comp)
{
    int bigest_numinter= 0;
    int size = 0;
    int swapped = 1;
    int count = 0;

    Node *head = list;
    Node *prehead = list;
    Node *storehead = list;
    Node *temp_tail = list;
    Node *pre_temp_tail = list;

    Node *dumtemp = (Node*)malloc(sizeof(Node));
    dumtemp -> value = 0;
    head = dumtemp -> next;
    prehead = dumtemp;

    for (Node* curr = list; curr != NULL; curr = curr -> next) 
    {
        size = size + 1;
    }

    while ((bigest_numinter * 3 + 1) < size)
    {
        bigest_numinter = bigest_numinter * 3 + 1;
    }

    for (int k = bigest_numinter; k > 0; k = (k - 1) / 3)
    {
        //printf("k%d\n", k);
        swapped = 1;
        while(swapped)
        {
            swapped = 0;
            temp_tail = storehead;
            head = storehead;
            prehead = dumtemp;
            for (int countinter = 0; countinter < (k); countinter++)
            {
                pre_temp_tail = temp_tail;
                temp_tail = temp_tail -> next;
            }

            //for(int x = 0; x < size; x = x + 1 + k)
            //while (temp_tail != NULL;)
            for(Node *ttail = temp_tail;ttail != NULL;ttail = ttail -> next)
            {
                //printf("1\n");

                count = bubbleSort(&head, &ttail, &prehead, &pre_temp_tail, &list);
                (*n_comp)++;
                swapped += count;

                if(prehead == dumtemp)
                {
                    storehead = head;
                }

                //prindebuglist(list);

                prehead = head;
                head = head -> next;
                pre_temp_tail = ttail;
                //temp_tail = temp_tail -> next;
            }
        }
    }
    free(dumtemp);
    return list;
}