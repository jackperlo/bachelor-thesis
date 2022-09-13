#include "p2d.h"
#include <iostream>
#include <string>

using namespace std;

const P2D P2D::UP(0, -1);
const P2D P2D::RIGHT(1, 0);
const P2D P2D::DOWN(0, 1);
const P2D P2D::LEFT(-1, 0);
const P2D P2D::JUMPING_UP(0, -2);
const P2D P2D::JUMPING_RIGHT(2, 0);
const P2D P2D::JUMPING_DOWN(0, 2);
const P2D P2D::JUMPING_LEFT(-2, 0);
const P2D P2D::null_p2d(-1, -1);
const Action Action::null_action(P2D::null_p2d, P2D::null_p2d, -1, -1, P2D::null_p2d);

P2D::P2D(){}
P2D::P2D(int x, int y) : x(x), y(y) { }

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

unsigned long long P2D::HashFun::operator()(const P2D& p) const {
  /* unsigned long long rowHash = hash<unsigned long long>()(17 * p.x);
  unsigned long long colHash = hash<unsigned long long>()(31 * p.y) << 1;
  return rowHash ^ colHash; */
  return (p.x)*(p.y);
}

bool P2D::CompareFun::operator() (const P2D& lhs, const P2D& rhs) const {
  return lhs.y < rhs.y or (lhs.y == rhs.y and lhs.x < rhs.x);
}

Action::Action(){}

Action::Action(P2D from, P2D dir, double heuristic_value, int movement_type, P2D head)
    : from(from), dir(dir), head(head), heuristic_value(heuristic_value), movement_type(movement_type) {}

ostream& operator<<(ostream& out, Action act) {
  return out << "From " << act.from << " direction " << act.dir << " moveType " << act.movement_type << " weight " << act.heuristic_value;
}

bool Action::operator==(const Action& other) const {
  return from == other.from && dir == other.dir && heuristic_value == other.heuristic_value && movement_type == other.movement_type;
}

P2D P2D::cellToP2D(Cell c){
  return P2D(c.get_x(), c.get_y());
}