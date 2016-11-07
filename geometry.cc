class Vector {
private:
    int x_coord, y_coord;
public:
    Vector(int x,int y): x_coord(x), y_coord(y) {
    }
    bool operator == (Vector v) {
        return x_coord == v.x() && y_coord == v.y();
    }
    int x() {
        return x_coord;
    }
    int y() {
        return y_coord;
    }
    Vector reflection() {
        return Vector(y_coord, x_coord);
    }
    Vector& operator += (Vector v) {
        x_coord += v.x();
        y_coord += v.y();
        return *this;
    }
};

class Position {
private:
    Vector my_position;
    Position(Vector v): my_position(v.x(), v.y()) {
    }
public:
    Position(int x,int y): my_position(x, y) {
    }
    bool operator == (Position p) {
        return my_position == p.my_position;
    }
    int x() {
        return my_position.x();
    }
    int y() {
        return my_position.y();
    }
    Position reflection() {
        return Position(my_position.reflection());
    }
    Position& operator += (Vector v) {
        my_position += v;
        return *this;
    }
    static const Position origin() {
        static const Position p = Position(0, 0);
        return p;
    }
};

