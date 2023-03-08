#include <stdio.h>
#include <windows.h>

int Coord[10] = { 1,2,2,2,2,2,2,2,2,2 };
int Count = 0;

void Draw();
void Move();

int main()
{
	while (1)
	{
		Draw();
		Move();
	}
}

void Draw()
{
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		if (Coord[i] == 1)
			printf("C");
		else if (Coord[i] == 2)
			printf(",");
		else
			printf(" ");
	}
}

void Move()
{
	char c;
	if ((c = getch()) == 77)
	{
		if (Count < 9)
		{
			Coord[Count] = 0;
			Count++;
			Coord[Count] = 1;
		}
		else
			exit(1);
	}	

	else if ((c == 75))
	{
		if (Count >= 0)
		{
			Coord[Count] = 2;		
			Coord[Count-1] = 1;
			Count--;
		}
		else
			exit(1);
	}
}