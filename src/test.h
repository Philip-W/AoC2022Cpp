
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

#include <immintrin.h>


void mul4_scalar(float* ptr){
    for (int i =0; i < 10; i++){
        ptr[i] =ptr[i] * ptr[i]; 
    }
}

void mul4_vectorised(float* ptr){
    __m128 f = _mm_loadu_ps(ptr);
    f = _mm_mul_ps(f, f);
    _mm_storeu_ps(ptr, f);
}

int test() {

    float vals[10] = {1.1, 4.5, 6.2, 9.1, 1.0, 2.9, 3.4, 6.7, 9.9, 12.1};
    auto t1 = high_resolution_clock::now();
    mul4_vectorised(vals); 
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<nanoseconds>(t2 - t1);

    std::cout << "Time Vectorised: " << ms_int.count() << "ns \n";



    t1 = high_resolution_clock::now();
    mul4_scalar(vals); 
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<nanoseconds>(t2 - t1);

    std::cout << "Time scalar: " << ms_int.count() << "ns \n";


    
    return 1; 
}
