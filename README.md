# OS_report
# 해당 report들은 경북대학교 강순주 교수님의 '운영체제' 강의 과제 내용입니다. 
# 사용 언어는 C로 한정하며, Make 및 GCC를 활용해 환경을 구성합니다. IDE 전용 프로젝트는 비허용됩니다.

# report 1
구조체를 활용해 오리를 생성한다. 오리는 Queue 구조와 같이 잡힌 순서대로 순차적으로 제거되고, 최대 5마리까지 동시에 잡혀있을 수 있다.
필수 구현해야 할 기능은 '데이터 입력 및 리스트 전체출력', '특정 노드 출력', '특정 노드 삭제'이다. 

# report 2
커스텀 셸과 셸에서 동작하는 프로그램을 만든다.
sum, sub 등과 같이 하나 이상의 argument를 입력으로 받아 처리하는 프로그램이다.기능은 사칙연산 한두개로 하고, 각 기능별로 컴파일하여 별도의 실행 파일을 생성한다.
커스텀 셸 프로그램에서 작성한 프로그램을 동작한다. 셸에서 프로그램 실행 시 main함수에 argument를 전달할 수 있는 형태로 작성한다.
추가로 리눅스 터미널에서 동작하는 프로그램(ls, pwd 등)을 실행해봐도 좋다.

# report 3
정렬 알고리즘을 single/multi thread로 각각 구현하고 동작 성능을 비교하는 과제다.
알고리즘은 인터넷에서 코드를 찾아 활용해도 좋다. "pthread" 라이브러리를 활용하여 멀티스레드 프로그램을 구현하고 "time" 라이브러리를 활용하여 각각 수행 시간을 계산하라.

# report 4
"Socket, IPC를 이용한 보드 게임 구현"을 리눅스 상에서 직접 구현하자.
1. Socket API를 사용해야 한다. #include <sys/socket.h> , #include <sys/types.h>을 사용하라.
2. pthread를 통해 쓰레드를 구현해야 한다.
3. mutex, semaphore를 사용하여 동기화 문제를 적용, 해결해야 한다.
4. IPC (message queue등)을 사용해야 한다.
5. 게임 참가자는 2명 이상이다.
게임은 가위바위보, 홀짝 맞추기, 눈치게임, 주사위 눈이 높은 Client 찾기 등 자유롭게 선정하라.

# report 5
디바이스 드라이버 만들기.
50byte 길이의 ascii 문자열을 user mode 프로그램에서 kernel mode(device driver)로 전송하면, 대소문자를 바꿔서 user mode 프로그램으로 반환하고, 출력하는 프로그램을 작성한다.
문자열 입력 및 출력은 user mode 프로그램에서, 변환은 kernel mode 프로그램에서 이루어지도록 작성한다. 
