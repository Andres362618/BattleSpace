#pragma once
#include <math.h>
#include <list>
#include "Bala.h"
#include "Alarm.h"
using namespace std;

/**
 * Clase enemigo.
 * 
 * Clase encargada de manejar lo relacionado con los enemigos
 */
class Enemigo
{
public:
	// Variables
	double x;
	double y;
	int type_e;
	double cont;
	int direccion = 1;
	int vida;
	ALLEGRO_BITMAP* enemigo;

	// Funciones
	void action(int power, float mod_speed);
	void movimiento(float mod_speed);
	Enemigo(int x, int y, int type_e, float mod_vida);
	~Enemigo();

	// Objetos
	Alarm* alarm;
};

/**
 * Lista de oleadas.
 */
list<Enemigo*> oleada;

/**
 * Funcion enemigo.
 * 
 * Constructor de los enemigos
 * 
 * \param x
 * \param y
 * \param type_e
 */
Enemigo::Enemigo(int x, int y, int type, float mod_vida)
{
	this->x = x;
	this->y = y;
	this->enemigo = type == 0 ? al_load_bitmap("imagenes/enemigo.png") : type == 1 ? al_load_bitmap("imagenes/enemigo2.png") : al_load_bitmap("imagenes/enemigo3.png");
	this->alarm = new Alarm[15]();
	this->type_e = type;
	this->cont = 1;
	this->vida = 150 * mod_vida;
}

/**
 * Funcion ~Enemigo.
 * 
 * Encargada de eliminar los enemigos de pantalla
 * 
 */
Enemigo::~Enemigo()
{
	this->x = -200;
}

/**
 * Funcion action.
 * 
 * Encargada de manejar las acciones de los enemigos
 * 
 */
void Enemigo::action(int power, float mod_speed)
{
	// Dibuja al enemigo
	al_draw_bitmap(this->enemigo, x, y, 0);

	// Colisiones
	for (list<BulletCollector*>::iterator it = balas.begin(); it != balas.end(); it++)
	{
		BulletCollector* b = *it;
		if (b->x_b >= this->x and b->x_b <= this->x+100 and b->y_b >= this->y and b->y_b <= this->y+55)
		{
			b->x_b = 2000;
			this->vida -= (50 * 1/b->type_b) * power;
		}
	}

	this->movimiento(mod_speed);

	if (this->vida <= 0)
	{
		this->~Enemigo();
	}
}

/**
 * Funcion movimiento.
 * 
 * Encargada de los patrones de movimiento de los enemigos
 * 
 */
void Enemigo::movimiento(float mod_speed)
{
	switch (this->type_e)
	{
	case 0:
		if (this->alarm[0].alarm(1))
		{
			x -= 20 * mod_speed;
		}
		break;
	case 1:
		if (this->alarm[0].alarm(1))
		{
			x -= 10 * mod_speed;
			y += cos(x / 50) * 10;
		}
		break;
	case 2:
		if (this->alarm[0].alarm(1))
		{
			x -= 5 * mod_speed;

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
