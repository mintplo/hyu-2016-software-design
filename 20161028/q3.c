#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init_board(char board[3][3]); // 현재 보드의 상태를 보여준다 int get_player_move(int palyer, char board[][3]);
void disp_board(char board[3][3]);
void autoplay(char board[3][3]);
int get_player_move(int player, char board[3][3]);
void move_play(int player, char board[3][3], int x, int y);
int judge(char board[3][3]);

int main(void)
{
	char board[3][3];
	int quit = 0; init_board(board);

	do {
		disp_board(board);

		quit = get_player_move(0, board);// first plyer disp_board(board);
		quit = judge(board);
		if (quit != 0) {
			break;
		}

		autoplay(board);

		quit = judge(board);
	} while (quit == 0);

	disp_board(board);

	return 0;
}

void init_board(char board[3][3]) {
	int x, y;
	for (x = 0; x<3; x++)
		for (y = 0; y<3; y++) board[x][y] = ' ';
}

void disp_board(char board[3][3]) {
	int i;
	for (i = 0; i<3; i++) {
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
	}

	printf("---|---|---\n");
}

int get_player_move(int player, char board[3][3]) {
	int x, y, done = 0;

	while (done != 1) {
		printf("(x, y) 좌표(종료-1, -1): ");
		scanf("%d %d", &x, &y);

		if (x == -1 && y == -1) return 1;
		if (board[x][y] == ' ') break;
		// 현재 비어있는 자리이면, 더 이상 입력을 받을 필요가 없다. else printf("잘못된 위치입니다.\n");
	}

	move_play(player, board, x, y);

	return 0;
}

void move_play(int player, char board[3][3], int x, int y) {
	if (player == 0) board[x][y] = 'X';
	else board[x][y] = 'O';
}

void autoplay(char board[3][3]) {
	int x = rand() % 4;
	int y = rand() % 4;

	while (1) {
		if (board[x][y] == ' ') break;

		x = rand() % 4;
		y = rand() % 4;
	}

	move_play(1, board, x, y);
}

int judge(char board[3][3]) {
	int available = 0;
	int player1 = 0;
	int player2 = 0;

	// 행 승리 판단
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				available++;
			}

			if (board[i][j] == 'O') {
				player1++;
			}
			else if (board[i][j] == 'X') {
				player2++;
			}
		}

		if (player1 == 3) {
			printf("\nplayer1 승!\n");
			return 1;
		}
		else if (player2 == 3) {
			printf("\nplayer2 승!\n");
			return 1;
		}

		player1 = player2 = 0;
	}

	player1 = player2 = 0;

	// 열 승리 판단
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				available++;
			}

			if (board[j][i] == 'O') {
				player1++;
			}
			else if (board[j][i] == 'X') {
				player2++;
			}
		}

		if (player1 == 3) {
			printf("\nplayer1 승!");
			return 1;
		}
		else if (player2 == 3) {
			printf("\nplayer2 승!");
			return 1;
		}

		player1 = player2 = 0;
	}

	player1 = player2 = 0;

	// 대각선 승리 판단
	for (int i = 0; i < 3; i++) {
		if (board[i][i] == 'O') {
			player1++;
		}
		else if (board[i][i] == 'X') {
			player2++;
		}

		if (player1 == 3) {
			printf("\nplayer1 승!");
			return 1;
		}
		else if (player2 == 3) {
			printf("\nplayer2 승!");
			return 1;
		}
	}

	player1 = player2 = 0;

	// 역 대각선 승리 판단
	for (int i = 2; i >= 0; i--) {
		if (board[i][abs(i-2)] == 'O') {
			player1++;
		}
		else if (board[i][abs(i - 2)] == 'X') {
			player2++;
		}

		if (player1 == 3) {
			printf("\nplayer1 승!");
			return 0;
		}
		else if (player2 == 3) {
			printf("\nplayer2 승!");
			return 0;
		}
	}

	if (available == 0) {
		printf("\n 무승부 \n");

		return 1;
	}

	return 0;
}
