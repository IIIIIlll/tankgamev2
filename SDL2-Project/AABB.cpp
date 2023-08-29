#include "AABB.h"
#include "Vector2f.h"

AABB::AABB()
{
    halfHeight = 0.0f;
    halfWidth = 0.0f;
    centreX = 0.0f;
    centreY = 0.0f;
}

AABB::AABB(Vector2f* position, float height, float width)
{
    // We can get away with this as the init method
    // doesn't allocate any memory!
    init(position, height, width);
}

AABB::~AABB()
{

}

void AABB::init(Vector2f* position, float height, float width)
{
    halfWidth = width / 2.0f;
    halfHeight = height / 2.0f;

    setPosition(position);
}

float AABB::getHalfHeight()
{
    return halfHeight;
}

float AABB::getHalfWidth()
{
    return halfWidth;
}

float AABB::getCentreX()
{
    return centreX;
}

float AABB::getCentreY()
{
    return centreY;
}

void AABB::setPosition(Vector2f* position)
{
    centreX = position->getX() + halfWidth;
    centreY = position->getY() + halfHeight;
}

bool AABB::intersects(AABB* other)
{
    // If the sprite has no collision box
    // then give up. 
    if(other == nullptr)
        return false;

    bool hCheck = (fabs(this->getCentreX() - other->getCentreX()) < (this->getHalfWidth() + other->getHalfWidth()));
    bool vCheck = (fabs(this->getCentreY() - other->getCentreY()) < (this->getHalfHeight() + other->getHalfHeight()));

    return hCheck && vCheck;  
}