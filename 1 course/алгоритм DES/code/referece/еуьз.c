#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int input_string(uint8_t *str)
{
    uint8_t c;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        str[i] = c;
        i++;
    }
    // str[i] = '\0';
    return i;
}

int main()
{
    uint8_t str[255];
    int lenght = input_string(str);
    printf("%s\n", str);
    uint64_t hexstr = 0x0000000000000000;
    for (int i = 0; i < lenght; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            hexstr <<= 1;
            hexstr |= ((str[i] >> j) & 1);
            // printf("%d", (str[i] >> j) & 1);
            // }
            // printf("%0x\n", hexstr);
        }
    }

    printf("\nNumber: %016llx\n", hexstr);

    char text[lenght];
    int temp = 0;
    for (int i = 0; i < lenght; i++)
    {
        temp = 0;
        for (int j = 0; j < 8; j++)
        {
            printf("%d", (hexstr >> j + i * 8) & 0x0000000000000001);
            temp += pow(2, j) * ((hexstr >> j + i * 8) & 0x0000000000000001);
        }
        printf("\n%d - %c\n", temp, temp);
        text[lenght - i - 1] = temp;
    }
    printf("%s", text);

    return 0;
}

// int main() {
//     unsigned char bin[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64}; // "Hello World" в бинарном виде
//     char str[12]; // достаточный размер для строки "Hello World"
//     for(int i = 0; i < 11; i++) {
//         sprintf(&str[i], "%c", bin[i]);
//     }
//     printf("%s\n", str);
//     return 0;
// }

// // int main()
// // {
// //     uint64_t hex_num;
// //     printf("Enter a hexadecimal number: ");
// //     scanf("%x", &hex_num);
// //     printf("Decimal equivalent is: %lld\n", hex_num);
// //     return 0;
// // }