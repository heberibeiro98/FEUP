#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
  int i;
  printf("Argumentos:\n");
  for(i = 0; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  printf("\n");
  printf("Variáveis de ambiente:\n");
  while(*envp != 0) //O array das variáveis de ambiente é NULL-terminated, ou seja, a sua ultima posição tem um 0
  {                 //Então este ciclo vai correr até eu chegar à ultima posição, percorrendo assim as variaveis de ambiente todas
    printf("%s\n", *envp); //Imprime a variavel de ambiente atual
    *(envp++); //Alternativamente podia ser usado um for em vez de um while e envp[i] em vez de *(envp++)
  }
  return -1;
}
