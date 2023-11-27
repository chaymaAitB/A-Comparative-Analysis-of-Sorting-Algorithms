// Génère une liste non triée de taille donnée
void genererListeNonTriee(int [], int);

// Génère une liste partiellement triée de taille donnée
void genererListePartiellementTriee(int [], int );

// Génère une liste triée de taille donnée
void genererListeTriee(int [], int );


long long int  mesurer(void (*)(int [], int), int [], int ); // 1 iere parametreconstitue un pointeur sur une fonction de tri 

void afficherTableau2D(long long int** liste, int , int );

// Fonction gaussienne pour calculer les coefficients de pondération
double gaussian(double , double , double );

// Fonction pour lisser les mesures avec une fonction gaussienne
void lisserMesures_Gaussienne(long long int **mesures, int , int );
/* Une moyenne pondérée avec des coefficients de pondération basés sur une fonction gaussienne
 est généralement utilisée lorsque vous avez besoin de lisser des données en mettant l'accent sur les points de données 
 les plus proches du point central. Cette technique de lissage est souvent utilisée en traitement de signal, en analyse 
 de données, en prévision et dans d'autres domaines où il est important de réduire le bruit ou d'obtenir 
 une représentation plus précise des données.

void lisserMesures_Gaussienne(long long int **mesures, int , int );

 la moyenne mobile exponentielle.

Pour convertir une courbe bruyante en une courbe croissante tout en respectant les données, 
vous pouvez utiliser une technique de lissage qui met davantage l'accent sur la tendance générale 
des données plutôt que sur les fluctuations bruyantes. Une méthode courante pour ce faire est l'utilisation 
de moyennes mobiles, en particulier la moyenne mobile exponentielle.
void lissageMME(long long int **tableau, int , int , float );*/
/* utilisé pour créer des graphiques et des visualisations */
void generateAndWriteDataToFile(const char *filename, long long int **data_table, int , int , const char **column_headers, int *list_sizes);
void createGnuplotScript(
    const char *scriptFileName,
    const char *dataFileName,
    const char *outputFileName,
    const char *title,
    const char *xLabel,
    const char *yLabel,
    int,
    const char **columnHeaders
);