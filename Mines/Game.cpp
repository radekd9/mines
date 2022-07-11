#include "stdafx.h"
#include "Game.h"

void Game::Run(HWND hWnd)
{
	UncoverEmpty();
	Draw(hWnd);
	CheckEnd();
	Sleep(30);
}

void Game::Lclick(int pos_x, int pos_y)
{
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			Field &tfield = field[x][y];
			if (pos_x>tfield.s_x && pos_x<tfield.e_x && pos_y>tfield.s_y && pos_y<tfield.e_y)
			{
				if (tfield.state_out<11)
				{
					tfield.Uncover();
					if (tfield.state_in == 9) UncoverAll();
				}
			}
		}
	}
}

void Game::Rclick(int pos_x, int pos_y)
{
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			Field &tfield = field[x][y];
			if (pos_x>tfield.s_x && pos_x<tfield.e_x && pos_y>tfield.s_y && pos_y<tfield.e_y)
			{
				if (tfield.state_out == 10 || tfield.state_out == 11) tfield.state_out++;
				else if (tfield.state_out == 12) tfield.state_out = 10;
			}
		}
	}
}

void Game::LoadImages(HINSTANCE hInst)
{
	bmp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	bmp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	bmp[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	bmp[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	bmp[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	bmp[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	bmp[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	bmp[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	bmp[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	bmp[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
	bmp[10] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
	bmp[11] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
	bmp[12] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));
	srand(GetTickCount());
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			field[x][y].Set(x * 18, y * 18, x * 18 + 17, y * 18 + 17);
		}
	}
	New();
}


void Game::New(void)
{
	end = false;
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			field[x][y].setMines();
		}
	}

	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			if (field[x][y].state_in == 8) // empty field
			{
				field[x][y].state_in = CountAdjacent(x, y) - 1;
				if (field[x][y].state_in == -1) field[x][y].state_in = 8;
			}
		}
	}
}

int Game::CountAdjacent(int x, int y)
{
	int result = 0;
	if (x == 0)
	{
		if (y == 0)
		{
			if (field[x + 1][y].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
			if (field[x + 1][y + 1].state_in == 9) result++;
		}
		else if (y == N - 1)
		{
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x + 1][y - 1].state_in == 9) result++;
			if (field[x + 1][y].state_in == 9) result++;
		}
		else
		{
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x + 1][y - 1].state_in == 9) result++;
			if (field[x + 1][y].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
			if (field[x + 1][y + 1].state_in == 9) result++;
		}
	}

	if (x>0 && x<N - 1)
	{
		if (y == 0)
		{
			if (field[x - 1][y].state_in == 9) result++;
			if (field[x + 1][y].state_in == 9) result++;
			if (field[x - 1][y + 1].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
			if (field[x + 1][y + 1].state_in == 9) result++;
		}
		else if (y == N - 1)
		{
			if (field[x - 1][y - 1].state_in == 9) result++;
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x + 1][y - 1].state_in == 9) result++;
			if (field[x - 1][y].state_in == 9) result++;
			if (field[x + 1][y].state_in == 9) result++;
		}
		else
		{
			if (field[x - 1][y - 1].state_in == 9) result++;
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x + 1][y - 1].state_in == 9) result++;
			if (field[x - 1][y].state_in == 9) result++;
			if (field[x + 1][y].state_in == 9) result++;
			if (field[x - 1][y + 1].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
			if (field[x + 1][y + 1].state_in == 9) result++;
		}
	}

	if (x == N - 1)
	{
		if (y == 0)
		{
			if (field[x - 1][y].state_in == 9) result++;
			if (field[x - 1][y + 1].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
		}
		else if (y == N - 1)
		{
			if (field[x - 1][y - 1].state_in == 9) result++;
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x - 1][y].state_in == 9) result++;
		}
		else
		{
			if (field[x - 1][y - 1].state_in == 9) result++;
			if (field[x][y - 1].state_in == 9) result++;
			if (field[x - 1][y].state_in == 9) result++;
			if (field[x - 1][y + 1].state_in == 9) result++;
			if (field[x][y + 1].state_in == 9) result++;
		}
	}
	return result;
}

