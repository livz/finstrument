#include <stdio.h>

void f11() { 
	printf("  f11\n"); 
}
void f12() { 
	printf("  f12\n"); 
}

void f1() {  
	printf(" f1\n"); 
	f11(); 
	f12();
}

void f21() { 
	printf("  f21\n"); 
}

void f22() { 
	printf("  f22\n"); 
}

void f23() { 
	printf("  f23\n"); 
}

void f2() {  
	printf(" f2\n"); 
	f21(); 
	f22(); 
	f23();
}

void f() {
	printf("f\n"); 
	f1(); 
	f2(); 
}

int main() {

	f();

	return 0;
}
