#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define ROW 20
#define COLUMN 40
#define OBJMAX 100

int Field[ROW][COLUMN] = { 0 };
int UnitId = 20; // 현재는 ID 자동생성중

typedef struct unit
{
	int ID;
	int Type;
	int x;
	int y;
	int Enemy;
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
	{1,1,19,39,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{2,1,18,39,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{3,2,17,39,1,"퀸(Q)",70,150,6,15,1000,45,1,2},
	{4,2,17,38,1,"퀸(Q)",70,150,6,15,1000,45,1,2},
	{5,1,17,37,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{6,3,16,39,1,"디파일러(D)",60,200,2,10,1,60,5,2},
	{7,1,16,38,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{8,3,15,39,1,"디파일러(D)",60,200,2,10,1,60,5,2},
	{9,1,15,38,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{10,1,14,39,1,"히드라(H)",50,0,3,5,26,0,1,1},
	{11,4,0,0,2,"마린(M)",30,0,3,4,20,0,1,1},
	{12,4,1,0,2,"마린(M)",30,0,3,4,20,0,1,1},
	{13,4,2,0,2,"마린(M)",30,0,3,4,20,0,1,1},
	{14,6,2,1,2,"베슬(V)",80,140,5,12,50,35,3,2},
	{15,6,2,2,2,"베슬(V)",80,140,5,12,50,35,3,2},
	{16,5,3,0,2,"탱크(T)",120,0,4,17,40,0,1,2},
	{17,4,3,1,2,"마린(M)",30,0,3,4,20,0,1,1},
	{18,5,4,0,2,"탱크(T)",120,0,4,17,40,0,1,2},
	{19,4,4,1,2,"마린(M)",30,0,3,4,20,0,1,1},
	{20,4,5,0,2,"마린(M)",30,0,3,4,20,0,1,1}
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
void SortByID();

int main()
{
	char ch;
	Insert(); // 처음 배치한 유닛 필드에 소환

	while (1)
	{
		system("cls");
		Display();

		printf("명령어: (1)Produce (2)Select (3)SelectAll (4)Destroy (5)SortByID (q/Q)Quit\n");
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
				SortByID();
				break;

			case 'q':
			case 'Q':
				return 0;;
			}
		}
	}
}

void Insert()
{
	// 유닛의 타입을 가지고 0이 아니면 필드에 몬스터의 아이디를 입력시켜 소환시킨다. 
	int i;
	int m_id, m_x, m_y;
	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].Type != 0) // 살아있는 유닛 필드에 소환;
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
	// 필드에 적혀있는 아이디를 보고 0이 아니라면 각 유닛의 타입에 맞게 이니셜을 화면에 표시한다. 0이라면 공백을 표시하고, for문이 바뀔 때 엔터를 입력한다.
	int m_id;
	int m_x, m_y;
	int m_type;


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
			{
				printf(" ");
			}
		}
		printf("\n");
	}

}

