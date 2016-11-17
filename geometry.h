#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>
#include <cassert>
#include <cstddef>
#include <vector>
#include <initializer_list>

class Vector {
public:
    Vector(int x,int y);
    Vector(const Vector&);
    Vector(Vector&&);
    bool operator == (const Vector&) const;
    int x() const;
    int y() const;
    Vector reflection() const;
    Vector& operator += (const Vector&);
    Vector& operator = (const Vector& v) &;
    Vector& operator = (Vector&& v) &;
private:
    int x_coord, y_coord;
};

class Position {
public:
    Position(int x,int y);
    Position(const Position&);
    Position(Position&&);
    bool operator == (const Position&) const;
    int x() const;
    int y() const;
    Position reflection() const;
    Position& operator += (const Vector&);
    Position& operator = (const Position&) &;
    Position& operator = (Position&&) &;
    static const Position& origin();
private:
    Vector my_position;
    Position(Vector&&);
};


class Rectangle {
public:
    Rectangle(unsigned int width, unsigned int height, const Position& pos);
    Rectangle(unsigned int width, unsigned int height, Position&& pos);
    Rectangle(unsigned int width, unsigned int height);
    Rectangle(const Rectangle&);
    Rectangle(Rectangle&&);
    bool operator == (const Rectangle&) const;
    unsigned int width() const;
    unsigned int height() const;
    Position pos() const;
    Rectangle reflection() const;
    Rectangle& operator += (const Vector&);
    Rectangle& operator = (const Rectangle&) &;
    Rectangle& operator = (Rectangle&&) &;
    unsigned int area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(unsigned int place) const;
    std::pair<Rectangle, Rectangle> split_vertically(unsigned int place) const;
private:
    unsigned int w, h;
    Position p;
};


class Rectangles {
public:
    Rectangles(std::initializer_list<Rectangle>);
    Rectangles(const Rectangles&);
    Rectangles(Rectangles&&);
    Rectangle& operator [] (size_t pos);
    size_t size() const;
    bool operator == (const Rectangles&) const;
    Rectangles& operator += (const Vector&);
    Rectangles& operator = (const Rectangles&) &;
    Rectangles& operator = (Rectangles&&) &;
    void split_horizontally(size_t idx, unsigned int place);
    void split_vertically(size_t idx, unsigned int place);
private:
    std::vector<Rectangle> v;
    void insert_rectangles(size_t idx, std::pair<Rectangle, Rectangle>&&);
};

Vector operator + (const Vector&, const Vector&);
Position operator + (const Vector&, const Position&);
Position operator + (const Position&, const Vector&);
Rectangle operator + (const Rectangle&, const Vector&);
Rectangle operator + (const Vector&, const Rectangle&);
Rectangles operator + (const Vector&, const Rectangles&);
Rectangles operator + (const Rectangles&, const Vector&);

Rectangle merge_horizontally(const Rectangle&, const Rectangle&);
Rectangle merge_vertically(const Rectangle&, const Rectangle&);

#endif //GEOMETRY_H
