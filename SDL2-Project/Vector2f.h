#ifndef VECTOR2F_H_
#define VECTOR2F_H_

#include "SDL2Common.h"

/**
 * \class Vector2f
 *
 * \brief 2D Vector class using floats. 
 * 
 * \author Glenn L. Jenkins
 *
 * \date March 2021
 * 
 */
class Vector2f
{
private:
    float x; ///< x coordinate
    float y; ///< y coordinate
public:
    /// Default constructor 
    Vector2f();
    /// Overloaded constructor
    Vector2f(float x, float y);
    /// Copy constructor
    Vector2f(Vector2f* other);  
   
    /// Destructor
    ~Vector2f();

    /// Sets all elements to zero
    void zero();

    /// Normalises the vector (make unit lenght)
    void normalise();

    /// Get the length of the vector
    float length();

    /// Set the x value
    void setX(float x);

    /// Get the x value
    float getX(void);

    /// Set the y value
    void setY(float y);

    /// Get the y value
    float getY(void);

    /// Add the other vector to this one. 
    void add(Vector2f* other);

    /// Subtract the other vector from this one. 
	void sub(Vector2f* other);

    /// Scale the vector by a scalar value
    void scale(float scalar);

    /// Dot product
    float dotProduct(Vector2f* other);
};

#endif