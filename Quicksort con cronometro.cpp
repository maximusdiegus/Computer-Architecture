#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>


using namespace std;

void vector(int v[], int n);

int main(void){
	int *v;
	long double tiempos, tfinal, media;
	unsigned long talla;

	for (int i = 12; i <= 18; i++){

		talla = (unsigned long)powl(2, i);
		media = 0;
		for (int j = 0; j<30; j++){
			v = new int[talla];

			if (v){
				for (unsigned long j = 0; j<talla; j++){
					v[j] = rand();
				}
				tiempos = clock();
				vector(v, talla);
				tfinal = clock();

				media = media + ((tfinal - tiempos) / 60);

				delete[] v;
			}
			else{
				cout << "Error, no hay memoria suficiente" << endl;
				exit(1);
			}

		}
		cout << talla << "\t" << media / 30 << endl;
	}

	return 0;
}

void vector(int v[], int n){
	int p = -1;
	int j = 0;
	int k = 1;
	__asm{

		mov eax, p; // p
		mov ebx, j; // j
		mov edi, v; // v
		mov edx, -1;
		//  mov DW, 1;
	bucle1:
		inc eax; // incrementamos p
		inc eax; // HAY QUE INCREMENTAR LA P DOS VECES YA QUE LA DECREMENTAMOS ABAJO, POR LO TANTO HABRIA QUE INICIALIZAR P A -1 AL COMIENZO.
		cmp eax, n // comparo que p no sea mayor que n y en caso de que lo sea...
			jge fin; // ... lo mando a "fin".
		cmp eax, k //////
			je caso1;
		cmp eax, k
			jge caso2;
	caso1:
		// dec eax;
		mov ecx, [edi + eax * 4];
		dec eax;
		mov ebx, eax; // igualamos j a p-1
		jmp condicion1; // nos metemos en el while /////////
	caso2:
		mov ecx, [edi + eax * 4]; // igualamos ecx a v[p]
		dec eax; // p-1
		mov ebx, eax; // igualamos j a p-1
		jmp condicion1; // nos metemos en el while
		// mov[edi + (ebx * 4 + 4)], ecx; // metemos v[j+1] en ecx   ESTO HAY QUE METERLO EN OTRO LADO.
	condicion1:
		cmp ebx, edx // si j es menor que 0 y...
			jge condicion2;
	condicion2:
		cmp[edi + ebx * 4], ecx // ... ecx menor que v[j]...
			jge bucle2; // ...salimos del bucle...
		jmp funcion; // ... y volvemos al for.
	bucle2:
		mov esi, [edi + ebx * 4]; // metemos v[j] en una variable "esi"
		mov[edi + (ebx * 4 + 4)], esi; // en v[j+1] guardamos v[j]
		dec ebx; // decrementamos j
		cmp ebx, edx // si j sigue siendo mayor que 0...
			jge condicion3; // ...
	condicion3:
		cmp[edi + ebx * 4], ecx // ... y si v[j] sigue siendo mayor que ecx ...
			jge bucle2; // ... salimos del bucle.
		jmp funcion;
	funcion:
		mov[edi + (ebx * 4 + 4)], ecx; // en A[j+1] metemos ecx
		jmp bucle1;
	fin:

	}
}