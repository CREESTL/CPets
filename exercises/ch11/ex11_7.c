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
 *   There should be 2 versions of the main file. The original one
 *   and the one with all changes from temp file applied.
 *   If there is already a new version of main file, it should be updated next.
 *
 */

/**
 * TODO
 * 1. Remove debug puts
 * 2. Update new main file instead of main (if exists)
 * 3. Test with float amounts
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* File storing the initial state */
#define main_file "exercises/ch11/main.dat"
/* File to read updates from */
#define temp_file "exercises/ch11/temp.dat"
/* File to store updated info */
#define new_main_file "exercises/ch11/new_main.dat"
/* Temprorary buffer file */
#define buf_file "exercises/ch11/buf.dat"
/* Name of file to be removed */
#define del_file "exercises/ch11/del.dat"

#define USE_ORIG_MAIN 0
#define USE_NEW_MAIN 1

#define MAX_NAME 100

/**
 * Checks if file is empty
 * @file Pointer to the start of file
 */
bool check_empty(FILE *file)
{
    int trash;
    /* Need at least one scan to see the EOF */
    fscanf(file, "%d", &trash);
    if (feof(file))
    {
        rewind(file);
        return true;
    }
    rewind(file);
    return false;
}

/**
 * Choose whether to use an original main file (first run)
 * or a new main file from previous run
 * Returns 0 if use original main file
 * Returns 1 if use new main file
 */
