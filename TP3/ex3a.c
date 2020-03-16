#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid, parent, child;
  pid = fork();
  if(pid < 0)
  {
    printf("Error creating child process!\n");
    return -1;
  }
  else if(pid == 0) //Se pid == 0, executa o código da child
  {
    parent = getppid(); //getppid() retorna o pid do parent
    child = getpid(); //getpid() retorna o pid do próprio processo onde esta funçao foi chamada (neste caso, processo child)
    printf("-------------------------\n");
    printf("Printing Child's code!\n");
    printf("Child's PID: %d\n", child);
    printf("Parent's PID: %d\n", parent);
    printf("-------------------------\n");
  }
  return 0;
}
