#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include "invader.h"
using namespace sf;
#include <SFML/Graphics.hpp>

class Alpha : public Invader
{
public:
    int alphaDelay=5;
    float bombSpeed=0.2;

    Alpha(int X,int Y)
    {
        texture.loadFromFile("img/enemy_1.png");
        enemy_sprite.setTexture(texture);
	    x=X;y=Y;
	    enemy_sprite.setPosition(x,y);
	    enemy_sprite.setScale(0.5,0.5);
	    bomb = new Bomb(enemy_sprite.getPosition().x+22,enemy_sprite.getPosition().y+10,bombSpeed);
    }


    void update(float delay) override
    {
        int delay_int=delay;
        if(delay_int%alphaDelay==0 && bomb->sprite_Bomb.getPosition().y>800)
            bomb->sprite_Bomb.setPosition(enemy_sprite.getPosition().x+20,enemy_sprite.getPosition().y);

        bomb->move();
    }
    
    int getScoreValue() override{return 10;}
    
};
