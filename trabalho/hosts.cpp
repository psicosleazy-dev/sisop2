#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ASLEEP 0
#define AWAKEN 1
#define M 19


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

HOSTS* tabela[M];

void initialize_table()
{
    int i;
    for (i=0;i<M;i++)
	tabela[i] = NULL;
}

int create_key(){
    return 1 + rand() % 18;
}

void inserir(HOST host){
    HOSTS* newhost = NULL;
    int indice = create_key();
    newhost = (HOSTS*) calloc(1, sizeof(HOSTS));
    strcpy(newhost->host.hostname,host.hostname);
    strcpy(newhost->host.macadd,host.macadd);
    strcpy(newhost->host.ipadd,host.ipadd);
    tabela[indice] = newhost;
}
/*
void imprime(){
    HOSTS* node;
    for(int i = 0; i < M; i++){
        if(tabela[i] != NULL){
            for(node = tabela[i]; node != NULL; node = node->next){
                printf("Table[%d] - type: %d text: %s\n", i, node->type, node->text);
            }
        }
    }

}*/

void remove(char* ipadd){
    HOSTS* node;
    for(int i = 0; i < M; i++)
        if(tabela[i] != NULL)
            if(strcmp(tabela[i]->host.ipadd,ipadd)==0){
		free(tabela[i]);
		tabela[i] == NULL;
		break;
	    }
}

int main(){
    
    return 0;
}