void Produce()
{
	char ch;
	int m_x, m_y;
	int index;

	//소환할 몬스터를 고른 후 소환할 필드의 좌표를 선택한다. 필드에 값이 0이어야 소환이 가능하다. 인덱스 변수를 사용하여 남아있는 unit공간을 찾아서 그곳에 몬스터에 맞는 값을 입력해준다.
	while (1)
	{
		system("cls");

		printf("(1)히드라 (2)퀸 (3)디파일러 (4)마린 (5)탱크 (6)베슬 (q/Q)Quit\n");

		scanf_s(" %c", &ch);
		if ((ch >= '1' && ch <= '6') || (ch == 'q') || (ch == 'Q'))
		{
			if ((ch == 'q' || ch == 'Q'))
				return 0;

			while (1)
			{
				system("cls");
				printf("좌표를 입력하여 주십시오: ");

				scanf_s("%d %d", &m_x, &m_y);
				if ((m_x >= 0 && m_x < 20) && (m_y >= 0 && m_y < 40))
				{
					if (Field[m_x][m_y] == 0)
						break;
					else
					{
						printf("해당 좌표에 이미 유닛이 있습니다.");
						Sleep(1000);
					}
				}
				else
				{
					printf("올바른 좌표를 입력하여 주십시오:");
					Sleep(1000);
				}

			}
			break; // while 문을 완전히 빠져나간다.
		}


		else
		{
			printf("올바르지 않은 값입니다.");
			Sleep(1000);
		}

	}
	for (int i = 0; i < OBJMAX; i++) // 비어있는 공간을 찾을것이다. 아이디가 0이면 비어있는 공간이다.
	{
		if (unit[i].ID == 0)
			index = i; // 인덱스가 unit구조체의 넣을 수 있는 인덱스
	}

	switch (ch)
	{
	case '1':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 1;
		unit[index].Enemy = 1;
		strcpy_s(unit[index].Name, 10, "히드라(H)");
		unit[index].HP = 50;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '2':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 2;
		unit[index].Enemy = 1;
		strcpy_s(unit[index].Name, 6, "퀸(Q)");
		unit[index].HP = 70;
		unit[index].MP = 150;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '3':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 3;
		unit[index].Enemy = 1;
		strcpy_s(unit[index].Name, 12, "디파일러(D)");
		unit[index].HP = 60;
		unit[index].MP = 200;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '4':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 4;
		unit[index].Enemy = 2;
		strcpy_s(unit[index].Name, 10, "마린(M)");
		unit[index].HP = 30;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '5':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 5;
		unit[index].Enemy = 2;
		strcpy_s(unit[index].Name, 10, "탱크(T)");
		unit[index].HP = 120;
		unit[index].MP = 0;
		unit[index].x = m_x;
		unit[index].y = m_y;
		Insert();
		break;
	case '6':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 6;
		unit[index].Enemy = 2;
		strcpy_s(unit[index].Name, 10, "베슬(V)");
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
	// 선택한 좌표의 유닛의 정보를 표시한다. FIeld에서 값이 0이 아닌 녀석들을 출력하고 0이면 유닛이 없다고 표시한다. 아이디를 가지고 unit테이블에 참조를 한다.
	int m_x, m_y, m_id;;
	char ch;
	while (1)
	{
		system("cls");
		printf("좌표를 입력하시오: ");
		scanf_s("%d %d", &m_x, &m_y);
		if ((m_x >= 0 && m_x < 20) && (m_y >= 0 && m_y < 40))
		{
			if (Field[m_x][m_y] != 0)
			{
				m_id = Field[m_x][m_y];
				for (int i = 0; i < OBJMAX; i++)
				{

					if (m_id == unit[i].ID)

					{
						printf("ID: %d\n", unit[i].ID);
						printf("Type: %d\n", unit[i].Type);
						printf("Enemy: %d\n", unit[i].Enemy);
						printf("Name: %s\n", unit[i].Name);
						printf("HP: %d\n", unit[i].HP);
						printf("MP: %d\n", unit[i].MP);
						printf("(x,y): (%d,%d)\n", unit[i].x, unit[i].y);
						break;
					}

				}
				break;
			}
			else
			{
				printf("해당 좌표에 유닛이 없습니다.");
				Sleep(1000);
			}
		}
		else
		{
			printf("좌표값을 벗어났습니다.");
			Sleep(1000);
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
	//x1, x2, y1, y2 좌표를 입력받고, 그 범위 내에 있는 모든 유닛들을 출력할 것이다. 만약 유닛이 없다면(type == 0) 그것은 출력하지 않는다.
	int x1, x2, y1, y2;
	int m_id;
	int temp;
	char ch;

	while (1)
	{
		system("cls");
		printf("x1, y1좌표 입력: ");
		scanf_s("%d %d", &x1, &y1);
		if ((x1 >= 0) && (x1 < 20) && (y1 >= 0) && (y1 < 40))
		{
			break;
		}
		else
		{
			printf("올바르지 않은 좌표");
			Sleep(1000);
		}

	}

	while (1)
	{
		system("cls");
		printf("x2, y2좌표 입력: ");
		scanf_s("%d %d", &x2, &y2);
		if ((x2 >= 0) && (x2 < 20) && (y2 >= 0) && (y2 < 40))
		{
			break;
		}
		else
		{
			printf("올바르지 않은 좌표");
			Sleep(1000);
		}

	}
	// 좌표를 구했으면 여기부터 시작

	if (x1 > x2) // 밑에서 반복문을 돌릴려면 x1이 x2보다 작아야한다.
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if (y1 > y2) // 예를들어 0 0 / 0 19를 입력하면 올바르게 출력되는데, 0 19 / 0 0을 입력할 때 생기는 오류를 해결하기 위한 것이다.
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++) //열부터 유닛을 찾고, 다 찾고나면 다음 행의 유닛을 똑같이 찾아낸다.
		{
			//필드에 소환된 몬스터 아이디가 0이 아니라면 그 녀석의 정보를 출력한다. 아이디를 KEY값으로다가 unit 배열에서 찾아내야한다.
			if (Field[i][j] != 0)
			{
				m_id = Field[i][j];
				for (int k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID) // 해당 아이디를 찾으면 그녀석의 정보를 출력한다.
					{
						printf("ID: %d\n", unit[k].ID);
						printf("Type: %d\n", unit[k].Type);
						printf("Enemy: %d\n", unit[k].Enemy);
						printf("Name: %s\n", unit[k].Name);
						printf("HP: %d\n", unit[k].HP);
						printf("MP: %d\n", unit[k].MP);
						printf("(x,y): (%d,%d)\n", unit[k].x, unit[k].y);
						printf("\n");
						break;
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
	// 좌표를 입력하면 해당 좌표에 있는 유닛의 아이디를 참조하여 그 유닛의 모든 정보를 ID빼고 다 0으로 바꾼다. ID도 0으로 바꾸고싶은데 PPT보면 죽은 유닛 ID도 유지하라고해서, ID는 바꾸지 않는다.
	// 바꾸고나면 FIeld의 값을 0으로 바꿔서 몬스터가 소환되지 않은 상태로 만들면 된다.
	int m_x, m_y, m_id;

	while (1)
	{
		system("cls");
		printf("x, y좌표 입력: ");
		scanf_s("%d %d", &m_x, &m_y);
		if ((m_x >= 0) && (m_x < 20) && (m_y >= 0) && (m_y < 40))
		{
			if (Field[m_x][m_y] != 0) // 좌표 입력 잘했고, 필드에 유닛이 존재하고 있다면
			{
				m_id = Field[m_x][m_y]; // 그 유닛의 아이디를 복사하여
				for (int k = 0; k < OBJMAX; k++) //unit 구조체 배열에서 찾고
				{
					if (m_id == unit[k].ID) // 찾는다면 아이디 빼고 다 0으로 바꾼다. 아이디도 0으로 바꿔서 배열을 비어있는 공간으로 만들고싶은데, ID는 유지하라고해서 남겨둠.
					{
						unit[k].Type = 0;
						unit[k].Enemy = 0;
						strcpy_s(unit[k].Name,1, "");
						unit[k].HP = 0;
						unit[k].MP = 0;
						unit[k].x = 0;
						unit[k].y = 0;
						Field[m_x][m_y] = 0; // 필드에서 유닛 소환 해제
						return 0; // 작업이 끝났으면 그냥 로비로 돌아가도 됨
					}
				}
					
			}
			else
			{
				printf("해당 좌표에는 유닛이 존재하지 않습니다.");
				Sleep(1000);
				return 0;
			}
		}
		else
		{
			printf("올바르지 않은 좌표");
			Sleep(1000);
		}

	}

}

void SortByID()
{
	//유닛을 정렬시켜서 출력할건데, 현재는 ID를 임의로 입력해서 저장하는게 아니라 프로그램에 의해서 순서대로 ID가 증가하고 있기 때문에 
	//그냥 TYPE이 0이아닌(죽은 유닛이 아닌) 녀석들을 차례대로 출력해주면 된다.
	// 정렬을 해야할 시, ID순서대로 정렬하면 될 것이다. 선택정렬이든 버블정렬이든.
	//그것은 다음 시험 때 아이디를 임의로 부여해야하니까 그 때 필요한 것이니까 그 때 하기로 하자.
	char ch;
	system("cls");

	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].Type != 0)
		{
			printf("ID: %d\n", unit[i].ID);
			printf("Type: %d\n", unit[i].Type);
			printf("Enemy: %d\n", unit[i].Enemy);
			printf("Name: %s\n", unit[i].Name);
			printf("HP: %d\n", unit[i].HP);
			printf("MP: %d\n", unit[i].MP);
			printf("(x,y): (%d,%d)\n", unit[i].x, unit[i].y);
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

/*FindTarget()함수..
가까운 적 유닛 구하는 방법도 생각해뒀는데, 시간이없어서 못하겠다
유닛마다 Enemy로 저그와 테란을 구별하였고, 만약 Enemy가 다르면 상대방인것이다.
좌표를 입력했는데 아이디가 없으면 넘어가고, 아이디가 있으면 그 유닛의 Enemy가 1인지 2인지를 확인한다
만약 1이라면 unit구조체 배열에서 Enemy가 2인 녀석을 찾고, 거리공식을 이용하여 거리를 확인한다.
거리는 min이라는 변수에 넣어두고 가장 거리가 작은 녀석의 거리가 여기에 담긴다.
그리고, index변수를 만들어서 해당하는 유닛의 인덱스가 unit구조체 배열에서 어떤 인덱스에 위치하는지를 확인한다.
그 unit[index].id하면 해당하는 유닛의 아이디가 표현될 것이다.
집가서 해봐야겠다.*/