#pragma once
#include <allegro5/allegro.h>
#include "Bala.h"
using namespace std;

class Enemigo
{
public:
	// Variables
	int x;
	int y;
	ALLEGRO_BITMAP* enemigo;

	// Funciones
	Enemigo(int x, int y);
	void action();
	~Enemigo();
};

Enemigo::Enemigo(int x, int y)
{
	this->x = x;
	this->y = y;
	this->enemigo = al_load_bitmap("imagenes/enemigo.png");
}

void Enemigo::action()
{
	// Colisiones
	

	// Dibuja al enemigo
	al_draw_bitmap(this->enemigo, x, y, 0);
}

Enemigo::~Enemigo()
{

}