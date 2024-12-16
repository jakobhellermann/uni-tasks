#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    Rectangle(int x, int y, int width, int height);

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    Rectangle operator|(const Rectangle &other) const;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

Rectangle operator|(const Rectangle &a, const Rectangle &b);

Rectangle getRectangleUnion(const Rectangle &a, const Rectangle &b);

#endif //RECTANGLE_H
