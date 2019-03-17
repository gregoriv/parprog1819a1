#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double *wct)
{
    struct timeval tp;
    gettimeofday(&tp,NULL);
    *wct = (double) (tp.tv_sec+tp.tv_usec /1000000.0);
}

int main(int argc, char** argv)
{
    int i,j,k;
    double ts,te,ct;
    float *arra,*arrb,*arrc;
    float *pa,*pb,*pc;
    float sum;
  
    arra=(float *)malloc(N*N*sizeof(float)); 
  	if (arra==NULL){
	    printf("Error!\n");
	    exit(-1);
	  }
	  arrayb=(float *)malloc(N*N*sizeof(float)); 
	  if (arrb==NULL){
	    printf("Error!\n");
	    free(arra);
	    exit(-1);
	  }
	  arrc=(float *)malloc(N*N*sizeof(float)); 
	  if (arrc==NULL){
	    printf("Error!\n");
	    free(arra);
	    free(arrb);
	    exit(-1);
	  }
    for(i=0; i<N*N; i++) {
		  arra[i] = 2.0;
		  arrb[i] = 3.0;
		  arrc[i] = 20.0;
	  }
  
    get_walltime(&ts);
  
    pc = arrc;
    for(k = 0; k<N;k++)
    {
        pb = arrb;
        for(j = 0 ; j< N;j++)
        {
            pa = arra + k*N;
            sum = 0.0;
            for(i = 0 ; i<N;i++)
            {
                sum = sum + (*pa) * (*pb);
                pa++;
                pb++;
            }
            *pc = sum;
            pc++;
        }
    }
  
    get_walltime(&te);
  
    for (int i=0; i<N*N; i++) {
        if (arrc[i] != 6 * N) {
            printf("Error!\n");
            break;
        }
    }
    ct = (N* N) / ((te - ts) * 1e6);
 
    free(arra);
    free(arrb);
    free(arrc);
    return 0;
}
