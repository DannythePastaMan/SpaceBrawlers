#pragma once
#include <allegro5\allegro_primitives.h>
class bala
{
public:
	int coordenadaX;
	int coordenadaY;
	bool draw = false;

	void dibujar() {
		while (!draw) {
			draw = true;
			al_draw_filled_circle(coordenadaX, coordenadaY, 4, al_map_rgb(255, 255, 255));
			al_flip_display();
		}
	}
	bala(int coordenadaX, int coordenadaY) {
		dibujar();
		this->coordenadaX = coordenadaX;
		this->coordenadaY = coordenadaY;
	}

	
	

	~bala();
};

