#include "methodesTri.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void triBulle(int Tableau[], int n) {
    int *T = (int *)malloc(n * sizeof(int));
    memcpy(T, Tableau , n * sizeof(int));
    int temp;
    int swapped;

    do {
        swapped = 0;
        for (int i = 1; i < n; i++) {
            if (T[i - 1] > T[i]) {
                // Échanger T[i-1] et T[i]
                temp = T[i - 1];
                T[i - 1] = T[i];
                T[i] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
    free(T);
}

void triSelection(int Tableau[], int n) {
    int minIndex, temp;
    int *T = (int *)malloc(n * sizeof(int));
    memcpy(T, Tableau , n * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (T[j] < T[minIndex]) {
                minIndex = j;
            }
        }
        // Échanger T[i] et T[minIndex]
        temp = T[i];
        T[i] = T[minIndex];
        T[minIndex] = temp;
    }
        free(T);
}

void triInsertion(int Tableau[], int n) {
    int key, j;
    int *T = (int *)malloc(n * sizeof(int));
    memcpy(T, Tableau , n * sizeof(int));
    for (int i = 1; i < n; i++) {
        key = T[i];
        j = i - 1;

        while (j >= 0 && T[j] > key) {
            T[j + 1] = T[j];
            j--;
        }
        T[j + 1] = key;
    }
        free(T);

}
// tri rapide 
void echanger(int tableau[], int a, int b) {
    int temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

int partition(int tableau[], int debut, int fin) {
    int pivot = tableau[fin];
    int i = (debut - 1);

    for (int j = debut; j <= fin - 1; j++) {
        if (tableau[j] < pivot) {
            i++;
            echanger(tableau, i, j);
        }
    }
    echanger(tableau, i + 1, fin);
    return (i + 1);
}

void triRapideRecursif(int tableau[], int debut, int fin) {
    if (debut < fin) {
        int pivot = partition(tableau, debut, fin);
        triRapideRecursif(tableau, debut, pivot - 1);
        triRapideRecursif(tableau, pivot + 1, fin);
    }
}

void triRapide(int T[], int taille) {
    int *tableau = (int *)malloc(taille * sizeof(int));
    memcpy(tableau, T , taille * sizeof(int));
    triRapideRecursif(tableau, 0, taille - 1);
}
// tri fusion
void fusion(int tableau[], int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    // Crée des tableaux temporaires
    int temp1[n1], temp2[n2];

    // Copie les données dans les tableaux temporaires temp1[] et temp2[]
    for (i = 0; i < n1; i++)
        temp1[i] = tableau[debut + i];
    for (j = 0; j < n2; j++)
        temp2[j] = tableau[milieu + 1 + j];

    // Fusionne les tableaux temporaires en un seul tableau
    i = 0;
    j = 0;
    k = debut;
    while (i < n1 && j < n2) {
        if (temp1[i] <= temp2[j]) {
            tableau[k] = temp1[i];
            i++;
        } else {
            tableau[k] = temp2[j];
            j++;
        }
        k++;
    }

    // Copie les éléments restants de temp1[] (s'il y en a)
    while (i < n1) {
        tableau[k] = temp1[i];
        i++;
        k++;
    }

    // Copie les éléments restants de temp2[] (s'il y en a)
    while (j < n2) {
        tableau[k] = temp2[j];
        j++;
        k++;
    }
}

void triFusionRecursif(int tableau[], int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        triFusionRecursif(tableau, debut, milieu);
        triFusionRecursif(tableau, milieu + 1, fin);

        fusion(tableau, debut, milieu, fin);
    }
}

void triFusion(int T[], int taille) {
    int *tableau = (int *)malloc(taille * sizeof(int));
    memcpy(tableau, T , taille * sizeof(int));
    triFusionRecursif(tableau, 0, taille - 1);
}
//tri par tas
void entasser(int tableau[], int n, int i) {
    int plusGrand = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && tableau[gauche] > tableau[plusGrand])
        plusGrand = gauche;

    if (droite < n && tableau[droite] > tableau[plusGrand])
        plusGrand = droite;

    if (plusGrand != i) {
        int temp = tableau[i];
        tableau[i] = tableau[plusGrand];
        tableau[plusGrand] = temp;
        entasser(tableau, n, plusGrand);
    }
}

void triTas(int T[], int n) {
    int *tableau = (int *)malloc(n * sizeof(int));
    memcpy(tableau, T , n * sizeof(int));
    for (int i = n / 2 - 1; i >= 0; i--)
        entasser(tableau, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = tableau[0];
        tableau[0] = tableau[i];
        tableau[i] = temp;
        entasser(tableau, i, 0);
    }
}
// Tri Shell
void triShell(int T[], int n) {
    int *tableau = (int *)malloc(n * sizeof(int));
    memcpy(tableau, T , n * sizeof(int));
    for (int intervalle = n / 2; intervalle > 0; intervalle /= 2) {
        for (int i = intervalle; i < n; i += 1) {
            int temp = tableau[i];
            int j;
            for (j = i; j >= intervalle && tableau[j - intervalle] > temp; j -= intervalle) {
                tableau[j] = tableau[j - intervalle];
            }
            tableau[j] = temp;
        }
    }
}
//

SortFunctions sort_functions = {
    {
    triBulle,
    triSelection,
    triInsertion,
    triRapide,
    triFusion,
    triTas,
    triShell
    }
};
