#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define ROW 20
#define COLUMN 40
#define OBJMAX 100

int Field[ROW][COLUMN] = { 0 };
int UnitId = 20;

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

void Insert();
void Display();
void Produce();
void Select();
void SelectAll();
void Destroy();
void SortBy();

int main()
{
	char ch;
	Insert();
	while (1)
	{
		system("cls");
		Display();
		printf("[명령어: (1)Produce (2)Select (3)SelectAll (4)Destroy (5)SortById (q/Q)Quit\n");

		scanf_s(" %c", &ch);
		if ((ch >= '1' && ch <= '5') || (ch == 'q') || (ch == 'Q'))
		{
			switch (ch)
			{
			case '1':
				Produce();
				break;
			case '2':
				Select();
				break;
			case '3':
				SelectAll();
				break;
			case '4':
				Destroy();
				break;
			case '5':
				SortBy();
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
	int m_id, m_x, m_y;;
	// 유닛 타입이 0이 아니라면 그녀석의 아이디를 필드에 넣는다.
	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].Type != 0)
		{
			m_id = unit[i].ID;
			m_x = unit[i].x;
			m_y = unit[i].y;
			Field[m_x][m_y] = m_id;
		}

	}
}

void Display()
{
	int m_id;
	int m_type;
	//필드에 생성된 몬스터의 아이디를 가지고 타입을찾아 이니셜을 띄운다
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (Field[i][j] != 0)
			{
				m_id = Field[i][j];
				for (int k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID)
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
}

void Produce()
{
	char ch;
	int m_x, m_y, m_id;
	int index;
	//유닛을 결정하고 좌표를 입력하면 비어있는 공간을 찾아 집어넣는다.
	while (1)
	{
		system("cls");
		printf("[1.히드라 2.퀸 3.디파일러 4.마린 5. 탱크 6.베슬 q/Q.Exit]\n");
		scanf_s(" %c", &ch);
		if ((ch >= '1' && ch <= '6') || (ch == 'q') || (ch == 'Q'))
		{
			if ((ch == 'q') || (ch == 'Q'))
				return 0;

			while (1)
			{
				system("cls");
				printf("좌표 입력: \n");
				scanf_s("%d %d", &m_x, &m_y);
				if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)))
					if (Field[m_x][m_y] == 0)
						break;
					else
					{
						printf("해당 좌표에 유닛이 존재");
						Sleep(1000);
						return 0;
					}
				else
				{
					printf("벗어난 좌표값");
					Sleep(1000);
				}
			}
		}
		break;
	}

	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].ID == 0)
			index = i;
	}

	switch (ch)
	{
	case '1':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 10, "히드라(H)");
		unit[index].Type = 1;
		unit[index].HP = 50;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '2':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 6, "퀸(Q)");
		unit[index].Type = 2;
		unit[index].HP = 70;
		unit[index].MP = 150;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '3':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 12, "디파일러(D)");
		unit[index].Type = 3;
		unit[index].HP = 60;
		unit[index].MP = 200;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '4':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 8, "마린(M)");
		unit[index].Type = 4;
		unit[index].HP = 30;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '5':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 8, "탱크(T)");
		unit[index].Type = 5;
		unit[index].HP = 120;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '6':
		UnitId++;
		unit[index].ID = UnitId;
		strcpy_s(unit[index].Name, 8, "베슬(V)");
		unit[index].Type = 6;
		unit[index].HP = 80;
		unit[index].MP = 140;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	}
	return 0;
}

void Select()
{
	int m_x, m_y, m_id;
	char ch;
	//좌표를 입력받아 해당 좌표에 있는 유닛 아이디를 참조하여 그 유닛의 정보를 출력한다.
	while (1)
	{
		system("cls");
		printf("좌표를 입력하시오: ");
		scanf_s("%d %d", &m_x, &m_y);
		if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)))
			if (Field[m_x][m_y] != 0)
			{
				m_id = Field[m_x][m_y];		
				break;
			}
			else
			{
				printf("해당 좌표에 유닛 없음");
			}
		else
		{
			printf("잘못된 좌표값");
		}
	}

	for (int i = 0; i < OBJMAX; i++)
	{
		if (m_id == unit[i].ID)
		{
			printf("ID: %d\n",unit[i].ID);
			printf("NAME: %s\n", unit[i].Name);
			printf("TYPE: %d\n", unit[i].Type);
			printf("HP: %d\n", unit[i].HP);
			printf("MP: %d\n", unit[i].MP);
			printf("(x,y): %d %d\n", unit[i].x, unit[i].y);
		}
	}

	while (1)
	{
		printf("Press Enter...");
		if ((ch = _getch()) == 13)
			return 0;
	}
}

