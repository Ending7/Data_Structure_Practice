#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define ROW 20
#define COLUMN 40
#define OBJMAX 100

int Field[ROW][COLUMN] = { 0 };
int UnitId = 20; // ����� ID �ڵ�������

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
	{1,1,19,39,1,"�����(H)",50,0,3,5,26,0,1,1},
	{2,1,18,39,1,"�����(H)",50,0,3,5,26,0,1,1},
	{3,2,17,39,1,"��(Q)",70,150,6,15,1000,45,1,2},
	{4,2,17,38,1,"��(Q)",70,150,6,15,1000,45,1,2},
	{5,1,17,37,1,"�����(H)",50,0,3,5,26,0,1,1},
	{6,3,16,39,1,"�����Ϸ�(D)",60,200,2,10,1,60,5,2},
	{7,1,16,38,1,"�����(H)",50,0,3,5,26,0,1,1},
	{8,3,15,39,1,"�����Ϸ�(D)",60,200,2,10,1,60,5,2},
	{9,1,15,38,1,"�����(H)",50,0,3,5,26,0,1,1},
	{10,1,14,39,1,"�����(H)",50,0,3,5,26,0,1,1},
	{11,4,0,0,2,"����(M)",30,0,3,4,20,0,1,1},
	{12,4,1,0,2,"����(M)",30,0,3,4,20,0,1,1},
	{13,4,2,0,2,"����(M)",30,0,3,4,20,0,1,1},
	{14,6,2,1,2,"����(V)",80,140,5,12,50,35,3,2},
	{15,6,2,2,2,"����(V)",80,140,5,12,50,35,3,2},
	{16,5,3,0,2,"��ũ(T)",120,0,4,17,40,0,1,2},
	{17,4,3,1,2,"����(M)",30,0,3,4,20,0,1,1},
	{18,5,4,0,2,"��ũ(T)",120,0,4,17,40,0,1,2},
	{19,4,4,1,2,"����(M)",30,0,3,4,20,0,1,1},
	{20,4,5,0,2,"����(M)",30,0,3,4,20,0,1,1}
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
void SortByID();

