
#include <stdio.h> // 헤더 파일은 server.c의 것과 동일하므로 생략합니다. 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_data.h"

#define closesocket      close
#define PROTOPORT        5193        // 기본 프로토콜 포트 번호


extern int               errno;
char   localhost[] = "localhost";    // 호스트 이름의 기본값

struct {
    long msgtype;
    char data[256];
} msgbuf;
 

int main(int argc, char *argv[])
{
   char answer[10]; // answer : even or odd
   char sol1[10] = "even";
   char sol2[10] = "odd";
   
   key_t key=12345;
   int msqid;
   struct message msg; // struct message 타입의 'msg'를 선언한다. 

   if((msqid=msgget(key,IPC_CREAT|0666))==-1){ // 메세지 큐 식별자를 정희한다. 
           printf("msgget failed\n"); // 메세지 큐 생성에 실패한 경우 오류 메세지를 출력한다. 
           exit(0);
   }

   struct  hostent  *ptrh;   // host table 구조체 포인터
   struct  protoent *ptrp;   // protocol table 구조체 포인터
   struct  sockaddr_in sad;  // server의 주소를 저장하는 구조체
   int     sd;               // socket descriptor
   int     port;             // 프로토콜 포트 번호
   char    *host;            // 호스트 이름 pointer
   int     n;                // 읽은 문자 수
   char    buf[1000];        // server로부터 읽은 데이터 저장하기 위한 buf 선언.
   memset((char *)&sad,0,sizeof(sad));  // sad 구조체 초기화
   sad.sin_family = AF_INET;            

   if (argc > 2) port = atoi(argv[2]); // 프로토콜 포트 번호를 결정하자. 인수로 포트 번호가 주어졌다면 해당 번호를 사용한다. 
   else port = PROTOPORT; // 그렇지 않을 경우 기본 포트 번호를 사용한다. 
   if (port > 0) sad.sin_port = htons((u_short)port); // 포트 번호가 양수일 경우, sad.sin_port 필드에 해당 번호를 설정한다. 
   else
     { fprintf( stderr,"bad port number %s\n", argv[2]); // else, 오류 메세지를 출력. 
          exit(1);
     }
 if (argc > 1 ) host = argv[1]; // host 이름이 인수로 주어졌다면 그것을 사용한다. 
   else host = localhost; // 그렇지 않을 경우, 'localhost'를 사용한다. 
   ptrh = gethostbyname(host); // 호스트 이름을 해석, 호스트 정보를 가져온다.  
   if( ((char *)ptrh) == NULL)
     { fprintf( stderr, "invalid host:  %s\n", host);
       exit(1);
     }

 memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
   if ( ((int)(ptrp = getprotobyname("tcp"))) == 0)
     { fprintf( stderr, "cannot map \"tcp\" to protocol number\n");
       exit(1);
     }

   sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto); // 소켓을 생성.
   // PF_INET : IPv4프로토콜을 사용, SOCK_STREAM : TCP 소켓 생성, ptrp->p_proto : 프로토콜 번호를 설정.
   if (sd < 0)
     { fprintf( stderr, "socket creation failed\n"); // 생성 실패 시, 오류 메세지 출력. 
       exit(1);
     }

   if (connect(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) // server에 연결한다. 
     { fprintf( stderr, "connect failed\n"); // 연결 실패 시, 오류 메세지 출력. 
       exit(1);
     }

   n = recv(sd, buf, sizeof(buf), 0); // server로부터 데이터를 수신한다. 
   while(n > 0)
     {
       buf[n] = '\0';
       fprintf( stderr, "CLIENT: %s", buf); // 수신한 데이터를 터미널창에 출력한다. 
       n = recv(sd, buf, sizeof(buf), 0); // 수신한 길이가 0보다 크면, 계속 수신 및 출력한다. 
     }
   printf("Welcome to the odd even game! \nThe computer will generate a random integer! \nYou can guess if the number is odd or even!\n");
   printf("Choose between odd and even numbers! Good luck :)\n\n");
   scanf("%[^\n]s", &answer);
   //printf("%s \n\n", answer); // 사용자가 'even' 또는 'odd'를 고르게 한다. 
   
   if(msgrcv(msqid,&msg,sizeof(struct real_data),0,0)==-1){ // 메세지 큐에서 메세지를 수신한다. 
           printf("msgrcv failed\n"); // 수신 실패 시, 오류 메세지 출력. 
           exit(0);
   }
    
   if (msg.data.num % 2 == 0){ // num이 짝수인 경우
   	if (!strcmp(sol1, answer)) // 사용자도 'even'이라 입력하였다면
   		printf("%s\n", msg.data.answer1); // 정답임을 인정한다. 
   	else if (!strcmp(sol2, answer)) // 사용자가 'odd'라 입력하였다면
   		printf("%s\n", msg.data.answer2); // 오답임을 인정한다. 
   	else // 이상한 답변 작성 시, 경고문과 함께 종료한다. 
   		printf("please write right answer!!! \n"); 
   }
   
   if (msg.data.num % 2 != 0){ // num이 홀수인 경우
   	if (!strcmp(sol1, answer)) // 사용자가 'even'이라 입력하였다면
   		printf("%s\n", msg.data.answer2); // 오답임을 인정한다.
   	else if (!strcmp(sol2, answer)) // 사용자가 'odd'라 입력하였다면
   		printf("%s\n", msg.data.answer1); // 정답임을 인정한다.
   	else // 이상한 답변 작성 시, 경고문과 함께 종료한다. 
   		printf("please write right answer!!! \n");
   }
   
   
   if(msgctl(msqid,IPC_RMID,NULL)==-1){ // 메세지 큐 제거 함수를 사용한다. 
       printf("msgctl failed\n"); // 제거 실패 시, 오류 메세지 출력. 
       exit(0);
   }
   closesocket(sd); // 소켓을 닫는다. 
   exit(0); // 코드를 종료한다. 
}


