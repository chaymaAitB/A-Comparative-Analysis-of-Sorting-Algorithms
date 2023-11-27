#include "calculs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define M_PI 3.14159265358979323846

void genererListeNonTriee(int liste[], int taille) {
    // Initialize the random number generator
    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        liste[i] = rand() % 99 + 1; // Nombres aléatoires de 1 à 99
    }
}

void genererListePartiellementTriee(int liste[], int taille) {
    // Initialize the random number generator
    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        if (i % 3 == 0) {
            liste[i] = i;
        } else {
            liste[i] = rand() % 99 + 1;
        }
    }
}

void genererListeTriee(int liste[], int taille) {
    // Initialize the random number generator
    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        liste[i] = i;
    }
}

long long int mesurer(void (*tri)(int [], int), int liste[], int taille) {
    struct timespec start, end;
    long long int elapsed_time;

    clock_gettime(CLOCK_MONOTONIC, &start); // Record the start time

    tri(liste, taille);

    clock_gettime(CLOCK_MONOTONIC, &end); // Record the end time

    elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    //printf("for taille = %d on a T = %Lf\n",taille, elapsed_time); // in nanoseconds
    return elapsed_time;// en  nanoseconds
}

void afficherTableau2D(long long int ** liste, int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%lld ", liste[i][j]);
        }
        printf("\n");
    }
}

 /* lisser les données tout en conservant la tendance générale à la hausse
void lissageEtAjustementParColonne(long long int **tableau, int lignes, int colonnes) {
    for (int colonne = 0; colonne < colonnes; colonne++) {
        for (int ligne = 2; ligne < lignes; ligne++) {
            long long int difference = tableau[ligne][colonne] - tableau[ligne - 1][colonne];
            if (difference < 0) {
                tableau[ligne][colonne] = tableau[ligne - 1][colonne] ;
            }
        }
    }
} */
// Fonction gaussienne
double gaussian(double x, double mean, double sigma) {
    return exp(-((x - mean) * (x - mean)) / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
}

// Procédure pour lisser les mesures avec une fonction gaussienne
void lisserMesures_Gaussienne(long long int** mesures, int rows, int cols) {
    double mean = 0.5;
    double sigma = 0.1;

    // Créer un tableau temporaire pour stocker les nouvelles valeurs lissées
    long long int** mesuresLissees = (long long int**)malloc(rows * sizeof(long long int*));
    for (int i = 0; i < rows; ++i) {
        mesuresLissees[i] = (long long int*)malloc(cols * sizeof(long long int));
    }

    // Appliquer le lissage gaussien
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            double x = (double)i / (rows - 1);
            double weight = gaussian(x, mean, sigma);
            mesuresLissees[i][j] = 0;  // Initialise la valeur lissée à 0
            for (int k = 0; k < rows; ++k) {
                mesuresLissees[i][j] += (long long int)(weight * mesures[k][j]);
            }
        }
    }

    // Copier les valeurs lissées dans le tableau d'origine
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mesures[i][j] = mesuresLissees[i][j];
        }
    }

    // Libérer la mémoire du tableau temporaire
    for (int i = 0; i < rows; ++i) {
        free(mesuresLissees[i]);
    }
    free(mesuresLissees);
}
// Function to generate and write data to a file with column headers
void generateAndWriteDataToFile(const char *filename, long long int **data_table, int rows, int cols, const char **column_headers, int *list_sizes) {
    FILE *dataFile = fopen(filename, "w");

    if (dataFile == NULL) {
        perror("Error opening data file");
        exit(1);
    }

    // Write column headers
    fprintf(dataFile, "List Size");
    for (int j = 0; j < cols; j++) {
        fprintf(dataFile, "\t%s", column_headers[j]);
    }
    fprintf(dataFile, "\n");

    // Generate and write data to the file
    for (int i = 0; i < rows; i++) {
        fprintf(dataFile, "%d", list_sizes[i]); // Write list size
        for (int j = 0; j < cols; j++) {
            fprintf(dataFile, "\t%lld", data_table[i][j]);
        }
        fprintf(dataFile, "\n");
    }

    fclose(dataFile);
}

// Function to create a Gnuplot script for plotting
void createGnuplotScript(
    const char *scriptFileName,
    const char *dataFileName,
    const char *outputFileName,
    const char *title,
    const char *xLabel,
    const char *yLabel,
    int rows,
    const char **columnHeaders
) {
    FILE *scriptFile = fopen(scriptFileName, "w");

    if (scriptFile == NULL) {
        perror("Error opening plot script file");
        exit(1);
    }

    fprintf(scriptFile, "set terminal png\n");
    fprintf(scriptFile, "set output '%s'\n", outputFileName);
    fprintf(scriptFile, "set title '%s'\n", title);
    fprintf(scriptFile, "set xlabel '%s'\n", xLabel);
    fprintf(scriptFile, "set ylabel '%s'\n", yLabel);

    fprintf(scriptFile, "plot");
    for (int col = 2; col <= rows + 1; col++) {
    fprintf(scriptFile, " '%s' using 1:%d with lines title '%s'", dataFileName, col, columnHeaders[col - 2]);
    if (col < rows + 1) {
        fprintf(scriptFile, ",");
    }
}

    fprintf(scriptFile, "\n");

    fclose(scriptFile);
}
