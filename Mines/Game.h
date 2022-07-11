#pragma once
#include "Field.h"
#include "resource.h"

class Game
{
public:
	bool Active = true;
	void LoadImages(HINSTANCE hInst);
	void Run(HWND hWnd);
	void New(void);
	void Draw(HWND hWnd);
	void Lclick(int pos_x, int pos_y);
	void Rclick(int pos_x, int pos_y);
	void End(void);
	Game();
	~Game();

private:
	bool end;
	const int N = 10;
	Field field[10][10];
	HBITMAP bmp[13];
	int CountAdjacent(int x, int y);
	void UncoverAll(void);
	void UncoverEmpty(void);
	int CountMines(void);
	int CountUncovered(void);
	void CheckEnd(void);
};

