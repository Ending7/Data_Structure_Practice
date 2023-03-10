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
	{1,1,19,39,"�����(H)",50,0,3,5,26,0,1,1},
	{2,1,18,39,"�����(H)",50,0,3,5,26,0,1,1},
	{3,2,17,39,"��(Q)",70,150,6,15,1000,45,1,2},
	{4,2,17,38,"��(Q)",70,150,6,15,1000,45,1,2},
	{5,1,17,37,"�����(H)",50,0,3,5,26,0,1,1},
	{6,3,16,39,"�����Ϸ�(D)",60,200,2,10,1,60,5,2},
	{7,1,16,38,"�����(H)",50,0,3,5,26,0,1,1},
	{8,3,15,39,"�����Ϸ�(D)",60,200,2,10,1,60,5,2},
	{9,1,15,38,"�����(H)",50,0,3,5,26,0,1,1},
	{10,1,14,39,"�����(H)",50,0,3,5,26,0,1,1},
	{11,4,0,0,"����(M)",30,0,3,4,20,0,1,1},
	{12,4,1,0,"����(M)",30,0,3,4,20,0,1,1},
	{13,4,2,0,"����(M)",30,0,3,4,20,0,1,1},
	{14,6,2,1,"����(V)",80,140,5,12,50,35,3,2},
	{15,6,2,2,"����(V)",80,140,5,12,50,35,3,2},
	{16,5,3,0,"��ũ(T)",120,0,4,17,40,0,1,2},
	{17,4,3,1,"����(M)",30,0,3,4,20,0,1,1},
	{18,5,4,0,"��ũ(T)",120,0,4,17,40,0,1,2},
	{19,4,4,1,"����(M)",30,0,3,4,20,0,1,1},
	{20,4,5,0,"����(M)",30,0,3,4,20,0,1,1}
};

/*{
	{1,"�����(H)",50,0,3,5,25,0,1,1},
	{2,"��(Q)",70,150,6,15,1000,45,1,2},
	{3,"�����Ϸ�(D)",60,200,2,10,1,60,5,2},
	{4,"����(M)",30,0,3,4,20,0,1,1},
	{5,"��ũ(T)",120,0,4,17,40,0,1,2},
	{6,"����(V)",80,140,5,12,50,35,3,2}
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
		printf("[��ɾ�: (1)Produce (2)Select (3)SelectAll (4)Destroy (5)SortById (q/Q)Quit\n");

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
	// ���� Ÿ���� 0�� �ƴ϶�� �׳༮�� ���̵� �ʵ忡 �ִ´�.
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
	//�ʵ忡 ������ ������ ���̵� ������ Ÿ����ã�� �̴ϼ��� ����
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
	//������ �����ϰ� ��ǥ�� �Է��ϸ� ����ִ� ������ ã�� ����ִ´�.
	while (1)
	{
		system("cls");
		printf("[1.����� 2.�� 3.�����Ϸ� 4.���� 5. ��ũ 6.���� q/Q.Exit]\n");
		scanf_s(" %c", &ch);
		if ((ch >= '1' && ch <= '6') || (ch == 'q') || (ch == 'Q'))
		{
			if ((ch == 'q') || (ch == 'Q'))
				return 0;

			while (1)
			{
				system("cls");
				printf("��ǥ �Է�: \n");
				scanf_s("%d %d", &m_x, &m_y);
				if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)))
					if (Field[m_x][m_y] == 0)
						break;
					else
					{
						printf("�ش� ��ǥ�� ������ ����");
						Sleep(1000);
						return 0;
					}
				else
				{
					printf("��� ��ǥ��");
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
		strcpy_s(unit[index].Name, 10, "�����(H)");
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
		strcpy_s(unit[index].Name, 6, "��(Q)");
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
		strcpy_s(unit[index].Name, 12, "�����Ϸ�(D)");
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
		strcpy_s(unit[index].Name, 8, "����(M)");
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
		strcpy_s(unit[index].Name, 8, "��ũ(T)");
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
		strcpy_s(unit[index].Name, 8, "����(V)");
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
	//��ǥ�� �Է¹޾� �ش� ��ǥ�� �ִ� ���� ���̵� �����Ͽ� �� ������ ������ ����Ѵ�.
	while (1)
	{
		system("cls");
		printf("��ǥ�� �Է��Ͻÿ�: ");
		scanf_s("%d %d", &m_x, &m_y);
		if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)))
			if (Field[m_x][m_y] != 0)
			{
				m_id = Field[m_x][m_y];		
				break;
			}
			else
			{
				printf("�ش� ��ǥ�� ���� ����");
			}
		else
		{
			printf("�߸��� ��ǥ��");
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
	//x1 x2 y1 y2��ǥ�� �Է¹޾� �� ���� ���� �ִ� �������� ���. ���̵� 0�� �ƴѳ༮�� ���
	int x1, x2, y1, y2;
	int m_id;
	char ch;
	while (1)
	{
		system("cls");
		printf("x1, y1��ǥ �Է�: ");
		scanf_s("%d %d", &x1, &y1);
		if (((x1 >= 0) && (x1 < 20)) && ((y1 >= 0) && (y1 < 40)))
			break;
		else
		{
			printf("��� ��ǥ��");
			Sleep(1000);
		}
	}

	while (1)
	{	
		system("cls");
		printf("x2, y2��ǥ �Է�: ");
		scanf_s("%d %d", &x2, &y2);
		if (((x2 >= 0) && (x2 < 20)) && ((y2 >= 0) && (y2 < 40)))
			break;
		else
		{
			printf("��� ��ǥ��");
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
	//��ǥ�� �Է¹ް�, ���̵� 0�� �ƴ϶�� unit���� �׳༮�� ã�ư� id���� 0���� �ٲ��ش�. �׷��� id�� �����ִ�ä��
	//type�� 0�̵ǹǷ� ���� �������� �����Ѵ�.
	int m_x, m_y, m_id;
	while (1)
	{
		system("cls");
		printf("��ǥ�� �Է��Ͻÿ�: ");
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
				printf("�ش� ��ǥ�� ������ �������� ����");
				Sleep(1000);
				return 0;
			}

		}
		else
		{
			printf("��� ��ǥ��");
			Sleep(1000);
		}
	}
}

void SortBy()
{
	//������ ID�� �ڵ����� �������̱� ������ �������ʿ���� ID�� 0�� �ƴ� �༮�� ������ָ� �ȴ�.
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
