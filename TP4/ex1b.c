#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct //definiçao de uma estrutura onde vao ser guardados os valores dos operandos a e b para duas das threads
{
  int a, b;
} operandos;

typedef void*(*func)(void*); //Tal como no ex1a.c, definiçao do tipo de funçao para que se criem as seguintes funçoes

void* add(void *arg)
{
  operandos t = *(operandos*)arg; //cast do argumento passado no pthread_join para o tipo operandos, para que se possam aceder aos valores a e b dentro da struct
  printf("%d + %d = %d\n", t.a, t.b, t.a + t.b);
}

void* sub(void *arg)
{
  operandos t = *(operandos*)arg;
  printf("%d - %d = %d\n", t.a, t.b, t.a - t.b);
}

void* multi(void *arg)
{
  int *t = (int*)arg; //casto do argumento passado no pthread_join para o tipo (int) para que se possa usar o apontador t para aceder ao array criado na funçao main
  printf("%d * %d = %d\n", t[0], t[1], t[0] * t[1]);
}

void* divi(void *arg)
{
  int *t = (int*)arg;
  printf("%d / %d = %d\n", t[0], t[1], t[0] / t[1]);
}

int main(int argc, char *argv[])
{
  if(argc < 3) //Se os operandos nao forem passados ao chamar o programa na terminal, o programa termina
  {
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  int i;
  int arr[2]; //Como o enunciado pede para duas das threads utilizarem um array em vez da struct, cria-se um array de dimensao 2 para armazenar os operandos
  pthread_t thread[4];
  operandos aux; //Variavel da estrutura criada para aceder aos operandos a e b dentro dela
  func fun[4];
  sscanf(argv[1], "%d", &aux.a); //Guarda argv[1] em "a" na estrutura como um inteiro
  sscanf(argv[2], "%d", &aux.b); //Guarda argv[1] em "b" na estrutura como um inteiro
  sscanf(argv[1], "%d", &arr[0]); //Guarda argv[1] em arr[0] como um inteiro
  sscanf(argv[2], "%d", &arr[1]); //Guarda argv[1] em arr[1] como um inteiro
  fun[0] = &add;
  fun[1] = &sub; //Mesma funçao que o exercicio anterior
  fun[2] = &multi;
  fun[3] = &divi;
  for(i = 0; i < 2; i++) //Este for vai passar como argumento para duas das threads a variavel aux que é utilizada para aceder à estrutura
  {
    pthread_create(&(thread[i]), 0, fun[i], &aux);
  }
  for(i = 2; i < 4; i++) //Este for vai passar como argumento para as outras duas threads o array criado para armazenar os dois operandos
  {
    pthread_create(&(thread[i]), 0, fun[i], &arr);
  }
  for(i = 0; i < 4; i++) //Tal como no exercicio anterior, este for serve para garantir que as threads acabam o seu trabalho antes do programa terminar
  {
    pthread_join(thread[i], 0);
  }
  return 0;
}
