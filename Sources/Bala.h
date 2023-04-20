#pragma once
#include <allegro5/allegro.h>
#include <list>
using namespace std;

/**
 * Clase bala.
 * 
 * Encargada de manejar los aspectos correspondientes a la bala
 * 
 */
class Bala
{
public:
	// Variables
	int x;
	int y;
	int type;
	float velocidad;
	ALLEGRO_BITMAP* bala;

	// Funciones
	void mov();
	Bala(int x, int y, int type);
	~Bala();
};
/**
 * Lista de balas.
 */
list<Bala*> balas;

/**
 * Funcion contructora del objetos bala.
 * 
 * \param x
 * \param y
 * \param type
 */
Bala::Bala(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	bala = al_load_bitmap("imagenes/bala.png");
	this->type = type;
}

/**
 * Funcion mov.
 * 
 * Encargada del movimiento de las balas
 * 
 * \param
 */
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

/**
 * Funcion ~Bala.
 * 
 * Funcion encargada de llamar a Bullet Collector
 * 
 */
Bala::~Bala()
{
	//balas.remove(this);
}
