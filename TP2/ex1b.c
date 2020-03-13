#include "unistd.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "stdio.h"

int main(int argc, char* argv[])
{
  int ficheiro_original = open(argv[1], O_RDONLY);
  int ficheiro_destino = open(argv[2], O_WRONLY | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR); //Vê o que as flags fazem
  if(ficheiro_destino == -1)
  {
    printf("Erro ao criar ficheiro!\n");
    return -1;
  }
  char buffer[64]; //Buffer de 64 bytes
  int byteslidos, tamanhobytes = 0;
  for(;;) //Este for é exatamente igual ao do ex1a.c, a unica diferença é que o write está a escrever os contéudos
  {       //Num ficheiro novo e nao no output do terminal como no ex1a.c
    byteslidos = read(ficheiro_original, buffer, sizeof(buffer));
    if(byteslidos <= 0)
    {
      break;
    }
    write(ficheiro_destino, buffer, byteslidos);
    tamanhobytes += byteslidos;
  }
  printf("Número de bytes lidos: %d\n", tamanhobytes);
  return 0;
}
