#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include "bomb.h"
using namespace sf;

class Enemy
{
public:
    Texture texture;
    Sprite enemy_sprite;
    int x,y,speed,health;
    Bomb* bomb;


    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual int getScoreValue() = 0;

};

/*
    Enemy** enemy = new Enemy*[3];

    // Create instances of different enemy types
        enemy[0] = new Alpha();
        enemy[1] = new Beta();
        enemy[2] = new Gamma();

    //Enemies display
        window.draw(enemy[0]->enemy_sprite); 
        window.draw(enemy[1]->enemy_sprite); 
        window.draw(enemy[2]->enemy_sprite); 

        or 

    
    //Enemies display
    for (int i = 0; i < 3; i++)
        enemy[i]->render(window);

*/
