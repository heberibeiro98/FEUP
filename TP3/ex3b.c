#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid, parent, child, grandchild;
  child = fork();
  if(child < 0)
  {
    printf("Error creating child process!\n");
    return -1;
  }
  else if(child > 0) //Se child > 0, executa o código do parent
  {
    printf("Child's PID = %d\n", child); //child contem o valor retornado por fork() e esse valor é o pid da child
  }
  else if(child == 0) //Executa o codigo da child
  {
    grandchild = fork(); //Faz um novo fork, criando assim um processo child da propria child (a.k.a grandchild)
    if(grandchild < 0)
    {
      printf("Error creating grandchild process!\n");
    }
    else if(grandchild > 0) //Executa o código da child (parent da grandchild)
    {
      pid = getpid(); //Retorna o valor do processo que chama a funçao, neste caso retorna o pid da child
      parent = getppid(); //Retorna o valor do parent (processo original)
      printf("Child's PID: %d\n", pid);
      printf("Parent's PID: %d\n", parent);
    }
    else if(grandchild == 0) //Executa o codigo da grandchild (child da child)
    {
      pid = getpid(); //Retorna o valor do processo que chama a funçao, neste caso retorna o pid da grandchild
      parent = getppid(); //Retorna o valor do parent da grandchild (child)
      printf("Grandchild's PID: %d\n", pid);
      printf("Child(Grandchild's parent) PID: %d\n", parent);
    }
  }
  return 0;
}
