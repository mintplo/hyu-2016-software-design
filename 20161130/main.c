#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode *link;
} ListNode;

typedef struct ListHeader {
	int length;
	ListNode *head; // 다항식의 첫 번째 항을 가리킴
	ListNode *tail; // 사용하지 않음
} ListHeader;

void error(char *str) {
	printf("%s\n", str);
	exit(0);
}

// 초기화 함수
void init(ListHeader *plist)
{
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수, 
// expon는 지수
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

	// 연결 리스트의 초기화 	
	init(&list1);
	init(&list2);
	init(&list3);
	// 다항식 1을 생성 
	insert_node_last(&list1, 3, 12);
	insert_node_last(&list1, 2, 8);
	insert_node_last(&list1, 1, 0);
	// 다항식 2를 생성 
	insert_node_last(&list2, 8, 12);
	insert_node_last(&list2, -3, 10);
	insert_node_last(&list2, 10, 6);
	// 다항식 3 = 다항식 1 + 다항식 2
	poly_add(&list1, &list2, &list3);
	poly_print(&list3);
}
