#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 61
#define BUFFER 1
#define LLIST 2

typedef struct link
{
    char *data;
    struct link *next;
} Link;


Link *newLink(char data[]);
void readText(int userChoice, void* pointer);
void readTextToBuffer(char* pointer);
void readTextToLL(Link* pointer);

void printTextFromLL(Link* head);
Link* insertAfter(Link* p, char* data); // assume p is not NULL
void printText(int userChoice, void* pointer);
void printTextFromBuffer(char *pointer);
int LinkedListLength(Link * head);

Link *newLink(char* data)
{
    Link *p = (Link*)malloc(sizeof(Link));
    p->data= data;
    p->next= NULL;
    return p;
}

void readText(int userChoice, void* pointer)
{
    int size;
    if (userChoice == 1)
    {
        readTextToBuffer((char*)pointer);
    }
    else if (userChoice == 2)
    {
        readTextToLL((Link*)pointer);
    }
}
void readTextToBuffer(char* pointer)
{
    int currBufferSize = LENGTH+15;
    char c;
    int i=0;
    while ((c = getchar ()) != EOF)
    {
        if (c == '\n')//Ignoring line drop
        {
            continue;
        }
        pointer[i]=c;
        i++;
        if (i==currBufferSize)//Increase the data structure as needed while recording
        {
            currBufferSize+=LENGTH;
            pointer = (char *)realloc(pointer, currBufferSize);
        }
    }
    pointer[i]='\0'; //Flag for the end of the text
}
void readTextToLL(Link* pointer)
{
    Link* currPointer = pointer;//To save the initial pointer
    char c;
    char* curNode = (char*)calloc(LENGTH,sizeof(char));
    int i = 0;
    while ((c = getchar ()) != EOF)
    {
        if (c == '\n')//Ignoring line drop
        {
            continue;
        }
        curNode[i]=c;
        i++;
        if (!currPointer) //Organization of nods on the list
        {
            currPointer = newLink(curNode);
        }
        if(i == (LENGTH-1)) //Each node contains 60 characters
        {
            currPointer = insertAfter(currPointer,curNode);
            curNode = (char*)calloc(LENGTH,sizeof(char));
            i=0;
        }
        continue;
    }
    insertAfter(currPointer, curNode);//The last node not necessarily contains 60 characters
    printTextFromLL(pointer);
}


Link* insertAfter(Link* p, char* data) // assume p is not NULL
{
    Link *q = newLink(data);
    q->next= p->next;
    p->next= q;
    return q;

}
void printText(int userChoice, void* pointer)
{
    if (userChoice == 1)
    {
        printTextFromBuffer((char*)pointer);
    }
    else if (userChoice == 2)
    {
        printTextFromLL(pointer);
    }
}

void printTextFromBuffer(char *pointer)
{
    int i = 0;
    while (pointer[i] != '\0') //As long as the print did not reach the flag
    {
        putchar(pointer[i]);
        i++;
        if (i % (LENGTH-1) == 0)//Every 60 characters go down a line
        {
            printf("\n");
        }
    }
}

void printTextFromLL(Link* node)
{
    while (node != NULL)
    {
        node = node->next;
        printf("%s",node->data);
        printf("\n");//Every 60 characters go down a line
    }
}

int main ()
{
    int userChoice;
    char *p;
    printf("Please select a method for implementing the data userChoice:\n 1.A single buffer.\n 2.A Linked list.\n");
    while((userChoice != BUFFER)&&(userChoice != LLIST))        // loop until a legal number is entered
    {
        scanf("%d", &userChoice); //Do if 1 then buffer and if 2 then list
        if((userChoice!=BUFFER)&&(userChoice!=LLIST))
            printf("please pick a valid number\n");
    }
    printf("Please input text:\n");
    if(userChoice==BUFFER)
    {
        p = (char*)calloc(LENGTH,sizeof(char));
        readText(userChoice, p);
    }
    else if (userChoice == LLIST)
    {
        Link **p = NULL;
        readText(userChoice, &p);
    }
    if (!p)
    {
        printf("There is not enough memory. Sorry.\n");
        exit(1);
    }
    else
        printText(userChoice,p);
    free(p); //free the allocated sentry
    return(0);
}
