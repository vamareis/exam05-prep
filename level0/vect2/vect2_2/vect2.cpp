#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return (*this);
}

vect2   vect2::operator+(const vect2& other) const
{
    return (vect2(this->x + other.x, this->y + other.y));
}

vect2   vect2::operator-(const vect2& other) const
{
    return (vect2(this->x - other.x, this->y - other.y));
}

vect2   vect2::operator*(int scalar) const
{
    return (vect2(this->x * scalar, this->y * scalar));
}

vect2&  vect2::operator+=(const vect2& other)
{
    this->x += other.x;
    this->y += other.y;
    return (*this);
}

vect2&  vect2::operator-=(const vect2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return (*this);
}

vect2&  vect2::operator*=(int scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return (*this);
}

vect2   vect2::operator++(int)
{
    vect2 tmp(*this);
    this->x += 1;
    this->y += 1;
    return (tmp);
}

vect2&  vect2::operator++()
{
    this->x += 1;
    this->y += 1;
    return (*this);
}

vect2   vect2::operator--(int)
{
    vect2 tmp(*this);
    this->x -= 1;
    this->y -= 1;
    return (tmp);
}

vect2&  vect2::operator--()
{
    this->x -= 1;
    this->y -= 1;
    return (*this);
}

vect2   vect2::operator-() const
{
    return (vect2(-x, -y));
}

int&    vect2::operator[](int index)
{
    if (index == 0)
        return (x);
    return (y);
}

const int&    vect2::operator[](int index) const
{
    if (index == 0)
        return (x);
    return (y);
}

bool    vect2::operator==(const vect2& other) const
{
    return (this->x == other.x && this->y == other.y);
}

bool    vect2::operator!=(const vect2& other) const
{
    return (this->x != other.x || this->y != other.y);
}

int vect2::getX() const
{
    return (this->x);
}

int vect2::getY() const
{
    return (this->y);
}

vect2  operator*(int scalar, const vect2& v)
{
    return (vect2(scalar * v.getX(), scalar * v.getY()));
}

std::ostream&   operator<<(std::ostream& out, const vect2& v)
{
    out << "{" << v.getX() << ", " << v.getY() << "}";
    return (out);
}