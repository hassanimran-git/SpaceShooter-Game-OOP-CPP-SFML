#include <SFML//Graphics.hpp>
#include "player.h"
#pragma once
using namespace std;
using namespace sf;

class Bomb
{
public:
    Texture texture;
    Sprite sprite_Bomb;
    float speed;

    Bomb(float x, float y,float speed)
    {
        texture.loadFromFile("img/enemy_laser.png");
        sprite_Bomb.setTexture(texture);
        sprite_Bomb.setScale(0.75, 0.75);
        sprite_Bomb.setPosition(x, y);
        this->speed=speed;
    }
    // void updateBomb(int x,int y)
    // {
    //     // if(sprite_Bomb.getPosition().y >= 700)
    //     //     sprite_Bomb.setPosition(x,y);
        
    // }
    void move()
    {
        float delta_y=1;
        delta_y*=speed;
        sprite_Bomb.move(0, delta_y);
    } 
};



