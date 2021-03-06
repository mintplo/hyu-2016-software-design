#define _CRT_SECURE_NO_WARNINGS
#define SEAT_SIZE_PER_THEATER 20
#define THEATER_NUMBER 5
#include <stdio.h>

const int theaterMaxSeats[THEATER_NUMBER] = { SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER };
int theaterSeats[SEAT_SIZE_PER_THEATER][SEAT_SIZE_PER_THEATER] = { 0 };
int availableTheaterSeats[THEATER_NUMBER] = { SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER };

char movieTitles[THEATER_NUMBER][40];

int isOccupied(int theater, int seat);
void registerSeat(int theater, int seat);
void cancelSeat(int theater, int seat);
void showTheaterStatus();
void showTheaterSeatStatus(int theater);

void main() {
	int availableTheaterNumber = 0;
	int seatIndex = 0;
	int theaterIndex = 0;
	int menuIndex = 0;

	sprintf(movieTitles[0], "%s", "Spider Man");
	sprintf(movieTitles[1], "%s", "Martian");
	sprintf(movieTitles[2], "%s", "X Man");
	sprintf(movieTitles[3], "%s", "Taken");
	sprintf(movieTitles[4], "%s", "Marvel");

	while (1) {
		printf("\n============= 멀티플렉스 영화관 좌석 예약 시스템 =============\n");
		printf(" - 1. 예약 (상영관 선택 및 좌석 예약)\n");
		printf(" - 2. 조회 (상영관 상태 조회 (상영관별 상영 영화 제목, 예약 상황))\n");
		printf(" - 3. 예약 취소 (예약을 취소함)\n");
		printf(" - 4. 끝내기 (프로그램을 종료함)\n");

		printf("\n메뉴를 선택해주세요: ");
		scanf("%d", &menuIndex);

		switch (menuIndex) {
			case 1:
				availableTheaterNumber = 0; // 초기화
				for (int i = 0; i < THEATER_NUMBER; i++) {
					if (availableTheaterSeats[i] <= 0) {
						continue;
					}

					availableTheaterNumber++;
				}

				if (availableTheaterNumber == 0) {
					printf("\n현재 예약 가능한 상영관이 없습니다.\n");
					continue;
				}

				// 현재 상영관 개략적인 상황 출력
				showTheaterStatus();

				printf("\n예약할 상영관을 입력해주세요. (1 ~ 5): ");
				scanf("%d", &theaterIndex);

				if (theaterIndex < 1 || theaterIndex > 5) {
					printf("예약할 상영관 번호를 잘못 입력했습니다.");

					continue;
				}

				showTheaterSeatStatus(theaterIndex);

				printf("\n예약할 좌석을 입력해주세요. : ");
				scanf("%d", &seatIndex);

				registerSeat(theaterIndex, seatIndex);

				continue;
			case 2:
				showTheaterStatus();

				continue;
			case 3:
				printf("\n예약 취소할 상영관을 입력해주세요. (1 ~ 5): ");
				scanf("%d", &theaterIndex);

				if (theaterIndex < 1 || theaterIndex > 5) {
					printf("예약할 상영관 번호를 잘못 입력했습니다.");

					continue;
				}

				// 현재 예약 상황 출력
				showTheaterSeatStatus(theaterIndex);

				printf("\n취소 하려는 예약 좌석을 입력해주세요. (한 자리만): ");
				scanf("%d", &seatIndex);

				cancelSeat(theaterIndex, seatIndex);
				showTheaterSeatStatus(theaterIndex);

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

int isOccupied(int theater, int seat) {
	return (theaterSeats[theater - 1][seat - 1] == 1);
}

void registerSeat(int theater, int seat) {
	int handphone;

	if (0 >= seat || seat > theaterMaxSeats[theater - 1]) {
		printf("\n잘못된 좌석 번호입니다. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	if (isOccupied(theater, seat) == 1) {
		printf("\n이미 예약된 자리입니다. 다른 좌석을 선택해주세요. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	printf("\n핸드폰 번호를 입력해주세요. [010과 -를 제외한 숫자 8자리]: ");
	scanf("%d", &handphone);

	theaterSeats[theater - 1][seat - 1] = 1;
	availableTheaterSeats[theater - 1]--;

	printf("\n예약이 완료되었습니다. 감사합니다.\n");

	return;
}

void cancelSeat(int theater, int seat) {
	if (0 >= seat || seat > theaterMaxSeats[theater - 1]) {
		printf("\n잘못된 좌석 번호입니다. \n기본 화면으로 돌아갑니다....\n");

		return;
	}

	if (theaterSeats[theater - 1][seat - 1] == 0) {
		return;
	}

	theaterSeats[theater - 1][seat - 1] = 0;
	availableTheaterSeats[theater - 1]++;
}

void showTheaterStatus() {
	printf("\n현재 전체 영화관 상황입니다.\n");

	for (int i = 0; i < THEATER_NUMBER; i++) {
		printf("======================================================\n");
		printf("\n%d - [%s] | 남은 좌석 수: %2d\n", i + 1, movieTitles[i], availableTheaterSeats[i]);
		printf("\n======================================================\n");
		showTheaterSeatStatus(i + 1);
	}
}

void showTheaterSeatStatus(int theater) {
	printf("\n%d번 영화관 좌석 상황입니다. (0: 빈 좌석, 1: 예약된 좌석)\n", theater);
	printf("\n현재 비어있는 총 좌석 개수: %2d\n", availableTheaterSeats[theater - 1]);
	printf("============================================================================================================\n");

	for (int i = 0; i < theaterMaxSeats[theater - 1]; i++) {
		printf("| %2d | ", i + 1);
	}

	printf("\n============================================================================================================\n");
	for (int i = 0; i < theaterMaxSeats[theater - 1]; i++) {
		printf("| %2d | ", theaterSeats[theater - 1][i]);
	}
	printf("\n============================================================================================================\n");

	printf("\n");
}