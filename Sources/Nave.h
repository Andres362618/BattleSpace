#pragma once
#include <allegro5/allegro.h>

class Nave
{
public:
	// Variables
	int x;
	int y;
	ALLEGRO_BITMAP* nave;
	float velocidad;
	int direccion;
	ALLEGRO_EVENT_QUEUE* queue;
	int alto = 500;

	// Funciones
	void mov(ALLEGRO_BITMAP* fondo);
	Nave();
	~Nave();
};

Nave::Nave()
{
	x = 0;
	y = 200;
	nave = al_load_bitmap("imagenes/nave.png");

}

void Nave::mov(ALLEGRO_BITMAP* fondo)
{
	velocidad = 5.0f;
	direccion = 0;

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Registramos los eventos de teclado en la cola de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());

	while (true) {
		// Obtenemos el siguiente evento de la cola
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= alto - 50)
		{
			y = alto - 50;
		}

		// Si el evento es de teclado, comprobamos la tecla pulsada
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				direccion = -1;
				break;
			case ALLEGRO_KEY_S:
				direccion = 1;
				break;
			}
		}
		// Si el evento es de liberación de tecla, detenemos el movimiento
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_S:
				direccion = 0;
				break;
			}
		}

		// Actualizamos la posición del objeto en función de la dirección y velocidad
		y += direccion * velocidad;

		// Dibujamos el objeto en la nueva posición
		al_draw_bitmap(fondo, 0, 0, 0);
		al_draw_bitmap(nave, x, y, 0);
		al_flip_display();
	}
}

Nave::~Nave()
{

}