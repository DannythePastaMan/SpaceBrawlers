// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"bala.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include<iostream>

using namespace std;

//Variables Globales

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *fontM, *fontI;
ALLEGRO_BITMAP *imageM = NULL;
ALLEGRO_BITMAP *imageI = NULL;
ALLEGRO_BITMAP *imageJ = NULL;
ALLEGRO_BITMAP *sprite1 = NULL;
ALLEGRO_BITMAP *sprite2 = NULL;
ALLEGRO_EVENT_QUEUE *eventqueueM;
ALLEGRO_EVENT_QUEUE *eventqueueJ;
ALLEGRO_EVENT_QUEUE *eventqueueI;
ALLEGRO_EVENT eventsM;
ALLEGRO_EVENT eventsJ;
ALLEGRO_EVENT eventsI;
ALLEGRO_TIMER *cron;
ALLEGRO_KEYBOARD_STATE keyboardstate;

int opc = 0;
int speed = 30; 
int sprite1x = 1920 / 2;
int sprite1y = 1080 - 100;
int sprite2x = 1920 / 2;
int sprite2y = 1080 - 1050;
int bullposx[6];
int bullposy[6];
int counter = 0;
const int bullspeed = 5;
bool Menuout = false;//ciclo menu
bool Game = false;//ciclo game in
bool Instruccionesout = false;//ciclo pantalla de instruccioens
bool shoot = false;//ciclo para disparar
bool draw = false;//ciclo para dibujar las bullets(sin uso)

//end variables globales

//Inicializacion de variables
void VarStart() {
	
	al_init();
	
	al_install_keyboard();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();

	display = al_create_display(1920, 1080);

	cron = al_create_timer(1.00 / 60.00);

	eventqueueM = al_create_event_queue();
	eventqueueJ = al_create_event_queue();
	eventqueueI = al_create_event_queue();

	
	imageM = al_load_bitmap("Sky2.jpg");
	imageJ = al_load_bitmap("back.png");
	imageI = al_load_bitmap("Sky2.png");

	sprite1 = al_load_bitmap("playerShip2_red.png");
	sprite2 = al_load_bitmap("playerShip2_green.png");

	fontM = al_load_ttf_font("full Pack 2025.ttf", 100, ALLEGRO_ALIGN_CENTER);
	fontI = al_load_ttf_font("DIMIS___.ttf", 100, ALLEGRO_ALIGN_CENTER);

	cron = al_create_timer(1.0 / 60.0);

	al_register_event_source(eventqueueM, al_get_keyboard_event_source());
	al_register_event_source(eventqueueM, al_get_timer_event_source(cron));
	al_register_event_source(eventqueueM, al_get_display_event_source(display));

	al_register_event_source(eventqueueJ, al_get_keyboard_event_source());
	al_register_event_source(eventqueueJ, al_get_timer_event_source(cron));
	al_register_event_source(eventqueueJ, al_get_display_event_source(display));

	al_register_event_source(eventqueueI, al_get_keyboard_event_source());
}
//End Inicializacion

//Colllision
int Collision(float x, float y, float x2, float y2, int width, int height, int width2, int height2) {
	if (x + width<x2 || x> x2 + width2 || y + height < y2 || y > y2 + height2) {
		return false;
		}
	return true;
}

//Pantalla de Menu
void MenuScreen() {

		al_draw_bitmap(imageM, 0, 0, 0);

		al_draw_text(fontM, al_map_rgb(255, 255, 255), 1500, 100, ALLEGRO_ALIGN_CENTER, "Space");
		al_draw_text(fontM, al_map_rgb(255, 255, 255), 1450, 250, ALLEGRO_ALIGN_CENTER, "Brawlers");

		if (opc == 0) {
			al_draw_text(fontM, al_map_rgb(192, 57, 43), 550, 500, ALLEGRO_ALIGN_RIGHT, "Jugar");
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 1175, 700, ALLEGRO_ALIGN_RIGHT, "Instrucciones");
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 450, 900, ALLEGRO_ALIGN_RIGHT, "Salir");
		}


		if (opc == 1) {
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 550, 500, ALLEGRO_ALIGN_RIGHT, "Jugar");
			al_draw_text(fontM, al_map_rgb(192, 57, 43), 1175, 700, ALLEGRO_ALIGN_RIGHT, "Instrucciones");
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 450, 900, ALLEGRO_ALIGN_RIGHT, "Salir");
		}

		if (opc == 2) {
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 550, 500, ALLEGRO_ALIGN_RIGHT, "Jugar");
			al_draw_text(fontM, al_map_rgb(255, 255, 255), 1175, 700, ALLEGRO_ALIGN_RIGHT, "Instrucciones");
			al_draw_text(fontM, al_map_rgb(192, 57, 43), 450, 900, ALLEGRO_ALIGN_RIGHT, "Salir");
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

