/*

   Convert from Celcius to Fahrenheit

*/

#include <stdio.h>

float to_celc(int);
float to_fahr(int);

int main(void)
{
    puts("\nFrom Celcius to Fahrenheit");
    printf("%20s%20s\n", "Celcius", "Fahrenheit");
    for (float c_temp = 0; c_temp <= 100; c_temp++)
    {
        printf("%20f%20f\n", c_temp, to_fahr(c_temp));
    }
    puts("\nFrom Fahrenheit to Celcius");
    printf("%20s%20s\n", "Fahrenheit", "Celcius");
    for (float f_temp = 32; f_temp <= 212; f_temp++)
    {
        printf("%20f%20f\n", f_temp, to_celc(f_temp));
    }
    
    return 0;
}

float to_fahr(int c_temp)
{
    return (float)(c_temp * 9 / 5) + (float)32;
}

float to_celc(int f_temp)
{
    return (float)((f_temp - 32) * 5) / (float)9;
}