void SelectAll()
{
	//x1 x2 y1 y2좌표를 입력받아 그 범위 내에 있는 유닛정보 출력. 아이디가 0이 아닌녀석만 출력
	int x1, x2, y1, y2;
	int m_id;
	char ch;
	while (1)
	{
		system("cls");
		printf("x1, y1좌표 입력: ");
		scanf_s("%d %d", &x1, &y1);
		if (((x1 >= 0) && (x1 < 20)) && ((y1 >= 0) && (y1 < 40)))
			break;
		else
		{
			printf("벗어난 좌표값");
			Sleep(1000);
		}
	}

	while (1)
	{	
		system("cls");
		printf("x2, y2좌표 입력: ");
		scanf_s("%d %d", &x2, &y2);
		if (((x2 >= 0) && (x2 < 20)) && ((y2 >= 0) && (y2 < 40)))
			break;
		else
		{
			printf("벗어난 좌표값");
			Sleep(1000);
		}
	}
	if (x2 < x1)
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if (y2 < y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	for (int i = x1; i <= x2;i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			if (Field[i][j] != 0)
			{
				m_id = Field[i][j];
				for (int k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID)
					{
						printf("ID: %d\n", unit[k].ID);
						printf("NAME: %s\n", unit[k].Name);
						printf("TYPE: %d\n", unit[k].Type);
						printf("HP: %d\n", unit[k].HP);
						printf("MP: %d\n", unit[k].MP);
						printf("(x,y): %d %d\n", unit[k].x, unit[k].y);
						printf("\n");
					}
				}

			}
		}
	}
	while (1)
	{
		printf("Press Enter...");
		if ((ch = _getch()) == 13)
			return 0;
	}
}

void Destroy()
{
	//좌표를 입력받고, 아이디가 0이 아니라면 unit에서 그녀석을 찾아가 id빼고 0으로 바꿔준다. 그러면 id는 남아있는채로
	//type이 0이되므로 죽은 유닛으로 간주한다.
	int m_x, m_y, m_id;
	while (1)
	{
		system("cls");
		printf("좌표를 입력하시오: ");
		scanf_s("%d %d", &m_x, &m_y);
		if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)))
		{
			if (Field[m_x][m_y] != 0)
			{	
				m_id = Field[m_x][m_y];
				for (int i = 0; i < OBJMAX; i++)
				{
					if (m_id == unit[i].ID)
					{
						strcpy_s(unit[i].Name, 1, "");
						unit[i].Type = 0;
						unit[i].HP = 0;
						unit[i].MP = 0;
						unit[i].x = 0;
						unit[i].y = 0;
						Field[m_x][m_y] = 0;
						return 0;
					}

				}
			}
			else
			{
				printf("해당 좌표에 유닛이 존재하지 않음");
				Sleep(1000);
				return 0;
			}

		}
		else
		{
			printf("벗어난 좌표값");
			Sleep(1000);
		}
	}
}

void SortBy()
{
	//지금은 ID를 자동으로 생성중이기 때문에 정렬할필요없이 ID가 0이 아닌 녀석만 출력해주면 된다.
	char ch;

	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].ID != 0)
		{
			printf("ID: %d\n", unit[i].ID);
			printf("NAME: %s\n", unit[i].Name);
			printf("TYPE: %d\n", unit[i].Type);
			printf("HP: %d\n", unit[i].HP);
			printf("MP: %d\n", unit[i].MP);
			printf("(x,y): %d %d\n", unit[i].x, unit[i].y);
			printf("\n");
		}
	}
	while (1)
	{
		printf("Press Enter...");
		if ((ch = _getch()) == 13)
			return 0;
	}
}
