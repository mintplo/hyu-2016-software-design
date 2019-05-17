#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	char name[MAX_LENGTH];
	char address[MAX_LENGTH];
	char phone[MAX_LENGTH];
	char desc[MAX_LENGTH];
} typedef PERSON;

// 입력 버퍼를 날려주는 유틸리티 함수 원형
void flush_stdin();

// 주소록 프로그램 관련 함수 원형
void print_menu();

void print_person(PERSON person);
void add_person(FILE *fp);
void search_person(FILE *fp);
int find_person(FILE *fp, char* name, PERSON* person);
void update_person(FILE *fp);

void main(void) {
	FILE *fp;
	int select;

	// 시작 전 주소록을 저장하는 데이터 파일 열기
	if ((fp = fopen("./address.dat", "a+")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.");
		return;
	}

	while (1) {
		print_menu();

		printf("메뉴를 선택하세요: ");
		scanf("%d", &select);

		switch (select) {
			case 1:
				add_person(fp);
				break;
			case 2:
				update_person(fp);
				break;
			case 3:
				search_person(fp);
				break;
			case 4:
				return;
			default: break;
		}
	}

	// 종료전 스트림 닫기
	fclose(fp);
	return;
}

void flush_stdin() {
	char c;

	while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu() {
	printf("\n==============\n");
	printf("1. 추가\n2. 수정\n3. 검색\n4. 종료");
	printf("\n==============\n");
}

void print_person(PERSON person) {
	printf("\n==============\n");
	printf("이름: %s\n주소: %s\n핸드폰 번호: %s\n설명: %s", person.name, person.address, person.phone, person.desc);
	printf("\n==============\n");
}

void add_person(FILE* fp) {
	PERSON person;

	flush_stdin();

	printf("\n[주소록 추가]==============\n");

	// gets는 버퍼 오버플로우를 발생시킬 위험이 있어 fgets를 사용하라고 함.
	// http://stackoverflow.com/questions/1694036/why-is-the-gets-function-so-dangerous-that-it-should-not-be-used
	printf("이름: ");
	fgets(person.name, sizeof(person.name), stdin);

	printf("주소: ");
	fgets(person.address, sizeof(person.address), stdin);

	printf("핸드폰 번호: ");
	fgets(person.phone, sizeof(person.phone), stdin);

	printf("설명: ");
	fgets(person.desc, sizeof(person.desc), stdin);

	// 마지막 줄에 추가하기 위해 커서 이동
	fseek(fp, 0, SEEK_END);
	fwrite(&person, sizeof(person), 1, fp);
}

void search_person(FILE* fp) {
	char name[MAX_LENGTH];
	PERSON person;

	fseek(fp, 0L, SEEK_SET);
	flush_stdin();

	printf("\n[주소록 검색]==============\n");

	printf("검색할 이름: ");
	fgets(name, sizeof(name), stdin);

	if (find_person(fp, name, &person) != -1) {
		print_person(person);

		return;
	}

	printf("\n해당 이름을 가진 사람이 주소록에 없습니다.");
}

// 재사용 코드를 줄이기 위해
int find_person(FILE* fp, char* name, PERSON* person) {
	while (!feof(fp)) {
		fread(person, sizeof(PERSON), 1, fp);
		if (strcmp(person->name, name) == 0) {
			return 1;
		}
	}

	return -1;
}

void update_person(FILE* fp) {
	char name[MAX_LENGTH];
	PERSON person;

	fseek(fp, 0L, SEEK_SET);
	flush_stdin();

	printf("\n[주소록 수정]==============\n");

	printf("수정할 사람의 이름: ");
	fgets(name, sizeof(name), stdin);

	if (find_person(fp, name, &person) == -1) {
		printf("\n해당 이름을 가진 사람이 주소록에 없습니다.");

		return;
	}

	printf("이름: ");
	fgets(person.name, sizeof(person.name), stdin);

	printf("주소: ");
	fgets(person.address, sizeof(person.address), stdin);

	printf("핸드폰 번호: ");
	fgets(person.phone, sizeof(person.phone), stdin);

	printf("설명: ");
	fgets(person.desc, sizeof(person.desc), stdin);

	fseek(fp, -(long)(sizeof((person))), SEEK_CUR);
	fwrite(&person, sizeof((person)), 1, fp);
}