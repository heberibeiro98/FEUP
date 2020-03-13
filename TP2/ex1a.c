#include "unistd.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "stdio.h"

int main(int argc, char* argv[])
{
  int ficheiro = open(argv[1], O_RDONLY);
  char buffer[64]; //Buffer de 64 bytes
  int byteslidos, tamanhobytes = 0;
  for(;;) //Ciclo infinito que vai ser cancelado pelo break dentro do if
  {       //Basicamente estou a evitar usar while(1) e a evitar inicializar a variavel byteslidos para fazer um while com condiçao
    byteslidos = read(ficheiro, buffer, sizeof(buffer)); //Vai ler o ficheiro, guardar os seus conteudos no buffer e retorna
    if(byteslidos <= 0)                                  //o numero de bytes lidos, que vai ser guardado na variavel "byteslidos"
    {
      break;
    }
    write(STDOUT_FILENO, buffer, byteslidos); //Imprime para o output do terminal o que está escrito no buffer(ou seja, o que estava) escrito no ficheiro
    tamanhobytes += byteslidos; //tamanhobytes armazena o numero total de bytes lidos pelo read, razao pela qual ele é incrementado pelo numero de bytes lidos a cada ciclo
  }
  printf("Número de bytes lidos: %d\n", tamanhobytes); //Imprime bytes lidos no ficheiro
}
