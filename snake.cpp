#include <iostream>

#include "snake.h"
#include "niveau.h"

Coordonnees Coordonnees::next(Direction d, const Niveau& n) const
{
	Coordonnees c = Coordonnees(*this);

	switch(d) {
		case Haut:
			if(c.y == 0) c.y = n.hauteur() -1;
			else c.y -= 1;
			break;
		case Gauche:
			if(c.x == 0) c.x = n.largeur() -1;
			else c.x -= 1;
			break;
		case Bas: 		c.y = (c.y + 1) % n.hauteur(); break;
		case Droite:	c.x = (c.x + 1) % n.largeur(); break;
		default: break; //couper le warning
	}

	return c;
}

bool operator==(const Coordonnees& a, const Coordonnees& b)
{
	return a.X() == b.X() && a.Y() == b.Y();
}

bool operator!=(const Coordonnees& a, const Coordonnees& b)
{
	return !(a==b);
}

bool Corps::collision(const Corps& c) const
{
	Coordonnees C = m_elements.back();
	for(unsigned int i = 0; i != c.m_elements.size(); ++i)
		if(C == c.m_elements[i]) return true;

 	return false;
}

void Corps::avancer(Direction d, const Niveau& n, bool agrandir)
{
	m_elements.push_back(m_elements.back().next(d, n));
	if(!agrandir) m_elements.pop_front();
}

void Snake::tourner(Direction d)
{
	if(!(
			(m_direction == Haut && d == Bas) ||
			(m_direction == Bas && d == Haut) ||
			(m_direction == Gauche && d == Droite) ||
			(m_direction == Droite && d == Gauche)
		))
		m_direction = d;
}
