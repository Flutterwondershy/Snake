#pragma once

#include <vector>

#include "objet_niveau.h"

class Niveau
{
public:
  Niveau(unsigned int largeur, unsigned int hauteur);
  ~Niveau();
  
  unsigned int hauteur() const {return m_grille.size();}
  unsigned int largeur() const
    {return m_grille.size() > 0 ? m_grille[0].size() : 0;}

  bool collision(unsigned int x, unsigned int y) const
    {return !m_grille[x][y]->franchissable();}

private:
  std::vector<std::vector<Objet_Niveau*> > m_grille;

};
