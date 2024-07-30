#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include "enemy.h"
using namespace sf;
#include <SFML/Graphics.hpp>

class Invader : public Enemy
{
public:
    void update(float deltaTime) override = 0;
    //common to all 3 invaders
    void render(sf::RenderWindow& window) override{window.draw(enemy_sprite);}

    int getScoreValue() override = 0;
};
