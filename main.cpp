// pac man game
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 30;
int size = 20; //number of pixels
int w = size * num_horzBox;  //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height

// variables to dertermine length and direction
int direction;    //direction character is moving
int character_length = 1; // size of the character

//Actual Snake in game is an array of x,y coordinates of sprite2
struct pacman
{
    int x, y;       // only need one sprite needed for one pacman item
}p;

//***NEW*** this is the fruit or food that the snake will eat
struct Fruit
{
    int x, y;    //each sprite of food needs an x,y coordinate
}food[100];

//move snake head based on user input and body by incrementing
//forward by iterating through arrays previous position
/*void move() {
    //1st update body so everything updates in proper order
    //move the body only!  s[0] = head will not be changed here
    // for snake 1
    for (int i = character_length; i > 0; i--)
    {
        p[i].x = p[i - 1].x;
        p[i].y = p[i - 1].y;
    }
*/
    //2nd update the head
    // p[0] depends on direction user inputs
    
    // y is for up/down
    if (direction == 0)     //if user presses up
        p[0].y -= 1;
    if (direction == 1)     //if user presses down
        p[0].y += 1;

    // x is for left/right
    if (direction == 2)     //if user presses left
        p[0].x -= 1;
    if (direction == 3)     //if user presses right
        p[0].x += 1;
    
    
    //***NEW*** If Snake eats food it should grow
    //check if snake head = food location
    // snake 1
    if (((s1[0].x) == food.x) && ((s1[0].y) == food.y))
    {
        //increment snake
        character_length++;
        
        //Randomly place food somewhere else
        food.x = rand() % num_horzBox;
        food.y = rand() % num_vertBox;
        
        // 2) modify timing as snake eats fruit, game should get faster!
        
    }
    
    //***NEW*** Boundary Checking snake as is hits screen end
    //loop snake back on other side
    // snake 1
    //LEFT and RIGHT
    if (s1[0].x > num_horzBox)
        s1[0].x = 0;
    if (s1[0].x < 0)
        s1[0].x = num_horzBox;
    //TOP and BOTTOM
    if (s1[0].y > num_vertBox)
        s1[0].y = 0;
    if (s1[0].y < 0)
        s1[0].y = num_vertBox;
    
    //***NEW*** Check if you eat body of snake
    // snake 1
    for (int i = 1; i < character_length; i++)
    {
        //Cut Snake body from place eaten
        if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)
            character_length = i;
    }
}

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));
    
    //Window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");
    
    //Textures load an image into the GPU Memory
    sf::Texture t1, t2, t3, t4;
    // rock image
    t1.loadFromFile("/Users/michellelim/Desktop/images/rock.png");
    // paper image
    t2.loadFromFile("/Users/michellelim/Desktop/images/paper.png");
    // scissors image
    t3.loadFromFile("/Users/michellelim/Desktop/images/scissors.png");
    
    //Sprite has physical dimmensions that can be set in
    //coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite sprite1(t1);
    sf::Sprite sprite2(t2);
    sf::Sprite sprite3(t3);
    sf::Sprite sprite4(t4);
    
    //***NEW*** initially place food somewhere on screen
    food.x = 10;
    food.y = 10;
    
    // initially place snake 1 somewhere
    s1[0].x = 15;
    s1[0].y = 15;

    
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
        
        //Control for Snake by User1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;
        
        if (timer > delay)
        {
            timer = 0; //reset timer
            move();    //move Snake one sprite forward
        }
        
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
                //Set position of sprite1 one at a time
                sprite1.setPosition(i*size, j*size);
                //Draw sprite1 but, do not show it on screen.
                window.draw(sprite1);
            }
        }
        
        //2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background
        // snake 1
        for (int i = 0; i < character_length; i++)
        {
            //position sprite2 one at a time
            sprite2.setPosition(s1[i].x*size, s1[i].y*size);
            //Draw sprite2 one at a time by drawing over background
            window.draw(sprite2);
        }
        
        
        //***NEW*** 3rd: Draw Fruit
        sprite3.setPosition(food.x*size, food.y*size);
        window.draw(sprite3);
        
        //Show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
