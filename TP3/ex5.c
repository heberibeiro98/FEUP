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
  char *args[] = {"gcc", argv[1]}; //Os argumentos passados a execve é como se estivessemos a compilar um programa no terminal (ex: gcc test.c, em que test.c é o argv[1])
  execve("/usr/bin/gcc", args, envp); //Ver man execve
  return 0;
}

//Basicamente este programa é tal e qual o exercicio 4, mas sem criar um child process.
