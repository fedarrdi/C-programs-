#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char * base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(char *byte3)
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

char *base64_decode(char *byte4)
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


char *break_msg3(char *msg)
{
    char *package3 = malloc(3);
    char *out4 = malloc(4);
    if(!package3 || !out4) return NULL;

    for(int i = 0;i < 4;out4[i++] = 0);

    int n = strlen(msg);
    package3 = realloc(package3, n % 3);
    for(int i = n;i < n + 3;i++)
        package3[i] = 0;

    n += n % 3;

    int msg4_index = 0;
    char *msg4_out = malloc(n + n/3);
    if(!msg4_out) return NULL;

    for(int i = 0;i < n;i += 3)
    {
        package3[0] = msg[i];
        package3[1] = msg[i + 1];
        package3[2] = msg[i + 2];

        out4 = base64_encode(package3);
        for(int j = 0;j < 4;j++)
            msg4_out[msg4_index++] = out4[j];
    }
    return msg4_out;
}

char *decode_msg(char *encoded_msg)
{
    char *package4 = malloc(4);
    char *out3 = malloc(3);
    if(!package4 || !out3) return NULL;

    int m = strlen(encoded_msg);

    int n = (3 * m) / 4;

    char *out_msg3 = malloc(n);
    if(!out_msg3) return NULL;
    int msg3_index = 0;
    for(int i = 0;i < m;i+=4)
    {
        package4[0] = encoded_msg[i];
        package4[1] = encoded_msg[i + 1];
        package4[2] = encoded_msg[i + 2];
        package4[3] = encoded_msg[i + 3];

        out3 = base64_decode(package4);
        for(int j = 0;j < 3;j++)
            out_msg3[msg3_index++] = out3[j];
    }
    return out_msg3;
}

int main()
{
    char *encoded_msg = break_msg3("The human mind has a primitive ego defense mechanism that negates all realities.");

    int n = strlen(encoded_msg);
    for(int i = 0;i < n;i++)
        printf("%c", base64_chars[encoded_msg[i]]);
    printf("\n");

   char *decoded_msg = decode_msg(encoded_msg);

   int m = strlen(decoded_msg);
   for(int i = 0;i < m;i++)
       printf("%c", decoded_msg[i]);

   return 0;
}