//Pantalla de Instrucciones
void Instrucciones() {
	
		al_draw_bitmap(imageM, 0, 0, 0);

		al_draw_text(fontI, al_map_rgb(255, 255, 255), 1020, 0, ALLEGRO_ALIGN_CENTER, "*Instrucciones*");

		al_draw_text(fontI, al_map_rgb(255, 255, 255), 130, 350, ALLEGRO_ALIGN_CENTER, "A");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 270, 350, ALLEGRO_ALIGN_CENTER, "D");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 130, 250, ALLEGRO_ALIGN_CENTER, "<<--");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 270, 250, ALLEGRO_ALIGN_CENTER, "-->>");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 1300, 340, ALLEGRO_ALIGN_LEFT, "Movimiento");

		al_draw_text(fontI, al_map_rgb(255, 255, 255), 250, 500, ALLEGRO_ALIGN_CENTER, "[Spacebar]");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 1350, 515, ALLEGRO_ALIGN_LEFT, "Disparos");

		al_draw_text(fontI, al_map_rgb(255, 255, 255), 200, 700, ALLEGRO_ALIGN_CENTER, "[Esc]");
		al_draw_text(fontI, al_map_rgb(255, 255, 255), 1150, 720, ALLEGRO_ALIGN_LEFT, "Volver al menu");

		al_draw_text(fontI, al_map_rgb(255, 255, 255), 960, 950, ALLEGRO_ALIGN_CENTER, "Backspace(Volver al menu)");


		al_flip_display();
	}

//Controles para las Instrucciones
void ControlsInstrucciones() {

	al_wait_for_event(eventqueueI, &eventsI);
	if (eventsI.type == ALLEGRO_EVENT_KEY_DOWN) {

		switch (eventsI.keyboard.keycode) {

		case ALLEGRO_KEY_BACKSPACE:
			Instruccionesout = true;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			break;

		}
	}
}

//Pantalla del Juego
void GameInGraphics() {

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(imageJ, 0, 0, 0);
		al_draw_bitmap(sprite1, sprite1x, sprite1y, ALLEGRO_ALIGN_CENTER);
		al_draw_bitmap(sprite2, sprite2x, sprite2y, ALLEGRO_ALIGN_CENTER);

		al_flip_display();
}

//Controles del juego
void  GameInControls() {

	al_wait_for_event(eventqueueJ, &eventsJ);
	if (eventsJ.type == ALLEGRO_EVENT_TIMER) {
		al_get_keyboard_state(&keyboardstate);

		if (al_key_down(&keyboardstate, ALLEGRO_KEY_D)) {
			if (sprite1x < 1800) {
				sprite1x += speed;
			}
		}

		if (al_key_down(&keyboardstate, ALLEGRO_KEY_RIGHT)) {
			if (sprite2x < 1800) {
				sprite2x += speed;
			}
		}

		if (al_key_down(&keyboardstate, ALLEGRO_KEY_A)) {
			if (sprite1x > 20) {
				sprite1x -= speed;
			}
		}

		if (al_key_down(&keyboardstate, ALLEGRO_KEY_LEFT)) {
			if (sprite2x > 20) {
				sprite2x -= speed;
			}
		}

		if (al_key_down(&keyboardstate, ALLEGRO_KEY_SPACE)) {
			for (int i = 0; i <= 5; i++) {
				bullposx[i] = sprite1x + 55;
				bullposy[i] = sprite1y - 10;

				counter+=1;
				for(int i = 1; i <= counter; i++) {
					bullposy[i] -= 5;
					al_draw_filled_circle(bullposx[i], bullposy[i], 4, al_map_rgb(255, 255, 255));
					al_flip_display();
					break;
				}
			}

		}
			if (al_key_down(&keyboardstate, ALLEGRO_KEY_ESCAPE)) {
				Game = true;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
			}
		}
	}

//Controles del menu
void ControlsMenu() {

	al_wait_for_event(eventqueueM, &eventsM);
	if (eventsM.type == ALLEGRO_EVENT_KEY_DOWN) {

		switch (eventsM.keyboard.keycode) {

		case ALLEGRO_KEY_W:
			opc--;
			if (opc < 0) {
				opc = 2;
			}
			break;

		case ALLEGRO_KEY_S:
			opc++;
			if (opc > 2) {
				opc = 0;
			}
			break;

		case ALLEGRO_KEY_UP:
			opc--;
			if (opc < 0) {
				opc = 2;
			}
			break;

		case ALLEGRO_KEY_DOWN:
			opc++;
			if (opc > 2) {
				opc = 0;
			}
			break;

		case ALLEGRO_KEY_ENTER:
			if (opc == 1) {

				while (!Instruccionesout) {
					Instrucciones();
					ControlsInstrucciones();
				}
				Instruccionesout = false;
				break;
			}

			if (opc == 2) {

				Menuout = true;
				al_flip_display();
				al_destroy_display(display);
				break;
			}

			if (opc == 0) {
				al_start_timer(cron);
				while (!Game) {
					GameInGraphics();
					GameInControls();
				}
				Game = false;
				break;

			}
		}
	}
}

void MenuStart() {

	while (!Menuout) {
		MenuScreen();
		ControlsMenu();
	}
}

int main(int argc, char **argv)
{
	VarStart();
	MenuStart();
}


	



