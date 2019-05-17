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

	printf("실습문제 9장. #10: 달력 만들기\n");

	printf("년도를 입력하세요: ");
	scanf("%d", &year);

	printf("\n월을 입력하세요: ");
	scanf("%d", &month);

	print_month_calendar(year, month);
}

// 년, 월에 맞는 달력을 출력
void print_month_calendar(int year, int month) {
	int week_day = 0;

	// 타이틀 출력
	printf("\n==================================================================\n");
	printf("\t월\t화\t수\t목\t금\t토\t일");
	printf("\n==================================================================\n");

	// 년, 월에 맞는 일수 만큼 반복
	for (int i = 1; i <= get_month_days(year, month); i++) {
		if (!validate_date(year, month, i)) {
			printf("\n잘못 입력한 연,월,일 입니다.");
			break;
		}

		week_day = get_week_day(year, month, i);

		// 1일이 어디 요일에 가야하는지 확인하고 커서를 보낸다.
		if (i == 1) {
			for (int j = 0; j < week_day; j++) {
				printf("\t");
			}
		}

		// 요일 출력
		printf("\t%2d", i);

		// 일요일이 마지막이기 때문에 줄바꿈
		if (week_day == 6) {
			printf("\n");
		}
	}

	// 가독성을 위해 줄바꿈 한번 더
	printf("\n");
}

// 연월일 유효성 검사
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

// 윤년에 해당하는지 여부 리턴
int is_leap_year(int year) {
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
		return 1;
	}

	return 0;
}

// 년, 월의 총 일수 리턴
int get_month_days(int year, int month) {
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		// 윤년과 관련된 월
		case 2:
			if (is_leap_year(year)) return 29;
			return 28;
		default:
			return 0;
	}
}

// Zeller 알고리즘으로 년, 월, 일에 맞는 요일 리턴
// 기존 알고리즘 (0 - 토, 1 - 일, 2 - 월, 3 - 화, 4 - 수, 5 - 목, 6 - 금)
// 범용적인 week_day는 0을 월요일 또는 일요일로 쓰기 때문에 0을 월요일로 간주하도록 하는 로직 추가
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