#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
int i = 1;			// 인덱스

typedef struct word 		// 단어와 인덱스를 저장할 구조체
{
	char* cutword;
	int index;
	struct word* Next;
} word;

void SearchList(word* p);
word* LinkedList(word* p);

int main()			// 메인 함수
{
	word* tail, *Head = (word*) malloc(sizeof(word));  // Head에 메모리 동적할당
	Head->Next = NULL;
	tail = Head;
	FILE* rfp;					// 복사할 파일
	FILE* wfp; 					// 복사될 파일
	FILE* fp;					// linked list가 구현될 파일
	char* inp;					// 메모리
	int buf_size = MAX * MAX;			// buf_size 최대로
	char* ptr;					// 포인터
	int file_size;					// 파일 크기
	int count = 0;					// 개행 문자 개수

	rfp = fopen("Maroon5_Sugar.txt", "r");		// 복사할 파일 open
	wfp = fopen("Maroon5_Sugar_cpy.txt", "w");	// 복사될 파일 open

// Maroon5_Sugar.txt file 크기 구하기

	fseek(rfp, 0, SEEK_END);			// 커서를 파일 끝으로
	file_size = ftell(rfp);				// rfp 파일의 크기
	fseek(rfp, 0, SEEK_SET);			// 커서를 파일 처음으로

	inp = malloc(buf_size);				// 메모리 동적할당


// Maroon5_Sugar.txt file의 개행 문자를 띄워 쓰기로 대체하면서 Maroon5_Sugar_cpy.txt file 에 복사
	while ((file_size - count) > ftell(wfp))
	{
		fgets(inp, buf_size, rfp);
		ptr = strtok(inp, "\n");
		fputs(ptr, wfp);
		fputs(" ", wfp);
		count++;
	}

	fclose(rfp);					// 파일 닫기
	fclose(wfp);					// 파일 닫기

	fp = fopen("Maroon5_Sugar_cpy.txt", "r");	// 읽기 전용으로 copy file open


// Maroon5_Sugar_cpy.txt file을 읽으면서 단어 단위로 자르고 Linked list를 구현

	while (fgets(inp, buf_size, fp))
	{
		ptr = strtok(inp, " .,-?");		// 한 단어 자르기

		while (ptr != NULL)
		{
			tail->cutword = ptr;		// 자른 단어 구조체에 넣기
			tail->index = i;			// 인덱스 구조체에 넣기
			tail = LinkedList(tail);		// linked list

			printf("%d ", i);			// index 출력
			printf("%s\n", ptr);			// 단어 출력

			ptr = strtok(NULL, " .,-?");

			i++;   				// index 증가

		}

	}

	printf("\n");

	while (1)					// search
	{
		SearchList(Head);
	}


	fclose(fp);					// file close

	return 0;
}

void SearchList(word* p)				// search
{
	char* sword = (char*) malloc(sizeof(char) * MAX); // 검색 단어를 받을 포인터
	int search = 0;
	int cnt1 = 0;					// 검색될 단어 총 개수를 저장
	char* include_word1;
	char* include_word2;

	printf(" 찾을 단어 : ");
	fflush(stdin);
	gets(sword);

// 검색 단어 sword의 첫 문자가 대문자일 때 실행
	if (sword[0] >= 'A' && sword[0] <= 'Z')
	{
		while (p->Next != NULL)
		{
			// 첫 문자가 대문자로 시작하는 단어 찾기
			include_word1 = strchr(p->cutword, sword[0]);
			if (strnicmp(include_word1, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			// 첫 문자가 소문자로 시작하는 단어 찾기
			include_word2 = strchr(p->cutword, sword[0] + 32);
			if (strnicmp(include_word2, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			p = p->Next;
		}

	}

// 검색 단어 sword의 첫 문자가 소문자일 때 실행
	else if (sword[0] >= 'a' && sword[0] <= 'z')
	{
		while (p->Next != NULL)
		{
			// 첫 문자가 소문자로 시작하는 단어 찾기
			include_word1 = strchr(p->cutword, sword[0]);
			if (strnicmp(include_word1, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			// 첫 문자가 대문자로 시작하는 단어 찾기
			include_word2 = strchr(p->cutword, sword[0] - 32);
			if (strnicmp(include_word2, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			p = p->Next;
		}

	}

// 검색 단어 sword의 첫 문자가 대소문자가 아닐 때 실행
	else
	{
		while (p->Next != NULL)
		{
			include_word1 = strchr(p->cutword, sword[0]);
			if (strnicmp(include_word1, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			p = p->Next;

		}
	}

	if (!search)
	{

		printf(" 단어 '%s'은 없음. \n", sword);

	}

	printf("단어'%s'을 포함하는 단어  : 총 %d개 검색됨\n ", sword, cnt1);

}

// p를 받아 linked list 구현
word* LinkedList(word* p)
{
	p->Next = (word*) malloc(sizeof(word));
	p = p->Next;
	p->Next = NULL;

	return p;
}
