#include <stdbool.h> // 표준 라이브러리 헤더 4개 사용.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Element; // 유연한 사용 목적. 다른 자료형 Queue가 필요하다면 이
					  // 줄만 수정하면 된다.
typedef struct tQueueNode { // linked list 노드로 정의.
	Element queue[50];
	struct tQueueNode *next;
} QueueNode;

typedef struct { // 큐의 원소 개수를 나타내는 count, 큐의 front 및 rear 노드에
				 // 대한 포인터 포함.
	int count;
	QueueNode *front, *rear; // 각각의 변수에 대한 설명은 보고서를 참고.
} Queue;

Queue *
CreateQueue(int size) { // 새로운 Queue를 만들고, queue의 포인터를 반환한다.
	Queue *pNewQueue =
		(Queue *)malloc(sizeof(Queue)); // malloc으로 동적 할당하자.
	if (pNewQueue == NULL)				// 줄 메모리가 없다는 의미.
		return NULL; // 그런 경우, 공간이 없으므로 return한다.
	pNewQueue->count = 0; // Create 단계에선 들어온 element가 없으므로 count = 0
	pNewQueue->front = pNewQueue->rear =
		NULL;		  // 포인터 값들도 NULL 값으로 둔다.
	return pNewQueue; // 초기값이 설정된 queue를 반환한다.
}

bool IsEmptyQueue(
	Queue *q) { // Queue가 비어 있는지 확인한다. 비어있으면 true, 아니면 false.
	if (q->count <=
		0) // count <=0 이면, Queue가 비어 있다는 의미이므로 true 반환.
		return true; // stdbool.h를 include했으므로 c언어에서도 true, false 사용
					 // 가능.
	else
		return false; // count>0이면, Queue 안에 element가 최소 한 개 있다는
					  // 의미이므로 false 반환.
}

void Enqueue(
	Queue *pQueue,
	Element *item) { // Queue의 끝에 원소 item을 추가한다.
	QueueNode *pNewNode =
		(QueueNode *)malloc(sizeof(QueueNode)); // malloc으로 동적 할당하자.
	if (pNewNode ==
		NULL) // malloc을 사용할 때, 메모리를 못줄 때는 NULL값을 준다.
		return; // 그런 경우, 공간이 없으므로 return한다.
	strcpy(
		pNewNode->queue,
		item); // 현재 자료형이 char형이므로, strcpy로 문자열을 복사한다.
	pNewNode->next = NULL;
	if (pQueue->count <= 0) { // 맨 처음 enqueue하는 경우
		pQueue->front = pQueue->rear =
			pNewNode; // 하나의 Queue struct만 존재하므로 front와 rear가 같은
					  // 값을 가진다.
	} else { // 이미 enqueue된 요소가 있는 경우
		pQueue->rear->next = pNewNode; // linking해준다.
		pQueue->rear =
			pNewNode; // 더 뒤에 들어온 요소가 생겼으므로 rear값도 수정해준다.
	}
	pQueue->count++; // 하나의 값이 enqueue되었으므로 count +1을 해준다.
}

Element item[100] = {
	0}; // dequeue 함수에서 return해주기 위해 전역 변수로 선언한다.

Element *Dequeue(Queue *pQueue) { // Queue에서 첫 번째 원소를 제거하고 반환한다.
	QueueNode *pFront =
		NULL; // pFront라는 QueueNode를 정의한다. NULL값으로 생성한다.
	if (pQueue->count <= 0) // 반환할 요소가 없으므로
		return 0;			// 그대로 return한다.
	pFront = pQueue->front; // Queue의 front 덩어리 전체를 pFront로 받는다.
	strcpy(
		item,
		pFront->queue); // pFront->queue, 즉 제거할 요소의 value를 item이라는
						// 변수에 복사해준다. (char형이므로 strcpy 사용)
	if (pQueue->count ==
		1) { // 만약 dequeue를 할 Queue에 원소가 하나밖에 없었다면
		pQueue->front = pQueue->rear =
			NULL; // 원소를 dequeue할 경우 Queue는 NULL 상태가 되므로 포인터
				  // 값들도 NULL로 둔다.
	} else { // 그러나 dequeue를 하더라도 해당 Queue에 다른 원소가 최소 하나
			 // 이상 남아있다면
		pQueue->front = pFront->next; // 다시 알맞은 자리로 linking해준다.
	}
	free(pFront); // dequeue를 다 했으므로, pFront를 free 선언해준다.
	pQueue->count--; // dequeue는 요소를 제거하는 것이므로, count -1을 해준다.
	return item; // dequeue되는 대상, 그 요소를 return한다.
} // 함수의 파라미터가 포인터 pQueue이므로, Queue는 return하지 않아도 주소값에
  // 해당하는 덩어리로써 자동 저장된다고 보면 된다.

void DestroyQueue(Queue *pQueue) { // Queue를 파괴한다. 해당 큐와 관련된 모든
								   // 메모리를 해제한다.
	int i;
	QueueNode *pCur = NULL,
			  *pNext = NULL; // destroy를 위해 Queuenode를 몇 개 선언해준다.
	for (pCur = pQueue->front; pCur != NULL; pCur = pNext) {
		pNext = pCur->next;
		free(pCur); // free 선언에 사용된 pCur도 free 선언한다.
	}
	pQueue->count = 0; // 오류가 없도록 디폴트값으로 확실히 변경해준다.
	pQueue->front = pQueue->rear =
		NULL; // 마찬가지로, 디폴트값으로 확실히 변경해준다.
	free(pQueue); // 내부를 단계적으로 free 선언한 후, 최종적으로 pQueue로 free
				  // 선언을 한다.
} // void이므로 아무것도 return하지 않는다.

