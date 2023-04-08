// Importa librerias
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

// Nombre de espacio a utiizar
using namespace std;

int jugar_Inicial();
int jugar_Intermedio();
int jugar_Experto();
// Establece las medidas de la ventana
int ancho = 700;
int alto = 525;

ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* starStoneTitulo;
ALLEGRO_FONT* starStoneTexto;
ALLEGRO_FONT* evilEmpire;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* FPS;
ALLEGRO_EVENT_QUEUE* event_queue;

// Colores
ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR verde = al_map_rgb(0, 255, 0);
ALLEGRO_COLOR amarillo = al_map_rgb(255, 255, 0);
ALLEGRO_COLOR rojo = al_map_rgb(255, 0, 0);

// Funcion main
int main() {
	// Inicia e instala las funciones para el uso de las librerias
	al_init_font_addon();
	al_init_ttf_addon();
	al_init();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();

	// Crea la ventana
	ventana = al_create_display(ancho, alto);
	// Carga fuentes de texto
	starStoneTitulo = al_load_font("fuentes/Starstone.ttf", 60, 0);
	starStoneTexto = al_load_font("fuentes/Starstone.ttf", 35, 0);
	evilEmpire = al_load_font("fuentes/Evil Empire.otf", 45, 0);

	// Nombra la ventana
	al_set_window_title(ventana, "Battlespace");
	
	// Crea timer
	segundoTimer = al_create_timer(1.0);
	FPS = al_create_timer(1.0/60);

	//Crea cola de eventos
	event_queue = al_create_event_queue();

	// Imagenes
	ALLEGRO_BITMAP* fondoMenu = al_load_bitmap("imagenes/fondoMenu.jpg");

	// Registro de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(FPS));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Inicia el timer
	al_start_timer(segundoTimer);
	al_start_timer(FPS);
	int segundo = 0;
	int x = -1, y = -1;
	// Botones menu
	int botones[] = {0};
	botones[0] = 0;

	// Ciclo del menu
	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);


		/*
		// Evento segundos
		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			if(evento.timer.source == segundoTimer)
			{
				segundo++;
			}
		}
		*/


		// Limpia la pantalla
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// Fondo del menu
		al_draw_bitmap(fondoMenu, 0, 0, 0);


		/*
		// Creacion de botones y sus respectivas funciones
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			// Detecta click para elegir dificultad
			if (x >= 75 && x <= 225 && y >= 400 && y <= 450)
			{
				botones[0] = 1;
				if (evento.mouse.button & 1)
				{
					jugar_Inicial();
				}
			}
			else
			{
				botones[0] = 0;
			}

			if (x >= 265 && x <= 435 && y >= 400 && y <= 450)
			{
				botones[0] = 2;
				if (evento.mouse.button & 1)
				{
					jugar_Intermedio();
				}
			}
			else
			{
				botones[0] = 2;
			}

			if (x >= 475 && x <= 625 && y >= 400 && y <= 450)
			{
				botones[0] = 3;
				if (evento.mouse.button & 1)
				{
					jugar_Experto();
				}
			}
			else
			{
				botones[0] = 3;
			}
		}
		 */


		// Cambio de color de los botones al pasar sobre ellos
		if (botones[0] == 1)
		{
			al_draw_filled_rectangle(75, 400, 225, 450, verde);
			al_draw_text(starStoneTexto, negro, 104, 395, NULL, "Inicial");
		}
		else
		{
			al_draw_filled_rectangle(75, 400, 225, 450, blanco);
			al_draw_text(starStoneTexto, negro, 104, 395, NULL, "Inicial");
		}

		if (botones[0] == 2)
		{
			al_draw_filled_rectangle(265, 400, 435, 450, amarillo);
			al_draw_text(starStoneTexto, negro, 267, 395, NULL, "Intermedio");
		}
		else
		{
			al_draw_filled_rectangle(265, 400, 435, 450, blanco);
			al_draw_text(starStoneTexto, negro, 267, 395, NULL, "Intermedio");
		}

		if (botones[0] == 3)
		{
			al_draw_filled_rectangle(475, 400, 625, 450, rojo);
			al_draw_text(starStoneTexto, negro, 495, 395, NULL, "Experto");
		}
		else
		{
			al_draw_filled_rectangle(475, 400, 625, 450, blanco);
			al_draw_text(starStoneTexto, negro, 495, 395, NULL, "Experto");
		}

		// Pinta elementos en la ventana
		// Printea el nombre del juego en la ventana menu
		al_draw_text(starStoneTitulo, blanco, 220, 40, NULL, "Battlespace");
		
		// Printea Elija dificultad
		al_draw_text(starStoneTexto, blanco, 250, 250, NULL, "Elija dificultad");
		
		// Eventos del teclado
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evento.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT: {

					int operacion = (botones[0] - 1) % 4;
					botones[0] = operacion == 0? 3 : operacion;

					cout << botones[0] << endl;
						break;
				}
				case ALLEGRO_KEY_RIGHT: {
					int operacion = (botones[0] + 1) % 4;
					botones[0] = operacion == 0? 1 : operacion;

					cout << botones[0] << endl;
					break;
				}

				case ALLEGRO_KEY_ENTER:
				{
					if (botones[0] == 1) {
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						jugar_Experto();
					}
				}
				case ALLEGRO_KEY_PAD_ENTER:
				{
					if (botones[0] == 1) {
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						jugar_Experto();
					}
				}

				default:
					break;
			}
		}

		// Printea el timer
		//al_draw_text(evilEmpire, al_map_rgb(255, 255, 255), (ancho/2) - 10, 0, NULL, (to_string(segundo)).c_str());

		al_flip_display();
	}

	return 0;
}






























int jugar_Inicial() {

	// Cambia las dimensiones de la ventana
	ancho = 900;
	alto = 700;
	ventana = al_create_display(ancho, alto);
	cout << "Inicial" << endl;


	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(negro);

		al_flip_display();
	}
	return 0;
}

int jugar_Intermedio() {

	// Cambia las dimensiones de la ventana
	ancho = 900;
	alto = 700;
	ventana = al_create_display(ancho, alto);
	cout << "Intermedio" << endl;

	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(negro);

		al_flip_display();
	}

	return 0;
}

int jugar_Experto() {

	// Cambia las dimensiones de la ventana
	ancho = 900;
	alto = 700;
	ventana = al_create_display(ancho, alto);
	cout << "Experto" << endl;

	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(negro);

		al_flip_display();
	}

	return 0;
}
