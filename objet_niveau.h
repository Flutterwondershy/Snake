#pragma once

class Objet_Niveau
{
public:
  Objet_Niveau() :
    m_ramassable(false),
    m_consommable(false),
    m_franchissable(false),
    m_duree(-1) {}
  virtual ~Objet_Niveau() {}

  bool ramassable() const {return m_ramassable;}
  bool consommable() const {return m_consommable;}
  bool franchissable() const {return m_franchissable;}

  unsigned int tempsRestant()
    {return (m_duree == -1) ? 1 : m_duree;}

  virtual void effet() = 0;

protected:
  bool m_ramassable;
  bool m_consommable;
  bool m_franchissable;
  int m_duree;
};

class Brique : public Objet_Niveau
{
  Brique() : Objet_Niveau() {m_franchissable = false;}
  void effet() {}
};

class Vide : public Objet_Niveau
{
public:
  Vide() : Objet_Niveau() {}
  void effet() {}
};
