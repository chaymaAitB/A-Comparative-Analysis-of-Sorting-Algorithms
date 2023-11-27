/*
Etude experimental pour comparer la performence des plusieurs algorithms de tri :
- sélection - tri rapide
- insertion - tri fusion
- bulle     - ...
On doit produire un résultat graphique comme suit :

temps
^
|   bulle
|  /  /rapide
| /  /
|/__/______________> taille N
 1ms   2ms
*/

// initialisation aléatoire du tableua à trier soit tab statique (nobre fixe d'éléments ) ou dynamique (pointeur, la taile n'est pas fixe)

// 2 configuration une favorable pour le tri et autre n'est pas, comme un tab trié est favorable pour bulle.

// pour le graphique lier votre script avec GNU.PLOT en utilisant popen.

// livrable

// faire en équie de 2 ou 3 PERSONNES

// période : 2 semaines 
#include "methodesTri.h"
#include "calculs.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>

#define NB_PTS_MAX 10 000 
#define NB_METH_MAX 10 

int main() {
    int taille;
    int methode;
    int pas ;
    const char *column_names[] = {
        "triBulle",
        "triSelection",
        "triInsertion",
        "triRapide",
        "triFusion",
        "triTas",
        "triShell"
    };
    printf("Donner nb pts, sachant que le Max est 10 000 : ");
    scanf("%d",&taille);
    printf("Donner nb methds, sachant que le Max est 7  :");
    scanf("%d",&methode);
    printf("Donner nb pas, sachant que 0<pas<=pts  :");
    scanf("%d",&pas);
    int count;
    if (pas == 1)
    {
        count= taille -1 ;
    }
    else {
        count = (int)(taille/pas);
    }
    //int f = count - 1;
    int* list_sizes = (int*)malloc(count * sizeof(int));
    if (list_sizes == NULL) {
        perror("Error allocating memory for list sizes");
        exit(1);
    }
    if (pas == 1)
    {
        for (int i = 0; i < count; i++) {
        list_sizes[i] = (i + 2); // Adjust the formula as needed
        }
    }
    else
    {
        for (int i = 0; i < count; i++) {
        list_sizes[i] = (i + 1) * pas; // Adjust the formula as needed
        }
    }
    
    int *listeNonTriee = (int *)malloc(taille * sizeof(int));   
    int *listePartiellementTriee = (int *)malloc(taille * sizeof(int));
    int *listeTriee = (int *)malloc(taille * sizeof(int));


    long long int** mesures_listeNonTriee = (long long int**)malloc(count * sizeof(long long int*));
    for (int i = 0; i < count; i++) {
    mesures_listeNonTriee[i] = (long long int*)malloc(methode * sizeof(long long int ));
    }    
    
    long long int** mesures_listePartiellementTriee = (long long int**)malloc(count * sizeof(long long int*));
    for (int i = 0; i < count; i++) {
    mesures_listePartiellementTriee[i] = (long long int*)malloc(methode * sizeof(long long int ));
    } 

    long long int** mesures_listeTriee = (long long int**)malloc(count * sizeof(long long int*));
    for (int i = 0; i < count; i++) {
    mesures_listeTriee[i] = (long long int*)malloc(methode * sizeof(long long int ));
    } 

   

    genererListeNonTriee(listeNonTriee, taille);
    genererListePartiellementTriee(listePartiellementTriee, taille);
    genererListeTriee(listeTriee, taille);
    /* Afficher le contenu du tableau
    for (int i = 0; i < taille; i++) {
        printf("%d ", listeNonTriee[i]);
    }*/
    int n;
    if (pas == 1)
    {
        n= 2 ;
    }
    else {
        n = pas;
    }

    // générer le tableau de temps d'execution de Liste non trie
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < methode; j++)
        {
        mesures_listeNonTriee[i][j] = mesurer(sort_functions.functions[j], listeNonTriee, n);
        }
        n = n + pas;
    }
    if (pas == 1)
    {
        n= 2 ;
    }
    else {
        n = pas;
    }
    // générer le tableau de temps d'execution de Liste semi trie
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < methode; j++)
        {
        mesures_listePartiellementTriee[i][j] = mesurer(sort_functions.functions[j], listePartiellementTriee, n);
        }  
        n = n + pas;

    }
    // générer le tableau de temps d'execution de Liste trie
    if (pas == 1)
    {
        n= 2 ;
    }
    else {
        n = pas;
    }    
    for (int i = 0; i < count; i++)
    {
       for (int j = 0; j < methode; j++)
        {
        mesures_listeTriee[i][j] = mesurer(sort_functions.functions[j], listeTriee, n);
        } 
        n = n + pas;

    }
    /*printf("Avant lissage :\n");
    afficherTableau2D(mesures_listeNonTriee, count, methode);*/
    // Allouez de la mémoire pour le tableau de destination (copie)
    //long long int** T = (long long int**)malloc(f * sizeof(long long int*));

    lisserMesures_Gaussienne( mesures_listeNonTriee, count , methode);
    lisserMesures_Gaussienne( mesures_listePartiellementTriee, count , methode);
    lisserMesures_Gaussienne( mesures_listeTriee, count , methode);

/*
    for (int i = 1; i < count; i++) {
        T[i - 1] = (long long int *)malloc(methode * sizeof(long long int));
        memcpy(T[i - 1], mesures_listeNonTriee[i], methode * sizeof(int));
    }   */ 

    //afficherTableau2D(mesures_listeNonTriee, count, methode);
    generateAndWriteDataToFile("data1.txt", mesures_listeNonTriee, count, methode, column_names, list_sizes);
    createGnuplotScript("plotScript1.plt", "data1.txt", "output1.png", "Sorting Method Comparison for no sorted liste ", "List Size", "Execution Time (ns)", methode, column_names);
    
    generateAndWriteDataToFile("data2.txt", mesures_listePartiellementTriee, count, methode, column_names, list_sizes);
    createGnuplotScript("plotScript2.plt", "data2.txt", "output2.png", "Sorting Method Comparison for semi sorted liste ", "List Size", "Execution Time (ns)", methode, column_names);
    
    generateAndWriteDataToFile("data3.txt", mesures_listePartiellementTriee, count, methode, column_names, list_sizes);
    createGnuplotScript("plotScript3.plt", "data3.txt", "output3.png", "Sorting Method Comparison for sorted liste ", "List Size", "Execution Time (ns)", methode, column_names);
    
    // free space 
    free(listeNonTriee);
    free(listePartiellementTriee);
    free(listeTriee);
    free(list_sizes);
    // free space
    for (int i = 0; i < count; i++) {
    free(mesures_listeNonTriee[i]);
    }
    free(mesures_listeNonTriee);

    for (int i = 0; i < count; i++) {
    free(mesures_listePartiellementTriee[i]);
    }
    free(mesures_listePartiellementTriee);

    for (int i = 0; i < count; i++) {
    free(mesures_listeTriee[i]);
    }
    free(mesures_listeTriee);
    /*
    La première exécution d'une méthode de tri peut sembler plus lente que les suivantes, même pour des tableaux de même taille. 
    Plusieurs raisons expliquent ce phénomène, notamment le chargement initial, la gestion de la mémoire, les optimisations du compilateur et les effets de cache. 
    Ces facteurs sont courants et la première exécution implique souvent des opérations supplémentaires. Il est recommandé de comparer les performances 
    des méthodes de tri en utilisant la moyenne des temps d'exécution sur plusieurs ensembles de données de test.
    */

    return 0;

} 
