#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Bullet.h"
#include "addOn.h"

using namespace sf;
class Player
{
public:
	Texture tex;
	Sprite sprite_ship;
	float speed = 0.6;
	int x, y;
	Bullet *b;
	Texture tiltedRight;
	Texture tiltedLeft;
	AddOns** add = new AddOns*[4];

	Player()
	{
		tex.loadFromFile("img/player_ship.png");
		sprite_ship.setTexture(tex);
		x = 360;
		y = 600;
		sprite_ship.setPosition(x, y);
		sprite_ship.setScale(0.65, 0.65); // 0.75,0.75
		b = new Bullet();
		tiltedRight.loadFromFile("img/ship_right_tilt.png");
		tiltedLeft.loadFromFile("img/ship_left_tilt.png");

   		add[0] = new Lives();
		add[1] = new Danger();
		add[2] = new Fire();
		add[3] = new Sheild();

	}
	void fire()
	{
		b->move();
	}
	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		if (s == "l")
		{
			delta_x = -1;
		} // move the player left
		else if (s == "r")
		{
			delta_x = 1;
		}
		// move the player right
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;

		delta_x *= speed;
		delta_y *= speed;

		// WRAP AROUND

		x = sprite_ship.getPosition().x;
		y = sprite_ship.getPosition().y;
		// geting players cordinates;

		if (x > 771)
		{
			sprite_ship.setPosition(-71, y);
		} // right
		if (x < -71)
		{
			sprite_ship.setPosition(771, y);
		} // left

		if (y > 771)
		{
			sprite_ship.setPosition(x, -71);
		} // down
		if (y < -70)
		{
			sprite_ship.setPosition(x, 771);
		} // up

		sprite_ship.move(delta_x, delta_y);
	}

	void callAddOn()
	{
		srand(time(0));
		int x=400,y=-30;
		int randomNumber = rand() % 50 + 1;
		if(randomNumber==1){add[0]->addon_sprite.setPosition(x,y);}
		if(randomNumber==2){add[1]->addon_sprite.setPosition(x,y);}
		if(randomNumber==3){add[2]->addon_sprite.setPosition(x,y);}
		if(randomNumber==4){add[3]->addon_sprite.setPosition(x,y);}
	}
};
