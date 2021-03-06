#include <iostream>
#include <ctype.h>

#define FICHES_MAX 500
#define CHAR_MAX 50
#define SEXE_FEMININ_MAJUSCULE 'F'
#define SEXE_FEMININ_MINUSCULE 'f'
#define CARACTERE_NUL '\0'

using namespace std;

struct Fiche
{
    char nom[FICHES_MAX];
    char prenom[FICHES_MAX];
    unsigned int age;
    char sexe;
};

int main()
{
    Fiche fiches[FICHES_MAX];
    
    unsigned int nbFiches = 0;
    unsigned int nbFemmes = 0;
    unsigned int positionPlusJeuneEleve = 0;
    
    do
    {
        cin >> nbFiches;
    }
    while(nbFiches > FICHES_MAX);
    
    for(unsigned int i=0;i<nbFiches;i++)
    {
        cout << "Nom : ";
        cin >> fiches[i].nom;
        cout << "Prénom : ";
        cin >> fiches[i].prenom;
        cout << "Sexe (f/m) : ";
        cin >> fiches[i].sexe;
        cout << "Age : ";
        cin >> fiches[i].age;
        
        // Réécriture majuscule
        fiches[i].nom[0] = toupper(fiches[i].nom[0]);
        fiches[i].prenom[0] = toupper(fiches[i].prenom[0]);

        // Réécriture minuscule
        for(unsigned int j=1; fiches[i].nom[j] != CARACTERE_NUL ;j++)
        {
            fiches[i].nom[j] = tolower(fiches[i].nom[j]);
            fiches[i].prenom[j] = tolower(fiches[i].prenom[j]);
        }
        
        if((fiches[i].sexe == SEXE_FEMININ_MINUSCULE) || ( fiches[i].sexe == SEXE_FEMININ_MAJUSCULE))
        {
            nbFemmes++;
        }
    }
    
    unsigned int plusJeuneEleve = fiches[0].age;
            
    for(unsigned int i = 0; i < nbFiches;i++)
    {
        if(plusJeuneEleve > fiches[i].age)
        {
            plusJeuneEleve = fiches[i].age;
            positionPlusJeuneEleve = i;
        }
    } 
    
    cout << "Nombre de femmes : " << nbFemmes << endl;
    cout << "Etudiant le plus jeune : " << fiches[positionPlusJeuneEleve].nom << " " << fiches[positionPlusJeuneEleve].prenom << " " << fiches[positionPlusJeuneEleve].age << " " << fiches[positionPlusJeuneEleve].sexe << endl;
    cout << "Liste des étudiants : " << endl;
    
    for(unsigned int i=0;i<nbFiches;i++)
    {
        cout << fiches[i].nom << " ";
        cout << fiches[i].prenom << " ";
        cout << fiches[i].age << " ";
        cout << fiches[i].sexe << endl;
    }
    
    return 0;
}