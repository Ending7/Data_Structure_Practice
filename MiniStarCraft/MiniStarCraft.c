#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define ROW 20
#define COLUMN 40
#define OBJMAX 100

int Field[ROW][COLUMN] = { 0 };
int UnitId = 20;

void Insert(); // 내가 생성한 유닛을 필드에 생성한다.
void Display(); // 필드에 유닛을 보여준다.
void Produce(); // 유닛을 생성한다.

typedef struct unit
{
	int ID;
	int Type;
	int x;
	int y;
	char Name[30];
	int HP;
	int MP;
	int Mlength;
	int Alength;
	int Damage;
	int	UseMp;
	int Arange;
	int	Cost;

}Unit;

Unit unit[OBJMAX] =
{
	{1,1,19,39,"히드라(H)",50,0,3,5,26,0,1,1},
	{2,1,18,39,"히드라(H)",50,0,3,5,26,0,1,1},
	{3,2,17,39,"퀸(Q)",70,150,6,15,1000,45,1,2},
	{4,2,17,38,"퀸(Q)",70,150,6,15,1000,45,1,2},
	{5,1,17,37,"히드라(H)",50,0,3,5,26,0,1,1},
	{6,3,16,39,"디파일러(D)",60,200,2,10,1,60,5,2},
	{7,1,16,38,"히드라(H)",50,0,3,5,26,0,1,1},
	{8,3,15,39,"디파일러(D)",60,200,2,10,1,60,5,2},
	{9,1,15,38,"히드라(H)",50,0,3,5,26,0,1,1},
	{10,1,14,39,"히드라(H)",50,0,3,5,26,0,1,1},
	{11,4,0,0,"마린(M)",30,0,3,4,20,0,1,1},
	{12,4,1,0,"마린(M)",30,0,3,4,20,0,1,1},
	{13,4,2,0,"마린(M)",30,0,3,4,20,0,1,1},
	{14,6,2,1,"베슬(V)",80,140,5,12,50,35,3,2},
	{15,6,2,2,"베슬(V)",80,140,5,12,50,35,3,2},
	{16,5,3,0,"탱크(T)",120,0,4,17,40,0,1,2},
	{17,4,3,1,"마린(M)",30,0,3,4,20,0,1,1},
	{18,5,4,0,"탱크(T)",120,0,4,17,40,0,1,2},
	{19,4,4,1,"마린(M)",30,0,3,4,20,0,1,1},
	{20,4,5,0,"마린(M)",30,0,3,4,20,0,1,1}
};

/*{
	{1,"히드라(H)",50,0,3,5,25,0,1,1},
	{2,"퀸(Q)",70,150,6,15,1000,45,1,2},
	{3,"디파일러(D)",60,200,2,10,1,60,5,2},
	{4,"마린(M)",30,0,3,4,20,0,1,1},
	{5,"탱크(T)",120,0,4,17,40,0,1,2},
	{6,"베슬(V)",80,140,5,12,50,35,3,2}
};*/

int main()
{
	char num;
	Insert();
	while (1)
	{
		system("cls");
		Display();
		printf("[명령어 입력]\n");
		printf("[1.Produce q/Q.Quit]\n");
		scanf_s(" %c", &num);

		if ((num == '1') || (num == 'q') || (num == 'Q'))
		{
			switch (num)
			{
			case '1':
				Produce();
				break;

			case 'q':
			case 'Q':
				return 0;
			}
		}
	}
}

void Insert()
{
	int i;
	int id, x, y;

	for (i = 0; i < 30; i++)
	{
		if (unit[i].Type != 0) // 죽은 몬스터가 아니라면 해당 몬스터를 필드에 소환한다.
		{
			id = unit[i].ID;
			x = unit[i].x;
			y = unit[i].y;
			Field[x][y] = id;
		}
	}
}

