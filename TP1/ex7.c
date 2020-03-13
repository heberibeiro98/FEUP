#include "stdio.h"

int main()
{
  char *c;
  __uint16_t i = 0x2411; /*uint16_t é um tipo de variavel em que a variavel tem 2 bytes (16 bits) - o numero que escolhi foi aleatorio*/
  c = (char *)&i; /*cast do endereço de i para o tipo (char *), que é um apontador de carateres/bytes. Isto permite-nos percorrer o endereço de i byte a byte incrementando ou decrementando c como feito nos ifs*/
  if(*(c+1) == 0x24 || *c == 0x11) /* *(c+1) é equivalente a ir para o proximo byte do endereço e *c é o primeiro byte  (pensa em COMP). Se este if se verificar, é little endian (relembra o que é isso)*/
  {
    printf("Little endian\n");
    printf("%#x - LSB\n", *c);
    printf("%#x - MSB\n", *(c+1));
  }
  else
  {
    printf("Big endian\n");
    printf("%#x - MSB\n", *c);
    printf("%#x - LSB\n", *(c+1));
  }
}