void Game::UncoverAll(void)
{
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			field[x][y].Uncover();
		}
	}
}

void Game::UncoverEmpty(void)
{
	int x, y;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			if (field[x][y].state_out == 8)
			{
				if (x == 0)
				{
					if (y == 0)
					{
						field[x + 1][y].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
						field[x + 1][y + 1].UncoverEmpty();
					}
					else if (y == N - 1)
					{
						field[x][y - 1].UncoverEmpty();
						field[x + 1][y - 1].UncoverEmpty();
						field[x + 1][y].UncoverEmpty();
					}
					else
					{
						field[x][y - 1].UncoverEmpty();
						field[x + 1][y - 1].UncoverEmpty();
						field[x + 1][y].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
						field[x + 1][y + 1].UncoverEmpty();
					}
				}

				if (x>0 && x<N - 1)
				{
					if (y == 0)
					{
						field[x - 1][y].UncoverEmpty();
						field[x + 1][y].UncoverEmpty();
						field[x - 1][y + 1].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
						field[x + 1][y + 1].UncoverEmpty();
					}
					else if (y == N - 1)
					{
						field[x - 1][y - 1].UncoverEmpty();
						field[x][y - 1].UncoverEmpty();
						field[x + 1][y - 1].UncoverEmpty();
						field[x - 1][y].UncoverEmpty();
						field[x + 1][y].UncoverEmpty();
					}
					else
					{
						field[x - 1][y - 1].UncoverEmpty();
						field[x][y - 1].UncoverEmpty();
						field[x + 1][y - 1].UncoverEmpty();
						field[x - 1][y].UncoverEmpty();
						field[x + 1][y].UncoverEmpty();
						field[x - 1][y + 1].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
						field[x + 1][y + 1].UncoverEmpty();
					}
				}

				if (x == N - 1)
				{
					if (y == 0)
					{
						field[x - 1][y].UncoverEmpty();
						field[x - 1][y + 1].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
					}
					else if (y == N - 1)
					{
						field[x - 1][y - 1].UncoverEmpty();
						field[x][y - 1].UncoverEmpty();
						field[x - 1][y].UncoverEmpty();
					}
					else
					{
						field[x - 1][y - 1].UncoverEmpty();
						field[x][y - 1].UncoverEmpty();
						field[x - 1][y].UncoverEmpty();
						field[x - 1][y + 1].UncoverEmpty();
						field[x][y + 1].UncoverEmpty();
					}
				}
			}//end if(field[x][y].state_out == 9)
		}//end for(y=0;y<N;y++)
	}//end for(x=0;x<N;x++)
}//end UncoverEmpty(void)

int Game::CountMines(void)
{
	int x, y, c = 0;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			if (field[x][y].state_in == 9) c++;
		}
	}
	return c;
}

int Game::CountUncovered(void)
{
	int x, y, c = 0;
	for (x = 0; x<N; x++)
	{
		for (y = 0; y<N; y++)
		{
			if (!field[x][y].Visible()) c++;
		}
	}
	return c;
}

void Game::CheckEnd(void)
{
	if (!end)
	{
		if (CountMines() == CountUncovered())
		{
			MessageBox(NULL, L"Congratulations", L"Winner", MB_OK);
			end = true;
		}
	}
}

void Game::End(void)
{
	for (int i = 0; i<13; i++) DeleteObject((HGDIOBJ)bmp[i]);
}

void Game::Draw(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC hdc = GetDC(hWnd);
	if (hdc)
	{
		HDC hdcNew = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNew, bmp[0]);
		int x, y;
		Field tfield;
		for (x = 0; x<N; x++)
		{
			for (y = 0; y<N; y++)
			{
				tfield = field[x][y];
				SelectObject(hdcNew, bmp[tfield.state_out]);
				BitBlt(hdc, tfield.s_x, tfield.s_y, 18, 18, hdcNew, 0, 0, SRCCOPY);
			}
		}

		SelectObject(hdcNew, hbmOld);
		DeleteDC(hdcNew);
		ReleaseDC(hWnd, hdc);
	}
	else MessageBox(NULL, L"Can't get hdc.", L"Error", MB_OK);
}

Game::Game() {}

Game::~Game() {}
