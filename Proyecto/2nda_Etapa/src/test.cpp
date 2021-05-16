#include "../headers/DM_Cache.h"

int main(void) {
  //unsigned long long hexadecimalADecimal(char *cadenaHexadecimal, int longitud) {
    //   unsigned long long decimal = 0;
    //   int potencia = 0;
    //   for (int i = longitud - 1; i >= 0; i--) {
    //     int valorActual = caracterHexadecimalADecimal(cadenaHexadecimal[i]);
    //     unsigned long long elevado = pow(BASE, potencia) * valorActual;
    //     decimal += elevado;
    //     potencia++;
    //   }
    //   return decimal;
    // }
  DM_Cache myCache = DM_Cache(1, 16, 4, 13, 13);
  size_t blockAssign = myCache.get_block_address(17);
  size_t tag_value = myCache.get_tag_value(17);
  std :: cout << blockAssign << std :: endl;
  std :: cout << tag_value << std :: endl;
}