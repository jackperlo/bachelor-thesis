#ifndef P2D_H
#define P2D_H

#include <iostream>
#include <string>
#include "cell.h"

using namespace std;

class P2D {
	public:
		int x, y;

		P2D();
		P2D(int x, int y);
		// P2D(const P2D& p2d); // this matches the default copy constructor
		operator string ();
		P2D operator+(const P2D& other) const;
		P2D operator-() const;
		P2D operator-(const P2D& other) const;
		P2D& operator+=(const P2D& other);
		int manatthan(const P2D& other) const;
		bool operator==(const P2D& other) const;
		bool operator!=(const P2D& other) const;
		friend ostream& operator<<(ostream& out, P2D p);
    	static P2D cellToP2D(Cell c);

		struct HashFun {
			size_t operator()(const P2D& p) const;
		};

		struct CompareFun {
			bool operator() (const P2D& lhs, const P2D& rhs) const;
		};

		static const P2D UP;
		static const P2D DX;
		static const P2D DOWN;
		static const P2D SX;
    static const P2D JUMPING_UP;
		static const P2D JUMPING_DX;
		static const P2D JUMPING_DOWN;
		static const P2D JUMPING_SX;
    static const P2D null_p2d;
};

struct Action {
	P2D from, dir, head;
	double weight;
	int movementType; //0->activeMove, 1->pushedMove, 2->jumpingMove
    
	Action();
	// Action(const Action &act); // this matches the default copy constructor
	Action(P2D from, P2D dir, double weight = 0.00, int movementType = 0, P2D head = P2D::null_p2d);
	friend ostream& operator<<(ostream& out, Action act);

  static const Action null_action;
};

#endif