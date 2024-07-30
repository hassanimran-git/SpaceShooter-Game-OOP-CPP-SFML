#include "player.h"
#include "Bullet.h"
#include "alpha.h"
#include "beta.h"
#include "gama.h"

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <ios> 

using namespace std;
using namespace std;

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Player p;
    int ship_x;
    int ship_y;
    int bullet_x;
    int bullet_y;    
    int level;
    float delay=0;
    int lives;
    int score=0;
    bool gameOver;
    bool EnemiesDead;
    string playerName;
    float powerup_acquired;
    bool sheild=false;
    bool fire_powerup=false;

    bool EnemyCreated=false;

    int enemy_count=19; //enemy here

    //lives
    Texture life_tex;
    Sprite l1;
    Sprite l2;
    Sprite l3;

    //enemy here
    Enemy** enemy = new Enemy*[enemy_count]; 

    Game()
    {
        bg_texture.loadFromFile("img/Backgroud_2.jpeg");
        background.setTexture(bg_texture);
        level=1;
        lives=3;
        score=0;
        gameOver=false;
        int x=10,y=15;
        life_tex.loadFromFile("img/life.png");
        l1.setTexture(life_tex);
        l1.setScale(0.035,0.035);
        l1.setPosition(x,y);

        l2.setTexture(life_tex);
        l2.setScale(0.035,0.035);
        l2.setPosition(x+40,y);

        l3.setTexture(life_tex);
        l3.setScale(0.035,0.035);
        l3.setPosition(x+80,y);

    }

    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        float timer = 0;


        bool isPaused = false; // Flag to indicate if the game is paused

        Font font;
        font.loadFromFile("font.ttf");
        Text levelText;
        levelText.setFont(font);
        levelText.setCharacterSize(24);
        levelText.setPosition(650, 10);

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            delay+=time;
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e)) 
            {
                if (e.type == Event::Closed)
                    window.close();
                else if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::P)
                    {
                        isPaused = !isPaused; // Toggle pause state
                    }
                }
            }

            if (!isPaused)
            {
                // Only update and render the game when it's not paused

                if (Keyboard::isKeyPressed(Keyboard::Left))
                    p.move("l");
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    p.move("r");
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    p.move("u");
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    p.move("d");

                // Call your functions here




                ship_x = p.sprite_ship.getPosition().x;
                ship_y = p.sprite_ship.getPosition().y;
                bullet_x = p.b->sprite_bullet.getPosition().x;
                bullet_y = p.b->sprite_bullet.getPosition().y;


                if ((Keyboard::isKeyPressed(Keyboard::Space)) && bullet_y < -65)
                    p.b->sprite_bullet.setPosition(ship_x + 30, ship_y);


                if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
                {
                    p.sprite_ship.setTexture(p.tiltedRight);
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
                {
                    p.sprite_ship.setTexture(p.tiltedLeft);
                }
                else
                {
                    p.sprite_ship.setTexture(p.tex);
                }

                levelText.setString("Level: " + std::to_string(level));


                ManageEnemies();

                p.fire();

                //randomization of addons
                p.callAddOn();


                //drawing all sprites
                window.clear(Color::Black);
                window.draw(background);
                window.draw(p.b->sprite_bullet);
                window.draw(p.sprite_ship);
        
                window.draw(levelText);


                //drawing add ons
                for (int i = 0; i < 4; i++)
                    window.draw(p.add[i]->addon_sprite);
                
                //draw sheild if add on is active
                if(sheild){window.draw(p.add[3]->forceFeild_sprite);}
                
                //regular checks for addons in everyloop
                update_addon();
                addonCollisionCheck();

                
                //checking lives and drawing life sprites accordingly
                if(lives>0)
                    window.draw(l1);
                if(lives>1)
                    window.draw(l2);
                if(lives>2)
                    window.draw(l3);

                //enemy here
                //draw enemies,bombs + collisons + alive enemies
                EnemiesDead=true;
                int randomNumber;
                for (int i = 0; i < enemy_count; i++){
                    randomNumber = rand() % 10 + 1;
                    enemy[i]->render(window);
                    window.draw(enemy[i]->bomb->sprite_Bomb); 
                    enemy[i]->update(delay + randomNumber);// Update Enemy and its Bomb
                    CheckCollisions(enemy[i]);
                    if(enemy[i]->enemy_sprite.getPosition().y!=1000)//enemy alive
                        EnemiesDead=false;
                }


                if(EnemiesDead && level==2){gameOver=true;}
                if(gameOver)
                {                    
                    window.close();
                    GameOver();                    
                }

                if(EnemiesDead && level==1)
                {   
                    level++;
                    EnemyCreated=false;
                    enemy_count=14;
                }

                
                window.display();///DIsplays Everything Drawn
            }
            else
            {
                //PAUSING FUNCTIONALITY

                Font font;
                font.loadFromFile("font.ttf"); 
                Text pauseText("Game Paused", font, 36);
                pauseText.setFillColor(Color::White);
                pauseText.setStyle(Text::Bold);
                pauseText.setPosition(250,350);

                window.clear(Color::Black);
                window.draw(background);
                // window.draw(p.b->sprite_bullet);
                // window.draw(p.sprite_ship);
                window.draw(pauseText);

                window.display();
            }
        }
    }
    //  Function Definitions



    void ManageEnemies()
    {
        if(!EnemyCreated && level==1)
        {
            int X=100,Y=100;
            // Alpha enemies
            enemy[0] = new Alpha(200-X, 100);
            enemy[1] = new Alpha(240-X, 130);
            enemy[2] = new Alpha(280-X, 160);
            enemy[3] = new Alpha(320-X, 190);
            enemy[4] = new Alpha(360-X, 220);

            // Beta enemies
            enemy[5] = new Beta(400-X, 100);
            enemy[6] = new Beta(440-X, 130);
            enemy[7] = new Beta(480-X, 160);
            enemy[8] = new Beta(520-X, 190);
            enemy[9] = new Beta(560-X, 220);

            // Gamma enemies
            enemy[10] = new Gamma(600-X, 100);
            enemy[11] = new Gamma(640-X, 130);
            enemy[12] = new Gamma(680-X, 160);
            enemy[13] = new Gamma(720-X, 190);
            enemy[14] = new Gamma(760-X, 220);

            // Alpha enemies
            enemy[15] = new Alpha(400-X, 70);
            enemy[16] = new Alpha(440-X, 70);
            enemy[17] = new Alpha(480-X, 70);
            enemy[18] = new Alpha(520-X, 70);
            enemy[19] = new Alpha(560-X, 70);

            EnemyCreated=true;
        }
        if(!EnemyCreated && level==2)
        {
            int xa=150;
            enemy[0] = new Alpha(500-xa, 70);
            enemy[1] = new Alpha(440-xa, 120);
            enemy[2] = new Alpha(560-xa, 120);
            enemy[3] = new Alpha(500-xa, 170);
            enemy[4] = new Alpha(440-xa, 220);
            enemy[5] = new Alpha(560-xa, 220);
            enemy[6] = new Alpha(500-xa, 270);
            enemy[7] = new Alpha(380-xa, 170);
            enemy[8] = new Alpha(620-xa, 170);
            enemy[9] = new Alpha(230-xa, 170);
            enemy[10]= new Alpha(770-xa, 170);
            enemy[11]= new Alpha(380-xa, 120);
            enemy[12]= new Alpha(620-xa, 120);
            enemy[13]= new Alpha(380-xa, 220);
            enemy[14]= new Alpha(620-xa, 220);

            EnemyCreated=true;
        }

    }

    void addonCollisionCheck()
    {
        FloatRect playerBounds = p.sprite_ship.getGlobalBounds();
        FloatRect life_bounds  = p.add[0]->addon_sprite.getGlobalBounds();
        FloatRect danger_bounds= p.add[1]->addon_sprite.getGlobalBounds();
        FloatRect fire_bounds  = p.add[2]->addon_sprite.getGlobalBounds();
        FloatRect sheild_bounds= p.add[3]->addon_sprite.getGlobalBounds();

        if (playerBounds.intersects(life_bounds)) {
            if(lives < 3){lives++;  p.add[0]->addon_sprite.setPosition(1000,-1000);}}

        if (playerBounds.intersects(danger_bounds)){gameOver=true;}



        if (playerBounds.intersects(fire_bounds))
        {
            fire_powerup=true;
            p.add[2]->addon_sprite.setPosition(1000,-1000);


        }
        if (playerBounds.intersects(sheild_bounds))
        {
            sheild=true;
            p.add[3]->addon_sprite.setPosition(1000,-1000);
        }

        
    }

    void update_addon() //mmove + danger sign conditions
    {
        float addon_speed=0.1;
        float delta_y=1;
        delta_y*=addon_speed;

        //moving all add-ons
        for (int i = 0; i < 4; i++){p.add[i]->addon_sprite.move(0, delta_y);} 

        if((p.add[2]->addon_sprite.getPosition().y)>200){fire_powerup=false;}
        if((p.add[3]->addon_sprite.getPosition().y)>200){sheild=false;}
        if(sheild){p.add[3]->forceFeild_sprite.setPosition(ship_x-20,ship_y-20);}
    }

    void CheckCollisions(Enemy* e)
    {
        // Get the bounds of all objects
        FloatRect playerBounds = p.sprite_ship.getGlobalBounds();
        FloatRect BulletBounds = p.b->sprite_bullet.getGlobalBounds();
        FloatRect enemyBounds = e->enemy_sprite.getGlobalBounds();
        FloatRect bombBounds = e->bomb->sprite_Bomb.getGlobalBounds();
        // Check if the bounding boxes intersect

        if (enemyBounds.intersects(playerBounds)) //ship - enemy collide
        {
            e->enemy_sprite.setPosition(-1000,1000);
            lives-=1;
            if(lives<=0){gameOver=true;}
            // cout<<"Collsion!"<<endl;
        }
        if (enemyBounds.intersects(BulletBounds)) //enemy shot
        {
            if(!fire_powerup)   
                p.b->sprite_bullet.setPosition(ship_x+1000,ship_y);

            e->enemy_sprite.setPosition(-1000,1000);// enemy exiled
            // cout<<"Enemy Hit!"<<endl;
            score+=level*(e->getScoreValue());
            // cout<<"score increased by : "<<level*(e->getScoreValue())<<endl;;
        }
        if ((bombBounds.intersects(playerBounds))) //player shot
        {
            if(!sheild)
            {
                // cout<<"Ship Hit!"<<endl;
                // e->bomb->sprite_Bomb.setPosition(e->enemy_sprite.getPosition().x+17,e->enemy_sprite.getPosition().y);
                e->bomb->sprite_Bomb.setPosition(-1000,1000);
                lives-=1;
                if(lives<=0){gameOver=true;}
            }

        }
    }

    void GameOver()
    {
        RenderWindow gameOverWindow(VideoMode(780, 780), "Game Over");
        Sprite bg;
        Texture texa;
        texa.loadFromFile("img/Backgroud_2.jpeg");
        bg.setTexture(texa);

        while (gameOverWindow.isOpen())
        {
            Event e;
            while (gameOverWindow.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    gameOverWindow.close();
            }
            gameOverWindow.clear(); // Clear the window before drawing
            gameOverWindow.draw(bg);


            // Create Game Over text
            Font font;
            font.loadFromFile("font.ttf"); 
            Text gameOverText("Game Over", font, 70); 
            gameOverText.setPosition(175, 200); 

            //score text
            Text scoreText("Your Score is: " + to_string(score), font, 35); 
            scoreText.setPosition(220, 300); 

            // enter name text
            Text enterNameText("Enter Your Name:", font, 30); 
            enterNameText.setPosition(220, 400); 

            bool typing = true; 

            while (gameOverWindow.isOpen())
            {
                Event e;
                while (gameOverWindow.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        gameOverWindow.close();

                    if (e.type == Event::TextEntered && typing)
                    {
                        //if backspace pressed Remove the last character
                        //else if normal char in assci range then Append
                        if (e.text.unicode == '\b' && !playerName.empty()){playerName.pop_back(); }
                        else if (e.text.unicode < 128 && e.text.unicode != '\b'){playerName += static_cast<char>(e.text.unicode); }
                    }

                    if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
                    {
                        // cout<<"Name Recived: "<<playerName<<endl;
                        // Save the playerName to a file or do further processing
                        gameOverWindow.close();
                        SaveToFile();
                    }
                }

                gameOverWindow.clear(); // Clear the game over window

                gameOverWindow.draw(bg); // Draw the background sprite

                gameOverWindow.draw(gameOverText); // Draw the "Game Over" text
                gameOverWindow.draw(scoreText); // Draw the score text
                gameOverWindow.draw(enterNameText); // Draw the "Enter Your Name" text

                if (typing)
                {
                    Text playerNameText(playerName, font, 35); // Create the text object for the player's name
                    playerNameText.setPosition(300, 500); // Set the position of the player's name text
                    gameOverWindow.draw(playerNameText); // Draw the player's name text
                }

                gameOverWindow.display(); // Display the contents of the game over window
            }
        }

    }
    
