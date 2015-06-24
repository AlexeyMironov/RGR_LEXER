#include <stdio.h>
#include <locale.h>
#include <time.h>

int stem[4][64];    // �������
int numRings[4];    // ���������� ����� �� �������� 
int numMoves;       // ���������� ����������� 

//================================================

void print_stem()				 //����� �������� ������������ ����� �� ��������

{
	int i, j;
	for (i = 1; i <= 3; i++) {
		printf("\n");
		printf("|");

		for (j = 0; j < numRings[i]; j++)
			printf(" %d", stem[i][j]);

	}
	printf("\n");
}

//================================================

void init(int numRingsings)            //������� ������������ ������������ �����
{
	for (numRings[1] = 0; numRingsings > 0; numRings[1]++, numRingsings--)
		stem[1][numRings[1]] = numRingsings;
	numRings[2] = numRings[3] = 0;
	numMoves = 0;
	print_stem();
}

//================================================

void move(int r1, int r2)                   //����������� ������ �� ������� r1 �� �������� r2
{
	stem[r2][numRings[r2]++] = stem[r1][--numRings[r1]];
	print_stem();         
	numMoves++;
}

//================================================

void hanoy(int numRings, int st1, int st2, int st3)  // ����������� �� ������� st1 �� �������� st3,
{													  // ��������� �������� st2 � �������� ��������������
	if (numRings == 1)
		move(st1, st3);
	else {
		hanoy(numRings - 1, st1, st3, st2);
		move(st1, st3);
		hanoy(numRings - 1, st2, st1, st3);
	}
}

//================================================

void main()
{

	clock_t time, end;
	time = clock();

	setlocale(LC_ALL, "rus");
	int numRings;
	printf("������� ���������� ������: ");
	scanf_s("%d", &numRings);
	init(numRings);
	hanoy(numRings, 1, 2, 3);
	printf("���������� �����������: %d\n", numMoves);

	time = clock() - time;
	printf("%f", (double)time / CLOCKS_PER_SEC);

	system("pause");

}