#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
  FILE *ficheiro = fopen(argv[1], "w"); //Cria um ficheiro de nome argv[1] no modo Write ("w")
  while(*envp != 0) //Enquanto nao chegar ao fim do array *envp[] (que termina em 0), imprime a string em cada posiçao
  {
    fprintf(ficheiro, "%s\n", *envp);
    *(envp++);
  }
  fclose(ficheiro);
  return 0;
}
