#define _CRT_SECURE_NO_WARNINGS
//#include "Queue_Array.h"
#include "Queue_List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i, num;
	int k = 0, j = 0;
	Queue *q = CreateQueue(100);
	char duck_weight[20];
	char p[50][100]; // char p[50][100], int j는 리스트 전체 출력 구문을 위한 변수다. 

  printf("\n[[ Duck Fishing Program !! ]]\n\n"); 
  printf("You can enter the weight of the duck you fish. \n\n");

	while (1) {
		printf("In (0), out (1), exit (2) : "); // enqueue, dequeue, finish의 선택지를 준다. 
		scanf("%d", &num);

		if (num == 0) { // enqueue. 오리의 무게를 입력.
			printf("\nEnter the weight of the duck you have fished! : ");
			scanf(" %[^\n]s", (duck_weight));
			strcpy(p[k++], duck_weight);
			Enqueue(q, duck_weight);
		} 
      
    else if (num == 1) { // dequeue. 선입선출의 방식으로 오리를 하나씩 제거.
			if (IsEmptyQueue(q)) { // (1) 만약 queue가 empty상태라면, dequeue가 불가능하다. 
				printf("\nThere are no ducks fished !! \n");
			} 
      else { // (2) queue가 empty상태가 아님을 확인했다면, FIFO 방식으로 먼저 들어온 오리 무게를 제거.
				printf("\n%s kg of duck will be removed !!", Dequeue(q));
				printf("\n");
				j++;
			}
		} 
      
    else if (num == 2) { // 종료 구문. while(1) 구문은 break; 없이 평생 돌기 때문에 이 구문이 필요.
			break;
		} 
      
    else { // 만약 0, 1, 2번 외의 다른 선택지를 선택했다면(존재하지 않으므로) 메뉴바로 return시킨다. 
			printf("input right number!\n");
		}

		printf("\nWeight list of Ducks: "); // 오리 무게 리스트 전체 출력 구문.
		if (IsEmptyQueue(q)) {
			printf("()");
			printf("\n\n");
		} else {
			printf("(");
			int a = 0;
			for (i = j; i < j + q->count; i++) {
				printf("%s", p[i]);
				if (a + 1 != q->count)
					printf(",");
				else
					printf(")");
				a = a + 1;
			}
			printf("\n\n");
		}
	}

	printf("\n");

	DestroyQueue(q);
	q = NULL;
	return 0;
}

