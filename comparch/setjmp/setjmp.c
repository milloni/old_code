#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

void foo(void);
void bar(void);

int error1 = 0;
int error2 = 1;

jmp_buf jbuf;

int main(void) {
	int rc = setjmp(jbuf);
	switch (rc) {
		case 0:  foo();                     break;
		case 1:  printf("error1 in foo\n"); break;
		case 2:  printf("error2 in foo\n"); break;
		default: printf("error1 in foo\n"); break;
	}
	return 0;
}

void foo(void) {
	if (error1) {
		longjmp(jbuf, 1);
	}
	bar();
}

void bar(void) {
	if (error2) {
		longjmp(jbuf, 2);
	}
}

