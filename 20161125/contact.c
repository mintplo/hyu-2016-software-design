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

// �Է� ���۸� �����ִ� ��ƿ��Ƽ �Լ� ����
void flush_stdin();

// �ּҷ� ���α׷� ���� �Լ� ����
void print_menu();

void print_person(PERSON person);
void add_person(FILE *fp);
void search_person(FILE *fp);
int find_person(FILE *fp, char* name, PERSON* person);
void update_person(FILE *fp);

void main(void) {
	FILE *fp;
	int select;

	// ���� �� �ּҷ��� �����ϴ� ������ ���� ����
	if ((fp = fopen("./address.dat", "a+")) == NULL) {
		fprintf(stderr, "������ �� �� �����ϴ�.");
		return;
	}

	while (1) {
		print_menu();

		printf("�޴��� �����ϼ���: ");
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

	// ������ ��Ʈ�� �ݱ�
	fclose(fp);
	return;
}

void flush_stdin() {
	char c;

	while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu() {
	printf("\n==============\n");
	printf("1. �߰�\n2. ����\n3. �˻�\n4. ����");
	printf("\n==============\n");
}

void print_person(PERSON person) {
	printf("\n==============\n");
	printf("�̸�: %s\n�ּ�: %s\n�ڵ��� ��ȣ: %s\n����: %s", person.name, person.address, person.phone, person.desc);
	printf("\n==============\n");
}

void add_person(FILE* fp) {
	PERSON person;

	flush_stdin();

	printf("\n[�ּҷ� �߰�]==============\n");

	// gets�� ���� �����÷ο츦 �߻���ų ������ �־� fgets�� ����϶�� ��.
	// http://stackoverflow.com/questions/1694036/why-is-the-gets-function-so-dangerous-that-it-should-not-be-used
	printf("�̸�: ");
	fgets(person.name, sizeof(person.name), stdin);

	printf("�ּ�: ");
	fgets(person.address, sizeof(person.address), stdin);

	printf("�ڵ��� ��ȣ: ");
	fgets(person.phone, sizeof(person.phone), stdin);

	printf("����: ");
	fgets(person.desc, sizeof(person.desc), stdin);

	// ������ �ٿ� �߰��ϱ� ���� Ŀ�� �̵�
	fseek(fp, 0, SEEK_END);
	fwrite(&person, sizeof(person), 1, fp);
}

void search_person(FILE* fp) {
	char name[MAX_LENGTH];
	PERSON person;

	fseek(fp, 0L, SEEK_SET);
	flush_stdin();

	printf("\n[�ּҷ� �˻�]==============\n");

	printf("�˻��� �̸�: ");
	fgets(name, sizeof(name), stdin);

	if (find_person(fp, name, &person) != -1) {
		print_person(person);

		return;
	}

	printf("\n�ش� �̸��� ���� ����� �ּҷϿ� �����ϴ�.");
}

// ���� �ڵ带 ���̱� ����
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

	printf("\n[�ּҷ� ����]==============\n");

	printf("������ ����� �̸�: ");
	fgets(name, sizeof(name), stdin);

	if (find_person(fp, name, &person) == -1) {
		printf("\n�ش� �̸��� ���� ����� �ּҷϿ� �����ϴ�.");

		return;
	}

	printf("�̸�: ");
	fgets(person.name, sizeof(person.name), stdin);

	printf("�ּ�: ");
	fgets(person.address, sizeof(person.address), stdin);

	printf("�ڵ��� ��ȣ: ");
	fgets(person.phone, sizeof(person.phone), stdin);

	printf("����: ");
	fgets(person.desc, sizeof(person.desc), stdin);

	fseek(fp, -(long)(sizeof((person))), SEEK_CUR);
	fwrite(&person, sizeof((person)), 1, fp);
}