/*

   Recursive call to main

*/

int count = 0;

int main(void)
{
    printf("Count is: %d\n", count);
    count++;
    main();

}