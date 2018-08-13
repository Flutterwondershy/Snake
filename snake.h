#pragma once

#include <deque>

#include "niveau.h"

enum Direction {Haut, Droite, Bas, Gauche, Inconnue}; //Direction::Inconnue peut être retiré si le GUI le permet

class Coordonnees {
	public:
		Coordonnees(unsigned int X, unsigned int Y) : x(X), y(Y) {}
		Coordonnees next(Direction d, const Niveau& n) const;

		unsigned int X() const {return x;}
		unsigned int Y() const {return y;}
	private:
		unsigned int x;
		unsigned int y;
};
bool operator==(const Coordonnees& a, const Coordonnees& b);
bool operator!=(const Coordonnees& a, const Coordonnees& b);

class Corps {
	public:
		Corps(Coordonnees c = Coordonnees(0,0)) { m_elements.push_back(c); }

		bool collision(const Corps& c) const;
		bool collision(const Niveau& n) const
			{Coordonnees c = m_elements.back();
			return n.collision(c.X(), c.Y());}

		void avancer(Direction d, const Niveau& n, bool agrandir = false);
		const std::deque<Coordonnees> getCorps() const {return m_elements;}

	private:
		std::deque<Coordonnees> m_elements;
};

class Snake {
	// La taille doit toujours être supérieure à 2
	public:
		Snake(const Niveau& n, Direction d = Droite, Coordonnees c = Coordonnees(0,0), unsigned int taille = 10)
		 : m_direction(d), m_corps(c) {m_corps.avancer(d, n, true); for(unsigned int i = 0; i < taille -2; i++) m_corps.avancer(d, n, true);}

		void avancer(const Niveau& n) {m_corps.avancer(m_direction, n);}
		void tourner(Direction d);

		const std::deque<Coordonnees> getCorps() const { return m_corps.getCorps(); }
	private:
		Direction m_direction;
		Corps m_corps;
};
