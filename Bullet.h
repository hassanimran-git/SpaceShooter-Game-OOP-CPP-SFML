#include <SFML//Graphics.hpp>
#include "player.h"
#pragma once
using namespace std;
using namespace sf;

class Bullet
{   
public:
float speed = 3.0;
    Texture texture;    
    Sprite sprite_bullet; 
    

    Bullet()
    {
        texture.loadFromFile("img/PNG/Lasers/laserRed05.png");//laserRed05.png  laserBlue02.png
        sprite_bullet.setTexture(texture);
        sprite_bullet.setScale(1,1);
        
    }

    void move()
    {
        float delta_y=-1;
        delta_y*=speed;
        sprite_bullet.move(0, delta_y);
    } 
    ~Bullet(){}
};


