#include <stdio.h>
#define N 1000

long sumaxy(int &n, long *x, long *y);
long sumax2(int &n, long *x);
long sumax(int &n, long *x);
long sumay(int &n, long *y);
long pendiente(int &n, long *sumax, long *sumay, long *sumaxy, long *sumax2);
long interseccion(int &n, long *sumax, long *sumay, long *m);

int main(void) {

	int n, i;
	long m, b, *sumax , *sumay , *sumaxy , *sumax2;
	long *x[N], *y[N];

	printf("\nCantidad  de puntos: ");  // Pedir la cantidad de puntos
	scanf("%d", &n);

	for (i = 0; i<n; i++) {    // pedir X e Y
		printf("\nPunto %d:         \tX : ", i + 1);
		scanf("%f", &y[i]);
		printf("                       \tY : ", i + 1);
		scanf("%f", &x[i]);
	}

	
		sumaxy = sumaxy(n, x, y);   // sumar los produtos       
		sumax2 = sumax2(n, x);		// sumar los valores de x^2      
		sumax = sumax(n, x);		// sumar los valores de x        
		sumay = sumay(n, y);		// sumar los valores de y
	
	//Calcular la pendiente (m) y la interseccion (b)
	m = pendiente(n, sumax, sumay, sumaxy, sumax2);
	b = interseccion(n, sumax, sumay, m);

	// Mostrar los valores de la pendiente y de la interseccion
	printf("\n\npendiente(m) = %f \nInterseccion(b) = %f\n", m, b);

	// mostrar la formula
	printf("\nRecta de regresión sobre Y = %f*X+ (%f)\n", m, b);

	system("break");
}

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
			cmp ecx, 0;					// comparamos si ecx es igual a 0. 
			jnz for1;					// si ecx NO es igual a 0, saltamos al inicio del bucle
			mov eax, esp;				// movemos el contenido del registro esp a eax
			mov num, eax;	// el resultado de las operaciones almacenado en eax se mueve a la variable result 
			
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
			cmp ecx, 0;					// comparamos si ecx es igual a 0.
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

		mov esi, x;
		mov ecx, m;
		mov esp, 0;
		mov edx, 0;

		jmp for3;

		for3:							// for para sumar los valores de x
			mov eax, [esi + 4 * edx];	// metemos x[i] en el registro eax
			add ebx, eax;				// sumamos eax y edx y lo almacenamos en eax
			inc edx;					// incrementamos ebx que será la variable que recorra el vector
			dec ecx;					// decrementamos el valor de ecx en 1 unidad
			cmp ecx, 0;					// comparamos si ecx es igual a 0.
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

		mov esi, y;
		mov ebx, 0;
		mov ecx, m;
		mov esp, 0;
		jmp for4;

		for4:									// for para sumar los valores de y
			mov eax, [esi + 4 * ebx];			// movemos [esi + 4 * ebx] al registro edx	-> edx = y[i]
			add esp, eax;						// sumamos eax y edx y lo almacenamos en eax
			inc ebx;							// incrementamos ebx que será la variable que recorra el vector
			dec ecx;							// decrementamos el valor de ecx en 1 unidad
			cmp ecx, 0;							// comparamos si ecx es igual a 0.
			jnz for4;							// realiza un salto a la etiqueta for4 mientras ecx no sea igual a 0
			mov eax, esp;						// movemos el contenido del registro esp a eax
			mov result, eax;					// el resultado de las operaciones almacenado en eax se mueve a la variable result  
			
	}

	return (result);

}

long pendiente(int &n, long *sumax, long *sumay, long *sumaxy, long *sumax2) {

	long result;

	__asm {

		mov eax, n;						//movemos el valor de n a eax
		mov ebx, sumaxy;				//movemos el valor de sumaxy a ebx
										//inicializaremos mas tarde el valor de sumax2, sumax y sumay


		imul eax, ebx;					//multiplicamos eax por ebx -> (n * sumaxy)
		push eax;						//enviamos el resultado de eax a la pila (pila  = n * sumaxy)
		mov eax, edx;					//movemos edx a eax (eax = sumax)
		mov ebx, ecx;					//movemos ebx a ecx (ebx = sumay)
		imul eax, ebx;					//multiplicamos eax por ebx -> (sumax * sumay)
		mov ebx, eax;					//movemos el resultado de eax a ebx
		pop eax;						//sacamos el valor de la pila y lo almacenamos en eax (ahora eax = n * sumaxy)
		sub eax, ebx					//restamos eax entre ebx y lo almacenamos en eax
		push eax;						//almacenamos el valor de eax en la pila (pila = n*sumaxy - sumax*sumay)
		mov eax, n;						//volvemos a mover el valor de n al registro eax
		mov ebx, sumax2;				//movemos el valor de sumax2 al registro ebx
		imul eax, ebx;					//multiplicamos eax por ebx y lo almacenamos en eax (eax = n*sumax2)
		push eax;						//enviamos el valor de eax a la pila. Se almacena encima (no lo borra) del valor anteriormente almacenado
		mov eax, sumax;					//movemos el valor de sumax al registro eax (eax = sumax)
		mov ebx, sumax;					//movemos el valor de sumax al registro ebx (ebx = sumax)
		imul eax, ebx;					//multiplicamos eax por ebx y lo almacenamos en eax (eax = sumax*sumax)
		mov ebx, eax;					//movemos el valor de eax a ebx (ebx = sumax*sumax)
		pop eax;						//el ultimo valor almacenado en la pila (n*sumax2) lo pasamos al registro eax
		sub eax, ebx;					//restamos eax - ebx	->	(n*sumax2 - sumax*sumax) y lo almacenamos en eax
		mov ebx, eax;					//movemos el resultado a ebx
		pop eax;						//el resultado de (n*sumaxy - sumax*sumay) almacenado anteriormente en la pila lo pasamos a eax
		idiv ebx;						//dividimos eax entre ebx y lo almacenamos en eax
		mov result, eax;				//el valor de eax lo pasamos a la variable result

	}
	//  = (n*sumaxy - sumax*sumay) / (n*sumax2 - sumax*sumax);
	return (result);
}

long interseccion(int &n, long *sumax, long *sumay, long *m) {

	float result;

	__asm {

		mov eax, m;						//movemos el valor de m al registro eax
		mov ebx, sumax;					//movemos el valor de sumax al registro ebx

		imul eax, ebx;					//multiplicamos eax por ebx y lo almacenamos en eax		-> (eax = m*sumax)
		mov ebx, eax;					//movemos el valor de eax a ebx		-> (ebx = m*sumax)
		mov eax, sumay;					//movemos el valor de sumay al registro eax	(eax = sumay)
		sub eax, ebx;					//restamos eax - ebx y lo almacenamos en eax (sumay - m*sumax)
		mov ebx, n;						//movemos el valor de n al regustro ebx (ebx = n)
		idiv ebx;						//dividimos eax entre ebx y lo almacenamos en ebx
		mov result, eax;				//movemos el valor de eax (resultado de la division anterior) a la variable result 

		//b = (sumay - m*sumax) / n;

	}

	return (result);
}