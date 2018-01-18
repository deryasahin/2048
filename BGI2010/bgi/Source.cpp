#include "graphics.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

int table[5][5];
int score = 0;
#define LEFTARROW 75
#define RIGHTARROW 77
#define UPARROW 72
#define DOWNARROW 80

void drawRectangle(void);
char* converNumberToChar();
void numAtRandomPosition();
char* convertRandomNumberToChar();
int generateNum();
int notPlay();
void scorePrint();
int controlEmpty(int, int);
void stop();
void updateScreen();
void moveLeft();
void addLeft();
void moveRight();
void addRight();
void moveUp();
void addUp();
void moveDown();
void addDown();


void finish()
{
	while (!kbhit())
	{
		delay(200);
	}
}

int main(void)
{
	initwindow(500, 500, "2048");
	drawRectangle();
	int key;
	while (1)
	{
		key = getch();
		if (key == LEFTARROW)
		{
			moveLeft();
			addLeft();
			moveLeft();
			updateScreen();
		}
		else if (key == RIGHTARROW)
		{
			moveRight();
			addRight();
			moveRight();
			updateScreen();
		}

		else if (key == UPARROW)
		{
			moveUp();
			addUp();
			moveUp();
			updateScreen();
		}
		
		else if (key == DOWNARROW)
		{
			moveDown();
			addDown();
			moveDown();
			updateScreen();
		}
		

	}
}


int generateNum()
{
	int num;
	srand(time(NULL));
	do {
		num = (rand() % 4 - 2 + 1) + 2;

	} while (num % 2 != 0);
	return num;

}


char* convertRandomNumberToChar()
{
	char *buffer = (char *)calloc(4, sizeof(char));
	int a;
	a = generateNum();
	itoa(a, buffer, 10);
	return buffer;
}

void numAtRandomPosition()
{
	int i = 0, j = 0;

	static int k = 0;


	char *gelen;
	gelen = convertRandomNumberToChar();
	srand(time(NULL));

	if (k == 0)
	{
		table[1][1] = generateNum();
		outtextxy(1 * 50 + 60, 1 * 50 + 60, gelen);
		table[1][1] = atoi(gelen);
		k++;

	}
	else {

		int a, b;
		a = (rand() % 4);
		b = (rand() % 4);
		while (controlEmpty(a, b) != 1)
		{
			a = (rand() % 4);
			b = (rand() % 4);
			if (notPlay() != 0)
			{
				stop();
			}

		}
		outtextxy(b * 50 + 60, a * 50 + 60, gelen);
		table[a][b] = atoi(gelen);
	}
	

}

void drawRectangle(void)
{
	int i, j = 50;
	setcolor(3);
	rectangle(30, 30, 300, 300);
	for (i = 50; i <= 250; i += 50)
	{
		for (j = 50; j <= 250; j += 50)
		{
			rectangle(i, j, i + 30, j + 30);
			setcolor(3);
		}

	}

	numAtRandomPosition();
}

int controlEmpty(int a, int b)
{
	int control = 0;

	if (table[a][b] == NULL)
	{
		control = 1;

	}

	return control;
}





int notPlay()
{
	int control = 1;
	int count = 0;
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (table[i][j] != NULL)
			{
				count++;
			}
		}
	}
	if (count == 25)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void stop()
{
	static int i = 0;
	if (i == 0)
	{
		table[5][5] = { 0 };
		cleardevice();
		setcolor(7);
		rectangle(40, 50, 220, 165);
		setbkcolor(4);
		outtextxy(60, 75, "GAME OVER");
		outtextxy(60, 105, "YOUR SCORE IS:");
		char *buffer = (char *)calloc(4, sizeof(char));
		itoa(score, buffer, 10);
		outtextxy(185, 105, buffer);
		i++;
	}
	finish();
}

char* convertNumberToChar(int a)
{
	char *buffer = (char *)calloc(4, sizeof(char));
	itoa(a, buffer, 10);
	return buffer;
}

void updateScreen()
{
	cleardevice();
	drawRectangle();
	int i, j;
	char * gelen;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (table[i][j] != NULL)
			{
				gelen = convertNumberToChar(table[i][j]);
				outtextxy(j * 50 + 60, i * 50 + 60, gelen);
			}
		}
	}
	scorePrint();

}

void scorePrint(void)
{
	char *buffer = (char *)calloc(4, sizeof(char));
	itoa(score, buffer, 10);
	outtextxy(310, 350, "score:");
	outtextxy(350, 350, buffer);
}



void moveLeft()
{
	int i, j, t;
	for (i = 0; i < 5; i++)
	{
		for (j = 1; j < 5; j++)
		{
			if (table[i][j] != NULL)
			{
				int temp = j;
				for (t = j - 1; t >= 0; t--)
				{
					if (table[i][t] == NULL)
					{
						table[i][t] = table[i][temp];
						table[i][temp] = NULL;
						temp = t;

					}
				}
			}
		}
	}

}

void addLeft()
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 1; j < 4; j++)
		{
			if (table[i][j] == table[i][j - 1])
			{
				table[i][j - 1] = table[i][j] + table[i][j - 1];
				table[i][j] = NULL;
				score = score + table[i][j - 1];
			}
		}
	}
}

void moveRight()
{
	int i, j, t;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (table[i][j] != NULL)
			{
				for (t = j + 1; t < 5; t++)
				{
					if (table[i][t] == NULL)
					{
						table[i][t] = table[i][j];
						table[i][j] = NULL;

					}
				}
			}
		}
	}

}

void addRight()
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (table[i][j] == table[i][j + 1])
			{
				table[i][j + 1] = table[i][j] + table[i][j + 1];
				table[i][j] = NULL;
				score = score + table[i][j + 1];
			}
		}
	}
}


void moveUp()
{
	int i, j, t;
	for (i = 1; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			int temp = i;
			if (table[i][j] != NULL)
			{
				for (t = i - 1; t >= 0; t--)
				{
					if (table[t][j] == NULL)
					{
						table[t][j] = table[temp][j];
						table[temp][j] = NULL;
						temp = t;

					}
				}
			}
		}
	}

}

void addUp()
{
	int i, j;
	for (i = 1; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (table[i][j] == table[i - 1][j])
			{
				table[i - 1][j] = table[i][j] + table[i - 1][j];
				table[i][j] = NULL;
				score = score + table[i - 1][j];
			}
		}
	}
}


void moveDown()
{
	int i, j, t;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (table[i][j] != NULL)
			{
				for (t = i + 1; t < 5; t++)
				{
					if (table[t][j] == NULL)
					{
						table[t][j] = table[i][j];
						table[i][j] = NULL;

					}
				}
			}
		}
	}

}

void addDown()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (table[i][j] == table[i + 1][j])
			{
				table[i + 1][j] = table[i + 1][j] + table[i][j];
				table[i][j] = NULL;
				score = score + table[i + 1][j];
			}
		}
	}
}