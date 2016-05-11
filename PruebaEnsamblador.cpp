#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

long sumaxy(int &n, long *x, long *y);
long sumax2(int &n, long *x);
long sumax(int &n, long *x);
long sumay(int &n, long *y);

int main(void) {

	long x[3] = { 1,2,3 };
	long y[3] = { 3,2,1 };
	long ca, cu, pe, pi; //sumaxy, sumax^2, sumax, sumay
	int n = 2;

	//ca = sumaxy(n, x, y);
	cu = sumax2(n, x);
	//pe = sumax(n, x);
	//pi = sumay(n, y);

	cout <</* ca <<*/ cu /*<< pe << pi*/ << endl;
	
	 getchar();
}

/*long ensamblador(int &n, long *x, long *y){
	

	/*int n = 2;
	long sumax = 2;
	long sumay = 10;
	long m = 2;

	
		/*mov eax, 0;						//asignamos el valor 0 al regsitro ax. Ax hará de contador i en los bucles for
		mov ecx, op;					//asignamos el valor op al registro cx (op = la operacion que se va a realizar ahora)
		
		mov ebx, 0;
		mov edi, x;
		mov esi, y;


		
		mov ecx, m;						//movemos el valor de m al registro eax
		mov eax, ecx;
		mov ebx, sumax;					//movemos el valor de sumax al registro ebx

		imul eax, ebx;					//multiplicamos eax por ebx y lo almacenamos en eax		-> (eax = m*sumax)
		mov ebx, eax;					//movemos el valor de eax a ebx		-> (ebx = m*sumax)
		mov eax, sumay;					//movemos el valor de sumay al registro eax	(eax = sumay)
		sub eax, ebx;					//restamos eax - ebx y lo almacenamos en eax (sumay - m*sumax)
		mov ebx, n;						//movemos el valor de n al regustro ebx (ebx = n)
		idiv ebx;						//dividimos eax entre ebx y lo almacenamos en ebx
		mov numero, eax;				//movemos el valor de eax (resultado de la division anterior) a la variable result 
								//b = (sumay - m*sumax) / n;

		
		
		mov eax, 0;
		mov ecx, c;
		mov esi, 3;
		mov eax, [ecx];// va de 4 en 4 [ecx] = 1 // [ecx + 4] = 2 // [ecx + 8] = 3
		mov numero, eax;
		*/

long sumaxy(int &n, long *x, long *y) { // Cambia el registro ebp a otro (esp) 

	long num;
	long m = n + 1;
	
	__asm {

		mov esi, x;
		mov edi, y;
		mov ebx, 0;
		mov ecx, m;
		mov edx, 0;
		mov esp, 0;

		for1:							// for para sumar los productos
			mov eax, [edi + 4 * edx];	// metemos x[i] en el registro eax
			mov ebx, [esi + 4 * edx];	// metemos y[i] en el registro ebx
			imul ebx;					// multiplicamos ebx por eax y lo almacenamos en eax
			add esp, eax;				// sumamos eax + esp y lo almacenamos en esp
			inc edx;					// incrementamos ebp que será la variable que recorra el vector
			dec ecx;					// decrementamos el valor de ecx en 1
			cmp ecx, -1;				// comparamos si ecx es igual a 0. 
			jnz for1;					// si ecx NO es igual a 0, saltamos al inicio del bucle
			mov eax, esp;				// movemos el contenido del registro esp a eax
			mov num, eax;				// el resultado de las operaciones almacenado en eax se mueve a la variable result 
			
	}

	return(num);

}

long sumax2(int &n, long *x) {

	long result;
	long m = n + 1;

	__asm {

		mov edi, x;
		mov ebx, 0;
		mov eax, 0;
		mov ecx, m;
		mov edx, 0;
		jmp for2;

		for2:							// for para sumar los valores de x^2
			mov eax, [edi + 4 * edx];	// metemos x[i] en el registro eax
			imul eax;					// multiplicamos eax por eax y lo almacenamos en eax
			add ebx, eax;				// sumamos el registro eax + esp y movemos el resultado a esp
			inc edx;					// incrementamos ebx que será la variable que recorra el vector
			dec ecx;					// decrementamos el valor de ecx
			cmp ecx, -1;				// comparamos si ecx es igual a 0.
			jnz for2;					// realiza un salto a la etiqueta for3 mientras ecx no sea igual a 0
			mov eax, ebx;				// movemos el contenido del registro esp a eax
			mov result, eax;			// el resultado de las operaciones almacenado en eax se mueve a la variable result 
	
	}

	return (result);

}

long sumax(int &n, long *x) {

	long result;
	long m = n + 1;

	__asm {

		mov edi, x;
		mov ecx, m;
		mov esp, 0;
		mov edx, 0;

		jmp for3;

		for3:							// for para sumar los valores de x
			mov eax, [edi + 4 * edx];	// metemos x[i] en el registro eax
			add ebx, eax;				// sumamos eax y edx y lo almacenamos en eax
			inc edx;					// incrementamos ebx que será la variable que recorra el vector
			dec ecx;					// decrementamos el valor de ecx en 1 unidad
			cmp ecx, -1;				// comparamos si ecx es igual a 0.
			jnz for3;					// realiza un salto a la etiqueta for3 mientras ecx no sea igual a 0
			mov eax, ebx;				// movemos el contenido del registro esp a eax
			mov result, eax;			// el resultado de las operaciones almacenado en eax se mueve a la variable result 
			
	}

	return (result);

}

long sumay(int &n, long *y) {

	long result;
	long m = n + 1;

	__asm {

		mov edi, y;
		mov ecx, m;
		mov ebx, 0;
		mov edx, 0;
		jmp for4;

		for4:									// for para sumar los valores de y
			mov eax, [edi + 4 * edx];			// movemos [esi + 4 * ebx] al registro edx	-> edx = y[i]
			add ebx, eax;						// sumamos eax y edx y lo almacenamos en eax
			inc edx;							// incrementamos ebx que será la variable que recorra el vector
			dec ecx;							// decrementamos el valor de ecx en 1 unidad
			cmp ecx, -1;						// comparamos si ecx es igual a 0.
			jnz for4;							// realiza un salto a la etiqueta for4 mientras ecx no sea igual a 0
			mov eax, ebx;						// movemos el contenido del registro esp a eax
			mov result, eax;					// el resultado de las operaciones almacenado en eax se mueve a la variable result  
			
	}

	return (result);

}