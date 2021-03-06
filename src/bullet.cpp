#include "../include/bullet.h"
Bullet::Bullet()
{
    bulletState = false;
    bulletVelocity = Vector(0.0,0.0);
    rectangle.setSize(sf::Vector2f(10.0,10.0));
    rectangle.setOrigin(rectangle.getSize().x/2.0, rectangle.getSize().y/2.0);
    //ctor
}
sf::RectangleShape Bullet::getRect() const
{
    return rectangle;
}

void Bullet::activate()
{
    bulletState = true;
    bulletVelocity=Vector(8.0l,270.0l);
}

bool Bullet::getState() const
{
    return bulletState;
}

void Bullet::setVelocity(Vector vel)
{
    bulletVelocity = vel;
}

void Bullet::resetBull(sf::Vector2f position)
{
    //Reset our state to not in the air!
    bull_x = position.x;
    bull_y = position.y;
    rectangle.setPosition(bull_x, bull_y);
    bulletState = false;
}

void Bullet::bulletLogic()
{
    //If we are in bounds...
    if(bull_y > 0 && bull_y < 1030)
    {
        //Update our position
        bull_x += bulletVelocity.getXComponent();
        bull_y += bulletVelocity.getYComponent();
        rectangle.setPosition(bull_x, bull_y);
    }
    else
    {
        //Otherwise, reset!
        resetBull(sf::Vector2f(0.0,0.0));
    }
}
Bullet::~Bullet()
{
    //dtor
}
