#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    double *grades = NULL;
    int capacity = 5; // Start with space for 5 doubles (40 bytes)
    int count = 0;
    double grade;
    double sum = 0.0;

    // Heap usage tracking
    int num_allocs = 0;
    int num_frees = 0;
    size_t total_bytes = 0;
    void *current_heap = NULL;

    printf("Enter a list of grades below where each grade is separated by a newline character.\n");
    printf("After the last grade is entered, enter a negative value to end the list.\n");

    while (scanf("%lf", &grade) == 1)
    {
        if (grade < 0)
        {
            break;
        }

        // First grade: allocate initial 40 bytes
        if (count == 0)
        {
            grades = (double *)malloc(40); // Initial 40 bytes
            if (grades == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            current_heap = grades;
            num_allocs++;
            total_bytes += 40;
            printf("Allocated 40 bytes to the heap at %p.\n", (void *)grades);
        }

        // Store the grade and print message
        grades[count] = grade;
        sum += grade;
        printf("Stored %.6f in the heap at %p.\n", grade, (void *)&grades[count]);
        count++;

        // Check if heap is full after storing
        if (count == capacity)
        {
            printf("Stored %d grades (%d bytes) to the heap at %p.\n",
                   count, count * 8, current_heap);
            printf("Heap at %p is full.\n", current_heap);

            // Allocate new space with 40 more bytes
            size_t new_size = (capacity + 5) * sizeof(double); // 80 bytes total
            double *temp = (double *)malloc(new_size);
            if (temp == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                free(grades);
                num_frees++;
                return 1;
            }

            printf("Allocated %zu bytes to the heap at %p.\n",
                   new_size, (void *)temp); // Show total new size (80 bytes)

            // Copy data and print message
            memcpy(temp, grades, count * sizeof(double));
            printf("Copied %d grades from %p to %p.\n",
                   count, current_heap, (void *)temp);

            // Free old space and print message
            printf("Freed %zu bytes from the heap at %p.\n",
                   capacity * sizeof(double), current_heap);

            free(grades);
            num_frees++;
            num_allocs++;
            total_bytes += new_size; // Add the full 80 bytes to total

            grades = temp;
            current_heap = temp;
            capacity += 5; // Increase capacity by 5 doubles (40 bytes)
        }
    }

    if (count > 0)
    {
        double average = sum / count;

        printf("The average of %d grades is %f.\n", count, average);
        for (int i = 0; i < count; i++)
        {
            printf("%d. The grade of %.6f is %s the average.\n",
                   i + 1,
                   grades[i],
                   (grades[i] >= average) ? ">=" : "<");
        }

        printf("Freed %zu bytes from the heap at %p.\n",
               capacity * sizeof(double), current_heap);
        free(grades);
        num_frees++;
    }
    else
    {
        printf("The average of 0 grades is 0.000000.\n");
    }

    printf("total heap usage: %d allocs, %d frees, %zu bytes allocated\n",
           num_allocs, num_frees, total_bytes);

    return 0;
}
