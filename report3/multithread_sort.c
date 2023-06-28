#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define CHECK_END -1

static int *array = NULL;
static pthread_t tid[2];

static void div_array(int *, int, int);
static void merge_sort(int *);

void *left_sort(void *size) // 왼쪽 절반 정렬 스레드 함수
{
	int s = *((int *)size); // 'size'를 'int'로 자료형 변환한 다음 's'에 저장한다. 
	int middle = s / 2; // 왼쪽 절반의 마지막 인덱스, middle을 계산한다. 

	div_array(array, 0, middle); // 'array' 배열의 [0]부터 ['middle']까지를 정렬한다. 
}

void *right_sort(void *size) // 오른쪽 절반 정렬 스레드 함수
{
	int s = *((int *)size); // 자료형 변환한 다음 's'에 저장한다. 
	int middle = s / 2; // 오른쪽 절반의 시작 인덱스, middle을 계산한다. 

	div_array(array, middle + 1, s); // 'array' 배열의 ['middle']부터 끝까지 정렬한다. 
}

static void init_array(int size)
{
	int count = 0;
	array = (int *)malloc(sizeof(int) * size);

	for (count = 0; count < size; count++)
	{
		array[count] = rand() % size + 1;
	}
}

static void display_array(int size)
{
	int count = 0;
	for (count = 0; count < size; count++)
	{
		printf("%d", array[count]);

		if (count + 1 < size)
			printf(", ");
		else
			printf(" END\n");
	}
}

static void merge(int *arr, int start, int middle, int end)
{
	int *arr_left, *arr_right;
	int left = 0, right = 0;
	int count = 0;

	arr_left = (int *)malloc(sizeof(int) * (middle - start + 2));
	arr_right = (int *)malloc(sizeof(int) * (end - middle + 1));

	for (count = 0; count <= middle - start; count++)
	{
		arr_left[count] = arr[start + count];
	}

	arr_left[count] = CHECK_END;

	for (count = 0; count < end - middle; count++)
	{
		arr_right[count] = arr[middle + count + 1];
	}

	arr_right[count] = CHECK_END;

	for (count = start; count <= end; count++)
	{
		if ((arr_left[left] == CHECK_END || arr_left[left] > arr_right[right]) && arr_right[right] != CHECK_END)
		{
			arr[count] = arr_right[right++];
		}
		else
			arr[count] = arr_left[left++];
	}

	free(arr_left);
	free(arr_right);
}

static void div_array(int *arr, int start, int end)
{
	int middle = (start + end) / 2;

	if (start < end)
	{
		div_array(arr, start, middle);
		div_array(arr, middle + 1, end);

		merge(arr, start, middle, end);
	}
}

static void sort_merge(int size) // 멀티 스레드로 병합 정렬 수행하는 함수
{
	size = size - 1; // 배열의 크기를 1 감소시킨 값을 인덱스의 범위로 설정한다. 

	pthread_create(&tid[0], NULL, &left_sort, &size); // 'left_sort'함수를 실행하는 스레드를 생성
	pthread_create(&tid[1], NULL, &right_sort, &size); // 'right_sort'함수를 실행하는 스레드를 생성

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); // 생성한 스레드들이 종료될 때까지 대기

	merge(array, 0, size / 2, size); // 2개의 절반 배열들의 범위를 병합한다. -> 전체 배열 정렬
}

int main(void)
{
	srand(time(0));

	struct timeval btime, atime;
	long sec, msec;
	int size = 0;

	printf("input size of array : ");
	scanf("%d", &size);

	init_array(size);

	printf("Array before sorting:\n");
	display_array(size);

	gettimeofday(&btime, NULL);

	sort_merge(size); 
  // 싱글스레드에서는 div_array 함수를 호출하였으나 멀티 스레드에서는 이 함수를 호출한다. 

	gettimeofday(&atime, NULL);

	printf("Array after sorting:\n");
	display_array(size);

	sec = atime.tv_sec - btime.tv_sec;
	msec = atime.tv_usec - btime.tv_usec;
	printf("Elapsed time: %ld sec %ld msec\n", sec, msec);

	free(array); // 동적 할당을 해주었으므로 동적 할당 해제

	return 0;
}

