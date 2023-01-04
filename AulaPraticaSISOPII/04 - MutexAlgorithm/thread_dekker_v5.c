#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

void dormir () {
  usleep((rand() % 11) * 100000); /* dormir 0, 100, 200, ..., 1000 milissegundos */
}

/* Variaveis compartilhadas */
int p1wantstoenter, p2wantstoenter;
int turn;

static void * thread_process1(void *arg)
{
    int thread_id = 1;

    printf("Hello! I'm thread %d!\n", thread_id);

    do {
      p1wantstoenter = 1;
      while (p2wantstoenter == 1) {
	      if (turn == 2) {
		      /* liberar a intencao de entrar */;
	      	      p1wantstoenter = 0;
	              while (turn == 2) /* nao fazer nada */;
	              /* indicar de novo que queremos entrar */
                      p1wantstoenter = 1;
	       }
      }
      printf("I'm thread %d and I'm entering my critical region!\n", thread_id);
      dormir();
      printf("I'm thread %d and I'm leaving my critical region!\n", thread_id);

      turn = 2; p1wantstoenter = 0; /* indicar que saimos da secao critica */
    } while (1);

    return NULL;
}

static void * thread_process2(void *arg)
{
    int thread_id = 2;
 
    printf("Hello! I'm thread %d!\n", thread_id);

    do {
      p2wantstoenter = 1;
      while (p1wantstoenter == 1) {
	      if (turn == 1) {
		      /* liberar a intencao de entrar */;
              	      p2wantstoenter = 0;
                      while (turn == 1) /* nao fazer nada */;
                      /* indicar de novo que queremos entrar */
                      p2wantstoenter = 1;
	      }
      }
      printf("I'm thread %d and I'm entering my critical region!\n", thread_id);
       dormir();
      printf("I'm thread %d and I'm leaving my critical region!\n", thread_id);
      
      turn = 1; p2wantstoenter = 0; /* indicar que saimos da secao critica */
    } while (1);

    return NULL;
}


int main(int argc, char **argv)
{
    int thread_num, ret;
    pthread_t tinfo_process1, tinfo_process2;
    pthread_attr_t attr;
    void *res;
    
    ret = pthread_attr_init(&attr);
    
    p1wantstoenter = p2wantstoenter = 0; /* inicializar as variaveis de secao critica */
    turn = 1;

    ret = pthread_create(&tinfo_process1, &attr, &thread_process1, NULL);
    ret = pthread_create(&tinfo_process2, &attr, &thread_process2, NULL);

    ret = pthread_attr_destroy(&attr);
    
    ret = pthread_join(tinfo_process1, &res);
    printf("Joined with thread id %lu\n", tinfo_process1);
    free(res);

    ret = pthread_join(tinfo_process2, &res);
    printf("Joined with thread id %lu\n", tinfo_process2);
    free(res);

    exit(EXIT_SUCCESS);
}
