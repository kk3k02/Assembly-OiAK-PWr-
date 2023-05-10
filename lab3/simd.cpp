#include <iostream>
#include <stdio.h>
#include <xmmintrin.h>
#include <time.h>

long long timestamp();

__m128 add(__m128 a, __m128 b);
__m128 sub(__m128 a, __m128 b);
__m128 mul(__m128 a, __m128 b);
__m128 div(__m128 a, __m128 b);

int main(){

	__m128 a, b;
	
	a = _mm_set_ps(8.0,2.0,6.0,10.0);
	b = _mm_set_ps(2.0,1.0,3.0,1.0);
	
	__m128 g = div(a, b);
	
	float* float_pointer = reinterpret_cast<float*>(&g);
	
	for(int i=0; i < 4; i++){
		std::cout<<float_pointer[i] << " ";
	}
}

__m128 add(__m128 a, __m128 b){ // Dodawanie a+b
	__m128 result;
	
	asm(
		"movups %1, %%xmm0\n"
		"movups %2, %%xmm1\n"
		"addps %%xmm1, %%xmm0\n"
		"movups %%xmm0, %0"
		:"=g" (result)
		:"g" (a), "g" (b)
		:"xmm0", "xmm1", "memory"
		);
	
	return result;
}

__m128 sub(__m128 a, __m128 b){ // Odejmowanie a-b
	__m128 result;
	
	asm(
		"movups %1, %%xmm0\n"
		"movups %2, %%xmm1\n"
		"subps %%xmm1, %%xmm0\n"
		"movups %%xmm0, %0"
		:"=g" (result)
		:"g" (a), "g" (b)
		:"xmm0", "xmm1", "memory"
		);
		
	return result;
}

__m128 mul(__m128 a, __m128 b){ // Mnozenie a*b

	__m128 result;

	asm(
		"movups %1, %%xmm0\n"
		"movups %2, %%xmm1\n"
		"mulps %%xmm1, %%xmm0\n"
		"movups %%xmm0, %0"
		:"=g" (result)
		:"g" (a), "g" (b)
		:"xmm0", "xmm1", "memory"
	);
	
	return result;
}

__m128 div(__m128 a, __m128 b){

	__m128 result;

	asm(
		"movups %1, %%xmm0\n"
		"movups %2, %%xmm1\n"
		"divps %%xmm1, %%xmm0\n"
		"movups %%xmm0, %0"
		:"=g" (result)
		:"g" (a), "g" (b)
		:"xmm0", "xmm1", "memory"
	);
	
	return result;
}
