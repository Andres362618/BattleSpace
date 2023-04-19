#pragma once
#include <allegro5/allegro.h>
#include <list>
using namespace std;

class Bala
{
public:
	// Variables
	int x;
	int y;
	float velocidad;
	ALLEGRO_BITMAP* bala;

	// Funciones
	void mov();
	Bala(int x, int y);
	~Bala();
};

list<Bala*> balas;

Bala::Bala(int x, int y)
{
	this->x = x;
	this->y = y;
	bala = al_load_bitmap("imagenes/bala.png");
}

void Bala::mov()
{
	velocidad = 10.0f;
	
	if (x < 800)
	{
		x += velocidad;
	}
	else
	{
		this->~Bala();
	}
	al_draw_bitmap(this->bala, x, y, 0);
}

Bala::~Bala()
{
	
}