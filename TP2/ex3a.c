#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef char name[30];
typedef struct
{
  name st;
	int grades[3];
} test_t;

int main(int argc, char *argv[])
{
  test_t aluno;
  int i, aux;
  char buffer[sizeof(aluno.st) + sizeof(aluno.grades)]; //Buffer em que o seu tamanho é o tamanho do st
  if(argc < 6)                                          //mais o tamanho do array grades, ou seja, neste
  {                                                     //buffer vai ficar informaçao como pro exemplo
    printf("Error! Not enough arguments.\n");           //"Joao305570" que vai ser guardada no ficheiro
    return -1;
  }
  strncpy(aluno.st, argv[2], sizeof(aluno.st)); //Copia o argv[2] (nome do aluno), para a string aluno.st
  sscanf(argv[3], "%d", &aluno.grades[0]);      //Utilizei o strncpy porque esta funçao permite definir o numero de elementos
  sscanf(argv[4], "%d", &aluno.grades[1]);      //que queres copiar, evitando assim erros de falta de espaço no aluno.st
  sscanf(argv[5], "%d", &aluno.grades[2]);      //O sscanf guarda nas posiçoes do array grades as notas inseridas (argv[3], argv[4] e argv[5]) como inteiros
  int destino = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR); //Ve no man o que cada flag faz
  if(destino == -1)
  {
    printf("Error opening/creating file!");
    return -1;
  }
  for(i = 0; i < sizeof(aluno.st); i++) //Este for vai percorrer a string aluno.st elemento a elemento e guardar cada um no buffer, por ordem
  {
    buffer[i] = aluno.st[i];
  }
  aux = sizeof(aluno.st);                  //Apos ser guardado o nome no buffer, temos de inserir os valores armazenados no array grades logo a seguir
  for(i = 0; i < sizeof(aluno.grades); i++)//e é por essa razao que utilizei a variavel aux, assim no próximo ciclo for, estou a inserir as grades após
  {                                        //o nome que já foi inserido
    buffer[aux + i] = (char)aluno.grades[i];
  }
  write(destino, buffer, sizeof(buffer));
  return 0;
}
