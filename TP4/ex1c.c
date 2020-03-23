#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int resultados[4]; //Definiçao de um array global para armazenar os resultados das 4 operaçoes

typedef struct //Estrutura que armazena os dois operandos
{
  int a, b;
} operandos;

typedef void*(*func)(void*); //Mesma explicaçao que ex1a.c

void* add(void *arg)
{
  operandos t = *(operandos*)arg; //Cast do argmumento passado à thread para o tipo operandos para que se possa aceder aos valores de a e b
  resultados[0] = t.a + t.b;      //da estrutura dentro da funçao
}

void* sub(void *arg)
{
  operandos t = *(operandos*)arg;
  resultados[1] = t.a - t.b;
}

void* multi(void *arg)
{
  operandos t = *(operandos*)arg;
  resultados[2] = t.a * t.b;
}

void* divi(void *arg)
{
  operandos t = *(operandos*)arg;
  resultados[3] = t.a / t.b;
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  int i;
  pthread_t thread[4];
  operandos aux;
  func fun[4];
  sscanf(argv[1], "%d", &aux.a);
  sscanf(argv[2], "%d", &aux.b);
  fun[0] = &add;
  fun[1] = &sub;
  fun[2] = &multi;
  fun[3] = &divi;
  for(i = 0; i < 4; i++) //O resto do programa é muito parecido aos outros, tal como no ex1b.c é passada a variavel da estrutra como argumento
  {                      //para que a funçao a ser executada pela thread possa aceder aos operandos a e b
    pthread_create(&(thread[i]), 0, fun[i], &aux);
  }
  for(i = 0; i < 4; i++) //Mesma explicaçao das alineas anteriores
  {
    pthread_join(thread[i], 0);
  }
  printf("%d + %d = %d\n", aux.a, aux.b, resultados[0]);
  printf("%d - %d = %d\n", aux.a, aux.b, resultados[1]);  //Imprime os resultados de cada operaçao
  printf("%d * %d = %d\n", aux.a, aux.b, resultados[2]);
  printf("%d / %d = %d\n", aux.a, aux.b, resultados[3]);
  return 0;
}
