#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
int i = 1;			// �ε���

typedef struct word 		// �ܾ�� �ε����� ������ ����ü
{
	char* cutword;
	int index;
	struct word* Next;
} word;

void SearchList(word* p);
word* LinkedList(word* p);

int main()			// ���� �Լ�
{
	word* tail, *Head = (word*) malloc(sizeof(word));  // Head�� �޸� �����Ҵ�
	Head->Next = NULL;
	tail = Head;
	FILE* rfp;					// ������ ����
	FILE* wfp; 					// ����� ����
	FILE* fp;					// linked list�� ������ ����
	char* inp;					// �޸�
	int buf_size = MAX * MAX;			// buf_size �ִ��
	char* ptr;					// ������
	int file_size;					// ���� ũ��
	int count = 0;					// ���� ���� ����

	rfp = fopen("Maroon5_Sugar.txt", "r");		// ������ ���� open
	wfp = fopen("Maroon5_Sugar_cpy.txt", "w");	// ����� ���� open

// Maroon5_Sugar.txt file ũ�� ���ϱ�

	fseek(rfp, 0, SEEK_END);			// Ŀ���� ���� ������
	file_size = ftell(rfp);				// rfp ������ ũ��
	fseek(rfp, 0, SEEK_SET);			// Ŀ���� ���� ó������

	inp = malloc(buf_size);				// �޸� �����Ҵ�


// Maroon5_Sugar.txt file�� ���� ���ڸ� ��� ����� ��ü�ϸ鼭 Maroon5_Sugar_cpy.txt file �� ����
	while ((file_size - count) > ftell(wfp))
	{
		fgets(inp, buf_size, rfp);
		ptr = strtok(inp, "\n");
		fputs(ptr, wfp);
		fputs(" ", wfp);
		count++;
	}

	fclose(rfp);					// ���� �ݱ�
	fclose(wfp);					// ���� �ݱ�

	fp = fopen("Maroon5_Sugar_cpy.txt", "r");	// �б� �������� copy file open


// Maroon5_Sugar_cpy.txt file�� �����鼭 �ܾ� ������ �ڸ��� Linked list�� ����

	while (fgets(inp, buf_size, fp))
	{
		ptr = strtok(inp, " .,-?");		// �� �ܾ� �ڸ���

		while (ptr != NULL)
		{
			tail->cutword = ptr;		// �ڸ� �ܾ� ����ü�� �ֱ�
			tail->index = i;			// �ε��� ����ü�� �ֱ�
			tail = LinkedList(tail);		// linked list

			printf("%d ", i);			// index ���
			printf("%s\n", ptr);			// �ܾ� ���

			ptr = strtok(NULL, " .,-?");

			i++;   				// index ����

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
	char* sword = (char*) malloc(sizeof(char) * MAX); // �˻� �ܾ ���� ������
	int search = 0;
	int cnt1 = 0;					// �˻��� �ܾ� �� ������ ����
	char* include_word1;
	char* include_word2;

	printf(" ã�� �ܾ� : ");
	fflush(stdin);
	gets(sword);

// �˻� �ܾ� sword�� ù ���ڰ� �빮���� �� ����
	if (sword[0] >= 'A' && sword[0] <= 'Z')
	{
		while (p->Next != NULL)
		{
			// ù ���ڰ� �빮�ڷ� �����ϴ� �ܾ� ã��
			include_word1 = strchr(p->cutword, sword[0]);
			if (strnicmp(include_word1, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			// ù ���ڰ� �ҹ��ڷ� �����ϴ� �ܾ� ã��
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

// �˻� �ܾ� sword�� ù ���ڰ� �ҹ����� �� ����
	else if (sword[0] >= 'a' && sword[0] <= 'z')
	{
		while (p->Next != NULL)
		{
			// ù ���ڰ� �ҹ��ڷ� �����ϴ� �ܾ� ã��
			include_word1 = strchr(p->cutword, sword[0]);
			if (strnicmp(include_word1, sword, strlen(sword)) == 0)
			{
				printf("index : %d\n", p->index);
				search = 1;
				cnt1++;
			}

			// ù ���ڰ� �빮�ڷ� �����ϴ� �ܾ� ã��
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

// �˻� �ܾ� sword�� ù ���ڰ� ��ҹ��ڰ� �ƴ� �� ����
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

		printf(" �ܾ� '%s'�� ����. \n", sword);

	}

	printf("�ܾ�'%s'�� �����ϴ� �ܾ�  : �� %d�� �˻���\n ", sword, cnt1);

}

// p�� �޾� linked list ����
word* LinkedList(word* p)
{
	p->Next = (word*) malloc(sizeof(word));
	p = p->Next;
	p->Next = NULL;

	return p;
}
