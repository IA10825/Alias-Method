#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#define SIZE 4


double random() {
    return (double)(rand()) / RAND_MAX;
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    double normalSize = 1.0 / SIZE;

    char names[SIZE + 1] = "ABCD";
    char aliases[SIZE + 1] = "~~~~";

    double dist[SIZE] = {0.01, 0.01, 0.01, 0.97 };
    double barriers[SIZE] = { 0 };

    while (1) {
        double* donor = NULL;
        double* recipient = NULL;
        for (int i = 0; i < SIZE; i++) {
            if (dist[i] < normalSize) {
                donor = dist + i;
                break;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            if (dist[i] > normalSize) {
                recipient = dist + i;
                break;
            }
        }
        if (donor == NULL || recipient == NULL) break;

        *(barriers + (donor - dist)) = (*donor) * 4;
        double donorLack = normalSize - (*donor);
        (*donor) += donorLack;
        (*recipient) -= donorLack;

        *(aliases + (donor - dist)) = *(names + (recipient - dist));
    }
    for (int i = 0; i < SIZE; i++) {
        if (barriers[i] == 0) {
            barriers[i] = 1;
        }
    }
    

    while (1) {
        printf("Имена: %s\n", names);
        printf("Алиасы: %s\n", aliases);
        printf("Барьеры: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%lf ", barriers[i]);
        }
        printf("\n");

        double rnd = random() * 4;
        int cellIndex = floor(rnd);
        double internalIndex = rnd - floor(rnd);

        printf("\nСлучайная величина: %lf", rnd);
        printf("\nНомер ячейки: %d", cellIndex);
        printf("\nОценка выбора внутри ячейки: %lf", internalIndex);
        printf("\nРезультат: %c \n\n", internalIndex > barriers[cellIndex] ? aliases[cellIndex] : names[cellIndex]);
        getchar();
        printf("\n");
    }
}