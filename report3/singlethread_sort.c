#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define CHECK_END -1
// '-1'을 'CHECK_END' 함수로 정의한다.

static int *array =
    NULL; // 정적 전역 변수 'array'를 선언하고, NULL값을 선언한다.

static void div_array(int *, int, int);
static void merge_sort(int *);

static void init_array(int size) // 배열을 초기화하는 함수
{

  int count = 0; // 지역 변수 선언
  array = (int *)malloc(sizeof(int) *
                        size); // 입력받은 사이즈에 맞게 동적 할당을 해준다.
  for (count = 0; count < size;
       count++) // for문을 사용하여 랜덤 값을 하나씩 넣어준다.
  {
    array[count] = rand() % size + 1; // rand()는 랜덤한 숫자를 반환하는 함수다.
  }
}

static void display_array(int size) // 배열을 '쉼표'로 구분하여 화면에 출력한다.
{
  int count = 0; // 지역 변수 선언
  for (count = 0; count < size; count++) {
    printf("%d", array[count]); // for문에 맞게 순서대로 숫자를 출력한다.

    if (count + 1 < size)
      printf(
          ", "); // 맨 마지막 숫자 뒤에는 '쉼표'가 오지 않게 for문을 조정한다.
    else
      printf(" END\n"); // 숫자 출력이 끝났다면 END를 printf한다.
  }
}

static void merge(int *arr, int start, int middle, int end) { // merge 알고리즘
  int *arr_left, *arr_right; // 정수형 포인터 변수 선언
  int left = 0, right = 0; // arr_left, arr_right 배열의 현재 인덱스를 나타내는 변수
  int count = 0;

  arr_left = (int *)malloc(sizeof(int) * (middle - start + 2));
  arr_right = (int *)malloc(sizeof(int) * (end - middle + 1));
  // 둘 다 'arr' 배열의 일부를 복사하여 저장할 임시 배열이다. 

  for (count = 0; count <= middle - start; count++) {
    arr_left[count] = arr[start + count];
    // 'start' 부터 'middle - start' 까지의 원소를 'arr_left'에다가 복사한다.
    // 배열을 반으로 자르고 그 앞부분을 복사한 것과 동일하다. 
  }

  arr_left[count] = CHECK_END; 
  // 임시 배열의 끝을 나타내기 위해, 배열의 마지막 element에 상수값을 저장해준다. 

  for (count = 0; count < end - middle; count++) {
    arr_right[count] = arr[middle + count + 1];
    // 'middle + count + 1'부터 'end'까지의 원소를 'arr_right'에다가 복사한다. 
  }

  arr_right[count] = CHECK_END; // 마찬가지로, 끝을 나타내기 위해 상수값을 넣어둔다. 

  for (count = start; count <= end; count++) { // 'start'부터 'end'까지 for문을 수행
    if ((arr_left[left] == CHECK_END || arr_left[left] > arr_right[right]) &&
        arr_right[right] != CHECK_END) {
      // 'arr_left'의 현재 인덱스 'left'가 CHECK_END 값과 같거나
      // 'arr_left'의 현재 원소가 'arr_right'의 현재 원소보다 크면서 'right'가 CHECK_END와 다르다면
      // 'arr_right'의 현재 원소를 'arr'의 'count'인덱스에 할당하고, 'right' 값을 1 증가한다. 
      arr[count] = arr_right[right++];
    } else
      arr[count] = arr_left[left++];
      // 그렇지 않으면, 'arr_left'의 현재 원소를 'arr'의 'count'에 할당하고, 'left' 값을 1 증가한다.
  }

  free(arr_left); // 동적 할당 해제
  free(arr_right); // 동적 할당 해제 
}

static void div_array(int *arr, int start, int end) {
  int middle = (start + end) / 2; // 배열을 가운데에서 분할할 인덱스를 계산한다. 

  if (start < end) { // 분할할 배열의 크기가 1보다 크다면
    div_array(arr, start, middle); // 왼쪽 절반을 재귀 함수 쓰면서 정렬~~ 한다. 
    div_array(arr, middle + 1, end); // 오른쪽 절반을 재귀 함수 쓰면서 정렬~~ 한다. 

    merge(arr, start, middle, end); // 합병 정렬을 수행한다. 정렬된 상태로 합쳐진다. 
  }
}

int main(void) {
  srand(time(0)); // for 난수 발생, 시드(seed)를 초기화한다. 현재 시간을 시드로 사용 중

  struct timeval btime, atime; // 정렬 전, 후의 시간을 저장하는 변수다. 
  long sec, msec;
  int size = 0;

  printf("input size of array : ");
  scanf("%d", &size); // user로부터 정렬할 배열의 크기, 'size'를 input받는다. 

  init_array(size); // 입력받은 크기에 맞게 배열을 초기화한다. 

  printf("before sorting\n"); 
  display_array(size); // 정렬 전의 배열 출력

  gettimeofday(&btime, NULL); // 현재 시간을 저장

  div_array(array, 0, size - 1);

  gettimeofday(&atime, NULL); // 합병 정렬 완료된 후의 시간을 저장

  printf("Array after sorting:\n");
  display_array(size); // 정렬 후의 배열 출력

  sec = atime.tv_sec - btime.tv_sec; // 정렬에 소요된 시간(초)를 계산
  msec = atime.tv_usec - btime.tv_usec; // 정렬에 소요된 시간(마이크로초)를 계산
  printf("Elapsed time: %ld sec %ld msec\n", sec, msec);

  return 0;
}
