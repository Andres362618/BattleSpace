// Importa librerias
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

// Nombre de espacio a utiizar
using namespace std;

// Inicia las funciones
int jugar_Inicial();
int jugar_Intermedio();
int jugar_Experto();
void moverNave(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* objeto, float& y_pos, ALLEGRO_BITMAP* fondoInicial);

// Establece los enteros para la ventana
int ancho;
int alto;

ALLEGRO_DISPLAY* ventanaMenu;
ALLEGRO_DISPLAY* ventanaJuego;
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

	// Inicia la musica
	

	int segundo = 0;
	int x = -1, y = -1;
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
						// Inicia el juego
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						// Inicia el juego
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						// Inicia el juego
						jugar_Experto();
					}
				}
				case ALLEGRO_KEY_PAD_ENTER:
				{
					if (botones[0] == 1) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						// Inicia el juego
						jugar_Inicial();
					}
					if (botones[0] == 2) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						// Inicia el juego
						jugar_Intermedio();
					}
					if (botones[0] == 3) {
						// Destruye el menu
						al_destroy_display(ventanaMenu);
						// Inicia el juego
						jugar_Experto();
					}
				}

				default:
					break;
			}
		}
		// Pinta todo el pantalla
		al_flip_display();
	}

	return 0;
}









int jugar_Inicial() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	ventanaJuego = al_create_display(ancho, alto);

	

	// Carga fondo
	ALLEGRO_BITMAP* fondoInicial = al_load_bitmap("imagenes/fondoInicial.jpg");
	al_draw_bitmap(fondoInicial, 0, 0, 0);


	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Inicial");



	al_init();
	al_install_keyboard();

	ALLEGRO_BITMAP* nave = al_load_bitmap("imagenes/nave.png");
	float y_pos = 200;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(ventanaJuego));

	// Pone el fondo

	moverNave(queue, ventanaJuego, nave, y_pos, fondoInicial);




	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		

		// Detecion de botones
		switch (evento.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			al_destroy_display(ventanaJuego);
			main();
		}

		al_flip_display();
	}

	return 0;
}









int jugar_Intermedio() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	ventanaJuego = al_create_display(ancho, alto);

	// Carga fondo
	ALLEGRO_BITMAP* fondoIntermedio = al_load_bitmap("imagenes/fondoIntermedio.jpg");

	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Intermedio");

	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(negro);
		// Pone el fondo
		al_draw_bitmap(fondoIntermedio, 0, 0, 0);

		// Detecion de botones
		switch (evento.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			al_destroy_display(ventanaJuego);
			main();
		}

		al_flip_display();
	}

	return 0;
}









int jugar_Experto() {

	// Cambia las dimensiones de la ventana
	ancho = 800;
	alto = 500;
	ventanaJuego = al_create_display(ancho, alto);
	// Carga fondo
	ALLEGRO_BITMAP* fondoExperto = al_load_bitmap("imagenes/fondoExperto.jpg");

	// Nombra la ventana
	al_set_window_title(ventanaJuego, "Battlespace Experto");

	while (true)
	{
		// Se prepara para nuevos eventos
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);

		// Limpia la pantalla
		al_clear_to_color(negro);
		// Pone el fondo
		al_draw_bitmap(fondoExperto, 0, 0, 0);

		// Detecion de botones
		switch (evento.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			al_destroy_display(ventanaJuego);
			main();
		}

		al_flip_display();
	}

	return 0;
}









// Funci�n para mover la nave
void moverNave(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* objeto, float& y_pos, ALLEGRO_BITMAP* fondoInicial) {
	// Variables para controlar la velocidad y direcci�n del movimiento
	float velocidad = 5.0f;
	int direccion = 0;

	// Registramos los eventos de teclado en la cola de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());

	// Bucle principal de la funci�n
	while (true) {
		// Obtenemos el siguiente evento de la cola
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

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
		// Si el evento es de liberaci�n de tecla, detenemos el movimiento
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_S:
				direccion = 0;
				break;
			}
		}
		// Si el evento es de cierre de la ventana, salimos de la funci�n
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return;
		}

		// Actualizamos la posici�n del objeto en funci�n de la direcci�n y velocidad
		y_pos += direccion * velocidad;

		// Dibujamos el objeto en la nueva posici�n
		al_draw_bitmap(fondoInicial, 0, 0, 0);
		al_draw_bitmap(objeto, 0, y_pos, 0);
		al_flip_display();
	}
}
