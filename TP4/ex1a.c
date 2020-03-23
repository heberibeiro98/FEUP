#include <pthread.h>
#include <stdio.h>

int a, b; //Definiçao das variaveis globais

typedef void*(*func)(void*); //Definiçao de um tipo de funçao que vai ser utilizado para escrever as funçoes utilizadas pelas threads

void* add(void *arg) //Funçao que executa a adiçao
{
  printf("%d + %d = %d\n", a, b, a + b);
}

void* sub(void *arg) //Funçao que executa a subtraçao
{
  printf("%d - %d = %d\n", a, b, a - b);
}

void* multi(void *arg) //Funçao que executa a multiplicaçao
{
  printf("%d * %d = %d\n", a, b, a * b);
}

void* divi(void *arg) //Funçao que executa a divisao
{
  printf("%d / %d = %d\n", a, b, a / b);
}

int main(int argc, char *argv[])
{
  if(argc < 3) //Se tiver menos de 3 arguemntos, retorna erro (para alem do ./a.out sao necessarios os dois valores para as variaveis globais)
  {
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  int i;
  pthread_t thread[4];
  func fun[4]; //Criaçao de um array do tipo func (criado pelo typedef void*(*func)(void*)), para que possamos passar a cada thread a funçao que tem de executar
  sscanf(argv[1], "%d", &a); //Guarda argv[1] na  variavel global "a" como um inteiro
  sscanf(argv[2], "%d", &b); //Guarda argv[2] na  variavel global "b" como um inteiro
  fun[0] = &add; //Coloca em cada posiçao do array fun uma funçao das criadas
  fun[1] = &sub;
  fun[2] = &multi;
  fun[3] = &divi;
  for(i = 0; i < 4; i++) //Neste for sao criadas as 4 threads e para cada uma vai ser passada umas das funçoes, sem qualquer argumento para essas funçoes
  {
    pthread_create(&(thread[i]), 0, fun[i], 0);
  }
  for(i = 0; i < 4; i++) //Este for garante que o programa espera que cada thread criada acabe a sua funçao antes de terminar o programa
  {                     //caso contrario o programa poderia terminar antes que as threads acabassem de executar o seu codigo
    pthread_join(thread[i], 0);
  }
  return 0;
}
