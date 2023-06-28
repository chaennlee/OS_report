
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXARGC 20
// argc의 개수를 20개로 제한한다.
#define MAXLINE 80
// 입력받는 문자 개수를 80개로 제한한다.

extern char **environ;

int execute(char **);
char **gettoken(char *); // string line을 하나씩 잘라주는 역할을 하는 함수

int main() {
  char line[MAXLINE], *token;
  char **args;
  int status = 0;

  printf("My Shell Started.... \n"); // Shell start

  while (1) {

    printf("MyShell>");
    fgets(line, MAXLINE, stdin); // 키보드에서 line을 통째로 읽는다.

    if (strncmp(line, "quit", 4) !=
        0) { // 길이를 지정, 두 문자열을 비교하는 strncmp 함수를 이용
      args = gettoken(line); // line을 쪼개는 함수다. 포인터 배열을 반환.
      status = execute(args); // Myshell 안에서 받아서 token에서 수행한다.
      printf("\n");

    } else {
      exit(1); // line 앞 4자리가 quit이면 종료한다.
    }
  }

  free(args);

  return (1);
}

char **gettoken(char *line) {

  int idx = 0;
  char delim[] = " \t\r\n"; // delimeter 기준으로 잘라준다.
  char **tokenList = malloc(MAXLINE);
  // 80byte의 공간 힙에 할당하고, **tokenList로 주소를 가르킨다.
  char *token; // 분리된 문자열을 임시저장하는 공간

  if (!tokenList) { // heap에 공간이 없다는 뜻으로 에러가 발생한다.
    printf("malloc error \n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, delim); // 문자열을 delimeter 기준으로 분리한다.
  while (token != NULL) { // NULL 값을 만나기 전까지 반복한다. 
    tokenList[idx] = token;
    idx++;

    if (idx > MAXARGC - 1) { //배열의 index가 기준치를 넘을 경우, 경고 출력 후 종료한다. 
      printf("Too many args  \n");
      break;
    }
    token = strtok(NULL, delim); // line data가 다 없어진 경우다.
  }

  tokenList[idx] = NULL; // 문자열이 끝난다는 의미로 NULL을 생성한다. 
  return tokenList; // 포인터 배열을 반환한다. 
}

int execute(char **args) {
  pid_t pid; // 프로세스 ID(PID)를 저장하는 타입이다. opaque type이다.
  int status;
  int i = 1;
  // int len, j;
  //char *k;
  // k = (char*)malloc(strlen(args[1]));
  // len = strlen(*args);
  //./add가 아닌, add를 입력해도 수행되게 하기 위해 고군분투하였지만, 아직 완벽히 작동되진 않는다.

  char s1[5] = "add";
  char s2[5] = "mul";

  if (args[0] == NULL) { // 명령이 없으면 그대로 반환한다. 
    return 1;
  }

  printf(" %s ", args[0]); // command 출력
  while (args[i] != NULL) {
    printf(" %s", args[i]); // 값들 출력
    i++;
  }
  printf("\n");

  /*if(strcmp(args[0], s1) == 0) {
       strcpy(k, args[1]);
       strcpy(args[0], "./add");
       for(j=1; j<len; j++){
               args[j] = args[j+1];
       }
       args[len] = k;

  }

  if(strcmp(args[0], s2) == 0) {
       strcpy(k, args[1]);
       strcpy(args[0], "./mul");
       for(j=1; j<len; j++){
               args[j] = args[j+1];
       }
       args[len] = k;
  }*/

  if (strcmp(args[0], "quit") == 0)
    return 1;

  pid = fork(); // fork()함수, 함수를 호출한 프로세스를 복사하는 기능을 한다.
  if (pid == 0) { // pid는 프로세스 id로, 자식 프로세스에서는 0이 반환된다.
    if (execvp(args[0], args) == -1) { // execvp()는 PATH에 등록된 디렉토리에 있는 프로그램을 실행
      printf("excvp error \n");
      exit(0); // execvp가 실행되지 않았다면 종료한다. 
    }
  }

  return (1);
}



