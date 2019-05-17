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
		printf("\n============= ��Ƽ�÷��� ��ȭ�� �¼� ���� �ý��� =============\n");
		printf(" - 1. ���� (�󿵰� ���� �� �¼� ����)\n");
		printf(" - 2. ��ȸ (�󿵰� ���� ��ȸ (�󿵰��� �� ��ȭ ����, ���� ��Ȳ))\n");
		printf(" - 3. ���� ��� (������ �����)\n");
		printf(" - 4. ������ (���α׷��� ������)\n");

		printf("\n�޴��� �������ּ���: ");
		scanf("%d", &menuIndex);

		switch (menuIndex) {
			case 1:
				availableTheaterNumber = 0; // �ʱ�ȭ
				for (int i = 0; i < THEATER_NUMBER; i++) {
					if (availableTheaterSeats[i] <= 0) {
						continue;
					}

					availableTheaterNumber++;
				}

				if (availableTheaterNumber == 0) {
					printf("\n���� ���� ������ �󿵰��� �����ϴ�.\n");
					continue;
				}

				// ���� �󿵰� �������� ��Ȳ ���
				showTheaterStatus();

				printf("\n������ �󿵰��� �Է����ּ���. (1 ~ 5): ");
				scanf("%d", &theaterIndex);

				if (theaterIndex < 1 || theaterIndex > 5) {
					printf("������ �󿵰� ��ȣ�� �߸� �Է��߽��ϴ�.");

					continue;
				}

				showTheaterSeatStatus(theaterIndex);

				printf("\n������ �¼��� �Է����ּ���. : ");
				scanf("%d", &seatIndex);

				registerSeat(theaterIndex, seatIndex);

				continue;
			case 2:
				showTheaterStatus();

				continue;
			case 3:
				printf("\n���� ����� �󿵰��� �Է����ּ���. (1 ~ 5): ");
				scanf("%d", &theaterIndex);

				if (theaterIndex < 1 || theaterIndex > 5) {
					printf("������ �󿵰� ��ȣ�� �߸� �Է��߽��ϴ�.");

					continue;
				}

				// ���� ���� ��Ȳ ���
				showTheaterSeatStatus(theaterIndex);

				printf("\n��� �Ϸ��� ���� �¼��� �Է����ּ���. (�� �ڸ���): ");
				scanf("%d", &seatIndex);

				cancelSeat(theaterIndex, seatIndex);
				showTheaterSeatStatus(theaterIndex);

				continue;
			case 4:
				printf("\n���� ���α׷��� ����˴ϴ�.");

				return;
			default:
				printf("�߸��� �޴� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �������ּ���.\n");
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
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (isOccupied(theater, seat) == 1) {
		printf("\n�̹� ����� �ڸ��Դϴ�. �ٸ� �¼��� �������ּ���. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	printf("\n�ڵ��� ��ȣ�� �Է����ּ���. [010�� -�� ������ ���� 8�ڸ�]: ");
	scanf("%d", &handphone);

	theaterSeats[theater - 1][seat - 1] = 1;
	availableTheaterSeats[theater - 1]--;

	printf("\n������ �Ϸ�Ǿ����ϴ�. �����մϴ�.\n");

	return;
}

void cancelSeat(int theater, int seat) {
	if (0 >= seat || seat > theaterMaxSeats[theater - 1]) {
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (theaterSeats[theater - 1][seat - 1] == 0) {
		return;
	}

	theaterSeats[theater - 1][seat - 1] = 0;
	availableTheaterSeats[theater - 1]++;
}

void showTheaterStatus() {
	printf("\n���� ��ü ��ȭ�� ��Ȳ�Դϴ�.\n");

	for (int i = 0; i < THEATER_NUMBER; i++) {
		printf("======================================================\n");
		printf("\n%d - [%s] | ���� �¼� ��: %2d\n", i + 1, movieTitles[i], availableTheaterSeats[i]);
		printf("\n======================================================\n");
		showTheaterSeatStatus(i + 1);
	}
}

void showTheaterSeatStatus(int theater) {
	printf("\n%d�� ��ȭ�� �¼� ��Ȳ�Դϴ�. (0: �� �¼�, 1: ����� �¼�)\n", theater);
	printf("\n���� ����ִ� �� �¼� ����: %2d\n", availableTheaterSeats[theater - 1]);
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