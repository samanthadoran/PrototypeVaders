#include "../include/player.h"

Player::Player()
{

    //Set up our player shape
    rectangle.setSize(sf::Vector2f(20,20));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOrigin(rectangle.getSize().x/2.0, rectangle.getSize().y/2.0);
    x = 960;
    y = 900;
    rectangle.setPosition(x,y);


    //The bullet should follow the player
    bullet.resetBull(rectangle.getPosition());
    //ctor
}

void Player::control()
{
    //If there is no input, our acceleration should be 0!
    acceleration = Vector();

    //Go left!
    //Creates an acceleration vector pointing to the left (Theta = 180)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        acceleration = Vector(1, 180);
    }

    //Go right!
    //Creates an acceleration vector pointing to the Right (Theta = 0)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        acceleration = Vector(1, 0);
    }

    //Space to shoot
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //If we don't currently have a bullet in the air...
        if(!bullet.getState())
        {
            //Reset its position to our current position and fire it!
            bullet.resetBull(rectangle.getPosition());
            bullet.activate();
        }
    }
}

sf::RectangleShape Player::getRect() const
{
    return rectangle;
}

Bullet * Player::getBull()
{
    //Pass a pointer to player's bullet, useful for restting it from Game
    Bullet * pBull = &bullet;
    return (pBull);
}

void Player::update()
{
    long double accel_x    = acceleration.getXComponent();
    long double accel_y    = acceleration.getYComponent();

    //So we can slow down
    double factor          = 1.0;


    //If we aren't accelerating, we should slow down
    if(abs(accel_x) < 1)
    {
        factor = .8;
        //Slow down.
    }

    //Makes adding vectors easier
    long double velocity_x = velocity    .getXComponent();
    long double velocity_y = velocity    .getYComponent();

    //Vf = Vi + at
    velocity_x            += accel_x;
    velocity_y            += accel_y;

    long double newMag     = sqrt(pow(velocity_x*factor,2) + pow(velocity_y*factor,2));
    long double newTheta   = atan2(velocity_y*factor,velocity_x*factor)*(180.0l/PI);

    velocity               = Vector(newMag,newTheta);


    //So we don't go out of bounds
    if(!(x+velocity_x*factor > 1920 || x+velocity_x*factor < 0))
    {
        x                     += velocity_x*factor;
        y                     += velocity_y*factor;
    }
    else
    {
        //We can no longer be under acceleration, otherwise it would put us passed the barrier
        if(x + velocity_x*factor - accel_x > 0 && x + velocity_x*factor - accel_x< 1920)
        {
            x += velocity_x*factor - accel_x;
            y += velocity_y*factor - accel_y;
        }
        else
        {
            //We need to lower the factor, lest we still go passed the barrier
            if(x > 2 && x < 1918)
            {
                factor = .1;
                x += velocity_x*factor - accel_x;
                y += velocity_y*factor - accel_y;
            }
        }
    }


    //Keep our shape up to date
    rectangle.setPosition(x,y);

    //If our bullet is in the air..
    if(bullet.getState())
    {
        //Run the logic!
        bullet.bulletLogic();
    }
    else
    {
        //Otherwise, keep it up to date in position
        bullet.resetBull(rectangle.getPosition());
    }
}

Player::~Player()
{
    //dtor
}
