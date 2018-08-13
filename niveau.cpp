#include "niveau.h"

Niveau::Niveau(unsigned int largeur = 20, unsigned int hauteur = 10)
{
  m_grille.resize(hauteur);
  for(
    std::vector<std::vector<Objet_Niveau*> >::iterator it = m_grille.begin();
    it != m_grille.end();
    ++it)
  {
    it->resize(largeur);
    for(
      std::vector<Objet_Niveau*>::iterator it2 = it->begin();
      it2 != it->end();
      ++it2)
    {
      *it2 = new Vide();
    }
  }
}

Niveau::~Niveau()
{
  for(
    std::vector<std::vector<Objet_Niveau*> >::iterator it = m_grille.begin();
    it != m_grille.end();
    ++it)
    for(
      std::vector<Objet_Niveau*>::iterator it2 = it->begin();
      it2 != it->end();
      ++it2)

      delete *it2;
}
