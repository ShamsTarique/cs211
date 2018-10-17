#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){

    int n = 64;
   


    double* a = (double*)calloc(sizeof(double),n*n);

    double* b = (double*)calloc(sizeof(double),n*n);
    double* c = (double*)calloc(sizeof(double),n*n);
    double* c1 = (double*)calloc(sizeof(double),n*n);
    double* c2 = (double*)calloc(sizeof(double),n*n);
    double* c3=  (double*)calloc(sizeof(double),n*n);

//filling matrix a and b with random doubles
    int i,j,k,i1,j1,k1 =0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            a[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0); //generate random double 0.00-100.00
            b[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0); 
        }
    }

/* ijk – simple triple loop algorithm with simple single register reuse*/

    clock_t time;
    time = clock();



    for (i=0; i<n; i++){
        for (j=0; j<n; j++) {
            register double r=c[i*n+j];
             for (k=0; k<n; k++){
                 r += a[i*n+k] * b[k*n+j];
            }
             c[i*n+j]=r;
        }
     } 
    
    time = clock()-time; 
  
/* ijk – blocked version algorithm*/
    clock_t time1;
    time1 = clock();

    int B = 10; //B = block size
    for (i = 0; i < n; i+=B){
        for (j = 0; j < n; j+=B){
            for (k = 0; k < n; k+=B){
                /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+B; i1++){
                    for (j1 = j; j1 < j+B; j1++) {
                        register double r=c[i1*n+j1];
                        for (k1 = k; k1 < k+B; k1++){
                            r += a[i1*n + k1]*b[k1*n + j1];
                        }
                        c1[i1*n+j1]=r;
                    } 
                }
            }
        }
    }

    time1 = clock()-time1;


//checking correctness
    double max_diff_of_matrix_c = 0.0;
    double max_diff_of_matrix_c1 = 0.0;

    double c_min = 99999.0;
    double c_max = 0.0;
    double c1_min = 99999.0;
    double c1_max = 0.0;


    for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because we dont change a &b
        for(j = 0; j<n;j++){
            if(c[i*n+j] < c_min)
                 c_min = c[i*n+j];
            if(c[i*n+j] > c_max)
                 c_max= c[i*n+j];
            if(c1[i*n+j] < c1_min)
                 c1_min = c1[i*n+j];
            if(c1[i*n+j] > c1_max)
                 c1_max = c1[i*n+j];
         }
    }
    
    max_diff_of_matrix_c = c_max - c_min;
    max_diff_of_matrix_c1 = c1_max - c1_min;    


   

//outputing time measurements: can be found in the [filename].txt or part1.txt
    printf("dgemm0 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time,((float)time)/CLOCKS_PER_SEC, max_diff_of_matrix_c); 

    printf("dgemm1 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time1,((float)time1)/CLOCKS_PER_SEC, max_diff_of_matrix_c1); 

return 0;

}
