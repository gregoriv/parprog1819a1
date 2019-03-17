#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>

void get_walltime(double *wct)
{
    struct timeval tp;
    gettimeofday(&tp,NULL);
    *wct = (double) (tp.tv_sec+tp.tv_usec /1000000.0);
}

int main(int argc, char** argv)
{
    int i,j,k;
    double ts,te ,ct;
    float *arra,*arrb,*arrc,*zero;
    __m128 va, vb;
    
    i=0;
    i=posix_memalign((void**)&arra,16,N*N*sizeof(float));
    if (i!=0){
        exit(1);
    }
    
    i=posix_memalign((void**)&arrb,16,N*N*sizeof(float));
    if (i!=0){
        free(arra);
        exit(2);
    }
    
    i=posix_memalign((void**)&arrc,16,N*N*sizeof(float));
    if (i!=0){
        free(arra);
        free(arrb);
        exit(3);
    }
    
    for (int i=0; i<N*N; i++){
        arra[i] = 2.0;
        arrb[i] = 3.0;
        arrc[i] = 20.0;
    }
  
    for (i=0; i<4; i++) {
        zero[i] = 0.0;
    }
    __m128 *sum = (__m128*) zero;
    __m128 tmp;

    get_walltime(&ts);

    pc=arrc
    for (k=0;k<N;k++){
        pb=arrb;
        vb=(__m128*) pb;
        for (j=0;j<N;j++) {
            pa = arra + k*N;
            va = (__m128*) pa;
            *sum = _mm_set_ps(0, 0, 0, 0);
            for (int i=0; i<N; i+=4){
                *sum = _mm_add_ps(*sum, _mm_mul_ps(*va, *vb));
                va++, vb++;
            }
            tmp=_mm_hadd_ps(*sum, *sum);
            *sum=_mm_hadd_ps(tmp, tmp);
            *pc = zero[0];
            pc++;
        }
    }

    // Get end time
    get_walltime(&te);

    
    for (int i=0;i<N*N; i++){
        if (arrc[i] != 6.0 * N){
            printf("Error! \n");
            break;
        }
    }
    
    ct=(N* N) / ((te - ts) * 1e6);
    printf( %f\n", ct);
    
    free(arra);
    free(arrb);
    free(arrc);
    return 0;
}
