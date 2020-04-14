#include "stdio.h"
#include "pthread.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writelock = PTHREAD_COND_INITIALIZER;
int reading = 0;
int m, n;

void readlock()
{
  pthread_mutex_lock(&mutex1);
  reading = 1;
}

void readunlock()
{
  pthread_mutex_lock(&mutex2);
  reading = 0;
  pthread_cond_signal(&writelock);
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
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
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    while(reading == 1)
    {
      pthread_cond_wait(&writelock, &mutex2);
    }
    pthread_mutex_unlock(&mutex2);
    m++;
    n++;
    pthread_mutex_unlock(&mutex1);
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
