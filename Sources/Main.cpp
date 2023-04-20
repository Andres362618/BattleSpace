// Importa librerias
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <list>

// Importa otros documentos de las clases
#include "Nave.h"
#include "Bala.h"
#include "Enemigo.h"
#include "Alarm.h"

// Nombre de espacio a utiizar
using namespace std;

// Inicia las funciones
int jugar_Inicial();
int jugar_Intermedio();
int jugar_Experto();
void crear();
void enemigo_action();

// Establece los enteros para la ventana
int ancho;
int alto;

// Prepara ventana, fuentes y cola de eventos
ALLEGRO_DISPLAY* ventanaMenu;
ALLEGRO_DISPLAY* ventanaJuego;
ALLEGRO_FONT* starStoneTitulo;
ALLEGRO_FONT* starStoneTexto;
ALLEGRO_FONT* evilEmpire;
ALLEGRO_EVENT_QUEUE* event_queue;

// Colores
ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR verde = al_map_rgb(0, 255, 0);
ALLEGRO_COLOR amarillo = al_map_rgb(255, 255, 0);
ALLEGRO_COLOR rojo = al_map_rgb(255, 0, 0);

Alarm* Timer = new Alarm();

bool play = true;

// Funcion main
int main() {
	// Establece las medidas de la ventana
	int ancho = 700;
	int alto = 525;

	// Inicia e instala las funciones para el uso de las librerias
	al_init_font_addon();
	al_init_ttf_addon();
	al_init();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();


	// Crea la ventana
	ventanaMenu = al_create_display(ancho, alto);

	// Carga fuentes de texto
	starStoneTitulo = al_load_font("fuentes/Starstone.ttf", 60, 0);
	starStoneTexto = al_load_font("fuentes/Starstone.ttf", 35, 0);
	evilEmpire = al_load_font("fuentes/Evil Empire.otf", 45, 0);

	// Nombra la ventana
	al_set_window_title(ventanaMenu, "Battlespace");

	//Crea cola de eventos
	event_queue = al_create_event_queue();

	// Imagenes
	ALLEGRO_BITMAP* fondoMenu = al_load_bitmap("imagenes/fondoMenu.jpg");

	// Registro de eventos
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Botones menu
	unsigned int botones[] = {0};
	botones[0] = 0;	

	// Ciclo del menu
	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// Fondo del menu
		al_draw_bitmap(fondoMenu, 0, 0, 0);

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
						break;
				}
				case ALLEGRO_KEY_RIGHT: {
					int operacion = (botones[0] + 1) % 4;
					botones[0] = operacion == 0? 1 : operacion;
					break;
				}

				case ALLEGRO_KEY_ENTER:
				{
					if (botones[0] == 1) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Experto();
					}
					break;
				}

				case ALLEGRO_KEY_PAD_ENTER:
				{
					if (botones[0] == 1) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						al_destroy_event_queue(event_queue);
						al_destroy_bitmap(fondoMenu);

						// Inicia el juego
						jugar_Experto();
					}
					break;
				}
			}
		}
		// Pinta todo el pantalla
		al_flip_display();
	}

	// Libera recursos
	al_destroy_display(ventanaMenu);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(fondoMenu);

	return 0;
}