int main()
{
	char ch;
	Insert(); // ó�� ��ġ�� ���� �ʵ忡 ��ȯ

	while (1)
	{
		system("cls");
		Display();

		printf("��ɾ�: (1)Produce (2)Select (3)SelectAll (4)Destroy (5)SortByID (q/Q)Quit\n");
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
	// ������ Ÿ���� ������ 0�� �ƴϸ� �ʵ忡 ������ ���̵� �Է½��� ��ȯ��Ų��. 
	int i;
	int m_id, m_x, m_y;
	for (int i = 0; i < OBJMAX; i++)
	{
		if (unit[i].Type != 0) // ����ִ� ���� �ʵ忡 ��ȯ;
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
	// �ʵ忡 �����ִ� ���̵� ���� 0�� �ƴ϶�� �� ������ Ÿ�Կ� �°� �̴ϼ��� ȭ�鿡 ǥ���Ѵ�. 0�̶�� ������ ǥ���ϰ�, for���� �ٲ� �� ���͸� �Է��Ѵ�.
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

	//��ȯ�� ���͸� �� �� ��ȯ�� �ʵ��� ��ǥ�� �����Ѵ�. �ʵ忡 ���� 0�̾�� ��ȯ�� �����ϴ�. �ε��� ������ ����Ͽ� �����ִ� unit������ ã�Ƽ� �װ��� ���Ϳ� �´� ���� �Է����ش�.
	while (1)
	{
		system("cls");

		printf("(1)����� (2)�� (3)�����Ϸ� (4)���� (5)��ũ (6)���� (q/Q)Quit\n");

		scanf_s(" %c", &ch);
		if ((ch >= '1' && ch <= '6') || (ch == 'q') || (ch == 'Q'))
		{
			if ((ch == 'q' || ch == 'Q'))
				return 0;

			while (1)
			{
				system("cls");
				printf("��ǥ�� �Է��Ͽ� �ֽʽÿ�: ");

				scanf_s("%d %d", &m_x, &m_y);
				if ((m_x >= 0 && m_x < 20) && (m_y >= 0 && m_y < 40))
				{
					if (Field[m_x][m_y] == 0)
						break;
					else
					{
						printf("�ش� ��ǥ�� �̹� ������ �ֽ��ϴ�.");
						Sleep(1000);
					}
				}
				else
				{
					printf("�ùٸ� ��ǥ�� �Է��Ͽ� �ֽʽÿ�:");
					Sleep(1000);
				}

			}
			break; // while ���� ������ ����������.
		}


		else
		{
			printf("�ùٸ��� ���� ���Դϴ�.");
			Sleep(1000);
		}

	}
	for (int i = 0; i < OBJMAX; i++) // ����ִ� ������ ã�����̴�. ���̵� 0�̸� ����ִ� �����̴�.
	{
		if (unit[i].ID == 0)
			index = i; // �ε����� unit����ü�� ���� �� �ִ� �ε���
	}

	switch (ch)
	{
	case '1':
		UnitId++;
		unit[index].ID = UnitId;
		unit[index].Type = 1;
		unit[index].Enemy = 1;
		strcpy_s(unit[index].Name, 10, "�����(H)");
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
		strcpy_s(unit[index].Name, 6, "��(Q)");
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
		strcpy_s(unit[index].Name, 12, "�����Ϸ�(D)");
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
		strcpy_s(unit[index].Name, 10, "����(M)");
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
		strcpy_s(unit[index].Name, 10, "��ũ(T)");
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
		strcpy_s(unit[index].Name, 10, "����(V)");
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
	// ������ ��ǥ�� ������ ������ ǥ���Ѵ�. FIeld���� ���� 0�� �ƴ� �༮���� ����ϰ� 0�̸� ������ ���ٰ� ǥ���Ѵ�. ���̵� ������ unit���̺� ������ �Ѵ�.
	int m_x, m_y, m_id;;
	char ch;
	while (1)
	{
		system("cls");
		printf("��ǥ�� �Է��Ͻÿ�: ");
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
				printf("�ش� ��ǥ�� ������ �����ϴ�.");
				Sleep(1000);
			}
		}
		else
		{
			printf("��ǥ���� ������ϴ�.");
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
	//x1, x2, y1, y2 ��ǥ�� �Է¹ް�, �� ���� ���� �ִ� ��� ���ֵ��� ����� ���̴�. ���� ������ ���ٸ�(type == 0) �װ��� ������� �ʴ´�.
	int x1, x2, y1, y2;
	int m_id;
	int temp;
	char ch;

	while (1)
	{
		system("cls");
		printf("x1, y1��ǥ �Է�: ");
		scanf_s("%d %d", &x1, &y1);
		if ((x1 >= 0) && (x1 < 20) && (y1 >= 0) && (y1 < 40))
		{
			break;
		}
		else
		{
			printf("�ùٸ��� ���� ��ǥ");
			Sleep(1000);
		}

	}

	while (1)
	{
		system("cls");
		printf("x2, y2��ǥ �Է�: ");
		scanf_s("%d %d", &x2, &y2);
		if ((x2 >= 0) && (x2 < 20) && (y2 >= 0) && (y2 < 40))
		{
			break;
		}
		else
		{
			printf("�ùٸ��� ���� ��ǥ");
			Sleep(1000);
		}

	}
	// ��ǥ�� �������� ������� ����

	if (x1 > x2) // �ؿ��� �ݺ����� �������� x1�� x2���� �۾ƾ��Ѵ�.
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if (y1 > y2) // ������� 0 0 / 0 19�� �Է��ϸ� �ùٸ��� ��µǴµ�, 0 19 / 0 0�� �Է��� �� ����� ������ �ذ��ϱ� ���� ���̴�.
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++) //������ ������ ã��, �� ã���� ���� ���� ������ �Ȱ��� ã�Ƴ���.
		{
			//�ʵ忡 ��ȯ�� ���� ���̵� 0�� �ƴ϶�� �� �༮�� ������ ����Ѵ�. ���̵� KEY�����δٰ� unit �迭���� ã�Ƴ����Ѵ�.
			if (Field[i][j] != 0)
			{
				m_id = Field[i][j];
				for (int k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID) // �ش� ���̵� ã���� �׳༮�� ������ ����Ѵ�.
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
	// ��ǥ�� �Է��ϸ� �ش� ��ǥ�� �ִ� ������ ���̵� �����Ͽ� �� ������ ��� ������ ID���� �� 0���� �ٲ۴�. ID�� 0���� �ٲٰ������ PPT���� ���� ���� ID�� �����϶���ؼ�, ID�� �ٲ��� �ʴ´�.
	// �ٲٰ��� FIeld�� ���� 0���� �ٲ㼭 ���Ͱ� ��ȯ���� ���� ���·� ����� �ȴ�.
	int m_x, m_y, m_id;

	while (1)
	{
		system("cls");
		printf("x, y��ǥ �Է�: ");
		scanf_s("%d %d", &m_x, &m_y);
		if ((m_x >= 0) && (m_x < 20) && (m_y >= 0) && (m_y < 40))
		{
			if (Field[m_x][m_y] != 0) // ��ǥ �Է� ���߰�, �ʵ忡 ������ �����ϰ� �ִٸ�
			{
				m_id = Field[m_x][m_y]; // �� ������ ���̵� �����Ͽ�
				for (int k = 0; k < OBJMAX; k++) //unit ����ü �迭���� ã��
				{
					if (m_id == unit[k].ID) // ã�´ٸ� ���̵� ���� �� 0���� �ٲ۴�. ���̵� 0���� �ٲ㼭 �迭�� ����ִ� �������� ����������, ID�� �����϶���ؼ� ���ܵ�.
					{
						unit[k].Type = 0;
						unit[k].Enemy = 0;
						strcpy_s(unit[k].Name,1, "");
						unit[k].HP = 0;
						unit[k].MP = 0;
						unit[k].x = 0;
						unit[k].y = 0;
						Field[m_x][m_y] = 0; // �ʵ忡�� ���� ��ȯ ����
						return 0; // �۾��� �������� �׳� �κ�� ���ư��� ��
					}
				}
					
			}
			else
			{
				printf("�ش� ��ǥ���� ������ �������� �ʽ��ϴ�.");
				Sleep(1000);
				return 0;
			}
		}
		else
		{
			printf("�ùٸ��� ���� ��ǥ");
			Sleep(1000);
		}

	}

}

void SortByID()
{
	//������ ���Ľ��Ѽ� ����Ұǵ�, ����� ID�� ���Ƿ� �Է��ؼ� �����ϴ°� �ƴ϶� ���α׷��� ���ؼ� ������� ID�� �����ϰ� �ֱ� ������ 
	//�׳� TYPE�� 0�̾ƴ�(���� ������ �ƴ�) �༮���� ���ʴ�� ������ָ� �ȴ�.
	// ������ �ؾ��� ��, ID������� �����ϸ� �� ���̴�. ���������̵� ���������̵�.
	//�װ��� ���� ���� �� ���̵� ���Ƿ� �ο��ؾ��ϴϱ� �� �� �ʿ��� ���̴ϱ� �� �� �ϱ�� ����.
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

/*FindTarget()�Լ�..
����� �� ���� ���ϴ� ����� �����ص״µ�, �ð��̾�� ���ϰڴ�
���ָ��� Enemy�� ���׿� �׶��� �����Ͽ���, ���� Enemy�� �ٸ��� �����ΰ��̴�.
��ǥ�� �Է��ߴµ� ���̵� ������ �Ѿ��, ���̵� ������ �� ������ Enemy�� 1���� 2������ Ȯ���Ѵ�
���� 1�̶�� unit����ü �迭���� Enemy�� 2�� �༮�� ã��, �Ÿ������� �̿��Ͽ� �Ÿ��� Ȯ���Ѵ�.
�Ÿ��� min�̶�� ������ �־�ΰ� ���� �Ÿ��� ���� �༮�� �Ÿ��� ���⿡ ����.
�׸���, index������ ���� �ش��ϴ� ������ �ε����� unit����ü �迭���� � �ε����� ��ġ�ϴ����� Ȯ���Ѵ�.
�� unit[index].id�ϸ� �ش��ϴ� ������ ���̵� ǥ���� ���̴�.
������ �غ��߰ڴ�.*/