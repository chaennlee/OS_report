#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Element; // 정수형 sorting data를 생성한다.
typedef struct tListNode { // 연결된 list node를 나타내는 tListNode 구조체를
						   // 생성
	Element data;			// data
	struct tListNode *next; // 다음 노드를 가리키는 포인터
} ListNode;

typedef struct {	// list 구초제를 생성
	int count;		// element 개수
	ListNode *head; // Queue의 front와 비슷한 개념
	ListNode *pos;  // Queue의 rear와 비슷한 개념
} List;

List *createList() {
	List *pNewList =
		(List *)malloc(sizeof(List)); // 동적할당을 통해 list를 선언한다.
	if (pNewList == NULL) // 줄 메모리가 없을 경우, 즉 공간이 없을 경우
		return NULL;	   // return한다.
	pNewList->count = 0;   // 초깃값을 설정한다. element 개수는 0개
	pNewList->head = NULL; // 포인터 값들도 NULL 값으로 둔다.
	pNewList->pos = NULL;
	return pNewList; // 초기 값이 설정된 list를 반환한다.
}

void _insertList(
	List *pList,
	ListNode *pPre,
	Element data) // List sorting까지 같이 구현
{
	ListNode *pNewNode =
		(ListNode *)malloc(sizeof(ListNode)); // listnode 구조체를 동적할당한다.
	pNewNode->data = data; // int형이므로, = 을 사용하여 data를 구조체의 data
						   // 변수에 복사한다.
	if (pPre == NULL) { // insert before head node, 이 전 node가 NULL값일 경우
		pNewNode->next = pList->head; // 현재 노드의 앞부분을 new node->next에,
		pList->head = pNewNode; // new node를 현재 노드의 head에 복사한다.
	} else {					// pPre가 NULL이 아닌 경우
		pNewNode->next = pPre->next; // 이전 노드 값이 존재한다는 의미이므로
									 // pPre->next를 new node-> next에 복사한다.
		pPre->next = pNewNode; // 마찬가지로 pPre->next에 pNewNode를 복사한다.
	}
	pList->count++; // insert 하였으므로 count는 1 증가한다.
}

bool _searchList(
	List *pList,
	ListNode **ppPre,
	ListNode **ppLoc,
	Element data) {
	for (*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc,
		*ppLoc = (*ppLoc)->next) { // for문을 돌려서 List 전체를 한 번 훑는다.
		if ((*ppLoc)->data == data)		// data was found
			return true;				// true를 반환한다.
		else if ((*ppLoc)->data > data) // data was not found and 한 바퀴 다
										// 돌았으면
			break;						// for문을 종료
	}
	return false; // return true를 실패한 경우, return false한다. (해당 data가
				  // 없다는 의미)
}

void addList(List *pList, Element data) {
	ListNode *pPre = NULL, *pLoc = NULL; // 초깃값 설정
	bool found = _searchList(
		pList, &pPre, &pLoc, data); // sorting이 제대로 이뤄지게 하기 위해서,
									// 이미 있는 data를 또 입력한다면
	if (!found) {						// 동작되지 않는다.
		_insertList(pList, pPre, data); // 새로운 값일 경우에만 insert된다.
	}
}

Element SearchList(
	List *pList,
	Element data) { // c언어에서는 true, false를 편리하게 사용할 수 없다.
	ListNode *pPre = NULL, *pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);
	if (!found)
		return 1; // 따라서 search가 실패했을 경우, no를 뜻하는 1을 반환하고
	else
		return 0; // search가 성공했을 경우, yes를 뜻하는 0을 반환한다.
}

void _deleteList(
	List *pList,
	ListNode *pPre,
	ListNode *pLoc) // linked된 list이므로, remove 후에도 linking 시켜줘야 한다.
					// 그래서 필요한 함수이다.
{
	if (pPre == NULL)
		pList->head = pLoc->next;
	else
		pPre->next = pLoc->next;
	free(pLoc);		// 동적할당을 하였으므로 free를 선언한다.
	pList->count--; // delete list를 수행하였으므로 count 값을 1 뺀다.
}

void removeList(List *pList, Element data) {
	ListNode *pPre = NULL, *pLoc = NULL;
	bool found = _searchList(
		pList,
		&pPre,
		&pLoc,
		data); // remove 전에 해당 data가 있는지 search한다.
	if (found) {
		_deleteList(pList, pPre, pLoc);
		printf("%d kg of duck will be removed !!\n", data);
	} else {
		printf("My List does not have %d kg of duck.\n", data);
	}
}

void ListTraverse(List *pList) // 현재 노드 출력 함수
{
	ListNode *pTraverse = NULL, *pNext = NULL;
	printf("\nWeight list of Ducks : ");
	for (pTraverse = pList->head; pTraverse != NULL; pTraverse = pNext) {
		pNext = pTraverse->next;
		printf(
			"%d ",
			pTraverse->data); // for문을 사용하여 list를 한 바퀴 다 돌고, 다
							  // 도는 과정에서 data를 하나씩 print한다. 수월하게
							  // 현재 노드 출력을 수행할 함수이다.
	}
	printf("\n\n");
}

void destroyList(List *pList) // list 제거 함수
{
	ListNode *pDel = NULL, *pNext = NULL;
	for (pDel = pList->head; pDel != NULL; pDel = pNext) {
		pNext = pDel->next;
		free(pDel); // for문을 돌려 꼼꼼하게 pDel을 free 선언한다.
	}
	free(pList); // 최종적으로 pList를 free 선언한다.
}