int jugar_Inicial() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	// Crea ventana de juego
	ventanaJuego = al_create_display(ancho, alto);

	// Crea timers para FPS y cadencia
	ALLEGRO_TIMER* FPS = al_create_timer(1.0 / 60);
	ALLEGRO_TIMER* cadencia = al_create_timer(0.5);
	// Crea cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Resgistro de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(FPS));
	al_register_event_source(queue, al_get_timer_event_source(cadencia));

	// Inicia timers
	al_start_timer(FPS);
	al_start_timer(cadencia);

	// Crea nuevo objeto de clase nave
	Nave* nave = new Nave();

	// Carga fondo
	ALLEGRO_BITMAP* fondoInicial = al_load_bitmap("imagenes/fondoInicial.jpg");

	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Inicial");

	// Inicia allegro y teclado
	al_init();
	al_install_keyboard();

	// Numero de balas a utilizar
	int n_balas = 500;

	// Hace que los numeros sean aleatorios
	srand(time(NULL));

	// Ciclo principal de juego
	while (play)
	{
		// Dibuja el fondo en pantalla
		al_draw_bitmap(fondoInicial, 0, 0, 0);

		// Llama a la funcion crear y enemigo_action
		crear();
		enemigo_action();

		// Obtenemos el siguiente evento de la cola
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// Llamado para disparar de manera automatica
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (n_balas > 0)
			{
				// Llama a la funcion disparar para agregar una nueva bala a la lista
				if (event.timer.source == cadencia)
				{
					// Llama a la funcion disparar en la clase nave
					nave->disparar();
					// Resta al numero de balas
					n_balas--;
				}
			}
			// Hace que la bala se mueva a 60 FPS
			if (event.timer.source == FPS)
			{
				// Recorre la lista de balas
				for (list<Bala*>::iterator it = balas.begin(); it != balas.end(); it++)
				{
					// Crea objeto de tipo bala
					Bala* b = *it;
					// Llama a la funcion mov en la clase bala
					b->mov();
				}
			}

		}

		// Revisa que se presione alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				// Registra el movimiento hacia arriba
			case ALLEGRO_KEY_W:
				nave->mov_up();
				break;
				// Registra el movimiento hacia abajo
			case ALLEGRO_KEY_S:
				nave->mov_down();
				break;
				// Registra cuando se cierra el juego
			case ALLEGRO_KEY_ESCAPE:
				play = false;
				break;
			}
		}

		// Revisa que se deje de presionar alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				nave->mov_stop();
				break;
			case ALLEGRO_KEY_S:
				nave->mov_stop();
				break;
			}
		}

		// Pinta el fondo y la nave
		nave->draw();
		al_flip_display();
	}

	// Libera memoria utilizada
	al_destroy_event_queue(queue);
	al_destroy_display(ventanaJuego);
	al_destroy_bitmap(fondoInicial);

	return 0;
}









int jugar_Intermedio() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	// Crea ventana de juego
	ventanaJuego = al_create_display(ancho, alto);

	// Crea timers para FPS y cadencia
	ALLEGRO_TIMER* FPS = al_create_timer(1.0 / 60);
	ALLEGRO_TIMER* cadencia = al_create_timer(0.5);
	// Crea cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Resgistro de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(FPS));
	al_register_event_source(queue, al_get_timer_event_source(cadencia));

	// Inicia timers
	al_start_timer(FPS);
	al_start_timer(cadencia);

	// Crea nuevo objeto de clase nave
	Nave* nave = new Nave();

	// Carga fondo
	ALLEGRO_BITMAP* fondoIntermedio = al_load_bitmap("imagenes/fondoIntermedio.jpg");

	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Intermedio");

	// Inicia allegro y teclado
	al_init();
	al_install_keyboard();

	// Numero de balas a utilizar
	int n_balas = 250;

	// Hace que los numeros sean aleatorios
	srand(time(NULL));

	// Ciclo principal de juego
	while (play)
	{
		// Dibuja el fondo en pantalla
		al_draw_bitmap(fondoIntermedio, 0, 0, 0);

		// Llama a la funcion crear y enemigo_action
		crear();
		enemigo_action();

		// Obtenemos el siguiente evento de la cola
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// Llamado para disparar de manera automatica
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (n_balas > 0)
			{
				// Llama a la funcion disparar para agregar una nueva bala a la lista
				if (event.timer.source == cadencia)
				{
					// Llama a la funcion disparar en la clase nave
					nave->disparar();
					// Resta al numero de balas
					n_balas--;
				}
			}
			// Hace que la bala se mueva a 60 FPS
			if (event.timer.source == FPS)
			{
				// Recorre la lista de balas
				for (list<Bala*>::iterator it = balas.begin(); it != balas.end(); it++)
				{
					// Crea objeto de tipo bala
					Bala* b = *it;
					// Llama a la funcion mov en la clase bala
					b->mov();
				}
			}

		}

		// Revisa que se presione alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				// Registra el movimiento hacia arriba
			case ALLEGRO_KEY_W:
				nave->mov_up();
				break;
				// Registra el movimiento hacia abajo
			case ALLEGRO_KEY_S:
				nave->mov_down();
				break;
				// Registra cuando se cierra el juego
			case ALLEGRO_KEY_ESCAPE:
				play = false;
				break;
			}
		}

		// Revisa que se deje de presionar alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				nave->mov_stop();
				break;
			case ALLEGRO_KEY_S:
				nave->mov_stop();
				break;
			}
		}

		// Pinta el fondo y la nave
		nave->draw();
		al_flip_display();
	}

	// Libera memoria utilizada
	al_destroy_event_queue(queue);
	al_destroy_display(ventanaJuego);
	al_destroy_bitmap(fondoIntermedio);

	return 0;
}









