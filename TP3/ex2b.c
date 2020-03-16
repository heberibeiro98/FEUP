#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[], char *envp[])
{
  int i;
  pid_t pid;
  pid = fork();
  if(pid < 0)
  {
    printf("Error creating child process!\n");
  }
  else if(pid > 0) //Se pid retornar maior que 0, o programa executa o codigo do parent (que é o codigo dentro deste if)
  {
    FILE *ficheiro1 = fopen(argv[1], "w"); //Cria um ficheiro de nome argv[1] no modo Write ("w")
    if(ficheiro1 == NULL)
    {
      printf("Errro creating file!\n");
    }
    for(i = 0; envp[i] != 0; i++) //Enquanto nao chegar ao fim do array *envp[] (que termina em 0), imprime a string em cada posiçao
    {
      fprintf(ficheiro1, "%s\n", envp[i]);
    }
    fclose(ficheiro1);
  }
  else if(pid == 0) //Se pid retornar 0, o programa executa o codigo do child (que é o codigo dentro deste if)
  {
    FILE *ficheiro2 = fopen(argv[2], "w"); //Cria um ficheiro de nome argv[2] no modo Write ("w")
    if(ficheiro2 == NULL)
    {
      printf("Error creating file!\n");
    }
    for(i = 0; envp[i] != 0; i++) //Enquanto nao chegar ao fim do array *envp[] (que termina em 0), imprime a string em cada posiçao
    {
      fprintf(ficheiro2, "%s\n", envp[i]);
    }
    fclose(ficheiro2);
  }
  //Tanto o codigo do parent como o codigo do child vao ser executados, o sistema operativo é que decide qual deles vai ser executado primeiro
  //e o primeiro a executar retorna o valor apropriado para executar o que ainda nao executou (para se verificarem ambos os ifs)
  return 0;
}
