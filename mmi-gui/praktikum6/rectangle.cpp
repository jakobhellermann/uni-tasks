#include "rectangle.h"
#include <algorithm>

Rectangle::Rectangle(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {
}

Rectangle getRectangleUnion(const Rectangle &a, const Rectangle &b) {
    int minX = std::min(a.getX(), b.getX());
    int minY = std::min(a.getY(), b.getY());

    int maxX = std::max(a.getX() + a.getWidth(), b.getX() + b.getWidth());
    int maxY = std::max(a.getY() + a.getHeight(), b.getY() + b.getHeight());

    return Rectangle(minX, minY, maxX - minX, maxY - minY);
}


Rectangle Rectangle::operator|(const Rectangle &b) const {
    return getRectangleUnion(*this, b);
}


Rectangle operator|(const Rectangle &a, const Rectangle &b) {
    return getRectangleUnion(a, b);
}
