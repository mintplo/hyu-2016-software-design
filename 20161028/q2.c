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
		printf("\n============= ��ȭ�� �¼� ���� �ý��� =============\n");
		printf(" - 1. ���� (�¼�����)\n");
		printf(" - 2. ��ȸ (�¼� ���� ��Ȳ ���)\n");
		printf(" - 3. ���� ��� (������ �����)\n");
		printf(" - 4. ������ (���α׷��� ������)\n");

		printf("\n�޴��� �������ּ���: ");
		scanf("%d", &menuIndex);

		switch (menuIndex) {
			case 1:
				if (availableSeats <= 0) {
					printf("\n���� ���� ������ �¼��� �����ϴ�.\n");
					continue;
				}

				// ���� ���� ��Ȳ ���
				showSeatStatus();

				printf("\n���� �¼��� �Է����ּ���. (�� �ڸ���): ");
				scanf("%d", &seatIndex);

				registerSeat(seatIndex);

				continue;
			case 2:
				showSeatStatus();

				continue;
			case 3:
				// ���� ���� ��Ȳ ���
				showSeatStatus();

				printf("\n��� �Ϸ��� ���� �¼��� �Է����ּ���. (�� �ڸ���): ");
				scanf("%d", &seatIndex);

				cancelSeat(seatIndex);
				showSeatStatus();

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

int isOccupied(int seat) {
	return (seats[seat - 1] == 1);
}

void registerSeat(int seat) {
	int handphone;

	if (0 >= seat || seat > SEAT_SIZE) {
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (isOccupied(seat) == 1) {
		printf("\n�̹� ����� �ڸ��Դϴ�. �ٸ� �¼��� �������ּ���. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	printf("\n�ڵ��� ��ȣ�� �Է����ּ���. [010�� -�� ������ ���� 8�ڸ�]: ");
	scanf("%d", &handphone);

	seats[seat - 1] = 1;
	availableSeats--;

	printf("\n������ �Ϸ�Ǿ����ϴ�. �����մϴ�.\n");

	return;
}

void cancelSeat(int seat) {
	if (0 >= seat || seat > SEAT_SIZE) {
		printf("\n�߸��� �¼� ��ȣ�Դϴ�. \n�⺻ ȭ������ ���ư��ϴ�....\n");

		return;
	}

	if (seats[seat - 1] == 0) {
		return;
	}

	seats[seat - 1] = 0;
	availableSeats++;
}

void showSeatStatus() {
	printf("\n���� �¼� ��Ȳ�Դϴ�. (0: �� �¼�, 1: ����� �¼�)\n");
	printf("\n���� ����ִ� �� �¼� ����: %2d\n", availableSeats);
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