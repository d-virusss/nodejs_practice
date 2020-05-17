#include <stdio.h>

int myStrlen(char* str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++);

	return i;
}

int main()
{
	char str[50] = "abcdcd";
	int num;

	printf("문자를 입력하시오: ");
	scanf_s("%s", str);

	num = myStrlen(str);

	printf("이 문장은 총 %d자입니다.", num);

	return 0;
}

