#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>
#include <cassert>
#include <cstddef>
#include <vector>
#include <initializer_list>

class Vector {
//TODO czy wystarczy wsadzenie "prywatne" tutaj, czy trzeba to jakoś lepiej ukryć?
private:
    int x_coord, y_coord;
public:
    Vector(int x,int y);
    bool operator == (Vector);
    int x();
    int y();
    Vector reflection();
    Vector& operator += (Vector);
};

class Position {
private:
    Vector my_position;
    Position(Vector v);
public:
    Position(int x,int y);
    bool operator == (Position);
    int x();
    int y();
    Position reflection();
    Position& operator += (Vector);
    static const Position origin();
};

class Rectangle {
private:
    unsigned int w, h;
    Position p;
public:
    Rectangle(unsigned int width, unsigned int height, Position pos);
    bool operator == (Rectangle);
    unsigned int width();
    unsigned int height();
    Position pos();
    Rectangle reflection();
    Rectangle& operator += (Vector);
    unsigned int area();
    std::pair<Rectangle, Rectangle> split_horizontally(unsigned int place);
    std::pair<Rectangle, Rectangle> split_vertically(unsigned int place);
};

class Rectangles {
private:
    std::vector<Rectangle> v;
    void insert_rectangles(size_t idx, std::pair<Rectangle, Rectangle>);
public:
    Rectangles(std::initializer_list<Rectangle>);
    Rectangle& operator [] (size_t pos);
    size_t size();
    bool operator == (Rectangles);
    Rectangles& operator += (Vector);
    void split_horizontally(size_t idx, unsigned int place);
    void split_vertically(size_t idx, unsigned int place);
};


#endif //GEOMETRY_H