unsigned choose_main_file(void)
{
    FILE *file;
    if ((file = fopen(new_main_file, "r")) != NULL)
    {
        /* In order to use new main file, it should exist and not be empty */
        if (!check_empty(file))
        {
            fclose(file);
            puts("USING NEW MAIN");
            return USE_NEW_MAIN;
        }
    }
    if ((file = fopen(main_file, "r+")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", main_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        fclose(file);
        puts("USING ORIG MAIN");
        return USE_ORIG_MAIN;
    }
}


/**
 * Counts workers in new main file
 * @chosen_file Old main or new main file to use
 */
int count_workers(const unsigned chosen_file)
{

    int count = 0;
    FILE *file;
    switch (chosen_file)
    {
        case USE_ORIG_MAIN:
            file = fopen(main_file, "r");
            break;
        case USE_NEW_MAIN:
            file = fopen(new_main_file, "r");
            break;
    }
    if (file == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", USE_NEW_MAIN ? new_main_file : main_file);
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
void remember_workers(double old_amounts[], const int workers_num)
{
    FILE *file = fopen(new_main_file, "r");
    if (file == NULL)
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
 * @from Main file to read from
 * @temp_amount Worker's amount from temp file
 * @prev_acc_count Account number of the previous worker in main file
 * @chosen_file Old main or new main file to use
 */
void update_and_copy(FILE *from, const double *temp_amount, const int prev_acc_count, const unsigned chosen_file)
{

    puts("");
    /**
     * Remember workers that are already in new main file
     * To not overwrite them again
     */
    int workers_num = count_workers(chosen_file);
    double old_amounts[workers_num];
    remember_workers(old_amounts, workers_num);

    rewind(from);

    FILE *to;
    switch (chosen_file)
    {
        case USE_ORIG_MAIN:
            to = fopen(new_main_file, "w");
            break;
        case USE_NEW_MAIN:
            to = fopen(buf_file, "w");
            break;
    }
    if (to == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", USE_NEW_MAIN ? buf_file : new_main_file);
        fclose(from);
        exit(EXIT_FAILURE);
    }
    else
    {

        int acc_num;
        char name[MAX_NAME];
        double amount;
        /* Copy all workers before the current one */
        for (int i = 0; i < prev_acc_count; i++)
        {
            fscanf(from, "%d%s%lf", &acc_num, name, &amount);

            /* If worker was in previous version of new main file - leave his old amount */
            if (acc_num <= workers_num)
            {
                if (i == 0)
                {
                    /* Do not print new line before first worker */
                    // TODO bug here, on 2nd run old_amounts[0] = 777 instead of 1000
                    fprintf(to, "%d %s %lf", acc_num, name, old_amounts[i]);
                    puts("AAA");
                }
                else
                {
                    fprintf(to, "\n%d %s %lf", acc_num, name, old_amounts[i]);
                    puts("BBB");
                }
            }
            else
            {
                fprintf(to, "\n%d %s %lf", acc_num, name, amount);
                puts("CCC");
            }
        }

        /* Copy the current worker with updated amount */
        fscanf(from, "%d%s%lf", &acc_num, name, &amount);
        double new_amount = amount + *temp_amount;
        if (new_amount < 0)
        {
            puts("Resulting amount cannot be negative");
            fclose(from);
            fclose(to);
            remove(buf_file);
            remove(del_file);
            exit(EXIT_FAILURE);
        }
        if (prev_acc_count == 0)
        {
            /* Do not print new line before first worker */
            fprintf(to, "%d %s %lf", acc_num, name, new_amount);
            puts("DDD");
        }
        else
        {
            fprintf(to, "\n%d %s %lf", acc_num, name, new_amount);
            puts("EEE");
        }

        /* Copy the rest of the workers */
        while (!feof(from))
        {
            fscanf(from, "%d%s%lf", &acc_num, name, &amount);
            fprintf(to, "\n%d %s %lf", acc_num, name, amount);
            puts("FFF");
        }
        

        /* If buf was used - rename it to new main and delete previous new main */
        if (chosen_file == USE_NEW_MAIN)
        {
            rename(new_main_file, del_file);
            rename(buf_file, new_main_file);
        }
    }

    remove(del_file);
    fclose(to);
}

/**
 * Update worker's data in main file
 * @temp_acc_num Number of worker's account from temp file
 * @temp_amount Worker's amount from temp file
 * @chosen_file Old main or new main file to use
 */
void update_main(const int *temp_acc_num, const double *temp_amount, const unsigned chosen_file)
{

    FILE *from;
    switch (chosen_file)
    {
        case USE_ORIG_MAIN:
            from = fopen(main_file, "r");
            break;
        case USE_NEW_MAIN:
            from = fopen(new_main_file, "r");
            break;
    }
    if (from == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", USE_NEW_MAIN ? new_main_file : main_file);
        exit(EXIT_FAILURE);
    }
    if (check_empty(from))
    {
        puts("File is empty!");
        fclose(from);
        exit(EXIT_FAILURE);
    }

    rewind(from);

    /* The account num previous to the matched one */
    unsigned prev_acc_count = 0;

    /* Indicates that worker from temp file was found in main file */
    bool found = false;

    /* Search for a worker */
    while (!feof(from))
    {
        int acc_num;
        char name[MAX_NAME];
        double amount;

        fscanf(from, "%d%s%lf", &acc_num, name, &amount);
        if (*temp_acc_num == acc_num)
        {
            /* Current worker from temp file is found in main file */
            found = true;
            update_and_copy(from, temp_amount, prev_acc_count, chosen_file);
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
        fclose(from);
        exit(EXIT_FAILURE);
    }

    fclose(from);
}

int main(void)
{

    FILE *temp_ptr;

    unsigned chosen_file = choose_main_file();

    if ((temp_ptr = fopen(temp_file, "r")) == NULL)
    {
        printf("[ERROR] Cannot read '%s' file!\n", temp_file);
        exit(EXIT_FAILURE);
    }
    else
    {

        if (check_empty(temp_ptr))
        {
            puts("File is empty!");
            fclose(temp_ptr);
            exit(EXIT_FAILURE);
        }

        while (!feof(temp_ptr))
        {
            int acc_num;
            double amount;

            read_from_temp(temp_ptr, &acc_num, &amount);
            update_main(&acc_num, &amount, chosen_file);
        }
    }

    fclose(temp_ptr);
    remove(buf_file);
    return 0;
}