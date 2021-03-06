#ifndef IHM_H
#define IHM_H

#include "JeuPoulePoule.h"

#define TEMPS_AFFICHAGE_CARTE 2

class IHM
{
    private:
       JeuPoulePoule *jeuPoulePoule;
       
    public:
        // constructeur(s) et destructeur(s)
        IHM(JeuPoulePoule *jeuPoulePoule=NULL);
        ~IHM();

        // méthode(s)
        void afficherRegles() const;
        void afficherExemple();
        void effacerIHM() const;
        void attendre() const;
        void afficherCarte(TypeCarte typeCarte, bool exemple=false);
};

#endif // IHM_H