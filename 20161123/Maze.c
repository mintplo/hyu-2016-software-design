//	maze.c
#include <stdio.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10   


typedef struct {
	short r;
	short c;
} element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
	{ 'e', '0', '0', '0', '1', '0', '0', '0', '0', '1' },
	{ '1', '0', '0', '0', '1', '0', '0', '0', '0', '1' },
	{ '1', '0', '1', '1', '1', '0', '0', '1', '0', '1' },
	{ '1', '0', '0', '0', '1', '0', '0', '1', '0', '1' },
	{ '1', '0', '1', '0', '1', '0', '0', '1', '0', '1' },
	{ '1', '0', '1', '0', '1', '0', '0', '1', '0', '1' },
	{ '1', '0', '1', '0', '1', '0', '0', '1', '0', '1' },
	{ '1', '0', '1',  '0', '0', '0', '0','1', '0', 'x' },
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' }
};

// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	
}
// �����Լ�
void push(StackType *s, element item)
{

}
// �����Լ�
element pop(StackType *s)
{

}
// ��ũ�Լ�
element peek(StackType *s)
{

}


// ��ġ�� ���ÿ� ����
void push_loc(StackType *s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void printStack(StackType *s)
{
	int i;
	for (i = 5; i>s->top; i--)
		printf("|     |\n");
	for (i = s->top; i >= 0; i--)
		printf("|(%01d,%01d)|\n", s->stack[i].r, s->stack[i].c);
	printf("-------\n");
}

void printMaze(char m[MAZE_SIZE][MAZE_SIZE])
{
	int i, j;
	for (i = 0; i < MAZE_SIZE; i++)
		printf("---");
	printf("\n");
	for (i = 0; i < MAZE_SIZE; i++) {
		for (j = 0; j < MAZE_SIZE; j++)
			printf(" %c ", m[i][j]);
		printf("\n");
	}
	for (i = 0; i < MAZE_SIZE; i++)
		printf("---");
	printf("\n");
}


void main()
{
	int r, c;
	StackType s;

	init(&s);
	here = entry;
	printMaze(maze);
	printStack(&s);

	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';

		// �Ʒ� ->������ ->�� ->����  : �� ������� �����Ϸ��� 
		// ���ÿ��� �ݴ�� �־�� �Ѵ�.

		push_loc(&s, r, c - 1);  // ����
		push_loc(&s, r - 1, c);  //��
		push_loc(&s, r, c + 1);  // ������
		push_loc(&s, r + 1, c);  //�Ʒ�

		printStack(&s);
		if (is_empty(&s)) {
			printf("����\n");
			return;
		}
		else
			here = pop(&s);

		printMaze(maze);
		getch();
	}
	printf("����\n");
}
