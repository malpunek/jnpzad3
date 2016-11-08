#include "geometry.h"

//Vector implementation

using pair_rectangle = std::pair<Rectangle, Rectangle>;

Vector::Vector(int x,int y): x_coord(x), y_coord(y) {
}
bool Vector::operator == (Vector v) {
    return x_coord == v.x() && y_coord == v.y();
}
int Vector::x() {
    return x_coord;
}
int Vector::y() {
    return y_coord;
}
Vector Vector::reflection() {
    return Vector(y_coord, x_coord);
}
Vector& Vector::operator += (Vector v) {
    x_coord += v.x();
    y_coord += v.y();
    return *this;
}

//Position implementation

Position::Position(Vector v): my_position(v.x(), v.y()) {
}
Position::Position(int x,int y): my_position(x, y) {
}
bool Position::operator == (Position p) {
    return my_position == p.my_position;
}
int Position::x() {
    return my_position.x();
}
int Position::y() {
    return my_position.y();
}
Position Position::reflection() {
    return Position(my_position.reflection());
}
Position& Position::operator += (Vector v) {
    my_position += v;
    return *this;
}
const Position Position::origin() {
    static const Position p = Position(0, 0);
    return p;
}

//Rectangle implementation

Rectangle::Rectangle(unsigned int width, unsigned int height, Position pos = Position::origin()): 
    w(width), h(height), p(pos) {
        assert(w != 0);
        assert(h != 0);
};
bool Rectangle::operator == (Rectangle r) {
    return w == r.width() && h == r.height() && p == r.pos();
}
unsigned int Rectangle::width() {
    return w;
}
unsigned int Rectangle::height() {
    return h;
}
Position Rectangle::pos() {
    return p;
}
Rectangle Rectangle::reflection() {
    return Rectangle(h, w, p.reflection());
}
Rectangle& Rectangle::operator += (Vector v) {
    p += v;
    return *this;
}
unsigned int Rectangle::area() {
    return w * h;
}
pair_rectangle Rectangle::split_horizontally(unsigned int place) {
    assert(place < h);
    Position second(p.x(), p.y() + place);
    return std::make_pair(Rectangle(w, place, p), Rectangle(w, h - place, second));
}
pair_rectangle Rectangle::split_vertically(unsigned int place) {
    assert(place < w);
    Position second(p.x() + place, p.y());
    return std::make_pair(Rectangle(place, h, p), Rectangle(w - place, h, second));
}

//Rectangles implementation

Rectangles::Rectangles(std::initializer_list<Rectangle> l = {}): v(l) {
}
Rectangle& Rectangles::operator[] (size_t pos) {
    return v[pos];
}
size_t Rectangles::size() {
    return v.size();
}
bool Rectangles::operator == (Rectangles r) {
    return v == r.v;
}
Rectangles& Rectangles::operator += (Vector v) {
    for (Rectangle& r: v) {
        r += v;
    }
}
void Rectangles::insert_rectangles(size_t idx, pair_rectangle rec) {
    v[idx] = rec.first;
    v.push_back(v.back());
    for (size_t i = v.size() - 1; i > idx + 1; i ++) {
        v[i] = v[i - 1];
    }
    v[idx + 1] = rec.second;
}
void Rectangles::split_horizontally(size_t idx, unsigned int place) {
    insert_rectangles(idx, split_horizontally(v[idx], place));
}
void Rectangles::split_vertically(size_t idx, unsigned int place) {
    insert_rectangles(idx, split_vertically(v[idx], place));
}
