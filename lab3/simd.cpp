#include <iostream>
#include <stdio.h>
#include <xmmintrin.h>
#include <time.h>

__m128 add(__m128 a, __m128 b);
__m128 sub(__m128 a, __m128 b);
__m128 mul(__m128 a, __m128 b);
__m128 div(__m128 a, __m128 b);

unsigned long long timestamp();

__m128 random_num(int count, __m128 vec);

int main(){

	__m128 a, b; // Zmienne do wykonywania dzialan
	
	int count[3] = {2048, 4096, 8192}; // Ilosc liczb w wektorze
	
	unsigned long long result_add, result_sub, result_mul, result_div; // Zmienne do przechowywania czasow operacji
	
	
	for(int i=0; i<3; i++){
		for(int j=0; j<10; j++){
			__m128 operation;
			unsigned long long start;
		
			a = random_num(count[i], a);
			b = random_num(count[i], b);
			
			start = timestamp();
			operation = add(a, b);
			result_add = timestamp() - start;
			
			start = timestamp();
			operation = sub(a, b);
			result_sub = timestamp() - start;
			
			start = timestamp();
			operation = mul(a, b);
			result_mul = timestamp() - start;
			
			start = timestamp();
			operation = div(a, b);
			result_div = timestamp() - start;
			
		}
	}
	
	__m128 _add = add(a, b);
	__m128 _sub = sub(a, b);
	__m128 _mul = mul(a, b);
	__m128 _div = div(a, b);
	
	
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
	
	asm volatile(
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

	asm volatile(
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

__m128 div(__m128 a, __m128 b){ // Dzielenie a/b
	__m128 result;

	asm volatile(
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

unsigned long long timestamp(){ // Pomiar ilosci cyklow procesora
	unsigned long long result;

	asm volatile(
		"xor %%eax, %%eax\n"
		"cpuid\n"
		"rdtsc"
		:"=A" (result)
		:
		:"ebx", "ecx"
	);
	
	return result;
}

__m128 random_num(int count, __m128 vec){
	srand(time(NULL));
	
	int* table = new int[count];
	
	for(int i=0; i<count; i++){
		table[i] = (std::rand() % RAND_MAX) + 1;
	}
	
	__m128i int_vec = _mm_load_si128((__m128i*)table);
	__m128 float_vec = _mm_castsi128_ps(int_vec);
	float_vec = _mm_add_ps(float_vec, vec);
	int_vec = _mm_castps_si128(float_vec);
	
	return _mm_castsi128_ps(int_vec);
}
