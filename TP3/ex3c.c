#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])                    //Este codigo é quase todo igual ao ex3b.c, com a exceçao de umas
{                                                   //poucas linhas que sao as unicas que vou comentar
  pid_t pid, parent, child, grandchild;
  int exit;
  child = fork();
  if(child < 0)
  {
    printf("Error creating child process!\n");
    return -1;
  }
  else if(child > 0)
  {
    wait(&exit); //wait vai fazer com que este processo espere que o seu child acabe de executar para continuar a executar o resto do codigo
    printf("-----------------------\n");
    printf("Printing Parent's code: \n");
    printf("Child's PID = %d\n", child);
    printf("Child's exit code: %d\n", WEXITSTATUS(exit)); //como argumento passei o endereço de int exit (ver man wait) e imprimo o exit code da child utilizando WEXITSTATUS(exit) (ver manual)
    printf("-----------------------\n");
  }
  else if(child == 0)
  {
    grandchild = fork();
    if(grandchild < 0)
    {
      printf("Error creating grandchild process!\n");
    }
    else if(grandchild > 0)
    {
      wait(&exit); //Tal como acima, este processo vai esperar que a sua child (grandchild do processo original neste caso) acabe de executar
      pid = getpid();
      parent = getppid();
      printf("-----------------------\n");
      printf("Printing Child's code: \n");
      printf("Child's PID: %d\n", pid);
      printf("Parent's PID: %d\n", parent);
      printf("Grandchild's exit code: %d\n", WEXITSTATUS(exit)); //E aqui vai imprimir o seu exit code
      printf("-----------------------\n");
    }
    else if(grandchild == 0)
    {
      pid = getpid();
      parent = getppid();
      printf("-----------------------\n");
      printf("Printing Grandchild's code: \n");
      printf("Grandchild's PID: %d\n", pid);
      printf("Child(Grandchild's parent) PID: %d\n", parent);
      printf("-----------------------\n");
      return 3; //Este return 3 é o exit code da grandchild. Fiz com que retornasse 3 pois a child retorna 2, logo faz sentido que grandchild retorne o numero a seguir
    }           //embora eles nao especifiquem no enunciado, por isso na verdade podia retornar o que quisesse
    return 2; //Este return 2 é o exit code da child. Retorna 2 porque é que o enunciado pede
  }
  return 0;
}
