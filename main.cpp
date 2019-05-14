// Michelle Lim

// pacman game
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>
#include <string>              // std::string, std::to_string

//dimensions for window size and background
int num_vertBox = 13, num_horzBox = 13;
int size = 20; //number of pixels
int w = size * num_horzBox;    //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height

// variables
int direction;          // direction pacman is moving
int pacmanSize = 1;     // size of pacman
int score = 0;          // player score, initally 0
// int speed = 2;       // speed of pacman

// pacman in game is an array of x, y coordinates of pacmanSprite
struct Pacman {
    int x, y;        // each sprite of pacman needs an x,y coordinate
}p[100];

// the dot that pacman will eat
struct Dot {
    int x, y;    // only need one sprite needed for one dot item
}d;

// ghost pacman needs to avoid
struct Ghost1 {
    int x, y;
}g1;

// ghost pacman needs to avoid
struct Ghost2 {
    int x, y;
}g2;

// ghost pacman needs to avoid
struct Ghost3 {
    int x, y;
}g3;

// ghost pacman needs to avoid
struct Ghost4 {
    int x, y;
}g4;


//move pacman based on user input
//forward by iterating through arrays previous position
void move() {
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
    // wanted to use speed variable here but then when pacman eats dot nothing happened
    if (direction == 0)
       p[0].y -= 1;            // if user presses up
    if (direction == 1)
        p[0].y += 1;            // if user presses down
    if (direction == 2)
        p[0].x -= 1;            // if user presses left
    if (direction == 3)
        p[0].x += 1;            // if user presses right
    
    // check if pacman location = dot location
    // if locations are same, that means pacman has eaten a dot
    // increment score
    // change locations of ghosts
    if (((p[0].x) == d.x) && ((p[0].y) == d.y))
    {
        score += 5;
        
        // randomly place dot somewhere else
        d.x = rand() % num_horzBox;
        d.y = rand() % num_vertBox;
        
        // randomly place ghost1 somewhere else
        g1.x = rand() % num_horzBox;
        g1.y = rand() % num_vertBox;
        // randomly place ghost2 somewhere else
        g2.x = rand() % num_horzBox;
        g2.y = rand() % num_vertBox;
        // randomly place ghost3 somewhere else
        g3.x = rand() % num_horzBox;
        g3.y = rand() % num_vertBox;
        // randomly place ghost4 somewhere else
        g4.x = rand() % num_horzBox;
        g4.y = rand() % num_vertBox;
    }
    // check if pacman location = any of the ghosts location
    // for now if location is same that means pacman touched a ghost so reset score
    // later on implement game over
    if (((p[0].x==g1.x)&&(p[0].y==g1.y)) ||
        ((p[0].x==g2.x)&&(p[0].y==g2.y)) ||
        ((p[0].x==g3.x)&&(p[0].y==g3.y)) ||
        ((p[0].x==g4.x)&&(p[0].y==g4.y))) {
        score = 0;
    }
}

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    //Window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "Pacman Game");
    
    // textures load an image into the GPU Memory
    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("/Users/michellelim/Desktop/images/blue.png");
    // image of pacman
    t2.loadFromFile("/Users/michellelim/Desktop/images/pacman.png");
    // image of dot
    t3.loadFromFile("/Users/michellelim/Desktop/images/dot.png");
    // image of ghost1
    t4.loadFromFile("/Users/michellelim/Desktop/images/g1.png");
    // image of ghost2
    t5.loadFromFile("/Users/michellelim/Desktop/images/g2.png");
    // image of ghost3
    t6.loadFromFile("/Users/michellelim/Desktop/images/g3.png");
    // image of ghost4
    t7.loadFromFile("/Users/michellelim/Desktop/images/g4.png");
    
    //Sprite has physical dimmensions that can be set in
    //coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite backgroundSprite(t1);
    sf::Sprite pacmanSprite(t2);
    // using texture rectangle bc i don't want to use my entire texture
    // (x, y, w, h) my textures are 20x20 pixels
    pacmanSprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
    sf::Sprite dotSprite(t3);
    sf::Sprite ghost1Sprite(t4);
    sf::Sprite ghost2Sprite(t5);
    sf::Sprite ghost3Sprite(t6);
    sf::Sprite ghost4Sprite(t7);
    
    // setting the icon
    sf::Image gameIcon;
    gameIcon.loadFromFile("/Users/michellelim/Desktop/images/pacmanRight.png");
    // using icon size as the dimensions and setting it
    window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
    
    // for score text
    // first need to upload font
    sf::Font font;
    font.loadFromFile("/Users/michellelim/Desktop/arial.ttf");
    // text will print SCORE: and im making size of font 20
    sf::Text text("SCORE: ", font, 20);
    // set color of text
    text.setColor(sf::Color::White);
    text.setPosition(0, 0);
    
    /*
    // for died TEXT
    // text will print You died and im making size of font 30
    sf::Text died("You died.", font, 30);
    died.setColor(sf::Color::White);
    died.setPosition(window.getSize().x/2, window.getSize().y/2);
    */
    
    // initially place dot somewhere on screen
    d.x = 1;
    d.y = 1;
    
    // initially place pacman somewhere
    p[0].x = 5;
    p[0].y = 5;
    
    // initially place ghost1 somewhere on screen
    g1.x = 3;
    g1.y = 6;
    // initially place ghost2 somewhere on screen
    g2.x = 7;
    g2.y = 3;
    // initially place ghost3 somewhere on screen
    g3.x = 9;
    g3.y = 9;
    // initially place ghost4 somewhere on screen
    g4.x = 0;
    g4.y = 10;
    
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
            // position pacman sprite one at a time
            pacmanSprite.setPosition(p[i].x*size, p[i].y*size);
            // draw pacmanSprite over background
            window.draw(pacmanSprite);
        }
        
        // draw dot
        dotSprite.setPosition(d.x*size, d.y*size);
        window.draw(dotSprite);
        
        // draw ghost1
        ghost1Sprite.setPosition(g1.x*size, g1.y*size);
        window.draw(ghost1Sprite);
        // draw ghost2
        ghost2Sprite.setPosition(g2.x*size, g2.y*size);
        window.draw(ghost2Sprite);
        // draw ghost3
        ghost3Sprite.setPosition(g3.x*size, g3.y*size);
        window.draw(ghost3Sprite);
        // draw ghost4
        ghost4Sprite.setPosition(g4.x*size, g4.y*size);
        window.draw(ghost4Sprite);
        
        // draw score text
        // need to use to_string to convert score to a string bc it is an int right now
        text.setString("SCORE: " + std::to_string(score));
        window.draw(text);
        
        // show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
