#pragma once
#include <allegro5/allegro.h>
#include "Bala.h"
using namespace std;

class Nave
{
public:
	// Variables
	int x;
	int y;
	float velocidad;
	int direccion;
	int alto = 500;
	ALLEGRO_BITMAP* nave;

	// Funciones
	void mov_up();
	void mov_down();
	void mov_stop();
	void disparar();
	void draw();
	Nave();
	~Nave();
};

Nave::Nave()
{
	x = 0;
	y = 200;
	nave = al_load_bitmap("imagenes/nave.png");
	velocidad = 10.0f;
}

void Nave::mov_up()
{
	direccion = -1;
}

void Nave::mov_down()
{
	direccion = 1;
}

void Nave::mov_stop()
{
	direccion = 0;
}

void Nave::draw()
{
	// Dibujamos el objeto en la nueva posición
	y += direccion * velocidad;
	if (y > 450)
	{
		y = 450;
	}
	else if (y < 0)
	{
		y = 0;
	}
	al_draw_bitmap(nave, x, y, 0);
}

void Nave::disparar()
{
	balas.push_back(new Bala(x, y, 0)); // Agrega una nueva bala a la lista
}

Nave::~Nave()
{

}
