#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void burbuja(int *vector);

int main(void) {
	srand(time(NULL));
	int vector[20];
	int valor;
	printf("Vector antes de ordenar: \n");

	for (int i = 0; i < 20; i++) {
		valor = rand() % 20;
		vector[i] = valor;
		printf(" %d ", vector[i]);
	}
	printf("\n");
	burbuja(vector);

	printf("Vector despues de ordenar: \n");

	for (int i = 0; i < 20; i++) {
		printf(" %d ", vector[i]);
	}
	printf("\n");
	getchar();
}

void burbuja(int *vector) {

	__asm {
		mov ecx, vector
		mov edi, 20
		bucle1:
		dec edi
			jz fin
			mov esi, 20
			bucle2 :
			dec esi
			jz bucle1
			mov eax, [ecx + 4 * esi]
			mov ebx, [ecx + 4 * (esi - 4)]
			cmp eax, ebx
			jnb bucle2
			mov[ecx + 4 * (esi - 4)], eax
			mov[ecx + 4 * esi], ebx
			jmp bucle2
			fin :

	}

}