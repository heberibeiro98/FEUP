#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
  if(argc < 2) //Se tiver menos que dois argumentos, o programa termina (o programa tem de ser chamado da forma ./a.out test.c)
  {
    printf("Not enough arguments!\n");
    return -1;
  }
  pid_t pid;
  int exit;
  pid =  fork(); //Cria child process
  if(pid < 0)
  {
    printf("Error creating child process!\n");
    return -1;
  }
  else if(pid > 0) //Se pid > 0, executa o codigo do parent
  {
    wait(&exit); //Espera que o codigo da child termine antes de prosseguir (fazer o printf)
    printf("Process terminated! (exit code = %d)\n", WEXITSTATUS(exit));
  }
  else if(pid == 0) //Se pid == 0, executa codigo da child
  {
    char *args[] = {"gcc", argv[1]}; //Os argumentos passados a execve é como se estivessemos a compilar um programa no terminal (ex: gcc test.c, em que test.c é o argv[1])
    execve("/usr/bin/gcc", args, envp); //Ver man execve
    return 2; //Retorna 2 como exit code
  }
  return 0;
}
