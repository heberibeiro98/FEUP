#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char buffer[64]; //Buffer de 64 bytes
  int byteslidos, tamanhobytes = 0;
  int save = dup(STDOUT_FILENO); //Estou a guardar o file descriptor do STDOUT_FILENO para o utilizar mais tarde(ele é responsável pelo output no terminal)
  if(argc < 2)                   //caso contrário não vou poder imprimir nada no fim do programa se a funçao a ser executada seja a do
  {                              //exercicio ex1b.c
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  int f1 = open(argv[1], O_RDONLY); //Abre o ficheiro original, dado pelo argv[1]
  if(argc >= 3) //Caso haja 3 ou mais argumentos, estamos na situaçao da funcionalidade deste programa ser a do ex1b.c
  {
    int f2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR); //Ve o que as flags fazem
    if(f2 != -1)                //Se o segundo ficheiro, dado por argv[2], foi criado com sucesso
    {                           //passamos o seu filedescriptor para o STDOUT_FILENO (dup2(f2, STDOUT_FILENO)), garantido assim que o resto do codigo funciona como
    dup2(f2, STDOUT_FILENO);   //é suposto, mas eliminando completamente a possibilidade de fazer output (tipo imprimir coisas no terminal)
  }                           //por isso mesmo é que fiz save do file descriptor do STDOUT_FILENO no inicio do programa, para o poder recuperar no fim
    else
    {
      printf("File already exists!\n");
      return -1;
    }
  }
  for(;;)
  {                                           //Este for é tal e qual o for do ex1a.c e ex1b.c, no entanto
    byteslidos = read(f1, buffer, sizeof(buffer));    //a funçao do STDOUT_FILENO depende de quantos argumentos foram passados                                              //se foram apenas passado 2 (./a.out nomedoficheiro), STDOUT_FILENO tem a sua funçao original
    if(byteslidos <= 0)                               //ou seja, o seu filedescriptor é o original e como nenhum ficheiro novo é criado, o conteudo do ficheiro original vai ser imprimido
    {                                                 //na terminal
      break;
    }                                                 //No entando, se foram passados 3 ou mais argumentos(./a.out nomedoficheirooriginal nomedoficheironovo)
    write(STDOUT_FILENO, buffer, byteslidos);         //STDOUT_FILENO perde o seu file descriptor original por causa do dup2(f2, STDOUT_FILENO) escrito acima
    tamanhobytes += byteslidos;                       //o que significa que STDOUT_FILENO tem agora o filedescriptor do ficheiro novo (f2), e por essa razao o programa
  }                                                   //vai funcionar como o programa do ex1b.c
  dup2(save, STDOUT_FILENO); //Nesta linha estou a recuperar o file descriptor do STDOUT_FILENO, garantido assim que posso voltar a executar output, como por exemplo, imprimir coisas no terminal
  printf("Número de bytes lidos: %d\n", tamanhobytes); //Este printf nao faria absolutamente nada se eu nao tivesse feito save do file descriptor do STDOUT_FILENO e o tivesse recuperado
  return 0;                                            //com a linha de codigo acima (dup2(save, STDOUT_FILENO) no caso da funcionalidade do programa ser a do ex1b.c)
}
