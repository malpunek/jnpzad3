#include "geometry.h"

//Vector implementation

using pair_rectangle = std::pair<Rectangle, Rectangle>;

Vector::Vector(int x,int y): x_coord(x), y_coord(y) {
}
Vector::Vector(const Vector& v): x_coord(v.x_coord), y_coord(v.y_coord) {
}
Vector::Vector(Vector&& v): x_coord(std::move(v.x_coord)), y_coord(std::move(v.y_coord)) {
}
bool Vector::operator == (const Vector &v) {
    return x_coord == v.x_coord && y_coord == v.y_coord;
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
Vector& Vector::operator += (const Vector& v) {
    x_coord += v.x_coord;
    y_coord += v.y_coord;
    return *this;
}
Vector Vector::operator + (const Vector& v) const {
    return Vector(x_coord + v.x_coord, y_coord + v.y_coord);
}
Vector& Vector::operator = (const Vector& v) {
    x_coord = v.x_coord;
    y_coord = v.y_coord;
    return *this;
}
Vector& Vector::operator = (Vector&& v) {
    x_coord = std::move(v.x_coord);
    y_coord = std::move(v.y_coord);
    return *this;
}

//Position implementation

Position::Position(Vector&& v): my_position(std::move(v)) {
}
Position::Position(int x,int y): my_position(x, y) {
}
Position::Position(const Position& p): my_position(p.my_position) {
}
Position::Position(Position&& p): my_position(std::move(p.my_position)) {
}
bool Position::operator == (const Position& p) {
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
Position& Position::operator += (const Vector& v) {
    my_position += v;
    return *this;
}
Position Position::operator + (const Vector& v) const {
    return Position(my_position + v);
}
Position& Position::operator = (const Position& p) {
    my_position = p.my_position;
    return *this;
}
Position& Position::operator = (Position&& p) {
    my_position = std::move(p.my_position);
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
    if (v.size() != r.size()) {
        return false;
    }
    for (size_t i = 0; i < v.size(); i ++) {
        if (not (v[i] == r.v[i])) {
            return false;
        }
    }
    return true;
}
Rectangles& Rectangles::operator += (Vector vec) {
    for (Rectangle& r: v) {
        r += vec;
    }
    return *this;
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
    insert_rectangles(idx, v[idx].split_horizontally(place));
}
void Rectangles::split_vertically(size_t idx, unsigned int place) {
    insert_rectangles(idx, v[idx].split_vertically(place));
}

//Operators implementation

Position operator + (const Vector& v, const Position& p) {
    return p + v;
}
