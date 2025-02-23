#include <stdio.h>
#include <stdlib.h>

int main() {
    double *grades = NULL;
    double grade, sum = 0.0;
    int count = 0, capacity = 5;
    int allocs = 0, frees = 0;

    // Allocate initial memory for 5 grades
    grades = (double *)malloc(capacity * sizeof(double));
    if (!grades) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    allocs++;

    printf("Enter a list of grades below where each grade is separated by a newline character.\n");
    printf("After the last grade is entered, enter a negative value to end the list.\n");

    while (scanf("%lf", &grade) && grade >= 0) {
        if (count == capacity) {
            // Increase capacity by 5
            capacity += 5;
            double *new_grades = (double *)realloc(grades, capacity * sizeof(double));
            if (!new_grades) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(grades);
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

    if (count > 0) {
        double average = sum / count;
        printf("The average of %d grades is %f.\n", count, average);
        for (int i = 0; i < count; i++) {
            printf("%d. The grade of %f is %s the average.\n", i + 1, *(grades + i), (*(grades + i) >= average) ? ">=" : "<");
        }
    } else {
        printf("The average of 0 grades is 0.000000.\n");
    }

    // Free allocated memory
    free(grades);
    frees++;

    printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, capacity * (int)sizeof(double));

    return 0;
}
