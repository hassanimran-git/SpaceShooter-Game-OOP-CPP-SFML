#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;
#include <fstream>

class HighscoreWindow
{
public:
    Font font;
    Text highscoreText;
    RenderWindow window;

    // badges
    Texture b1t;
    Sprite b1s;
    Texture b2t;
    Sprite b2s;
    Texture b3t;
    Sprite b3s;

    HighscoreWindow()
    {
        font.loadFromFile("font.ttf");

        highscoreText.setFont(font);
        highscoreText.setCharacterSize(55);
        highscoreText.setFillColor(Color::White);
        highscoreText.setPosition(150, 200);
        window.create(VideoMode(780, 780), "Highscores");

        b1t.loadFromFile("img/b1.png");
        b1s.setTexture(b1t);
        b1s.setScale(0.09, 0.09);
        b1s.setPosition(130, 320);

        b2t.loadFromFile("img/b2.png");
        b2s.setTexture(b2t);
        b2s.setScale(0.06, 0.06);
        b2s.setPosition(130, 370);

        b3t.loadFromFile("img/b3.png");
        b3s.setTexture(b3t);
        b3s.setScale(0.15, 0.15);
        b3s.setPosition(130, 420);
    }

    void display_highscores()
    {
        ifstream file("highscores.txt");
        string line, highscores;

        // Add "Highscores: " text at the beginning
        highscores += "Highscores:\n\n";

        while (std::getline(file, line))
        {
            // Customize the font, size, and format of the data
            highscores += "- " + line + "\n";
        }

        file.close();

        highscoreText.setString(highscores);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }

            window.clear();

            Text backText("[esc] MENU", font, 20);
            backText.setPosition(200, 600);
            backText.setFillColor(Color::White);

            window.draw(highscoreText);
            window.draw(b1s);
            window.draw(b2s);
            window.draw(b3s);
            window.draw(backText);
            window.display();
        }
    }
};
