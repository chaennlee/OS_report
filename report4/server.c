
#include <stdio.h> // 표준 입출력을 사용하기 위한 헤더 파일
#include <string.h> // 문자열 관련 함수를 위한 헤더 파일
#include <stdlib.h> // 'atoi', 'exit' 등의 함수 사용을 위한 헤더 파일
#include <sys/types.h> // 시스템 data type을 정의하는 헤더 파일
#include <sys/socket.h> // 소켓 프로그래밍을 위한 헤더 파일
#include <netinet/in.h> // IP를 사용하는 소켓 프로그래밍을 위한 헤더 파일
#include <netdb.h> // 네트워크 DB 관련 함수 사용을 위한 헤더 파일
#include <pthread.h> // 스레드 사용을 위한 헤더 파일
#include <sys/ipc.h> // IPC 기능을 사용하기 위한 헤더 파일
#include <sys/msg.h> // 메세지 큐를 사용하기 위한 헤더 파일
#include <time.h> 
#include "msg_data.h" // 메시지 data 구조체 등이 정의된, 사용자 정의 헤더 파일

void * serverthread(void * parm);       // 스레드 함수의 프로토타입
pthread_mutex_t  mut;
#define PROTOPORT 5193          // 기본 프로토콜 포트 번호
#define QLEN 6             // 요청된 대기열의 크기
int visits =  0;                        // 연결된 client의 수를 세아리는 변수


int main (int argc, char *argv[])
{     
     struct   hostent   *ptrh;     // host table 구조체 포인터
     struct   protoent  *ptrp;     // protocol table 구조체 포인터
     struct   sockaddr_in sad;     // server의 주소를 저장하는 구조체
     struct   sockaddr_in cad;     // client의 주소를 저장하는 구조체
     int      sd, sd2;             
     int      port;                // 프로토콜 포트 번호
     int      alen;                // 주소 길이
     pthread_t  tid;             // 쓰레드 ID를 저장하는 변수
     pthread_mutex_init(&mut, NULL); // 함수를 호출하여 뮤텍스를 초기화한다. 
     memset((char  *)&sad,0,sizeof(sad)); // sad 구조체를 0으로 초기화한다. 
     sad.sin_family = AF_INET;            
     sad.sin_addr.s_addr = INADDR_ANY;    // 로컬 IP주소로 설정한다. 
     // 프로코톨 포트 번호를 리눅스 터미널창에서 확인하고, 추출한다. 
     if (argc > 1) { // 인수가 지정된 경우, argv를 binary로 변환한다. 
                     port = atoi (argv[1]); /* convert argument to binary*/
     } else { // 인수가 지정되지 않은 경우, 기본 포트 번호를 사용한다. 
                      port = PROTOPORT; 
     }
     if (port > 0) // 잘못된 값인지 확인하고, 만일 잘못되었다면 else문으로 이동한다. 
                      sad.sin_port = htons((u_short)port);
     else { // 오류 메세지를 출력하고 종료한다. 
                      fprintf (stderr, "bad port number %s/n",argv[1]);
                      exit (1);
     }

 /* TCP(전송 제어 프로토콜)의 이름을 프로토콜 번호로 변환한다. */
     if ( ((int)(ptrp = getprotobyname("tcp"))) == 0)  {
                     fprintf(stderr, "cannot map \"tcp\" to protocol number");
                     exit (1);
     }

     sd = socket (PF_INET, SOCK_STREAM, ptrp->p_proto); // 소켓을 생성한다. 
     if (sd < 0) {
                       fprintf(stderr, "socket creation failed\n");
                       exit(1);
     }

     if (bind(sd, (struct sockaddr *)&sad, sizeof (sad)) < 0) { // 소켓에 로컬 address를 바인딩. 
                        fprintf(stderr,"bind failed\n");
                        exit(1);
     }

     if (listen(sd, QLEN) < 0) { // request 큐의 크기를 지정한다. 
                        fprintf(stderr,"listen failed\n");
                         exit(1);
     }
     alen = sizeof(cad);

 /* Main server loop */
     fprintf( stderr, "Server up and running.\n");
     
     while (1) {
         printf("SERVER: Waiting for contact ...\n");
         if (  (sd2=accept(sd, (struct sockaddr *)&cad, &alen)) < 0) { // client의 연결을 수락한다.
	                      fprintf(stderr, "accept failed\n");
                              exit (1);
	 }
	 pthread_create(&tid, NULL, serverthread, (void *) sd2 ); // 새로운 스레드를 생성.
     }
     close(sd);
}
void * serverthread(void * parm) // client의 요청을 처리하는 스레드 함수.
{
   key_t key = 12345; // 메세지 큐의 key값을 설정한다. 
   int msqid; // 메세지 큐의 id
   struct message msg; // 구조체 변수 'msg'를 선언하고, 초기화한다. 
   msg.msg_type=1;
   msg.data.num = rand()%100 + 1; // 홀짝 판단의 기준이 될 정수를 랜덤 생성한다. 
   strcpy(msg.data.answer1,"Your answer is RIGHT!! \n\n"); // 정답일 경우 출력. 
   strcpy(msg.data.answer2,"Your answer is WRONG!! \n\n"); // 오답일 경우 출력.

   if((msqid=msgget(key,IPC_CREAT|0666))==-1){ // 메세지 큐id를 얻어온다. 
       printf("msgget failed\n"); // 메세지 큐 id를 얻어오는데 실패한다면 해당 구문 출력 후 종료한다. 
       exit(0);
   }

   printf("message sent!! \nand the number is %d!!\n\n", msg.data.num); 
   // server의 터미널창에만 기준이 되는 num을 출력한다. 
   int tsd, tvisits;
   char     buf[100]; // server가 전송하는 문자열을 저장하기 위한 buf 선언.
   tsd = (int) parm; // 함수의 인자로 전달된 parm을 'tsd'변수로 저장한다. 
   pthread_mutex_lock(&mut); // 뮤텍스를 lock.
        tvisits = ++visits; // client가 더 왔으므로 tvisits의 값을 바꿔준다. 
   pthread_mutex_unlock(&mut); // 뮤텍스를 unlock.
   
   sprintf(buf,"This server has been contacted %d time%s\n",
	   tvisits, tvisits==1?".":"s."); // 최초 방문이라면 1time, n번째 방문이라면 n times라고 출력한다.
   printf("SERVER thread: %s", buf); // server의 터미널창에도 buf 내용을 출력한다. 
   send(tsd,buf,strlen(buf),0); // client에게 buf 내용을 전달한다. 
   
   if (msgsnd(msqid, &msg, sizeof(struct real_data), 0) == -1)
   { // 메세지 큐에 'msg' 구조체 데이터를 보내자. 
     perror("msgsnd error : \n"); // 실패한 경우 에러 메세지를 출력한다. 
     return 0;
   } 
   
   close(tsd); // 소켓을 닫는다. 
   pthread_exit(0); // 스레드를 종료한다. 
}




