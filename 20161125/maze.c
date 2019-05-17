#define _CRT_SECURE_NO_WARNINGS
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

void init(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	if (s->top == -1) {
		return 1;
	}

	return 0;
}

int is_full(StackType *s)
{
	if (s->top == MAX_STACK_SIZE - 1) {
		return 1;
	}

	return 0;
}

void push(StackType *s, element item)
{
	if (!is_full(&s)) {
		s->stack[s->top + 1] = item;
		s->top++;
	}
}

element pop(StackType *s)
{
	return s->stack[s->top--];
}

element peek(StackType *s)
{
	return s->stack[s->top];
}

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

void printMazeToTxt(char m[MAZE_SIZE][MAZE_SIZE], FILE* fp)
{
	int i, j;

	// 매 출력마다 파일의 끝으로 간다.
	fseek(fp, 0L, SEEK_END);
	
	for (i = 0; i < MAZE_SIZE; i++)
		fprintf(fp, "---");
	fprintf(fp, "\n");

	for (i = 0; i < MAZE_SIZE; i++) {
		for (j = 0; j < MAZE_SIZE; j++)
			fprintf(fp, " %c ", m[i][j]);
		fprintf(fp, "\n");
	}
	for (i = 0; i < MAZE_SIZE; i++)
		fprintf(fp, "---");
	fprintf(fp, "\n");
}


void main()
{
	int r, c;
	StackType s;

	init(&s);
	here = entry;
	printMaze(maze);
	printStack(&s);

	FILE *fp = NULL;
	if ((fp = fopen("./maze_rst.txt", "a+")) == NULL) {
		fprintf(stderr, "파일 %s을 열 수 없습니다.\n", fp);

		return;
	}

	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';

		push_loc(&s, r, c - 1);
		push_loc(&s, r - 1, c);
		push_loc(&s, r, c + 1);
		push_loc(&s, r + 1, c);

		printStack(&s);
		if (is_empty(&s)) {
			printf("empty");
			return;
		}
		else
			here = pop(&s);

		printMaze(maze);
		printMazeToTxt(maze, fp);

		getch();
	}

	fclose(fp);

	printf("complete");
}
