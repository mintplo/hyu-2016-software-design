#define _CRT_SECURE_NO_WARNINGS
#define SEAT_SIZE 10
#include <stdio.h>

int availableSeats = SEAT_SIZE;
int seats[SEAT_SIZE] = { 0 };

int isOccupied(int seat);
void registerSeat(int seat);
void cancelSeat(int seat);
void showSeatStatus();

void main() {
	int seatIndex = 0;
	int menuIndex = 0;

	while (1) {
		printf("\n============= 영화관 좌석 예약 시스템 =============\n");
		printf(" - 1. 예약 (좌석예약)\n");
		printf(" - 2. 조회 (좌석 예약 상황 출력)\n");
		printf(" - 3. 예약 취소 (예약을 취소함)\n");
		printf(" - 4. 끝내기 (프로그램을 종료함)\n");

		printf("\n메뉴를 선택해주세요: ");
		scanf("%d", &menuIndex);

		switch (menuIndex) {
			case 1:
				if (availableSeats <= 0) {
					printf("\n현재 예약 가능한 좌석이 없습니다.\n");
					continue;
				}

				// 현재 예약 상황 출력
				showSeatStatus();

				printf("\n예약 좌석을 입력해주세요. (한 자리만): ");
				scanf("%d", &seatIndex);

				registerSeat(seatIndex);

				continue;
			case 2:
				showSeatStatus();

				continue;
			case 3:
				// 현재 예약 상황 출력
				showSeatStatus();

				printf("\n취소 하려는 예약 좌석을 입력해주세요. (한 자리만): ");
				scanf("%d", &seatIndex);

				cancelSeat(seatIndex);
				showSeatStatus();

				continue;
			case 4:
				printf("\n예약 프로그램이 종료됩니다.");

				return;
			default:
				printf("잘못된 메뉴 번호를 입력하셨습니다. 다시 선택해주세요.\n");
				continue;
		}
	}
}

int isOccupied(int seat) {
	return (seats[seat - 1] == 1);
}

void registerSeat(int seat) {
	int handphone;

	if (0 >= seat || seat > SEAT_SIZE) {
		printf("\n잘못된 좌석 번호입니다. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	if (isOccupied(seat) == 1) {
		printf("\n이미 예약된 자리입니다. 다른 좌석을 선택해주세요. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	printf("\n핸드폰 번호를 입력해주세요. [010과 -를 제외한 숫자 8자리]: ");
	scanf("%d", &handphone);

	seats[seat - 1] = 1;
	availableSeats--;

	printf("\n예약이 완료되었습니다. 감사합니다.\n");

	return;
}

void cancelSeat(int seat) {
	if (0 >= seat || seat > SEAT_SIZE) {
		printf("\n잘못된 좌석 번호입니다. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	if (seats[seat - 1] == 0) {
		return;
	}

	seats[seat - 1] = 0;
	availableSeats++;
}

void showSeatStatus() {
	printf("\n현재 좌석 상황입니다. (0: 빈 좌석, 1: 예약된 좌석)\n");
	printf("\n현재 비어있는 총 좌석 개수: %2d\n", availableSeats);
	printf("======================================================\n");

	for (int i = 0; i < SEAT_SIZE; i++) {
		printf("| %2d |\t", i + 1);
	}

	printf("\n======================================================\n");
	for (int i = 0; i < SEAT_SIZE; i++) {
		printf("| %2d |\t", seats[i]);
	}

	printf("\n");
}