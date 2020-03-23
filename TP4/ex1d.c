#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>                               //A unica diferença deste programa em relaçao ao ex1c.c
                                                  //é que agora o resultado é retornado por cada thread em vez
typedef struct                                    //de ser guardado num array global
{
  int a, b;
} operandos;

typedef void*(*func)(void*);

void* add(void *arg)
{
  long res;                         //res é do tipo long porque o terminal dava warnings se fosse do tipo
  operandos t = *(operandos*)arg;   //int(apesar do programa funcionar na mesma)
  res = t.a + t.b;
  return (void *)res; //Era ao fazer este cast que o terminal dava warnings. O cast para (void *) é necessario
}                     //devido ao funcionamento da pthread_join (ver man pthread_join)

void* sub(void *arg)
{
  long res;
  operandos t = *(operandos*)arg;
  res = t.a - t.b;
  return (void *)res;
}

void* multi(void *arg)
{
  long res;
  operandos t = *(operandos*)arg;
  res = t.a * t.b;
  return (void *)res;
}

void* divi(void *arg)
{
  long res;
  operandos t = *(operandos*)arg;
  res = t.a / t.b;
  return (void *)res;
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  int i;
  void *resultado; //Esta variavel é utilizada como argumento em pthread_join (ver man pthread_join)
  pthread_t thread[4];
  operandos aux;
  func fun[4];
  char ops[5] = {'+', '-', '*', '/', '\0'}; //Este array serve apenas para imprimir o sinal certo em cada operaçao no fim do programa
  sscanf(argv[1], "%d", &aux.a);
  sscanf(argv[2], "%d", &aux.b);
  fun[0] = &add;
  fun[1] = &sub;
  fun[2] = &multi;
  fun[3] = &divi;
  for(i = 0; i < 4; i++) //Mesma logica das alineas anteriores
  {
    pthread_create(&(thread[i]), 0, fun[i], &aux);
  }
  for(i = 0; i < 4; i++) //Mesma logica das alineas anteriores, agora com um print de cada operaçao dentro do ciclo
  {
    pthread_join(thread[i], &resultado); //O segundo argumento (&resultado), faz com que o valor retornado da thread seja armazenado na variavel "resultado"
    printf("%d %c %d = %ld\n", aux.a, ops[i], aux.b, (long)resultado);
  }
  return 0;
}
