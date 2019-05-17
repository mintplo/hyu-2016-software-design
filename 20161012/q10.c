#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int validate_date(int year, int month, int day);
int is_leap_year(int year);

int get_month_days(int year, int month);
int get_week_day(int year, int month, int day);

void print_month_calendar(int year, int month);

void main() {
	int year, month;

	printf("�ǽ����� 9��. #10: �޷� �����\n");

	printf("�⵵�� �Է��ϼ���: ");
	scanf("%d", &year);

	printf("\n���� �Է��ϼ���: ");
	scanf("%d", &month);

	print_month_calendar(year, month);
}

// ��, ���� �´� �޷��� ���
void print_month_calendar(int year, int month) {
	int week_day = 0;

	// Ÿ��Ʋ ���
	printf("\n==================================================================\n");
	printf("\t��\tȭ\t��\t��\t��\t��\t��");
	printf("\n==================================================================\n");

	// ��, ���� �´� �ϼ� ��ŭ �ݺ�
	for (int i = 1; i <= get_month_days(year, month); i++) {
		if (!validate_date(year, month, i)) {
			printf("\n�߸� �Է��� ��,��,�� �Դϴ�.");
			break;
		}

		week_day = get_week_day(year, month, i);

		// 1���� ��� ���Ͽ� �����ϴ��� Ȯ���ϰ� Ŀ���� ������.
		if (i == 1) {
			for (int j = 0; j < week_day; j++) {
				printf("\t");
			}
		}

		// ���� ���
		printf("\t%2d", i);

		// �Ͽ����� �������̱� ������ �ٹٲ�
		if (week_day == 6) {
			printf("\n");
		}
	}

	// �������� ���� �ٹٲ� �ѹ� ��
	printf("\n");
}

// ������ ��ȿ�� �˻�
int validate_date(int year, int month, int day) {
	if (year > 0) {
		return 1;
	}

	if (1 <= month && month <= 12) {
		return 1;
	}

	if (get_month_days(year, month) < 32) {
		return 1;
	}

	return 0;
}

// ���⿡ �ش��ϴ��� ���� ����
int is_leap_year(int year) {
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
		return 1;
	}

	return 0;
}

// ��, ���� �� �ϼ� ����
int get_month_days(int year, int month) {
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		// ����� ���õ� ��
		case 2:
			if (is_leap_year(year)) return 29;
			return 28;
		default:
			return 0;
	}
}

// Zeller �˰������� ��, ��, �Ͽ� �´� ���� ����
// ���� �˰��� (0 - ��, 1 - ��, 2 - ��, 3 - ȭ, 4 - ��, 5 - ��, 6 - ��)
// �������� week_day�� 0�� ������ �Ǵ� �Ͽ��Ϸ� ���� ������ 0�� �����Ϸ� �����ϵ��� �ϴ� ���� �߰�
int get_week_day(int year, int month, int day) {
	int m, q, h, k, j;

	if (month <= 2) {
		year--;
		month += 12;
	}

	m = month;
	q = day;
	k = year % 100;
	j = year / 100;

	h = (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;

	if (h <= 1) {
		return h + 5;
	}

	return h - 2;
}