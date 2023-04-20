#pragma once
#include <allegro5/allegro.h>
#include "Bala.h"
using namespace std;

/**
 * Clase Nave.
 * 
 * Contiene todas las funciones respectivas a la nave
 * 
 */
class Nave
{
public:
	// Variables
	int x;
	int y;
	int y_n;
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
	int get_y();
	Nave(int speed);
};

/**
 * Constructor de la clase Nave.
 * 
 */
Nave::Nave(int speed)
{
	x = 0;
	y = 200;
	nave = al_load_bitmap("imagenes/nave.png");
	velocidad = 5.0f * speed;
}

/**
 * Clase mov up.
 * 
 * Encargada del movimiento hacia arriba
 * 
 */
void Nave::mov_up()
{
	direccion = -1;
}

/**
 * Clase mov down.
 * 
 * Encargada del movimiento hacia abajo
 * 
 */
void Nave::mov_down()
{
	direccion = 1;
}

/**
 * Clase mov stop.
 * 
 * Encargada de detener el movimiento
 * 
 */
void Nave::mov_stop()
{
	direccion = 0;
}

/**
 * Clase draw.
 * 
 * Encargada de pintar la nave en pantalla, modificar la y y evitar que salga de pantalla
 * 
 */
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

/**
 * Clase disparar.
 * 
 * Encargada de añadir balas a la lista de balas
 * 
 */
void Nave::disparar()
{
	balas.push_back(new BulletCollector(x, y, 1)); // Agrega una nueva bala a la lista
}

int Nave::get_y()
{
	y_n = x;
	return y_n;
}
