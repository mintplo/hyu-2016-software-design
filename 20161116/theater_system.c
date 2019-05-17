#define _CRT_SECURE_NO_WARNINGS
#define SEAT_SIZE_PER_THEATER 20
#define THEATER_NUMBER 5
#include <stdio.h>

struct Theater {
	char title[40];
	int seats[SEAT_SIZE_PER_THEATER];
	int availableSeats;
	int maxSeat;
} typedef theater;

theater theaters[] = {
	{ "", { 0, }, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER },
	{ "", { 0, }, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER },
	{ "", { 0, }, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER },
	{ "", { 0, }, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER },
	{ "", { 0, }, SEAT_SIZE_PER_THEATER, SEAT_SIZE_PER_THEATER }
};

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

	sprintf(theaters[0].title, "Spider Man");
	sprintf(theaters[1].title, "Martian");
	sprintf(theaters[2].title, "Taken");
	sprintf(theaters[3].title, "X - Man");
	sprintf(theaters[4].title, "Marvel");

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
				if (theaters[i].availableSeats <= 0) {
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
	return (theaters[theater - 1].seats[seat - 1] == 1);
}

void registerSeat(int theater, int seat) {
	int handphone;

	if (0 >= seat || seat > theaters[theater - 1].maxSeat) {
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (isOccupied(theater, seat) == 1) {
		printf("\n�̹� ����� �ڸ��Դϴ�. �ٸ� �¼��� �������ּ���. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	printf("\n�ڵ��� ��ȣ�� �Է����ּ���. [010�� -�� ������ ���� 8�ڸ�]: ");
	scanf("%d", &handphone);

	theaters[theater - 1].seats[seat - 1] = 1;
	theaters[theater - 1].availableSeats--;

	printf("\n������ �Ϸ�Ǿ����ϴ�. �����մϴ�.\n");

	return;
}

void cancelSeat(int theater, int seat) {
	if (0 >= seat || seat > theaters[theater - 1].maxSeat) {
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (theaters[theater - 1].seats[seat - 1] == 0) {
		return;
	}

	theaters[theater - 1].seats[seat - 1] = 0;
	theaters[theater - 1].availableSeats++;
}

void showTheaterStatus() {
	printf("\n���� ��ü ��ȭ�� ��Ȳ�Դϴ�.\n");

	for (int i = 0; i < THEATER_NUMBER; i++) {
		printf("======================================================\n");
		printf("\n%d - [%s] | ���� �¼� ��: %2d\n", i + 1, theaters[i].title, theaters[i].availableSeats);
		printf("\n======================================================\n");
		showTheaterSeatStatus(i + 1);
	}
}

void showTheaterSeatStatus(int theater) {
	printf("\n%d�� ��ȭ�� �¼� ��Ȳ�Դϴ�. (0: �� �¼�, 1: ����� �¼�)\n", theater);
	printf("\n���� ����ִ� �� �¼� ����: %2d\n", theaters[theater - 1].availableSeats);
	printf("============================================================================================================\n");

	for (int i = 0; i < theaters[theater - 1].maxSeat; i++) {
		printf("| %2d | ", i + 1);
	}

	printf("\n============================================================================================================\n");
	for (int i = 0; i < theaters[theater - 1].maxSeat; i++) {
		printf("| %2d | ", theaters[theater - 1].seats[i]);
	}
	printf("\n============================================================================================================\n");

	printf("\n");
}