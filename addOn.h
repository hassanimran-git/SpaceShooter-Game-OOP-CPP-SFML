    #include <SFML/Graphics.hpp>
    #include <time.h>
    #include <iostream>
    #include <fstream> 
    #include <algorithm>
    #include <ios> 
    using namespace sf;
    using namespace std;

    class AddOns 
    {
        public:
            int x,y,speed;
            Sprite addon_sprite;
            Texture sprite_tex;
            Sprite forceFeild_sprite;
            Texture forceFeild_tex;
    };


    class Lives : public AddOns
    {
        public:

            Lives()
            {   
                sprite_tex.loadFromFile("img/life.png");
                addon_sprite.setTexture(sprite_tex);
                addon_sprite.setScale(0.03,0.03);
                addon_sprite.setPosition(1000,1000);
            }
    };



    class Danger : public AddOns
    {
        public:
            Danger()
            {   
                sprite_tex.loadFromFile("img/danger.png");
                addon_sprite.setTexture(sprite_tex);
                addon_sprite.setScale(0.4,0.4);
                addon_sprite.setPosition(1000,1000);
            }
    };


    class Fire : public AddOns
    {
        public:
            Fire()
            {   
                sprite_tex.loadFromFile("img/fire.png");
                addon_sprite.setTexture(sprite_tex);
                addon_sprite.setScale(0.03,0.03);
                addon_sprite.setPosition(1000,1000);
            }
    };

    class Sheild : public AddOns
    {
        public:

            
            Sheild()
            {   
                sprite_tex.loadFromFile("img/sheild.png");
                addon_sprite.setTexture(sprite_tex);
                addon_sprite.setScale(0.07,0.07);
                forceFeild_tex.loadFromFile("img/forceFeild.png");
                forceFeild_sprite.setTexture(forceFeild_tex);
                forceFeild_sprite.setScale(0.8,0.8);
                addon_sprite.setPosition(1000,1000);
            }
    };