int Board[19][19] = { 0 };
int Black = 0;
int White = 0;
int Count = 1;

void DrawBoard();
void PutStone();
void StoneCount();

#include<stdio.h>
#include<windows.h>

int main()
{
	while (1)
	{
		DrawBoard();
		PutStone();
	}
}

void DrawBoard()
{
	system("cls");
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (Board[i][j] == 0)
				printf("+");
			else if (Board[i][j] == 1)
			{
				printf("��");
				Black++;
			}
			else
			{
				printf("��");
				White++;
			}

		}
		printf("\n");
	}
	StoneCount();
}

void PutStone()
{
	while (1)
	{
		int i = 0, j = 0;

		printf("��ǥ�� �Է����ּ���[ex 1 1]: ");
		scanf("%d %d", &i, &j);
		if ((i >= 0 && i < 19) && (j >= 0 && j < 19) && (Board[i][j] == 0))
		{
			if ((Count % 2) == 1)
			{
				Board[i][j] = 1;
				Count++;
			}
			else
			{
				Board[i][j] = 2;
				Count++;
			}
			break;
		}
		else
		{
			printf("���� �������ְų�, ��ǥ���� ������ϴ�. �ٽ� �����ֽʽÿ�.");
		}
	}
}

void StoneCount()
{
	printf("\n");
	printf("�浹�� ����: %d\n", Black);
	printf("�鵹�� ����: %d\n", White);
	Black = 0;
	White = 0;
}