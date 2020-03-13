#include <fcntl.h>          //O split vai dividir um ficheiro em vários ficheiros com um nome do genero
#include <sys/stat.h>       //testaa, testab, testac, etc. Quando a segunda letra chegar a 'z', a primeira passa a 'b'
#include <sys/types.h>      //e a segunda volta a ser 'a'. Exemplo: testba, testbb e por ai a fora. Quando a segunda letra
#include "unistd.h"         //for novamente um 'z', passa de novo a 'a' e a primeira letra avança para a proxima.
#include "string.h"         //Exemplo: testca, testcb, etc
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("Error! Not enough arguments.\n");
    return -1;
  }
  char *prefixo = argv[1]; //O prefixo é o nome do documento original (que também foi passado como argumento ao split. Ex: split ficheiroteste ficheiroteste)
  int tamanho_prefixo = strlen(prefixo);
  char extensao[] = ".mrg"; //O enunciado pede que o nome do ficheiro criado ao utilizar este programa seja argv[1].mrg, .mrg é a extensao
  int tamanho_total = tamanho_prefixo + sizeof(extensao); //Tamanho total do nome do ficheiro merged(prefixo + extensao .mrg)
  char *nome_destino = malloc(tamanho_total);
  strcpy(nome_destino, prefixo); //Copia o prefixo argv[1] para a string nome_destino
  strcpy(nome_destino + tamanho_prefixo, extensao); //Copia a extensao para completar o nome_destino, ficando do genero argv[1].mrg
  int ficheiro_destino = open(nome_destino, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR); //Cria um ficheiro de nome argv[1].mrg
  if(ficheiro_destino == -1)
  {
    printf("Error creating file!\n");
    return -1;
  }
  char *nome_fonte = malloc(tamanho_prefixo + 2); //nome_fonte é o nome dos ficheiros que foram criados a partir do split (ex: testaa, testab, testac, etc)
  strcpy(nome_fonte, prefixo); //Copia o prefixo para a string nome_fonte
  nome_fonte[tamanho_prefixo + 0] = 'a'; //A seguir ao prefixo vêm as duas letras (ex: testaa)
  nome_fonte[tamanho_prefixo + 1] = 'a';
  char buffer[64];
  for(;;) //Este for vai abrir todos os ficheiros que foram criados pelo split e copiar o seu conteudo para um so ficheiro, o ficheiro merged (extensao .mrg)
  {
  int ficheiro_fonte = open(nome_fonte, O_RDONLY);
  if(ficheiro_fonte == -1)
  {
    return -1;
  }
  for(;;)
  {
    int bytesread = read(ficheiro_fonte, buffer, sizeof(buffer));
    if(bytesread <= 0)
    {
      break;
    }
    write(ficheiro_destino, buffer, bytesread);
  }
  close(ficheiro_fonte); //Se chegou ao fim, por exemplo, do ficheiro testaa, entao fecha esse ficheiro com o close e passa ao proximo (que seria testab)
  if(nome_fonte[tamanho_prefixo + 1] == 'z') //Se a segunda letra já chegou ao 'z', entao volta a ser 'a' e a primeira letra passa à proxima
  {                                          //Ex: testaz -> testba
    nome_fonte[tamanho_prefixo + 0]++;
    nome_fonte[tamanho_prefixo + 1] = 'a';
  }
  else //Senão a primeira letra mantem-se igual e a segunda passa à proxima (ex: testaa -> testab). Isto é feito para que o for abra todos os ficheiros
  {    //criados com o split e copie o conteudo deles todos para o ficheiro .mrg
    nome_fonte[tamanho_prefixo + 1]++;
  }
  }
}
