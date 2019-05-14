// pacman game
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>
#include <string>              // std::string, std::to_string

//dimensions for window size and background
int num_vertBox = 20, num_horzBox = 20;
int size = 20; //number of pixels
int w = size * num_horzBox;    //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height

// variables
int direction;          // direction pacman is moving
int pacmanSize = 1;     // size of pacman
int score = 0;          // player score, initally 0

// pacman in game is an array of x, y coordinates of pacmanSprite
struct Pacman
{
    int x, y;        // each sprite of pacman needs an x,y coordinate
}p[100];

// the dot that pacman will eat
struct Dot
{
    int x, y;    // only need one sprite needed for one dot item
}d;

//move pacman based on user input
//forward by iterating through arrays previous position
void move() {
    // check if pacman location = dot location
    // if locations are same, that means pacman has eaten a dot
    // increment score
    if (((p[0].x) == d.x) && ((p[0].y) == d.y))
    {
        score += 5;
        
        // randomly place dot somewhere else
        d.x = rand() % num_horzBox;
        d.y = rand() % num_vertBox;
    }
    
    
    // boundary checking pacman as is hits screen end
    // loop pacman back on other side
    // LEFT and RIGHT
    if (p[0].x > num_horzBox)   // if location of pacman goes past the width of window; leaves from right of screen
        p[0].x = 0;             // make pacman come back from left of screen
    if (p[0].x < 0)             // if location of pacman goes less than the width of window; leaves from left of screen
        p[0].x = num_horzBox;   // make pacman come back from right of screen
    // TOP and BOTTOM
    if (p[0].y > num_vertBox)   // if location of pacman goes past the height of window; leaves from bottom of screen
        p[0].y = 0;             // make pacman come back from top of screen
    if (p[0].y < 0)             // if location of pacman goes less than the height of window; leaves from top of screen
        p[0].y = num_vertBox;   // make pacman come back from bottom of screen
    
    // location of pacman, p[0] depends on direction user inputs
    // x is for left/right; y is for up/down
    if (direction == 0)
        p[0].y -= 1;            //if user presses up
    if (direction == 1)
        p[0].y += 1;            //if user presses down
    if (direction == 2)
        p[0].x -= 1;            //if user presses left
    if (direction == 3)
        p[0].x += 1;            //if user presses right
    
}

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    //Window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "Pacman Game");
    
    //Textures load an image into the GPU Memory
    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("/Users/michellelim/Desktop/images/blue.png");
    // color of first snake
    t2.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    // 1) change the image of the fruit
    t3.loadFromFile("/Users/michellelim/Desktop/images/dot.png");
    
    //Sprite has physical dimmensions that can be set in
    //coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite backgroundSprite(t1);
    sf::Sprite pacmanSprite(t2);
    // using texture rectangle bc i don't want to use my entire texture
    // (x, y, w, h) my textures are 20x20 pixels
    pacmanSprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
    sf::Sprite dotSprite(t3);
    
    // setting the icon
    sf::Image gameIcon;
    gameIcon.loadFromFile("/Users/michellelim/Desktop/images/pacmanRight.png");
    // using icon size as the dimensions and setting it
    window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
    
    // for score TEXT
    // first need to upload font
    sf::Font font;
    font.loadFromFile("/Users/michellelim/Desktop/arial.ttf");
    // text will print SCORE: and making size of font 20
    sf::Text text("SCORE: ", font, 20);
    // set color of text
    text.setColor(sf::Color::White);
    text.setPosition(0, 0);
    
    //***NEW*** initially place dot somewhere on screen
    d.x = 10;
    d.y = 10;
    
    // initially place pacman somewhere
    p[0].x = 15;
    p[0].y = 15;
    
    
    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;
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
        
        window.clear();    //clear the window so new frame can be drawn in
        
        // placed in while loop to update
        //timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        // controls for pacman by user
        // when up arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = 0;
            pacmanSprite.setTextureRect(sf::IntRect(0, 20, 20, 20));
        }
        // when down array key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = 1;
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*2, 20, 20));
        }
        // when left arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 2;
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*3, 20, 20));
        }
        // when right arrow key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  {
            direction = 3;
            pacmanSprite.setTextureRect(sf::IntRect(0, 20*0, 20, 20));
        }
        
        if (timer > delay)
        {
            timer = 0; //reset timer
            move();    //move pacman one sprite forward
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
                //Draw background sprite but, do not show it on screen.
                window.draw(backgroundSprite);
            }
        }
        
        // then draw pacman otherwise background will be drawn over pacman if order was reversed with background
        for (int i = 0; i < pacmanSize; i++)
        {
            //position pacman sprite one at a time
            pacmanSprite.setPosition(p[i].x*size, p[i].y*size);
            //Draw sprite2 one at a time by drawing over background
            window.draw(pacmanSprite);
        }
        
        // draw dot
        dotSprite.setPosition(d.x*size, d.y*size);
        window.draw(dotSprite);
        
        // draw score text
        text.setString("SCORE: " + std::to_string(score));
        window.draw(text);
        
        //Show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
