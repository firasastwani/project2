#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    double *grades = NULL;
    double grade, sum = 0.0;
    int count = 0, capacity = 5;
    int allocs = 0, frees = 0;

    // Open the input file specified by the command-line argument
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Failed to open input file: %s\n", argv[1]);
        return 1;
    }

    // Allocate initial memory for 5 grades
    grades = (double *)malloc(capacity * sizeof(double));
    if (!grades)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }
    allocs++;

    // Read grades from the file
    while (fscanf(file, "%lf", &grade) == 1 && grade >= 0)
    {
        if (count == capacity)
        {
            // Increase capacity by 5
            capacity += 5;
            double *new_grades = (double *)realloc(grades, capacity * sizeof(double));
            if (!new_grades)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                free(grades);
                fclose(file);
                return 1;
            }
            grades = new_grades;
            allocs++;
            frees++;
        }
        // Store the grade
        *(grades + count) = grade;
        sum += grade;
        count++;
    }

    fclose(file);

    if (count > 0)
    {
        double average = sum / count;
        printf("The average of %d grades is %f.\n", count, average);
        for (int i = 0; i < count; i++)
        {
            printf("%d. The grade of %f is %s the average.\n", i + 1, *(grades + i), (*(grades + i) >= average) ? ">=" : "<");
        }
    }
    else
    {
        printf("The average of 0 grades is 0.000000.\n");
    }

    // Free allocated memory
    free(grades);
    frees++;

    printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, capacity * (int)sizeof(double));

    return 0;
}
