#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
   int i,j,k,t;
   
   if (argc < 2) { // 인자 값을 적게 받을 경우, return한다.
      printf("usage: mul [int] [int] .... \n");
      exit(0);
   }

   k = 1; // mul이니까 초기값은 1로 둔다.
   for (i=1 ; i<argc ; i++) {
      k = k * atoi(argv[i]); // atoi 함수를 사용하여 문자열을 정수로 바꿔
                             // 계산한다.
   }

   printf("The mul of "); // 과제에 나온 문법을 지켜가며 출력한다.
   for (t=1 ; t<argc-1 ; t++) {
      printf("%s and ", argv[t]);
   }
   printf("%s", argv[argc-1]); // and를 쓰지 않기 위해 마지막 인자는 따로 프린트한다.
   printf(" is %d \n", k);
   return(1);
}
