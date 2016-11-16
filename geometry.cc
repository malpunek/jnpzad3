#include "geometry.h"

//Vector implementation

using pair_rectangle = std::pair<Rectangle, Rectangle>;

Vector::Vector(int x,int y): x_coord(x), y_coord(y) {
}
Vector::Vector(const Vector& v): x_coord(v.x_coord), y_coord(v.y_coord) {
}
Vector::Vector(Vector&& v): x_coord(std::move(v.x_coord)), y_coord(std::move(v.y_coord)) {
}
bool Vector::operator == (const Vector &v) const {
    return x_coord == v.x_coord && y_coord == v.y_coord;
}
int Vector::x() const {
    return x_coord;
}
int Vector::y() const {
    return y_coord;
}
Vector Vector::reflection() const {
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
Vector& Vector::operator = (const Vector& v) & {
    x_coord = v.x_coord;
    y_coord = v.y_coord;
    return *this;
}
Vector& Vector::operator = (Vector&& v) & {
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
bool Position::operator == (const Position& p) const {
    return my_position == p.my_position;
}
int Position::x() const {
    return my_position.x();
}
int Position::y() const {
    return my_position.y();
}
Position Position::reflection() const {
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
const Position& Position::origin() {
    static const Position p = Position(0, 0);
    return p;
}


//Rectangle implementation

Rectangle::Rectangle(unsigned int width, unsigned int height, const Position& pos = Position::origin()): 
    w(width), h(height), p(pos) {
        assert(w != 0);
        assert(h != 0);
};
Rectangle::Rectangle(unsigned int width, unsigned int height, Position&& pos): 
    w(width), h(height), p(std::move(pos)) {
        assert(w != 0);
        assert(h != 0);
};
Rectangle::Rectangle(const Rectangle& r): w(r.w), h(r.h), p(r.p) {
}
Rectangle::Rectangle(Rectangle&& r): w(std::move(r.w)), h(std::move(r.h)), p(std::move(r.p)) {
}
bool Rectangle::operator == (const Rectangle& r) const {
    return w == r.w && h == r.h && p == r.p;
}
unsigned int Rectangle::width() const {
    return w;
}
unsigned int Rectangle::height() const {
    return h;
}
Position Rectangle::pos() const {
    return p;
}
Rectangle Rectangle::reflection() const {
    return Rectangle(h, w, p.reflection());
}
Rectangle& Rectangle::operator += (const Vector& v) {
    p += v;
    return *this;
}
Rectangle Rectangle::operator + (const Vector& v) const {
    return Rectangle(w, h, p + v);
}
Rectangle& Rectangle::operator = (const Rectangle& r) {
    w = r.w;
    h = r.h;
    p = r.p;
    return *this;
}
Rectangle& Rectangle::operator = (Rectangle&& r) {
    w = std::move(r.w);
    h = std::move(r.h);
    p = std::move(r.p);
    return *this;
}
unsigned int Rectangle::area() const {
    return w * h;
}
pair_rectangle Rectangle::split_horizontally(unsigned int place) const {
    assert(place < h);
    Position second(p.x(), p.y() + place);
    return std::make_pair(Rectangle(w, place, p), Rectangle(w, h - place, second));
}
pair_rectangle Rectangle::split_vertically(unsigned int place) const {
    assert(place < w);
    Position second(p.x() + place, p.y());
    return std::make_pair(Rectangle(place, h, p), Rectangle(w - place, h, second));
}

//Rectangles implementation

Rectangles::Rectangles(std::initializer_list<Rectangle> l = {}): v(l) {
}
Rectangles::Rectangles(const Rectangles& r): v(r.v) {
}
Rectangles::Rectangles(Rectangles&& r): v(std::move(r.v)) {
}
Rectangle& Rectangles::operator[] (size_t pos) {
    return v[pos];
}
size_t Rectangles::size() const {
    return v.size();
}
bool Rectangles::operator == (const Rectangles& r) const {
    if (v.size() != r.v.size()) {
        return false;
    }
    for (size_t i = 0; i < v.size(); i ++) {
        if (not (v[i] == r.v[i])) {
            return false;
        }
    }
    return true;
}
Rectangles& Rectangles::operator += (const Vector& vec) {
    for (Rectangle& r: v) {
        r += vec;
    }
    return *this;
}
Rectangles Rectangles::operator + (const Vector& vec) const {
    Rectangles result;
    for (const Rectangle& r: v) {
        result.v.push_back(r + vec);
    }
    return result;
}
Rectangles& Rectangles::operator = (const Rectangles& r) {
    v = r.v;
    return *this;
}
Rectangles& Rectangles::operator = (Rectangles&& r) {
    v = std::move(r.v);
    return *this;
}

void Rectangles::insert_rectangles(size_t idx, pair_rectangle&& rec) {
    v[idx] = std::move(rec.first);
    v.push_back(v.back());
    for (size_t i = v.size() - 1; i > idx + 1; i ++) {
        v[i] = v[i - 1];
    }
    v[idx + 1] = std::move(rec.second);
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

Rectangle operator + (const Vector& v, const Rectangle& r) {
    return r + v;
}

Rectangles operator + (const Vector& v, const Rectangles& r) {
    return r + v;
}

//Merge implementation

Rectangle merge_horizontally(const Rectangle& r1, const Rectangle& r2) {
    assert(r1.width() == r2.width());
    Vector v(0, r1.height());
    assert(r1.pos() + v == r2.pos());
    return Rectangle(r1.width(), r1.height() + r2.height(), r1.pos()); 
}
Rectangle merge_vertically(const Rectangle& r1, const Rectangle& r2) {
    assert(r1.height() == r2.height());
    Vector v(r1.width(), 0);
    assert(r1.pos() + v == r2.pos());
    return Rectangle(r1.width() + r2.width(), r1.height(), r1.pos());
}
