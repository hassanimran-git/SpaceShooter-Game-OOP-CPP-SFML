
    #include "game.h"
    #include "highscoreWindow.h"
    using namespace sf;

    class Menu {
    public:
        Text options[4];
        Font font;
        int selectedOption;
        Game g; 


        Menu() {
            int x=250;
            int y=200;
            font.loadFromFile("font.ttf");

            options[0].setFont(font);
            options[0].setString("New Game");
            options[0].setCharacterSize(48);
            options[0].setFillColor(Color::White);
            options[0].setPosition(x, y);

            options[1].setFont(font);
            options[1].setString("Resume");
            options[1].setCharacterSize(48);
            options[1].setFillColor(Color::White);
            options[1].setPosition(x+30, y+100);

            options[2].setFont(font);
            options[2].setString("Highscores");
            options[2].setCharacterSize(48);
            options[2].setFillColor(Color::White);
            options[2].setPosition(x-10, y+200);

            options[3].setFont(font);
            options[3].setString("Exit");
            options[3].setCharacterSize(48);
            options[3].setFillColor(Color::White);
            options[3].setPosition(x+75, y+300);

            selectedOption = 0;
        }

        void display_menu(RenderWindow& window) {

        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        if (selectedOption > 0) {
                            selectedOption--;
                        }
                    }
                    if (event.key.code == Keyboard::Down) {
                        if (selectedOption < 3) {
                            selectedOption++;
                        }
                    }
                    if (event.key.code == Keyboard::Return) {
                        switch (selectedOption) {
                        case 0:
                            window.close();
                            // Start game
                                g.start_game();
                                
                            break;
                        case 1:
                            // Continue game
                            break;
                        case 2:
                            high();
                            // window.close();

                            // Highscores
                           
                            break;
                        case 3:
                            // Exit
                            window.close();
                            break;
                        }
                    }
                }
            }

            // Update selected option appearance
            for (int i = 0; i < 4; i++) {
                if (i == selectedOption) {
                    options[i].setFillColor(Color::Cyan);
                }
                else {
                    options[i].setFillColor(Color::White);
                }
            }

            // Draw menu options
            window.clear();
            for (int i = 0; i < 4; i++) {
                window.draw(options[i]);
            }
            window.display();
        }
    }


    void high()
    {
        HighscoreWindow h;
            h.display_highscores();
    }


    };