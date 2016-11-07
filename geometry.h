#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector {
public:
    Vector(int x,int y);
    bool operator == (Vector);
    int x();
    int y();
    Vector reflection();
    Vector& operator += (Vector);
};

class Position {
public:
    Position(int x,int y);
    bool operator == (Position);
    int x();
    int y();
    Position reflection();
    Position& operator += (Vector);
    static const Position& origin();
};

#endif //GEOMETRY_H
