#include "crc8.h"
#include <stdint.h>
#include <string.h>

// Source: https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code
// Date of access: 2020-03-20

#define POLYNOMIAL 0xD8 /* 11011 followed by 0's */
typedef uint8_t crc;

#define WIDTH (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc crcSlow(uint8_t const message[], int nBytes) {
  crc remainder = 0;

  /*
   * Perform modulo-2 division, a byte at a time.
   */
  for (int byte = 0; byte < nBytes; ++byte) {
    /*
     * Bring the next byte into the remainder.
     */
    remainder ^= (message[byte] << (WIDTH - 8));

    /*
     * Perform modulo-2 division, a bit at a time.
     */
    for (uint8_t bit = 8; bit > 0; --bit) {
      /*
       * Try to divide the current data bit.
       */
      if (remainder & TOPBIT) {
        remainder = (remainder << 1) ^ POLYNOMIAL;
      } else {
        remainder = (remainder << 1);
      }
    }
  }

  /*
   * The final remainder is the CRC result.
   */
  return (remainder);
}

// Adapter.
unsigned char crc8(char *str) {
  size_t bytes = strlen(str);
  return crcSlow((unsigned char *)str, bytes);
}
