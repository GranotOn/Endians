#include <stdio.h>

typedef union
{
    unsigned char p[sizeof(unsigned long)];
    unsigned long i;
} bytes;
/**
 * We will store '1' and check the first address.
 * If it is 1 - the machine is big endian - we will return 1
 * If it is 0 - the machine is small endian - we will return 0
 **/
int is_big_endian()
{
    int x = 1; // if big endian than 0x01 in last byte

    unsigned char *y = (unsigned char *)&x; // 0x01

    return (int)(y[0] == 0);
}


/**
 * We will use a union to break and construct an unsinged long.
 **/
unsigned long merge_bytes(unsigned long x, unsigned long int y)
{

    bytes bx;
    bytes by;

    // let w = sizeof(x) = sizeof(y)
    bx.i = x; // bx.p now contains a 'w' byte array.
    by.i = y; // by.p now contains a 'w' byte array.

    bytes z; // We will return z.i after we construct z.p

    int big_endian = is_big_endian();

    for (int idx = 0; idx < sizeof(unsigned long); ++idx)
    { // Set each array with the apropriate byte
        z.p[idx] = (big_endian) ? ((idx <= 3) ? bx.p[idx] : by.p[idx]) 
                                : ((idx <= 3) ? by.p[idx] : bx.p[idx]);
    }

    return z.i;
}


unsigned long put_byte(unsigned long x, unsigned char b, int i)
{
    bytes z; // We will return z.i after changing z.p
    z.i = x; // copy x.

    int idx = (is_big_endian()) ? i : sizeof(x) - 1 - i;
    
    // let w = sizeof(x) * 8.
    z.p[idx] = b; // Replace the w/8 -1 - i byte with b.

    
    return z.i;
}