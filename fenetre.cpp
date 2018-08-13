#include <iostream>
#include <algorithm>

#include "fenetre.h"


sf::Sprite& Fenetre::spriteSnake(Type t, Direction d)
{
  m_spriteSnake.setTextureRect(sf::IntRect(t*64, 0, 64, 64));
  m_spriteSnake.setRotation(d*90);

  return m_spriteSnake;
}

void Fenetre::afficherSnake()
{
  const std::deque<Coordonnees> liste = m_snake->getCorps();
  Direction d = Droite;

  //TETE
  Coordonnees c(liste.back().X(), liste.back().Y());
  Coordonnees precedent(liste[liste.size()-2].X(), liste[liste.size()-2].Y());
  if(c.X() == precedent.X())
    if(precedent.Y() < c.Y()) d = Bas;
    else d = Haut;
  else
    if(precedent.X() < c.X()) d = Droite;
    else d = Gauche;

  spriteSnake(TETE, d);
  m_spriteSnake.setPosition(sf::Vector2f(c.X()*tailleTuile()+tailleTuile()/2, c.Y()*tailleTuile()+tailleTuile()/2));
  draw(m_spriteSnake);


  //CORPS
  for(unsigned int i = 1; i < liste.size() -1; i++)
  {
    Type t = CORPS;
    if(liste[i-1].Y() == liste[i].Y() && liste[i].Y() == liste[i+1].Y())
      d = Droite;
    else if(liste[i-1].X() == liste[i].X() && liste[i].X() == liste[i+1].X())
      d = Haut;
    else
    {
      d = orientation(liste[i-1], liste[i], liste[i+1]);
      t = ANGLE;
    }
    spriteSnake(t, d);
    m_spriteSnake.setPosition(sf::Vector2f(liste[i].X()*tailleTuile()+tailleTuile()/2, liste[i].Y()*tailleTuile()+tailleTuile()/2));
    draw(m_spriteSnake);
  }

  //QUEUE
  if(liste[0].X() == liste[1].X())
    if(liste[1].Y() < liste[0].Y()) d = Bas;
    else d = Haut;
  else
    if(liste[1].X() < liste[0].X()) d = Droite;
    else d = Gauche;
  spriteSnake(QUEUE, d);
  m_spriteSnake.setPosition(sf::Vector2f(liste[0].X()*tailleTuile()+tailleTuile()/2, liste[0].Y()*tailleTuile()+tailleTuile()/2));
  draw(m_spriteSnake);
}

void Fenetre::evenement()
{
  while (pollEvent(m_event))
  {
    if(m_event.type == sf::Event::Closed)
      close();
    if(m_event.type == sf::Event::KeyPressed)
    {
      switch(m_event.key.code)
      {
        case sf::Keyboard::Up:
          m_inputs.empiler(Haut);
          break;
        case sf::Keyboard::Down:
          m_inputs.empiler(Bas);
          break;
        case sf::Keyboard::Left:
          m_inputs.empiler(Gauche);
          break;
        case sf::Keyboard::Right:
          m_inputs.empiler(Droite);
          break;
        default: break;
      }
    }
    if (m_event.type == sf::Event::Resized)
    {
      redimmensionner();
      setSize(sf::Vector2u(m_event.size.width, m_event.size.height));
    }
  }
}

Direction Fenetre::orientation(const Coordonnees a, const Coordonnees b, const Coordonnees c) const
{
  if(a.Y() != b.Y()) return orientation(c, b, a);
  //a.y = b.y
    if(a.X() < b.X())
      if(b.Y() < c.Y()) return Haut;
      else return Droite;
    else
      if(b.Y() < c.Y()) return Gauche;
      else return Bas;
}

unsigned int Fenetre::tailleTuile() const
{
  return std::min(getSize().y / m_niveau->hauteur(), getSize().x / m_niveau->largeur());
}

Fenetre::Fenetre() : sf::RenderWindow(sf::VideoMode(640, 640), "Snake")
{
  setFramerateLimit(60);
  m_niveau = new Niveau(20,20);
  m_snake = new Snake(*m_niveau);

  if(!m_textureSnake.loadFromFile("Images/snake.png"))
    std::cerr << "Erreur: Chargement de Images/snake.png" << std::endl;
  m_textureSnake.setSmooth(true);

  m_spriteSnake.setTexture(m_textureSnake);
  m_spriteSnake.setOrigin(sf::Vector2f(32, 32));
  redimmensionner();
}

void Fenetre::run()
{
  sf::Clock temps;
  while (isOpen())
  {
    evenement();
    if(temps.getElapsedTime().asMilliseconds() > 100)
    {
      Direction d = m_inputs.getDirection();
      if(d != Inconnue) m_snake->tourner(d);

      m_snake->avancer(*m_niveau);

      clear(sf::Color(255, 214, 152));
      afficherSnake();
      display();
      temps.restart();
    }
  }
}
