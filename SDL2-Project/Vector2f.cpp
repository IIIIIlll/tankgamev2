#include "Vector2f.h"

#include <cmath>

/** \brief Default Constructor
 * 
 * This is the default constructor, it sets the values to 
 * zero. Most real vector classes don't do this ...
 */
Vector2f::Vector2f() 
{
    zero();
}

/** \brief An Overloaded Constructor
 *  \param x The initial value of x
 *  \param y The initial value of y
 *  Sets up a new Vector2f with the initial values provided. 
 */
Vector2f::Vector2f(float x, float y) 
{
    setX(x);
    setY(y);
}

/** \brief Copy Constructor
 *  \param other The vector we're copying. 
 *  Creates a new vector exactly the same as the last one.  
 */
Vector2f::Vector2f(Vector2f* other)
{
    // Copy constructors can access the
    // private attributes of the other
    // class!
    x = other->x;
    y = other->y;
}
    
/** \brief Destructor
 *  Destroys a Vector2f, not much too it.  
 */
Vector2f::~Vector2f()
{

}
 
/** \brief Sets the X coordinate
 *  \param x The new value of x
 *  Sets the x coordinate to the value given.  
 */
void Vector2f::setX(float x)
{
    this->x = x;
}
 
/** \brief Gets the X coordinate
 *  \return the value of x
 *  Gets the x coordinate.  
 */
float Vector2f::getX(void)
{
    return x;
}

/** \brief Sets the Y coordinate
 *  \param y The new value of y
 *  Sets the x coordinate to the value given.  
 */ 
void Vector2f::setY(float y)
{
    this->y = y;
}
 
/** \brief Gets the X coordinate
 *  \return the value of x
 *  Gets the x coordinate.  
 */
float Vector2f::getY(void)
{
    return y;
}
 
/** \brief Adds the given vector to this one. 
 *  \param other The vector to add to this one. 
 *  Add the given vector to this one. 
 */
void Vector2f::add(Vector2f* other)
{
    x += other->getX();
    y += other->getY();
}

/** \brief Subtracts the given vector from this one. 
 *  \param other The vector to subtract from this one. 
 *  Subctract the given vector from this one. 
 */
void Vector2f::sub(Vector2f* other)
{
    x -= other->getX();
    y -= other->getY();
}

/** \brief Scales the vector
 *  \param scalar The value to scale the vector by
 *  Scales the vector by a given value. 
 */
void Vector2f::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}


/** \brief Zeros the vector
 *  Sets both coordinates to the origin.  
 */
void Vector2f::zero()
{
    x = y = 0.0f;
}

/** \brief Normalise
 *  Ensures the vector is unit lenght.  
 */
void Vector2f::normalise()
{
    float lenght = length();
    if(lenght > 1.0f)
    {
        x /= lenght;
        y /= lenght;
    }
}

/** \brief Lenght of the vector
 *  \return The length
 *  Calculate and return the lenght of the vector.  
 */
float Vector2f::length()
{
    // Use Pythag ...
    return sqrtf((x*x) + (y*y));
}


/** \brief calculate the dotproduct between two vectors
 *  \return the dot product
 *  Calculate and return the dot product see
 *  https://www.mathsisfun.com/algebra/vectors-dot-product.html
 */
float Vector2f::dotProduct(Vector2f* other)
{
    return this->getX() * other->getX() + this->getY() * other->getY();
}