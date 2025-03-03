#include <cmath>
#include <iostream>

struct Vec2f 
{
    float x = 0;
    float y = 0;

    float getLength() const 
    {
        const float lengthSquare = x * x + y * y;
        return std::sqrt(lengthSquare);
    }
};

int main()
{
    Vec2f vector;
    vector.x = 3;
    vector.y = 4;

    std::cout << vector.getLength() << std::endl;

    return 0;
}
