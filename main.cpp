// simple pac man game where u only need to clear all dots
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 30;
int size = 20;                  //number of pixels
int w = size * num_horzBox;     //background number of pixels in width
int h = size * num_vertBox;     //background number of pixels in height

// variables to dertermine length and direction
int direction;    //direction character is moving
int character_length = 1; // size of the character

struct pacman
{
    int x, y;       // only need one sprite needed for one pacman item
}p;

// this is the dot that the pacman will eat
// actual dots in game is an array of x,y coordinates of dot sprite
struct Fruit
{
    int x, y;    //each sprite of food needs an x,y coordinate
}food[100];

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    //Window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "PacMan Game");
    
    //Textures load an image into the GPU Memory
    sf::Texture t1, t2, t3;
    // image of the background
    t1.loadFromFile("/Users/michellelim/Desktop/images/white.png");
    // image of dot
    t2.loadFromFile("/Users/michellelim/Desktop/images/dot.png");
    // image of pacman
    t3.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    
    //Sprite has physical dimmensions that can be set in
    //coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite background(t1);
    sf::Sprite dot(t2);
    sf::Sprite pacman(t3);
    
    //***NEW*** initially place food somewhere on screen
    food[0].x = 10;
    food[0].y = 10;
    
    // initially place snake 1 somewhere
    p.x = 15;
    p.y = 15;

    
    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;
    while (window.isOpen())
    {
        //Error in class I placed this before the while loop
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
        
        // controls for pacman by user
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;
        
        /*****************
         //Draw in window
         *****************/
        window.clear();    //clear the window so new frame can be drawn in
        
        //NOTE: Order matters as we will draw over items listed first.
        //Hence the background should be the first thing you will always do
        //1st: Draw Background first
        for (int i = 0; i < num_horzBox; i++)
        {
            for (int j = 0; j < num_vertBox; j++)
            {
                //Set position of background sprite one at a time
                background.setPosition(i*size, j*size);
                //Draw sprite1 but, do not show it on screen.
                window.draw(background);
            }
        }
        
        // draw dots next otherwise background will be drawn over dots
        for (int i=0; i<num_horzBox; i++) {
            for (int j=0; j<num_vertBox; j++) {
                // set position of dot sprite one at a time
                dot.setPosition(i*size, j*size);
                window.draw(dot);
            }
        }
    
        // set position of pacman sprite
        pacman.setPosition(p.x*size, p.y*size);
        window.draw(pacman);
        
        
        //Show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
