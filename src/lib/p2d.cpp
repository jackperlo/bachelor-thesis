#include "p2d.h"
#include <iostream>
#include <string>

using namespace std;

const P2D P2D::UP(0, -1);
const P2D P2D::DX(1, 0);
const P2D P2D::DOWN(0, 1);
const P2D P2D::SX(-1, 0);
const P2D P2D::null_p2d(0, 0);

P2D::P2D(int x, int y) : x(x), y(y) { }
P2D::P2D(const P2D& p2d) : x(p2d.x), y(p2d.y) { }

P2D::operator string (){
  string t = "";
  t = "(" + to_string(this->x) + ", " + to_string(this->y) + ")";
  return t; 
}

P2D P2D::operator+(const P2D& other) const {
  return P2D(x + other.x, y + other.y);
}

P2D P2D::operator-() const {
  return P2D(-x, -y);
}

P2D P2D::operator-(const P2D& other) const {
  return *this + (-other);
}

P2D& P2D::operator+=(const P2D& other) {
  this->x += other.x;
  this->y += other.y;
  return *this;
}

int P2D::manatthan(const P2D& other) const {
  return abs(x - other.x) + abs(y - other.y);
}

bool P2D::operator==(const P2D& other) const {
  return x == other.x && y == other.y;
}

bool P2D::operator!=(const P2D& other) const {
  return !(*this == other);
}

ostream& operator<<(ostream& out, P2D p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

size_t P2D::HashFun::operator()(const P2D& p) const {
  size_t rowHash = hash<int>()(17 * p.x);
  size_t colHash = hash<int>()(31 * p.y) << 1;
  return rowHash ^ colHash;
}

bool P2D::CompareFun::operator() (const P2D& lhs, const P2D& rhs) const {
  return lhs.y < rhs.y or (lhs.y == rhs.y and lhs.x < rhs.x);
}

Action::Action(P2D from, P2D dir, int weight, int movementType, P2D head) : from(from), dir(dir), weight(weight), movementType(movementType), head(head) { }

ostream& operator<<(ostream& out, Action act) {
  return out << "From " << act.from << " direction " << act.dir;
}

P2D P2D::cellToP2D(Cell c){
  return P2D(c.getX(), c.getY());
}