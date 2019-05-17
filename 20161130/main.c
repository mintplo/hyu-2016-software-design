#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode *link;
} ListNode;

typedef struct ListHeader {
	int length;
	ListNode *head; // ���׽��� ù ��° ���� ����Ŵ
	ListNode *tail; // ������� ����
} ListHeader;

void error(char *str) {
	printf("%s\n", str);
	exit(0);
}

// �ʱ�ȭ �Լ�
void init(ListHeader *plist)
{
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

// plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, 
// expon�� ����
void insert_node_last(ListHeader *plist, int coef, int expon)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->coef = coef;
	node->expon = expon;
	node->link = NULL;

	plist->length += 1;
	if (plist->head == NULL) {
		plist->head = node;
		return;
	}

	ListNode* node_temp = plist->head;

	while (node_temp != NULL) {
		if (node_temp->link == NULL) {
			break;
		}

		node_temp = node_temp->link;
	}

	node_temp->link = node;
}

// list3 = list1 + list2
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)
{
	ListNode* plist1_node = plist1->head;
	ListNode* plist2_node = plist2->head;

	while (plist1_node != NULL && plist2_node != NULL) {
		if (plist1_node->expon == plist2_node->expon) {
			int coef = plist1_node->coef + plist2_node->coef;
			insert_node_last(plist3, coef, plist1_node->expon);
			plist1_node = plist1_node->link;
			plist2_node = plist2_node->link;
		}
		else if (plist1_node->expon > plist2_node->expon) {
			insert_node_last(plist3, plist1_node->coef, plist1_node->expon);
			plist1_node = plist1_node->link;
		}
		else {
			insert_node_last(plist3, plist2_node->coef, plist2_node->expon);
			plist2_node = plist2_node->link;
		}
	}

	ListNode* pnode = (plist1_node == NULL) ? plist2_node : plist1_node;
	while (pnode != NULL) {
		insert_node_last(plist3, pnode->coef, pnode->expon);
		pnode = pnode->link;
	}
}

//
void poly_print(ListHeader *plist)
{
	ListNode *p = plist->head;
	for (; p; p = p->link) {
		printf("%d %d\n", p->coef, p->expon);
	}
}

//
void main()
{
	ListHeader list1, list2, list3;

	// ���� ����Ʈ�� �ʱ�ȭ 	
	init(&list1);
	init(&list2);
	init(&list3);
	// ���׽� 1�� ���� 
	insert_node_last(&list1, 3, 12);
	insert_node_last(&list1, 2, 8);
	insert_node_last(&list1, 1, 0);
	// ���׽� 2�� ���� 
	insert_node_last(&list2, 8, 12);
	insert_node_last(&list2, -3, 10);
	insert_node_last(&list2, 10, 6);
	// ���׽� 3 = ���׽� 1 + ���׽� 2
	poly_add(&list1, &list2, &list3);
	poly_print(&list3);
}
