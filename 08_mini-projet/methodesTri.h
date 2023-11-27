void triBulle(int [],int);
void triSelection(int [],int);
void triInsertion(int [],int);
//void tri Rapide
void echanger(int [], int , int);
int partition(int [], int , int ) ;
void triRapideRecursif(int [], int , int ) ;
void triRapide(int [], int );
//tri Fusion
void fusion(int [], int , int , int );

void triFusionRecursif(int [], int , int );

void triFusion(int [], int );
//tri par tas
void entasser(int [], int , int );

void triTas(int [], int );
// Tri Shell
void triShell(int [], int);

// Déclarer une structure pour le tableau de pointeurs de fonctions
typedef struct {
    void (*functions[7])(int *, int);
} SortFunctions;

// Déclarer une instance de la structure
SortFunctions sort_functions;