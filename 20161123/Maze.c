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

// 스택 초기화 함수
void init(StackType *s)
{
	
}
// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
	
}
// 삽입함수
void push(StackType *s, element item)
{

}
// 삭제함수
element pop(StackType *s)
{

}
// 피크함수
element peek(StackType *s)
{

}


// 위치를 스택에 삽입
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

		// 아래 ->오른쪽 ->위 ->왼쪽  : 이 순서대로 진행하려면 
		// 스택에는 반대로 넣어야 한다.

		push_loc(&s, r, c - 1);  // 왼쪽
		push_loc(&s, r - 1, c);  //위
		push_loc(&s, r, c + 1);  // 오른쪽
		push_loc(&s, r + 1, c);  //아래

		printStack(&s);
		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else
			here = pop(&s);

		printMaze(maze);
		getch();
	}
	printf("성공\n");
}
