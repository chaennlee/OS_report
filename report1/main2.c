#define _CRT_SECURE_NO_WARNINGS
#include "List_Link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
  int num;
  int num2 = 0;
  List *pList = createList(); // sorting list를 생성한다. 
  int n = 0, data = 0, ret = 0; 

  printf("Duck Fishing Program !!\n\n"); 
  printf("You can enter the weight of the duck you fish. \n\nHowever, the weight of ducks is expressed as a positive integer and does not overlap.\n\n");
  // 해당 코드는 linked list 자료구조로 sorting까지 가능한 코드이다. sort를 한다는 점에서 같은 숫자의 오리 무게를 두 번 넣으면, 한 번만 입력된다는 단점이 있다. 

  while(1){ // break를 만나기 전까지 영원히 loop되는 while문을 사용한다. 

    printf("In (0), Search (1), Out (2), Exit (3) : ");
    scanf("%d", &num);

    if(num==0){ // 오리 무게를 입력받는다. 
      printf("\nEnter the weight of the duck you have fished! : ");
      scanf("%d", &num2);
      addList(pList, num2);
    }

    else if(num==1){  // 특정 오리 무게를 출력한다. 정확히 말하면, 특정 오리 무게가 있는 지를 search한다. 
      printf("\nSearch : ");
      scanf("%d", &num2); // search 대상이 되는 오리 무게를 입력받는다. 
      if(SearchList(pList, num2) == 1){ // 오리 무게가 존재하는 경우
        printf("\nMy We don't have %d kg duck.\n", num2);
      }
      else if(SearchList(pList, num2) == 0){ // 오리 무게가 존재하지 않는 경우
        printf("\nYes, we have %d kg duck !!\n", num2);
      }
    }

    else if(num==2){ // 제거할 오리 무게를 입력받는다. 
      printf("\nEnter the weight of the duck to be removed : ");
      scanf("%d", &num2);
      removeList(pList, num2); // 해당 무게가 존재한다면 제거, 존재하지 않는다면 경고 메세지를 띄운다. 
    }

    else if(num==3){ // 오리 낚시를 종료한다. 
      break; 
    }

    else{ // 0, 1, 2, 3 외의 다른 숫자를 넣었을 경우, 경고 메세지를 띄운다. 
      printf("input right number!");
    }
   
    ListTraverse(pList); // 현재 list를 출력해주는 함수를 생성하였다. 
  }
  
  destroyList(pList); // destroy 후(free 선언), pList를 NULL로 선언한다. 
  pList = NULL; 
  return 0;
}
