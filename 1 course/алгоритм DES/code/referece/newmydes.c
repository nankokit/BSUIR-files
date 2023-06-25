// подключение необходимых библиотек
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Таблица начальной перестановки (IP)
static char IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

// Таблица расширения (E)
static char E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

// Формирование C0 и D0 для ключа раунда
static char C0D0[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

// Сдвиг ключа раунда
static char iteration_shift[] = {
    /* 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16 */
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Сжатие ключа раунда
static char Pk[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

// Таблицы замены (S)
static char S[8][64] = {{/* S1 */
                         14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                         0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                         4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                         15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                        {/* S2 */
                         15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                         3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                         0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                         13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                        {/* S3 */
                         10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                         13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                         13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                         1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                        {/* S4 */
                         7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                         13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                         10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                         3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                        {/* S5 */
                         2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                         14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                         4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                         11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                        {/* S6 */
                         12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                         10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                         9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                         4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                        {/* S7 */
                         4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                         13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                         1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                         6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                        {/* S8 */
                         13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                         1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                         7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                         2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

// Таблица перестановки после S-замен
static char P[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};

// Таблица конечной перестановки (FP)
static char FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

// функция начальной перестановки
uint64_t first_permutation(uint64_t input)
{
    uint64_t init_perm_res = 0;
    for (int i = 0; i < 64; i++)
    {
        init_perm_res <<= 1;
        init_perm_res |= (input >> (64 - IP[i])) & 0x0000000000000001;
    }
    return init_perm_res;
}

// функция создания всех 16 ключей
void generate_keys(uint64_t key, uint64_t sub_key[16])
{
    int i, j;       // создание переменных для циклов
    uint32_t C = 0; // создание переменных для генерации раундовых ключей
    uint32_t D = 0;
    uint64_t C0D0table = 0;
    uint64_t temp_key = 0;
    // формирование начальной таблицы C0 D0
    for (i = 0; i < 56; i++)
    {
        C0D0table <<= 1;
        C0D0table |= (key >> (64 - C0D0[i])) & 0x0000000000000001;
        // приравнивание i биту C0D0table значение бита key под номером C0D0[i]
    }
    // разбиение C0D0table на два вектора для дальнейшего формирования ключей
    C = (uint32_t)((C0D0table >> 28) & 0x000000000fffffff);
    D = (uint32_t)(C0D0table & 0x000000000fffffff);
    // формирование 16 ключей
    for (i = 0; i < 16; i++)
    {
        // сдвиг С0 и D0 в соответствии с таблицей сдвигов
        for (j = 0; j < iteration_shift[i]; j++)
        {
            C = 0x0fffffff & (C << 1) | 0x00000001 & (C >> 27);
            D = 0x0fffffff & (D << 1) | 0x00000001 & (D >> 27);
        }

        temp_key = 0;
        temp_key = (((uint64_t)C) << 28) | (uint64_t)D;

        sub_key[i] = 0;
        for (j = 0; j < 48; j++) // занесение i-го раундового ключа в массив
        {
            sub_key[i] <<= 1;
            sub_key[i] |= (temp_key >> (56 - Pk[j])) & 0x0000000000000001;
        }
    }
}

// сеть Фейстеля
void Feistel(uint32_t *L, uint32_t *R, uint64_t sub_key[16], int i, char mode)
{
    char row, column; // создание паременных для работы с таблицами S-замен
    uint64_t s_input = 0;
    uint32_t s_output = 0;
    for (int j = 0; j < 48; j++)
    {
        s_input <<= 1;
        s_input |= (uint64_t)(((*R) >> (32 - E[j])) & 0x00000001);
    }
    // если режим шифрования, то ключи идут в порядке генерации, если режим дешифрования, то в обратном порядке
    // операция XOR R с K
    if (mode == 'd')
    {
        // если режим дешифрования
        s_input = s_input ^ sub_key[15 - i];
    }
    else
    {
        // если режим шифрования
        s_input = s_input ^ sub_key[i];
    }
    // S таблицы замен
    for (int j = 0; j < 8; j++)
    {
        // получение значениий строки и столбца
        row = (char)((s_input & (0x0000840000000000 >> 6 * j)) >> 42 - 6 * j);
        row = (row >> 4) | row & 0x01;

        column = (char)((s_input & (0x0000780000000000 >> 6 * j)) >> 43 - 6 * j);

        s_output <<= 4;
        s_output |= (uint32_t)(S[j][16 * row + column] & 0x0f);
    }
    uint32_t f_function_res = 0;
    for (int j = 0; j < 32; j++)
    {
        f_function_res <<= 1;
        f_function_res |= (s_output >> (32 - P[j])) & 0x00000001;
    }
    uint32_t temp = (*R);
    (*R) = (*L) ^ f_function_res;
    (*L) = temp;
}
// функция конечной перестановки
uint64_t last_permutation(uint64_t pre_output)
{
    uint64_t inv_init_perm_res = 0;
    for (int i = 0; i < 64; i++)
    {
        inv_init_perm_res <<= 1;
        inv_init_perm_res |= (pre_output >> (64 - FP[i])) & 0x0000000000000001;
    }
    return inv_init_perm_res;
}
// функция шифрования, на вход поступает бинарные 64 бита информации,
// 64 бита ключа и режим,  'e' = шифрация; 'd' = дешифрация
uint64_t des(uint64_t input, uint64_t key, char mode)
{
    int i, j;                   // создание переменных для циклов
    uint64_t sub_key[16] = {0}; // создание массива для хранения раундовых ключей
    uint32_t L = 0;             // создание переменных для сети Фейстеля
    uint32_t R = 0;
    // общие переменные алгоритма
    uint64_t pre_output = 0;
    // начальная перестановка
    input = first_permutation(input);

    L = (uint32_t)(input >> 32) & 0x00000000ffffffff;
    R = (uint32_t)input & 0x00000000ffffffff;
    // генерация всех раундовых ключей
    generate_keys(key, sub_key);

    for (i = 0; i < 16; i++)
        Feistel(&L, &R, sub_key, i, mode);

    pre_output = (((uint64_t)R) << 32) | (uint64_t)L;
    // конечная перестановка
    pre_output = last_permutation(pre_output);
    return pre_output;
}

// функция посимвольного ввода строки
int input_string(char *str)
{
    char c;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        str[i] = c;
        i++;
    }
    return i;
}
// перенос строки в тип uint64_t
uint64_t text_to_bin(char *str, int length)
{
    uint64_t hexstr = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            hexstr <<= 1;
            hexstr |= (str[i] >> j) & 1;
        }
    }
    return hexstr;
}
// функция ввода
uint64_t get_text(int max)
{
    rewind(stdin);
    int length = 0;
    char str[255];
    while (length > max || length < 1)
    {
        printf("Enter max %d symbols\n", max);
        length = input_string(str);
    }
    uint64_t input = text_to_bin(str, length);
    return input;
}
// функция шифрации
void encryption()
{
    int length = 0;
    char str[255];
    printf("Enter text for encryption\n");
    uint64_t input = get_text(8);
    printf("Enter key for encryption\n");
    uint64_t key = get_text(7);
    uint64_t result = des(input, key, 'e');
    printf("Encrypted: %016llx\n", result);
}
// функция дешифрации
void decryption()
{
    printf("Enter HEX text for decryption\n");
    uint64_t input;
    scanf("%llx", &input);
    if (input == 0xf2b6cd5136eb14ba)
        printf("the same\n");
    else
        printf("dolboeb\n");
    // uint64_t input = 0xf2b6cd5136eb14ba;
    printf("Enter key for decryption\n");
    uint64_t key = get_text(7);
    uint64_t result;
    result = des(input, key, 'd');
    printf("D: %016llx\n", result);
}

int main(int argc, const char *argv[])
{
    char mode;
    printf("Choose program mode\nEnter ''e'' for encryption\nEnter ''d'' for decryption\n");
    do
        scanf("%c", &mode);
    while (mode != 'e' && mode != 'd');
    if (mode == 'e')
        encryption();
    else
        decryption();

    // int i;
    // uint64_t input = 0x00000068656c6c6f;
    // uint64_t key = 0x0000000154000000;
    // uint64_t result = input;

    // result = des(input, key, 'e');
    // printf("E: %016llx\n", result);
    // result = des(result, key, 'd');
    // printf("D: %016llx\n", result);

    exit(0);
}