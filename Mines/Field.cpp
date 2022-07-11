#include "stdafx.h"
#include "Field.h"

void Field::setMines(void)
{
	if (1 == rand() % 6) state_in = 9; //mine
	else state_in = 8;//empty field
	state_out = 10; //covered field
}

void Field::Set(int st_x, int st_y, int en_x, int en_y)
{
	s_x = st_x;
	s_y = st_y;
	e_x = en_x;
	e_y = en_y;
}

void Field::Uncover(void)
{
	state_out = state_in;
}

void Field::UncoverEmpty(void)
{
	if (state_in < 9) Uncover();
}
bool Field::Visible(void)
{
	if (state_in == state_out) return true;
	return false;
}

Field::Field(){}

Field::~Field(){}
