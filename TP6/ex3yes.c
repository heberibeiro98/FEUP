#include "stdio.h"
#include "pthread.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writelock = PTHREAD_COND_INITIALIZER;

int m, n;
int nreaders = 0;

void readlock()
{
  pthread_mutex_lock(&mutex);
  nreaders++;
  pthread_mutex_unlock(&mutex);
}

void readunlock()
{
  pthread_mutex_lock(&mutex);
  nreaders--;
  if(nreaders == 0)
  {
    pthread_cond_signal(&writelock);
  }
  pthread_mutex_unlock(&mutex);
}

void *read(void *arg)
{
  for(int i = 0; i < 50000000; i++)
  {
    readlock();
    if((i%1000000) == 0)
    {
      printf("m = %d ; n = %d\n", m, n);
    }
    readunlock();
  }
  return 0;
}

void *write(void *arg)
{
  for(int i = 0; i < 50000000; i++)
  {
    pthread_mutex_lock(&mutex);
    while(nreaders > 0)
    {
      pthread_cond_wait(&writelock, &mutex);
    }
    m++;
    n++;
    pthread_mutex_unlock(&mutex);
  }
  return 0;
}

int main()
{
  m = 0;
  n = 0;
  pthread_t threads[4];
  for(int i = 0; i < 2; i++)
  {
    pthread_create(&(threads[i]), 0, read, 0);
  }
  for(int i = 2; i < 4; i++)
  {
    pthread_create(&(threads[i]), 0, write, 0);
  }
  for(int i = 0; i < 2; i++)
  {
    pthread_join(threads[i], 0);
  }
  for(int i = 2; i < 4; i++)
  {
    pthread_join(threads[i], 0);
  }
  printf("Valores finais: m = %d ; n = %d\n", m, n);
}