int jugar_Experto() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	// Crea ventana de juego
	ventanaJuego = al_create_display(ancho, alto);

	// Crea timers para FPS y cadencia
	ALLEGRO_TIMER* FPS = al_create_timer(1.0 / 60);
	ALLEGRO_TIMER* cadencia = al_create_timer(0.5);
	// Crea cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Resgistro de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(FPS));
	al_register_event_source(queue, al_get_timer_event_source(cadencia));

	// Inicia timers
	al_start_timer(FPS);
	al_start_timer(cadencia);

	// Crea nuevo objeto de clase nave
	Nave* nave = new Nave();

	// Carga fondo
	ALLEGRO_BITMAP* fondoExperto = al_load_bitmap("imagenes/fondoExperto.jpg");

	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Experto");

	// Inicia allegro y teclado
	al_init();
	al_install_keyboard();

	// Numero de balas a utilizar
	int n_balas = 100;

	// Hace que los numeros sean aleatorios
	srand(time(NULL)); 

	// Ciclo principal de juego
	while (play)
	{
		// Dibuja el fondo en pantalla
		al_draw_bitmap(fondoExperto, 0, 0, 0);

		// Llama a la funcion crear y enemigo_action
		crear();
		enemigo_action();

		// Obtenemos el siguiente evento de la cola
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// Llamado para disparar de manera automatica
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (n_balas > 0)
			{
				// Llama a la funcion disparar para agregar una nueva bala a la lista
				if (event.timer.source == cadencia)
				{
					// Llama a la funcion disparar en la clase nave
					nave->disparar();
					// Resta al numero de balas
					n_balas--;
				}
			}
			// Hace que la bala se mueva a 60 FPS
			if (event.timer.source == FPS)
			{
				// Recorre la lista de balas
				for (list<Bala*>::iterator it = balas.begin(); it != balas.end(); it++)
				{
					// Crea objeto de tipo bala
					Bala* b = *it;
					// Llama a la funcion mov en la clase bala
					b->mov();
				}
			}

		}

		// Revisa que se presione alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				// Registra el movimiento hacia arriba
			case ALLEGRO_KEY_W:
				nave->mov_up();
				break;
				// Registra el movimiento hacia abajo
			case ALLEGRO_KEY_S:
				nave->mov_down();
				break;
				// Registra cuando se cierra el juego
			case ALLEGRO_KEY_ESCAPE:
				play = false;
				break;
			}
		}

		// Revisa que se deje de presionar alguna tecla
		if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				nave->mov_stop();
				break;
			case ALLEGRO_KEY_S:
				nave->mov_stop();
				break;
			}
		}

		// Pinta el fondo y la nave
		nave->draw();
		al_flip_display();
	}

	// Libera memoria utilizada
	al_destroy_event_queue(queue);
	al_destroy_display(ventanaJuego);
	al_destroy_bitmap(fondoExperto);

	return 0;
}




void crear()
{
	// Establece el numero de ronda, contador de enemigos creados y 2 numeros random para definir el tipo y pos_y del enemigo
	static int ronda = 1;
	static int cont = 0; // Enemigos creados
	int type = rand()%3; // Crea un numero random entre el 0 y el 2
	int y_spawn = rand() % 445; // Crea un numero random entre el 0 y el 2

	// Revisa por cual ronda va
	if (ronda < 6)
	{
		// Revisa cuantos enemigos se crearon
		if (cont < 5)
		{
			// Espera para crear nuevos enemigos
			if (Timer->alarm(150))
			{
				oleada.push_back(new Enemigo(800, y_spawn, type)); // Crea un enemigo random
				cont++; // Suma al contador de enemigos
			}
		}
		else
		{
			// Espera para crear nueva ronda
			if (Timer->alarm(200))
			{
				cont = 0; // Reinicia el contador
				ronda++; // Suma ronda
				type = rand() % 3; // Crea un numero random entre el 0 y el 2
				y_spawn = rand() % 445; // Cambia la pos_y
			}
		}
	}
	else
	{
		// Termina el juego
		cout << "End Game" << endl;
		play = false;
	}
}








// Funcion para las acciones de los enemigos
void enemigo_action()
{
	// Recorre la lista de los enemigos
	for (list<Enemigo*>::iterator it = oleada.begin(); it != oleada.end(); it++)
	{
		// Registra un nuevo enemigo en la lista
		Enemigo* b = *it;
		// Llama a la funcion action en la clase enemigo
		b->action();
	}
}