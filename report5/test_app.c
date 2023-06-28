#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h> // 대소문자 변환 함수를 사용하기 위해 호출한다. 

#define MAX_SIZE	50 // max size는 50으로 정한다. 

int main(void){
	int fd; // 파일 디스크립터 저장 목적. 
	
	char* in = (char*)malloc(sizeof(char) * MAX_SIZE);
	char* out = (char*)malloc(sizeof(char) * MAX_SIZE);

	
	if( (fd=open("/dev/mydevicefile", O_RDWR))<0 ){ // 파일을 읽기 + 쓰기 모드로 open한다. 
		perror("open error"); // open을 실패하면 오류 메세지와 더불어 프로그램을 종료한다. 
		free(in);
		free(out);
		return -1;
	}
	
	printf("Enter a message from user mode: "); // 사용자모드에서 문자열 입력
	fgets(out, MAX_SIZE, stdin); // 문자열 입력 받아 out에 저장한다. 
	write(fd, out, strlen(out)); // out을 fd를 통해 write한다. 

	read(fd, in, MAX_SIZE); // fd를 통해 데이터를 읽어온 다음, in에 저장한다. 
	

	printf("Received response from kernel mode: %s\n", in); // 커널모드에서 변환된 in을 출력한다. 

	free(in); // 동적 할당 해제. 
	free(out); // 동적 할당 해제. 

	close(fd); // fd를 닫는다. 
	return 0;
}


