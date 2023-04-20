#pragma once
#include <allegro5/allegro.h>
#include <list>
#include "Nave.h"
using namespace std;

/**
 * Clase bala.
 * 
 * Encargada de manejar los aspectos correspondientes a la bala
 * 
 */
class BulletCollector
{
public:
	// Variables
	int x_b;
	int y_b;
	int type_b;
	float velocidad;
	ALLEGRO_BITMAP* bala;

	// Funciones
	void mov();
	void BulletCollector_collector(int x_b, int y_b, int type_b);
	BulletCollector(int x, int y, int type_b);
};
/**
 * Lista de balas.
 */
list<BulletCollector*> balas;

/**
 * Funcion contructora del objetos bala.
 * 
 * \param x
 * \param y
 * \param type
 */
BulletCollector::BulletCollector(int x, int y, int type_b)
{
	this->x_b = x;
	this->y_b = y;
	bala = al_load_bitmap("imagenes/bala.png");
	this->type_b = type_b;
}

/**
 * Funcion mov.
 * 
 * Encargada del movimiento de las balas
 * 
 * \param velocidad
 */
void BulletCollector::mov()
{
	velocidad = 10.0f;
	
	if (x_b < 800)
	{
		x_b += velocidad;
	}
	else if (x_b >= 800 and x_b <= 1000)
	{
		//this->BulletCollector(x_b, y_b, this->type_b);
	}
	al_draw_bitmap(this->bala, x_b, y_b, 0);
}

/**
 * Funcion BulletCollector_collector.
 * 
 * Funcion encargada de colectar las balas
 * 
 */
void BulletCollector::BulletCollector_collector(int x, int y, int type)
{
	/*
	Nave* n = nullptr;
	int y_n = n->get_y();
	*/

	this->type_b = type_b++;
	this->x_b = 0;
	this->y_b = y;

	cout << 50 * 1 / type << endl;
}
