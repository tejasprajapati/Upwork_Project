#define WIDTH           (8 * sizeof(char))
#define TOPBIT          (1 << (WIDTH - 1))
#define POLYNOMIAL      0x04C11DB7

/*
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 */

char crcSlow(char const *message, int nBytes)
{
    char remainder = 0;	
    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (int byte = 0; byte < nBytes; ++byte)
    {
        /*
         * Bring the next byte into the remainder.
         */
        remainder ^= (message[byte] << (WIDTH - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (char bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /*
     * The final remainder is the CRC result.
     */
    return (remainder);

}   /* crcSlow() */

//char crcFast(char const *message, int nBytes)
//{
//    char data;
//    char remainder = 0;
//
//    /*
//     * Divide the message by the polynomial, a byte at a time.
//     */
//    for (int byte = 0; byte < nBytes; ++byte)
//    {
//        data = message[byte] ^ (remainder >> (WIDTH - 8));
//        remainder = crcTable[data] ^ (remainder << 8);
//    }
//
//    /*
//     * The final remainder is the CRC.
//     */
//    return (remainder);
//
//}   /* crcFast() */