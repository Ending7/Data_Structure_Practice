#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define ROW 20
#define COLUMN 40
#define OBJMAX 100

int Field[ROW][COLUMN] = { 0 };
int UnitId = 20;

void Insert(); // ���� ������ ������ �ʵ忡 �����Ѵ�.
void Display(); // �ʵ忡 ������ �����ش�.
void Produce(); // ������ �����Ѵ�.
void Destroy(); // ������ �����Ѵ�.
void Select(); // �ش� ��ǥ�� ���� ������ ����Ѵ�.

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

int main()
{
	char num;
	Insert();
	while (1)
	{
		system("cls");
		Display();
		printf("[��ɾ� �Է�]\n");
		printf("[1.Produce 2.Destroy 3.Select q/Q.Quit]\n");
		scanf_s(" %c", &num);

		if (((num >= '1') && (num <='3')) || (num == 'q') || (num == 'Q'))
		{
			switch (num)
			{
			case '1':
				Produce();
				break;

			case '2':
				Destroy();
				break;

			case '3':
				Select();
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
		if (unit[i].Type != 0) // ���� ���Ͱ� �ƴ϶�� �ش� ���͸� �ʵ忡 ��ȯ�Ѵ�.
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
		for (j = 0; j < COLUMN; j++) // �ʵ忡 ������ �ֳ� �Ⱦ��
		{
			if (Field[i][j] != 0) // ���� ������ ����ִٸ�
			{
				/*unit ���̺��� �˻��Ͽ� �ش� ���̵�� ���� �༮�� �ֳ� Ȯ���Ѵ�.
				�ִٸ� �׳༮�� TYPE�� Ȯ���Ͽ� �ش� ������ �̴ϼ��� ȭ�鿡 ǥ���Ѵ�.*/
				m_id = Field[i][j]; // �� �༮�� ID�� �����Ѵ�.
				for (k = 0; k < OBJMAX; k++)
				{
					if (m_id == unit[k].ID) // ã���� Ÿ���� �����ϰ� �������´�.
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
		printf("[������ ���ÿ�]\n");
		printf("[1.����� 2.�� 3.�����Ϸ� 4.���� 5.��ũ 6.���� q/Q.Quit]\n");
		scanf_s(" %c", &ch);

		if ((ch >= '1') && (ch <= '6'))
		{
			printf("��ǥ�� �Է��Ͻÿ�: ");
			while (1) // �ùٸ� ��ǥ���� �˻�
			{
				scanf_s("%d %d", &m_x, &m_y);
				if (((m_x >= 0) && (m_x < 20)) && ((m_y >= 0) && (m_y < 40)) && (Field[m_x][m_y] == 0))
					break;
				else
					printf("�ùٸ��� ���� ��ǥ");
			}

			for (i = 0; i < OBJMAX; i++) // id�� 0�� index �����س���
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
				//{1,"�����(H)", 50, 0, 3, 5, 25, 0, 1, 1}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 1;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 10, "�����(H)");
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
				//{2,"��(Q)",70,150,6,15,1000,45,1,2}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 2;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 6, "��(Q)");
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

				//{3,"�����Ϸ�(D)",60,200,2,10,1,60,5,2}

				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 3;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 12, "�����Ϸ�(D)");
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
				//{ 4,"����(M)",30,0,3,4,20,0,1,1 }
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 4;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "����(M)");
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
				//{5,"��ũ(T)",120,0,4,17,40,0,1,2},
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 5;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "��ũ(T)");
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
				//{ 6,"����(V)",80,140,5,12,50,35,3,2}
				UnitId++;
				unit[index].ID = UnitId;
				unit[index].Type = 6;
				unit[index].x = m_x;
				unit[index].y = m_y;
				strcpy_s(unit[index].Name, 8, "����(V)");
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

void Destroy()
{
	int x, y, i;
	int m_id;
	char ch;
	system("cls");
	printf("�����ϰ� ���� ������ �ִ� ��ǥ �Է�\n");
	while (1)
	{
		scanf_s("%d %d", &x, &y);
		if (((x >= 0) && (x < 20)) && ((y >= 0) && (y < 40))) //�ùٸ� ��ǥ �Է� ��
		{
			printf("��� �����Ͻðڽ��ϱ�? y/n "); //Ȯ���ϰ�
			while (1)
			{
				scanf_s(" %c", &ch);
				if (ch == 'y')
					break; 
				if (ch == 'n')
					return 0;
			}
			break; // �Լ� �̾ ����
		}
		else //�߸��� ��ǥ �Է� �� �ݺ�
			printf("�ùٸ� ��ǥ �Է�");
	}

	m_id = Field[x][y]; //���̵� ã��
	for (i = 0; i < OBJMAX; i++)
	{
		if (m_id == unit[i].ID) //���̵� ã����
		{/*ID ���� ������ ���� 0���� �ʱ�ȭ�Ѵ�.*/
			unit[i].Type = 0;
			unit[i].x = 0;
			unit[i].y = 0;
			strcpy_s(unit[i].Name, 1,"");
			unit[i].HP = 0;
			unit[i].MP = 0;
			unit[i].Mlength = 0;
			unit[i].Alength = 0;
			unit[i].Damage = 0;
			unit[i].UseMp = 0;
			unit[i].Arange = 0;
			unit[i].Cost = 0;
			Field[x][y] = 0; //�ʵ尪�� 0���� �ٽ� �ʱ�ȭ���ش�.
		}
	}
}

void Select()
{
	system("cls");
	int x, y, m_id,i;
	int ch;
	printf("��ǥ�� �Է��Ͻÿ�: ");

	scanf_s("%d %d", &x, &y);
	while (1)
	{
		if (((x >= 0) && (x < 20)) && ((y >= 0) && (y < 40)))
		{
			if (Field[x][y] == 0)
			{
				printf("�ش� ��ġ���� ������ �������� �ʽ��ϴ�.");
				Sleep(2000);
				return 0;
			}
			else
			{
				m_id = Field[x][y]; // ���̵� ����
				break;
			}
		}
		else
		{
			printf("��ǥ�� ������ ������ϴ�.");
			Sleep(2000);
			return 0;
		}
	}

	for (i = 0; i < OBJMAX; i++) // �ش� ���̵� �´� ������ ã�´�
	{
		if (m_id == unit[i].ID)
		{
			printf("ID: %d\n", unit[i].ID);
			printf("�̸�: %s\n", unit[i].Name);
			printf("HP: %d\n", unit[i].HP);
			printf("MP: %d\n", unit[i].MP);
			printf("��ǥ(x,y): (%d,%d)\n", unit[i].x, unit[i].y);
			break;
		}
	}
	
	while (1)
	{
		printf("Press Enter...");
		if ((ch = _getch()) == 13)
			return 0;
	}
}