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
  int i, aux = 0;
  char buffer[sizeof(aluno.st) + sizeof(aluno.grades)]; //Mesma explicaçao que no ex3a.c
  if(argc < 2)
  {
    printf("Errror! Not enough arguments.\n");
    return -1;
  }
  int ficheiro = open(argv[1], O_RDONLY); //argv[1] contem o nome do ficheiro criado em ex3a.c (és tu que tens de passar o nome como argumento no terminal)
  if(ficheiro == -1)                      //Isto abre esse ficheiro como read-only
  {
    printf("Error opening file!\n");
    return -1;
  }
  read(ficheiro, buffer, sizeof(buffer)); //Armazena no array buffer os conteudos do ficheiro (nome nota nota nota)
  for(i = 0; i < sizeof(aluno.st); i++)  //Vai armazenar em aluno.st o nome do aluno, elemento a elemento (letra a letra),
  {                                     //basicamente o inverso do que foi feito em ex3a.c
    aluno.st[i] = buffer[i];
  }
  aux += sizeof(aluno.st); //Mesma lógica do ex3a.c
  for(i = 0; i < sizeof(aluno.grades); i++) //De novo, processo inverso do que se fez em ex3a.c, com um cast para int agora
  {                                         //pois queres os valores das notas como inteiros (array grades é do tipo int)
    aluno.grades[i] = (int)buffer[aux+i];
  }
  printf("Student %s - Grades: %d %d %d\n", aluno.st, aluno.grades[0], aluno.grades[1], aluno.grades[2]); //Finalmente imprime-se tudo usando os elementos da estrutura
}
