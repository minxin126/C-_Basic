#include<stdio.h>
//���������ά�����һ�У�����������Ӹ�ʽ
void row_output(int i, int x[9][9])
{
	int j, flag;
	for (j = 0; j < 9; j++)
	{
		//����Ƿ�Ϊ3�ı���
		flag = (j + 1) % 3;
		//����3�ı���ʱ���������ո�
		if (flag == 0)
			printf("%d  ", x[i][j]);
		//�������һ���ո�
		else
			printf("%d ", x[i][j]);
	}
}
//000 000 000
//�����վŹ������ʽ���������
void output(int x[9][9])
{
	int i, flag;
	for (i = 0; i < 9; i++)
	{
		//����Ƿ�Ϊ3�ı���
		flag = (i + 1) % 3;
		row_output(i, x);
		//����3�ı���ʱ������������
		if (flag == 0)
			printf("\n\n");
		//�������һ������
		else
			printf("\n");
	}
}
/*
0 0 0

0 0 0

0 0 0*/
//validate������������x[i][j]�Ƿ�Ϊ���е�ֵ
int validate(int x[9][9], int i, int j, int num)
{
	int row, column;
	int isPossible = 1;
	//������i�в�ѯ�Ƿ����ظ���ֵ
	for (column = 0; column < 9; column++)
	{
		if (num == x[i][column]) isPossible *= 0;
		else isPossible *= 1;
	}
	//������j�в�ѯ�Ƿ����ظ���ֵ
	for (row = 0; row < 9; row++)
	{
		if (num == x[row][j]) isPossible *= 0;
		else isPossible *= 1;
	}
	//����x[i][i]���ڹ�(box)��ѯ�Ƿ����ظ���ֵ
	int box_i, box_j;
	//��λ����λ��
	int offset_x, offset_y;
	//����x����(��j������ӷ���)ƫ����
	offset_x = j - j % 3;
	//����y����(��i������ӷ���)ƫ����
	offset_y = i - i % 3;
	for (box_i = 0; box_i < 3; box_i++)
	{
		for (box_j = 0; box_j < 3; box_j++)
		{
			//��box_i,box_j��������ȷ�ľŹ���
			if (num == x[box_i + offset_y][box_j + offset_x]) isPossible *= 0;
			else isPossible *= 1;
		}
	}
	//��֤���󷵻�1�����򷵻�0
	return isPossible;
}

void solve_soduku(int x[9][9])
{
	int i, j, num, flag = 0;
	//�½�һ����ά���鸺���¼���ɸ������֣�����ʼʱ�ͱ���������֣���λ��
	int can_not_modify[9][9] = { 0 };
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (x[i][j] != 0) can_not_modify[i][j] = 1;
		}
	}
	//��ʼ��i��j
	i = 0;
	j = 0;
	//�����Ź��񣬴�x[0][0]��ʼ����
	while (i < 9)
	{
		while (j < 9)
		{
			//�ж��Ƿ�Ϊ��һ���Դ���ת����
		start:if (flag == 1 && j == -1)
		{
			i--;
			j = 8;
			goto start;
		}
		//�ж��Ƿ�Ϊ�Դ���ת�����ҵ�ǰֵ�����޸�
		else if (flag == 1 && can_not_modify[i][j] == 1)
		{
			//����������һ��
			j--;
			continue;
		}
		//�жϵ�ǰ�����Ƿ񲻿��޸�
		else if (can_not_modify[i][j] == 1)
		{
			j++;
			continue;
		}
		//��ʼ����
		else
		{
			num = x[i][j];
			//����ǰ���ӻ�δ��ֵ������������һ���Դ���ת��������1��ʼ����
			if (num == 0) num = 1;
			//��flag==1��������һ���Դ����������һ�δ����ֵ+1��������
			else if (flag == 1) num = x[i][j] + 1;
			//��ʼ����ת��ʶ��ֵ
			flag = 0;
			//��num��ʼ����������
			for (; num <= 10; num++)
			{
				//��validate�����жϳ��Ե�ֵ�Ƿ����
				//������н���ǰ���ӵ�ֵ��Ϊnum
				if (validate(x, i, j, num) == 1 && num < 10)
				{
					x[i][j] = num;
					j++;
					break;
				}
				//�����9��û�п��е�ֵ���룬˵��ǰ���д���ʼ��ǰֵΪ0��������һ�γ���
				else if (num == 10)
				{
					x[i][j] = 0;
					j--;
					//������ת��ʶflag=1
					flag = 1;
					break;
				}
			}
		}
		}
		//һ����������һ�е�һ����������
		j = 0;
		i++;
	}
}

void main()
{
	int i, j;
	char temp;
	int soduku[9][9];
	printf("�������by minx:\n 2019/12/22\n\n\n");
	printf("��������Ҫ��������:\n");
	printf("  123456789\n");
	for (i = 0; i < 9; i++)
	{
		printf("%d:", i + 1);
		for (j = 0; j < 10; j++)
		{
			temp = getchar();
			if (j < 9) soduku[i][j] = temp - '0';
		}
	}
	printf("\n�������������:\n");
	output(soduku);
	solve_soduku(soduku);
	printf("�����:\n");
	output(soduku);
}
/*
003070000
010906230
050130006
060000180
901000504
082000070
700084050
048502060
000010800
*/

/*
6 9 3  2 7 5  4 1 8
8 1 7  9 4 6  2 3 5
2 5 4  1 3 8  7 9 6

4 6 5  7 2 9  1 8 3
9 7 1  8 6 3  5 2 4
3 8 2  4 5 1  6 7 9

7 2 6  3 8 4  9 5 1
1 4 8  5 9 2  3 6 7
5 3 9  6 1 7  8 4 2
*/

/*
6 9 3 2 7 5 4 1 8
8 1 7 9 4 6 2 3 5
2 5 4 1 3 8 7 9 6
4 6 5 7 2 9 1 8 3
9 7 1 8 6 3 5 2 4
3 8 2 4 5 1 6 7 9
7 2 6 3 8 4 9 5 1
1 4 8 5 9 2 3 6 7
5 3 9 6 1 7 8 4 2*/