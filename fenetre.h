#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "snake.h"

enum Type {QUEUE, CORPS, ANGLE, TETE};

//Classe qui sert à ne prendre en compte que 3 inputs en avance
class InputDirection {
private:
  std::queue<Direction> m_file;
  unsigned int m_taille;
public:
  InputDirection(unsigned int taille = 3) : m_taille(taille) {}
  Direction getDirection()
  {
    if(!m_file.empty())
    {
      Direction d = m_file.front();
      m_file.pop();
      return d;
    }
    else return Inconnue;
  }
  void empiler(Direction d)
  {
    if(m_file.size() < m_taille && (m_file.empty() || m_file.front() != d))
        m_file.push(d);
  }
};

class Fenetre : public sf::RenderWindow
{
private:
  sf::Event m_event;
  sf::Texture m_textureSnake;
  sf::Sprite m_spriteSnake;

  Niveau* m_niveau;
  Snake* m_snake;

  InputDirection m_inputs;

  sf::Sprite& spriteSnake(Type t, Direction d);
  void afficherSnake();
  void evenement();
  Direction orientation(const Coordonnees a, const Coordonnees b, const Coordonnees c) const;
  unsigned int tailleTuile() const;
  void redimmensionner() {m_spriteSnake.setScale(tailleTuile()/64.0, tailleTuile()/64.0);}
public:
  Fenetre();
  ~Fenetre() {delete m_snake; delete m_niveau;}

  void run();


};
