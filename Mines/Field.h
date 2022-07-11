#pragma once
class Field
{
public:
	int s_x, s_y, e_x, e_y;
	int state_in;
	int state_out;
	void setMines(void);
	void Set(int, int, int, int);
	void Uncover(void);
	void UncoverEmpty(void);
	bool Visible(void);
	Field();
	~Field();
};

