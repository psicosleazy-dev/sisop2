#include<stdio.h>
#include<stdlib.h>
#define ASLEEP 0
#define AWAKEN 1

using namespace std;

typedef struct host{
    char* hostname;
    char* macadd;
    char* ipadd;
    int status;
} HOST;

typedef struct hosts{
    HOST host;
    struct hosts *next;
}HOSTS;

int initialize_list()
{
    HOSTS* head = NULL;
    head = (HOSTS *) malloc(sizeof(HOSTS));
    if(head == NULL)
        return 1;
    return 0;
}

void push(HOSTS* head, HOST host) {
    HOSTS* current = head;
    while (current->next != NULL)
        current = current->next;

    /* now we can add a new variable */
    current->next = (HOSTS*) malloc(sizeof(HOSTS));
    current->next->host = host;
    current->next->next = NULL;
}

int main(){
    return 0;
}
