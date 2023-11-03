/**
 *
 *   Workers' transactions tracking.
 *   There are 2 files: main file and temporary file.
 *   Main file stores data about workers:
 *   - Account number
 *   - Name
 *   - Current balance
 *   Temp file stores data about workers' funds transfers:
 *   - Account number
 *   - Transfered amount
 *       - Positive amount indicates that worker got a new order from clients
 *       - Negative amount indicates that worker got payment from clients
 *
 *   Workers data is stored in ascending order of account numbers (keys) in both files
 *   
 *   Main file cannot be empty
 *
 *   The program should read from temp file and update main file.
 *   There should be 2 versions of the main file. The one that does not contain
 *   data from temp file and the one that does.
 *
 */

/**
 * TODO
 * 1. When there is worker in main file but no worker in temp file - just copy
 *    worker to the next version of main file
 * 2. Pass to `update_main()` by value?
 * 3. Use consts for parameters
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define main_file "exercises/ch11/main.dat"
#define temp_file "exercises/ch11/temp.dat"
#define new_main_file "exercises/ch11/new_main.dat"

#define MAX_NAME 100

/**
 * Checks if file is empty
 * @file Pointer to the start of file
*/
void check_empty(FILE *file)
{
    int trash;
    /* Need at least one scan to see the EOF */ 
    fscanf(file, "%d", &trash);
    if (feof(file))
    {
        puts("File is empty!");
        rewind(file);
        exit(EXIT_FAILURE);
    }
    rewind(file);
}

/**
 * Counts workers in new main file
*/
int count_workers(void)
{

    int count = 0;
    FILE *file;
    if ((file = fopen(new_main_file, "r")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", new_main_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Check if empty */
        int trash;
        fscanf(file, "%d", &trash);
        if (feof(file))
        {
            fclose(file);
            return 0;
        }
        rewind(file);

        int acc_num;
        char name[MAX_NAME];
        double amount;
        while (!feof(file))
        {
            fscanf(file, "%d%s%lf", &acc_num, name, &amount);
            count++;
        }
    }
    fclose(file);
    return count;
}

/**
 * Remember amount each of workers has in new main file
 * @old_amounts Array of amounts to fill
 * @workers_num Number of workers in file
*/
void remember_workers(int old_amounts[], int workers_num)
{
    FILE *file;
    if ((file = fopen(new_main_file, "r")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", new_main_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        int acc_num;
        char name[MAX_NAME];
        double amount;
        /* Remember amounts workers have */
        for (int i = 0; i < workers_num; i++)
        {
            fscanf(file, "%d%s%lf", &acc_num, name, &amount);
            old_amounts[i] = amount;
        }
    }
    fclose(file);
}

/**
 * Read worker's data from temp file
 * @file Pointer to the start of temp file;
 * @acc_num Number of worker's account to read
 * @name Worker's name to read
 * @amount Worker's amount (income or order)
 */
void read_from_temp(FILE *file, int *acc_num, double *amount)
{
    char trash[MAX_NAME];
    fscanf(file, "%d%s%lf", acc_num, trash, amount);
}

/**
 * Update one worker's data in main file and copy the whole
 * file into another file
 * @file Pointer to the start of current (old) main file;
 * @temp_acc_num Number of worker's account from temp file
 * @temp_amount Worker's amount from temp file
 * @prev_acc_count Account number of the previous worker in main file
 */
void update_and_copy(FILE *file, int *temp_acc_num, double *temp_amount, int prev_acc_count)
{
    FILE *new_main_ptr;


    /**
     * Remember workers that are already in new main file
     * To not overwrite them again
     */
    int workers_num = count_workers();
    double old_amounts[workers_num];
    remember_workers(old_amounts, workers_num);

    rewind(file);

    if ((new_main_ptr = fopen(new_main_file, "w")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", new_main_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        int acc_num;
        char name[MAX_NAME];
        double amount;
        /* Copy all workers before the current one */
        for (int i = 0; i < prev_acc_count; acc_num++)
        {
            fscanf(file, "%d%s%lf", &acc_num, name, &amount);

            /* If worker was in previous version of new main file - leave his old amount */
            if (acc_num < workers_num)
            {
                fprintf(new_main_ptr, "%d %s %lf\n", acc_num, name, old_amounts[i]);
            }
            else
            {
                fprintf(new_main_ptr, "%d %s %lf\n", acc_num, name, amount);
            }
        }

        /* Copy the current worker with updated amount */
        fscanf(file, "%d%s%lf", &acc_num, name, &amount);
        fprintf(new_main_ptr, "%d %s %lf\n", acc_num, name, amount + *temp_amount);

        /* Copy the rest of the workers */
        while (!feof(file))
        {
            fscanf(file, "%d%s%lf", &acc_num, name, &amount);
            fprintf(new_main_ptr, "%d %s %lf\n", acc_num, name, amount);
        }
    }

    /* Now `file` points to the end of main file */

    fclose(new_main_ptr);
}

/**
 * Update worker's data in main file
 * @file Pointer to the start of current (old) main file;
 * @temp_acc_num Number of worker's account from temp file
 * @temp_amount Worker's amount from temp file
 */
void update_main(FILE *file, int *temp_acc_num, double *temp_amount)
{
    int acc_num;
    char name[MAX_NAME];
    double amount;
    
    rewind(file);

    /* The account num previous to the matched one */
    unsigned prev_acc_count = 0;

    /* Indicates that worker from temp file was found in main file */
    bool found = false;

    /* Search for a worker */
    while (!feof(file))
    {
        fscanf(file, "%d%s%lf", &acc_num, name, &amount);
        if (*temp_acc_num == acc_num)
        {
            /* Current worker from temp file is found in main file */
            found = true;
            update_and_copy(file, temp_acc_num, temp_amount, prev_acc_count);
        }
        else
        {
            prev_acc_count++;
        }
    }
    if (!found)
    {
        /* If current worker from temp file is not found in main file - throw */
        printf("No worker with account number %d found in main file!\n", *temp_acc_num);
        exit(EXIT_FAILURE);
    }
}

int main(void)
{

    int acc_num;
    double amount;

    FILE *temp_ptr, *main_ptr;
    if ((temp_ptr = fopen(temp_file, "r")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", temp_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        check_empty(temp_ptr);

        if ((main_ptr = fopen(main_file, "r+")) == NULL)
        {
            printf("[ERROR] Cannot read '%s' file!\n", main_file);
            exit(EXIT_FAILURE);
        }
        else
        {
            check_empty(main_ptr);

            /* Ok to operate both files */
            while (!feof(temp_ptr))
            {
                read_from_temp(temp_ptr, &acc_num, &amount);
                update_main(main_ptr, &acc_num, &amount);
            }
        }
    }

    fclose(temp_ptr);
    fclose(main_ptr);

    return 0;
}