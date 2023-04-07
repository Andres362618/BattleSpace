// Importa librerias
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <allegro5/allegro_primitives.h>

// Nombre de espacio a utiizar
using namespace std;

// Funcion main
int main() {
	// Inicia e instala las funciones para el uso de las librerias
	al_init_font_addon();
	al_init_ttf_addon();
	al_init();
	al_install_mouse();
	al_init_primitives_addon();

	// Establece las medidas de la ventana
	const int ancho = 800;
	const int largo = 600;

	// Crea la ventana
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, largo);
	// Carga fuentes de texto
	ALLEGRO_FONT* starStoneTitulo = al_load_font("Starstone.ttf", 60, 0);
	ALLEGRO_FONT* starStoneTexto = al_load_font("Starstone.ttf", 35, 0);
	ALLEGRO_FONT* evilEmpire = al_load_font("Evil Empire.otf", 45, 0);

	// Nombra la ventana
	al_set_window_title(ventana, "Battlespace");
	
	// Crea timer
	ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
	ALLEGRO_TIMER* FPS = al_create_timer(1.0/60);

	//Crea cola de eventos
	ALLEGRO_EVENT evento;
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	// Colores
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR verde = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR amarillo = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR rojo = al_map_rgb(255, 0, 0);

	// Registro de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(FPS));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	// Inicia el timer
	al_start_timer(segundoTimer);
	al_start_timer(FPS);
	int segundo = 0;
	int x = -1, y = -1;

	// Ciclo del menu
	while (true)
	{
		al_wait_for_event(event_queue, &evento);
		
		// Evento segundos
		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			if(evento.timer.source == segundoTimer)
			{
				segundo++;
			}
		}
		// Limpia la pantalla
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// Creacion de botones y sus respectivas funciones
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			// Detecta click para elegir dificultad
			if (x >= 125 && x <= 275 && y >= 450 && y <= 500)
			{
				if (evento.mouse.button & 1)
				{
					cout << "x: " << x << "y: " << y << endl;
				}
			}

			if (x >= 315 && x <= 485 && y >= 450 && y <= 500)
			{
				if (evento.mouse.button & 1)
				{
					cout << "x: " << x << "y: " << y << endl;
				}
			}

			if (x >= 525 && x <= 675 && y >= 450 && y <= 500)
			{
				if (evento.mouse.button & 1)
				{
					cout << "x: " << x << "y: " << y << endl;
				}
			}
		}

		// Cambio de color de los botones al pasar sobre ellos
		if (x >= 125 && x <= 275 && y >= 450 && y <= 500)
		{
			al_draw_filled_rectangle(125, 450, 275, 500, verde);
			al_draw_text(starStoneTexto, negro, 154, 445, NULL, "Inicial");
		}
		else
		{
			al_draw_filled_rectangle(125, 450, 275, 500, blanco);
			al_draw_text(starStoneTexto, negro, 154, 445, NULL, "Inicial");
		}

		if (x >= 315 && x <= 485 && y >= 450 && y <= 500)
		{
			al_draw_filled_rectangle(315, 450, 485, 500, amarillo);
			al_draw_text(starStoneTexto, negro, 317, 445, NULL, "Intermedio");
		}
		else
		{
			al_draw_filled_rectangle(315, 450, 485, 500, blanco);
			al_draw_text(starStoneTexto, negro, 317, 445, NULL, "Intermedio");
		}

		if (x >= 525 && x <= 675 && y >= 450 && y <= 500)
		{
			al_draw_filled_rectangle(525, 450, 675, 500, rojo);
			al_draw_text(starStoneTexto, negro, 545, 445, NULL, "Experto");
		}
		else
		{
			al_draw_filled_rectangle(525, 450, 675, 500, blanco);
			al_draw_text(starStoneTexto, negro, 545, 445, NULL, "Experto");
		}

		// Pinta elementos en la ventana
		// Printea el nombre del juego en la ventana menu
		al_draw_text(starStoneTitulo, blanco, 270, 90, NULL, "Battlespace");
		
		// Printea Elija dificultad
		al_draw_text(starStoneTexto, blanco, 300, 300, NULL, "Elija dificultad");
		
		// Printea el timer
		//al_draw_text(evilEmpire, al_map_rgb(255, 255, 255), (ancho/2) - 10, 0, NULL, (to_string(segundo)).c_str());

		al_flip_display();
	}

	return 0;
}