void Display()
{
	int i, j, k, m_id, m_type = 0;
	int ch;

	system("cls");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++) // 필드에 유닛이 있나 훑어본다
		{
			if (Field[i][j] != 0) // 만약 유닛이 살아있다면
			{
				/*unit 테이블을 검사하여 해당 아이디와 같은 녀석이 있나 확인한다.
				있다면 그녀석의 TYPE을 확인하여 해당 몬스터의 이니셜을 화면에 표시한다.*/
				m_id = Field[i][j]; // 그 녀석의 ID를 복사한다.
				for (k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID) // 찾으면 타입을 복사하고 빠져나온다.
					{
						m_type = unit[k].Type;
						break;
					}

				}
				if (m_type == 1)
					printf("H");
				else if (m_type == 2)
					printf("Q");
				else if (m_type == 3)
					printf("D");
				else if (m_type == 4)
					printf("M");
				else if (m_type == 5)
					printf("T");
				else if (m_type == 6)
					printf("V");
			}
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

void Produce()
{
	int i, index;
	int m_x, m_y;
	char ch;

	while (1)
	{
		system("cls");
		printf("[유닛을 고르시오]\n");
		printf("[1.히드라 2.퀸 3.디파일러 4.마린 5.탱크 6.베슬 q/Q.Quit]\n");
		scanf_s(" %c", &ch);

		if ((ch >= '1') && (ch <= '6'))
		{
			printf("좌표를 입력하시오: ");
			while (1) // 올바른 좌표인지 검사
			{
				scanf_s("%d %d", &m_x, &m_y);
				if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)) && (Field[m_x][m_y] == 0))
					break;
				else
					printf("올바르지 않은 좌표");
			}

			for (i = 0; i < OBJMAX; i++) // id가 0인 index 색출해내기
			{
				if (unit[i].ID == 0)
				{
					index = i;
					break;
				}
			}

			switch (ch)
			{
			case '1':
				//{1,"히드라(H)", 50, 0, 3, 5, 25, 0, 1, 1}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 1;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 10, "히드라(H)");
				unit[index].HP = 30;
				unit[index].MP = 0;
				unit[index].Mlength = 3;
				unit[index].Alength = 5;
				unit[index].Damage = 25;
				unit[index].UseMp = 0;
				unit[index].Arange = 1;
				unit[index].Cost = 1;
				Insert();
				return 0;

			case '2':
				//{2,"퀸(Q)",70,150,6,15,1000,45,1,2}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 2;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 6, "퀸(Q)");
				unit[index].HP = 70;
				unit[index].MP = 150;
				unit[index].Mlength = 6;
				unit[index].Alength = 15;
				unit[index].Damage = 1000;
				unit[index].UseMp = 45;
				unit[index].Arange = 1;
				unit[index].Cost = 2;
				Insert();
				return 0;

			case '3':

				//{3,"디파일러(D)",60,200,2,10,1,60,5,2}

				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 3;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 12, "디파일러(D)");
				unit[index].HP = 60;
				unit[index].MP = 200;
				unit[index].Mlength = 2;
				unit[index].Alength = 10;
				unit[index].Damage = 1;
				unit[index].UseMp = 60;
				unit[index].Arange = 5;
				unit[index].Cost = 2;
				Insert();
				return 0;

			case '4':
				//{ 4,"마린(M)",30,0,3,4,20,0,1,1 }
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 4;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "마린(M)");
				unit[index].HP = 30;
				unit[index].MP = 0;
				unit[index].Mlength = 3;
				unit[index].Alength = 4;
				unit[index].Damage = 20;
				unit[index].UseMp = 0;
				unit[index].Arange = 1;
				unit[index].Cost = 1;
				Insert();
				return 0;
			case '5':
				//{5,"탱크(T)",120,0,4,17,40,0,1,2},
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 5;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "탱크(T)");
				unit[index].HP = 120;
				unit[index].MP = 0;
				unit[index].Mlength = 4;
				unit[index].Alength = 17;
				unit[index].Damage = 40;
				unit[index].UseMp = 0;
				unit[index].Arange = 1;
				unit[index].Cost = 2;
				Insert();
				return 0;
			case '6':
				//{ 6,"베슬(V)",80,140,5,12,50,35,3,2}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 6;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "베슬(V)");
				unit[index].HP = 80;
				unit[index].MP = 140;
				unit[index].Mlength = 5;
				unit[index].Alength = 12;
				unit[index].Damage = 50;
				unit[index].UseMp = 35;
				unit[index].Arange = 3;
				unit[index].Cost = 2;
				Insert();
				return 0;
			}
		}
		else if (ch == 'q' || ch == 'Q')
			return 0;
	}
}