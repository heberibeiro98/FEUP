#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void* threadID(void* arg)
{
  long t = *(int *)arg; //O tipo da variavel é long pela mesma explicaçao dada em ex1d.c
  printf("TID: %ld  PID: %d\n", syscall(SYS_gettid), getpid());                //syscall(SYS_gettid) retorna o Thread ID(TID) da thread que chamou este systemcall
  return (void *)t;  //Retorna o numero da thread(passado como argumento)     //getpid() retorna o Process ID(PID) do processo que chamou este systemcall
}                                                                             //neste caso os PIDs vao ser todos iguais porque é o mesmo processo a executar
                                                                              //esse systemcall (todas as threads criadas pertencem ao mesmo processo neste caso)
int main(int argc, char *argv[])
{
  void *ret; //Esta variavel é utilizada como argumento em pthread_join (ver man pthread_join)
  pthread_t thread[3];
  int arr[3] = {1,2,3}; //Este array tem o proposito de enumerar as threads e é passado como argumento na criaçao das threads
  int i;
  for(i = 0; i < 3; i++)
  {
    pthread_create(&(thread[i]), 0, threadID, &(arr[i]));
  }
  printf("Main thread PID: %d\n", getpid()); //Este PID vai tambem ser igual aos das threads pela razao explicada acima
  for(i = 0; i < 3; i++)
  {
    pthread_join(thread[i], &ret); //O segundo argumento (&ret), faz com que o valor retornado da thread seja armazenado na variavel "ret"
    printf("Thread return value: %ld\n", (long)ret);
  }
  return 0;
}
