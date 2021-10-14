#include "points_To_Use.h"


points_To_Use::points_To_Use()
{
    _x = 0;
    _y = 0;
    lineBegins = false;
}

points_To_Use::points_To_Use(short x, short y, bool startofline)
{
    _x = x;
    _y = y;
    lineBegins = startofline;
}

points_To_Use::points_To_Use(const points_To_Use& p)
{
    _x = p._x;
    _y = p._y;
    lineBegins = p.lineBegins;
}

short points_To_Use::getX() const
{
    return _x;
}

void points_To_Use::setX(const short x)
{
    _x = x;
}

short points_To_Use::getY() const
{
    return _y;
}

void points_To_Use::setY(const short y)
{
    _y = y;
}

bool points_To_Use::islineBegins() const
{
    return lineBegins;
}




points_To_Use& points_To_Use::operator=(const points_To_Use& other)
{
    // Only do the assignment if we are not assigning
    // to ourselves
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
        lineBegins = other.lineBegins;
    }
    return *this;

}

bool points_To_Use::operator==(const points_To_Use& other) const
{
    if (_x == other._x && _y == other._y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
