#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include "invader.h"
using namespace sf;
#include <SFML/Graphics.hpp>

class Beta : public Invader
{
public:

int betaDelay=3;
float bombSpeed = 0.35;
    Beta(int X,int Y)
    {
        texture.loadFromFile("img/enemy_2.png");
        enemy_sprite.setTexture(texture);
	    x=X;y=Y;
	    enemy_sprite.setPosition(x,y);
	    enemy_sprite.setScale(0.45,0.45);
   	    bomb = new Bomb(enemy_sprite.getPosition().x+22,enemy_sprite.getPosition().y+10,bombSpeed);

    }
    

    void update(float delay) override
    {
        int delay_int=delay;
        if(delay_int%betaDelay==0)
            bomb->sprite_Bomb.setPosition(enemy_sprite.getPosition().x+15,enemy_sprite.getPosition().y+17);

        bomb->move();
    }

    int getScoreValue() override{return 20;}

};
