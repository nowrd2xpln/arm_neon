/************************  
 * neon.c 
 *
 ************************/

#include <stdio.h>


__attribute__((aligned (16)))
unsigned short int data1[8];
unsigned short int data2[8];
unsigned short int out[8];

void* neontest_save_buffer[16];


void
neontest(unsigned short int *a, unsigned short int *b,
				unsigned short int* q)
{
  __asm__(
"   movw        r12, #:lower16:neontest_save_buffer\n\t"
"   movt        r12, #:upper16:neontest_save_buffer\n\t"
"   stmia       r12, {r4-r11,  lr}        @ save registers\n\t"
"   vld1.16     {q1}, [r0:128]\n\t"
"   vld1.16     {q2}, [r1:128]\n\t"
"   vadd.i16    q0, q1, q2\n\t"
"   vst1.32     {q0}, [r2:128]\n\t"
"   movw        r12, #:lower16:neontest_save_buffer\n\t"
"   movt        r12, #:upper16:neontest_save_buffer\n\t"
"   ldmia       r12, {r4-r11,  lr}        @ reload all registers and return\n\t"
"finish:\n\t"
	);

}

int
main(int argc, char * argv[])
{
	FILE *img = NULL;
	int i = 0;

	printf("argc %d\n", argc);

	for(i = 0; i < argc; ++i){
		printf("argv[%d]: %s\n", i, argv[i]);
	}


	return(0);
}

