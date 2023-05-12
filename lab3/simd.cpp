#include <iostream>
#include <stdio.h>
#include <xmmintrin.h>
#include <time.h>
#include <chrono>
#include <fstream>

__m128 add(__m128 a, __m128 b);
__m128 sub(__m128 a, __m128 b);
__m128 mul(__m128 a, __m128 b);
__m128 div(__m128 a, __m128 b);

__m128 random_num(int count, __m128 vec);

int main(){

	__m128 a, b; // Zmienne do wykonywania dzialan
	
	int count[3] = {2048, 4096, 8192}; // Ilosc liczb w wektorze
	
	long long result_add=0, result_sub=0, result_mul=0, result_div=0; // Zmienne do przechowywania czasow operacji
	
	std::string fileName[3] = {"2048.txt", "4096.txt", "8192.txt"};
	
	
	for(int i=0; i<3; i++){
		std::cout<<"Typ obliczen: SIMD\n";
		std::cout<<"Liczba liczb:"<<count[i]<<"\n";
		std::cout<<"Sredni czas [ns]:\n";
		
		for(int j=0; j<10; j++){
			__m128 operation;
			
			a = random_num(count[i], a);
			b = random_num(count[i], b);
			
			auto start1 = std::chrono::high_resolution_clock::now();
			operation = add(a, b);
			auto end1 = std::chrono::high_resolution_clock::now();
			result_add = result_add + std::chrono::duration_cast<std::chrono::nanoseconds>(end1-start1).count();
			
			auto start2 = std::chrono::high_resolution_clock::now();
			operation = sub(a, b);
			auto end2 = std::chrono::high_resolution_clock::now();
			result_sub = result_sub + std::chrono::duration_cast<std::chrono::nanoseconds>(end2-start2).count();
			
			auto start3 = std::chrono::high_resolution_clock::now();
			operation = mul(a, b);
			auto end3 = std::chrono::high_resolution_clock::now();
			result_mul = result_mul + std::chrono::duration_cast<std::chrono::nanoseconds>(end3-start3).count();
			
			auto start4 = std::chrono::high_resolution_clock::now();
			operation = div(a, b);
			auto end4 = std::chrono::high_resolution_clock::now();
			result_div = result_div + std::chrono::duration_cast<std::chrono::nanoseconds>(end4-start4).count();
			
		}
		
		std::cout<< "+ " << result_add/10<<"\n";
		std::cout<< "- " << result_sub/10<<"\n";
		std::cout<< "* " << result_mul/10<<"\n";
		std::cout<< "/ " << result_div/10<<"\n\n";
		
		std::ofstream file(fileName[i]);
		
		if(file.is_open()){
			file <<"Typ obliczen: SIMD\n";
			file <<"Liczba liczb:"<<count[i]<<"\n";
			file <<"Sredni czas [ns]:\n";
		
			file << "+ " << result_add/10<<"\n";
			file << "- " << result_sub/10<<"\n";
			file << "* " << result_mul/10<<"\n";
			file << "/ " << result_div/10<<"\n\n";
			
			file.close();
		}
	}
	
	__m128 _add = add(a, b);
	__m128 _sub = sub(a, b);
	__m128 _mul = mul(a, b);
	__m128 _div = div(a, b);
	
	
}

__m128 add(__m128 a, __m128 b){ // Dodawanie a+b
	__m128 result;
	
	asm volatile(
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

__m128 random_num(int count, __m128 vec){ // Wypelnianie wektora losowymi liczbami
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
