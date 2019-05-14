// simple pac man game where u only need to get one dot
// and try to get as many before the time runs out
#include <SFML/Graphics.hpp>   //using namespace sf

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 30;
int size = 20;                  //number of pixels
int w = size * num_horzBox;     //background number of pixels in width
int h = size * num_vertBox;     //background number of pixels in height

// variables to dertermine length and direction
int direction;    //direction character is moving
int character_length = 1; // size of the character

struct pac {
    int x, y;   // only need one sprite needed for one pacman item
}p;

// this is the dot that the pacman will eat
struct dots {
    int x, y;    // only need one sprite needed for one dot item
}d;


void move() {
     //check if pacman = dot location
     if (((p.x) == d.x) && ((p.y) == d.y)) {
         //Randomly place food somewhere else
         d.x = rand() % num_horzBox;
         d.y = rand() % num_vertBox;
     }
}

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    // window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "PacMan Game");
    
    // textures load an image into the GPU Memory
    sf::Texture t1, t2, t3;
    // image of the background
    t1.loadFromFile("/Users/michellelim/Desktop/images/blue.png");
    // image of dot
    t2.loadFromFile("/Users/michellelim/Desktop/images/dot.png");
    // image of pacman
    t3.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    
    // sprite has physical dimmensions that can be set in
    // coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite backgroundSprite(t1);
    sf::Sprite dotSprite(t2);
    sf::Sprite pacmanSprite(t3);
    
    // setting the icon; i am making the icon the same as pacman sprite
    sf::Image gameIcon;
    gameIcon.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    // using icon size as the dimensions and setting it
    window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
    
    // initially set the position of pacman
    pacmanSprite.setPosition(200, 200);
    
    // initially set the position of dot
    dotSprite.setPosition(100, 300);
    
    while (window.isOpen())
    {
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
        
        /*****************
         //Draw in window
         *****************/
        window.clear();    //clear the window so new frame can be drawn in
        
        // controls for pacman by user
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pacmanSprite.move(0, -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pacmanSprite.move(0, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pacmanSprite.move(-1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pacmanSprite.move(1, 0);
        }
        
        //NOTE: Order matters as we will draw over items listed first.
        //Hence the background should be the first thing you will always do
        //1st: Draw Background first
        for (int i = 0; i < num_horzBox; i++)
        {
            for (int j = 0; j < num_vertBox; j++)
            {
                //Set position of background sprite one at a time
                backgroundSprite.setPosition(i*size, j*size);
                //Draw sprite1 but, do not show it on screen.
                window.draw(backgroundSprite);
            }
        }
        
        // display pacman sprite
        window.draw(pacmanSprite);
        
        // display dot sprite
        window.draw(dotSprite);
        
        //Show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
