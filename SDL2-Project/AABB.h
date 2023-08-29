#ifndef AABB_H_
#define AABB_H_

class Vector2f;

class AABB
{
private:
    float halfWidth;
    float halfHeight;

    float centreX;
    float centreY;

public:
    AABB();
    AABB(Vector2f* position, float height, float width);
    ~AABB();

    void init(Vector2f* position, float height, float width);

    float getHalfHeight();
    float getHalfWidth();

    float getCentreX();
    float getCentreY();

    bool intersects(AABB* other);

    void setPosition(Vector2f* pos);
};

#endif