#include <stdio.h>
#include <stdlib.h>

static const char * base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_decode(char *byte3)
{
    char *byte4 = malloc(4);
    if(!byte4) return NULL;

    for(int i = 0;i < 4; byte4[i++] = 0);

    int byte4_byte_index = 0, byte4_bit_index = 0;
    for(int i = 0;i < 3;i++)
    {
        char curr_byte3 = byte3[i];

        for(int byte3_bit_index = 0;byte3_bit_index < 8;byte3_bit_index++)
        {

            char byte3_curr_bit = (curr_byte3 & (1 << byte3_bit_index)) >> byte3_bit_index;
            byte4[byte4_byte_index] |= byte3_curr_bit << byte4_bit_index++;

            if(byte4_bit_index == 6)
            {
                byte4_byte_index ++;
                byte4_bit_index = 0;
            }
        }
    }

    return byte4;
}


char *base64_encode(char *byte4)
{
    char *byte3 = malloc(3);
    if(!byte3) return NULL;

    for(int i = 0;i < 3; byte3[i++] = 0);

    int byte3_byte_index = 0, byte3_bit_index = 0;

    for(int i = 0;i < 4;i++)
    {
        char curr_byte4 = byte4[i];
        for(int byte4_bit_index = 0;byte4_bit_index < 6;byte4_bit_index++)
        {
            char byte4_curr_bit = ((curr_byte4 & (1 << byte4_bit_index)) >> byte4_bit_index);
            byte3[byte3_byte_index] |= byte4_curr_bit << byte3_bit_index++;

            if(byte3_bit_index == 8)
            {
                byte3_byte_index++;
                byte3_bit_index = 0;
            }
        }
    }

    return byte3;
}

int main()
{
    char *msg = "Hey";
    char *base64_msg = base64_decode(msg);

    for(int i = 0;i < 4;i++)
        printf("%d ", base64_msg[i]);

    printf("\n");

    for(int i = 0;i < 4;i++)
        printf("%c", base64_chars[base64_msg[i]]);

    printf("\n");

    char *encoded_msg = base64_encode(base64_msg);
    
    for(int i = 0;i < 3;i++)
        printf("%c", encoded_msg[i]);

    return 0;

}
