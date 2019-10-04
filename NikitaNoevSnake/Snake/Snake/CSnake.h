#pragma once
#include "afx.h"

#include <vector>
#include <iterator>

using namespace std;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define BORDER 60
#define HEIGHT 600
#define WIDTH 600

#define POISON_NUM 10

class Snake : public CObject
{
	DECLARE_SERIAL(Snake);

private:
	

public:
	vector<CPoint> snake_list;
	vector<CPoint> default_state;
	UINT direction;
	BOOL is_food;
	CPoint food;
	CPoint poison[POISON_NUM];
	UINT speed; 

public:
	Snake();
	virtual ~Snake();

public:
	BOOL move();
	BOOL isDied(); 
	void generateFood();
	void changeDirection(UINT); 
	UINT getDirection();
	BOOL isFood(); 
	void setFood(BOOL);

};
