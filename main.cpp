// simple pac man game where u shoot ghost

#include <SFML/Graphics.hpp>   //using namespace sf
#include <iostream> // to show console output

int main()
{
    // pacman movement speed
    float speed = .5;
    
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    // window that we can play the game in
    // dimensions width: x; height: y
    sf::RenderWindow window(sf::VideoMode(500, 500), "PacMan Game");

    
    // declare textures; textures load an image into the GPU Memory
    sf::Texture t1, t2, t3;
    // image of the background
    t1.loadFromFile("/Users/michellelim/Desktop/images/blue.png");
    // image of dot
    t2.loadFromFile("/Users/michellelim/Desktop/images/dot.png");
    // image of pacman
    t3.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    
    
    // putting texture onto the sprite; sprite has physical dimmensions that can be set in
    // coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite backgroundSprite(t1);
    
    sf::Sprite dotSprite(t2);
    
    sf::Sprite pacmanSprite(t3);
    // initially set position of pacman in the center of the window
    pacmanSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
    // using texture rectangle bc i don't want to use my entire texture
    // (x, y, w, h) my textures are 20x20 pixels
    pacmanSprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
    

    
    // setting the icon
    sf::Image gameIcon;
    gameIcon.loadFromFile("/Users/michellelim/Desktop/images/pacmanRight.png");
    // using icon size as the dimensions and setting it
    window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
    
    // for score TEXT
    sf::Font font;
    font.loadFromFile("/Users/michellelim/Desktop/arial.ttf");
    sf::Text text("SCORE: ", font, 20);
    // set color of text
    text.setColor(sf::Color::White);
    text.setPosition(0, 0);

    
    // initially set the position of dot

    
    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;
    while (window.isOpen())
    {
        //Should be placed in while loop as shown here to update
        //timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        //Allow us to check when a user does something
        sf::Event e;
        
        //Check when the window is closed
        while (window.pollEvent(e))
        {
            //If user presses x in the top right, Windows, top left, Mac,  close the window
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear();    // clear the window so new frame can be drawn in
        
        // print the dimensions of my window onto console
        // std::cout << window.getSize().x << " " << window.sf::Window::getSize().y << std::endl;
        
        // controls for pacman by user; created speed variable so it's easier if i want to change his speed
        // when up arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pacmanSprite.move(0, -speed);
            pacmanSprite.setTextureRect(sf::IntRect(0, 20, 20, 20));
        }
        // when down array key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pacmanSprite.move(0, speed);
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*2, 20, 20));
        }
        // when left arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pacmanSprite.move(-speed, 0);
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*3, 20, 20));
        }
        // when right arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pacmanSprite.move(speed, 0);
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*0, 20, 20));
        }
        
        // order matters bc we will draw over items listed first
        // so background should be the first thing to draw
        

        // display pacman sprite
        // pacmanSprite.setPosition(p.x*size, p.y*size);
        window.draw(pacmanSprite);
        
        // display dot sprite
        // dotSprite.setPosition(d.x*size, d.y*size);
        window.draw(dotSprite);
        
        // display score text
        window.draw(text);
        //Show everything we have drawn on the screen
    
        window.display();
    }
    return 0;
}
