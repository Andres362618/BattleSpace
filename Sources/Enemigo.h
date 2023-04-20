#pragma once
#include <math.h>
#include <list>
#include "Bala.h"
#include "Alarm.h"
using namespace std;

class Enemigo
{
public:
	// Variables
	double x;
	double y;
	int type;
	double cont;
	int direccion = 1;
	int vida;
	ALLEGRO_BITMAP* enemigo;

	// Funciones
	void action();
	void movimiento();
	Enemigo(int x, int y, int type);
	~Enemigo();

	// Objetos
	Alarm* alarm;
};

list<Enemigo*> oleada;

Enemigo::Enemigo(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	this->enemigo = al_load_bitmap("imagenes/enemigo.png");
	this->alarm = new Alarm[15]();
	this->type = type;
	this->cont = 1;
	this->vida = 100;
}


Enemigo::~Enemigo()
{
	this->x = -200;
}

void Enemigo::action()
{
	// Dibuja al enemigo
	al_draw_bitmap(this->enemigo, x, y, 0);

	// Colisiones
	for (list<Bala*>::iterator it = balas.begin(); it != balas.end(); it++)
	{
		Bala* b = *it;
		if (b->x >= this->x and b->x <= this->x+100 and b->y >= this->y and b->y <= this->y+55)
		{
			b->x = 2000;
			this->vida -= 50;
		}
	}

	this->movimiento();

	if (this->vida <= 0)
	{
		this->~Enemigo();
	}
}

void Enemigo::movimiento()
{
	switch (this->type)
	{
	case 0:
		if (this->alarm[0].alarm(1))
		{
			x -= 20;
		}
		break;
	case 1:
		if (this->alarm[0].alarm(1))
		{
			x -= 10;
			y += cos(x / 50) * 10;
		}
		break;
	case 2:
		if (this->alarm[0].alarm(1))
		{
			x -= 5;

			if (y <= 0)
			{
				direccion = 1;
			}
			else if (y >= 450)
			{
				direccion = -1;
			}

			y += 10 * direccion;
		}
		break;
	}
}