///////////////////////////////////////////////////////////////////////////
//  FILE HANDLING


const int records = 4;
const int top = 3;
struct playerData //struct to store input line
{
    string name = "anonymous";
    int score = 0;
};



    void SaveToFile()
    {
        ofstream scoreFile("highscores.txt", ios::app);//open file in append mode
        if (scoreFile.is_open())
        {
            // append name and score 
            if(playerName=="")
                playerName = "NULL";
            scoreFile << playerName << " " << score << endl;
            scoreFile.close();

            sortFileByScore();
        }
    }

//////////////////////////////////////////////////////////////////////


void sortFileByScore() {

    playerData pd[records];

    // Open the input file
    ifstream inputFile("highscores.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return;
    }

    // Read player data from the input file
    for (int i = 0; i < records; ++i) {
        inputFile >> pd[i].name >> pd[i].score;
    }

    // Close the input file
    inputFile.close();

    // Sort the players array in descending order based on the score
    for (int i = 0; i < records - 1; ++i) {
        for (int j = 0; j < records - i - 1; ++j) {
            if (pd[j].score < pd[j + 1].score) {
                playerData temp = pd[j];
                pd[j] = pd[j + 1];
                pd[j + 1] = temp;
            }
        }
    }

    // Open the output file
    ofstream outputFile("highscores.txt");
    if (!outputFile.is_open()) {
        cout << "Unable to open the file for writing." << endl;
        return;
    }

    // Write the top three players' data to the output file
    for (int i = 0; i < top; ++i) {
        outputFile << pd[i].name << ' ' << pd[i].score << endl;
    }
    // Close the output file
    outputFile.close();

    // cout << "Top three players sorted and stored successfully." << endl;
}

///////////////////////////////////////////////////////////////////////////

};

// float enemyLeft = enemyPosition.x;
// float enemyRight = enemyPosition.x + enemySize.x;
// float enemyTop = enemyPosition.y;
// float enemyBottom = enemyPosition.y + enemySize.y;
// float playerLeft = playerPosition.x;
// float playerRight = playerPosition.x + playerSize.x;
// float playerTop = playerPosition.y;
// float playerBottom = playerPosition.y + playerSize.y;
// if (enemyRight >= playerLeft && enemyLeft <= playerRight && enemyBottom >= playerTop && enemyTop <= playerBottom)