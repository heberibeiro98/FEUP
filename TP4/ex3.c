#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef void*(*func)(void*);                            //Este programa é basicamente igual ao ex2.c, com a diferença que agora
                                                        //o numero de threads é passado como arguemnto em vez de ser 3
void* threadID(void* arg)
{
  long t = *(int *)arg;
  printf("TID: %ld\n", syscall(SYS_gettid)); //Imprime o Thread ID da thread a executar
  return (void *)t;
}

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("Not enough arguments!\n");
    return -1;
  }
  int *arr, i, aux;
  sscanf(argv[1], "%d", &aux); //Guarda argv[1] como inteiro em aux
  void *ret; //Variavel criada para ser usada como arguemnto em pthread_join
  pthread_t *thread;
  thread = malloc(sizeof(pthread_t)*aux); //Alocaçao de memoria para o array thread conforme o numero de threads que passarmos como argumento
  if(thread == NULL)
  {
    printf("Error allocating memory!\n");
    return -1;
  }
  arr = malloc(sizeof(int)*aux); //Alocaçao de memoria para o array arr(que armazena o numero de cada thread) conforme o numero de threads que passarmos como argumento
  if(arr == NULL)
  {
    printf("Error allocating memory!\n");
    return -1;
  }
  arr[0] = 1;
  for(i = 1; i < aux; i++) //Este for vai preencher o array por ordem (ex: 1, 2, 3, 4, 5, etc)
  {
    arr[i] = arr[i-1] + 1;
  }
  for(i = 0; i < aux; i++) //Este for cria cada thread e passa como argumento o numero dessa thread (atravas de arr[i])
  {
    pthread_create(&(thread[i]), 0, threadID, &(arr[i]));
  }
  for(i = 0; i < aux; i++) //Este for garante que cada thread termina e imprime o seu return value (o numero da thread)
  {
    pthread_join(thread[i], &ret);
    printf("Thread return value: %ld\n", (long)ret);
  }
  return 0;
}
