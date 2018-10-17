#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    //todo: test correctness
    

   int n = 4;
   


double* a = (double*)calloc(sizeof(double),n*n);

double* b = (double*)calloc(sizeof(double),n*n);
double* c = (double*)calloc(sizeof(double),n*n);
double* c1 = (double*)calloc(sizeof(double),n*n);
double* c2 = (double*)calloc(sizeof(double),n*n);
double* c3=  (double*)calloc(sizeof(double),n*n);
//filling matrix a and b with random doubles
    int i,j,k =0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            a[i*n+j] = ((double)rand()*100)/((double)rand_max + 0); //generate random double 0.00-100.00
            b[i*n+j] = ((double)rand()*100)/((double)rand_max + 0); 
        }
    }


/*dgemm0: simple ijk version triple loop algorithm*/
  //   std::chrono::time_point<std::chrono::system_clock> start, end;
  //  start = std::chrono::stystem_clock::now();
    clock_t time;
    time = clock();



    time = clock();  //clock returns the # of clock ticks elapsed sicne an epoch related to the particular program execution

     i,j,k =0; //reseting counters....had to include these counters because pre c++99 we could not declare variables inside a for loop, compiler problems
     for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            for (k=0; k<n; k++)
                c[i*n+j] += a[i*n+k] * b[k*n+j];
  //  end = std::chrono:system_clock::now();
  //  std::chrono::duration<double> elapsed_seconds = end - start; 
    time = clock()-time; 
    printf ("it took me %d clicks (%f seconds).\n",time,((float)time)/clocks_per_sec);

/*dgemm1: simple ijk version triple loop algorithm with register reuse*/
   // std::chrono::time_point<std::chrono::system_clock> start1, end1;
   // start1 = std::chrono::stystem_clock::now();
    clock_t time1;
    time1 = clock();
    
    for (i=0; i<n; i++){
        for (j=0; j<n; j++) {
            register double r = c1[i*n+j] ;
            for (k=0; k<n; k++)
                r += a[i*n+k] * b[k*n+j];
            c1[i*n+j] = r;
         }      
    }
    time1 = clock()-time1;
    printf ("it took me %d clicks (%f seconds).\n",time1,((float)time1)/clocks_per_sec);
  // end1 = std::chrono:system_clock::now();
  // std::chrono::duration1<double> elapsed_seconds = end1 - start1; 
 



    printf("\nmatrix: a\n");
    for(i = 0; i<n*n;i++){
        printf("%f,", a[i]);
    }     

    printf("\nmatrix: b \n");
    for(i = 0; i<n*n;i++){
        printf("%f,",b[i]);
    }     


    printf("\nmatrix: c\n");
    for(i = 0; i<n*n;i++){
        printf("%f,", c[i]);
    }     


    printf("\nmatrix: c1\n");
    for(i = 0; i<n*n;i++){
        printf("%f,", c1[i]);
    }     





    printf("\nmatrix: c3 implementation \n");

/*dgemm2: more aggressive register reuse*/
    
    clock_t time2;
    time2 = clock();

    for(i = 0; i < n; i += 2){
       for(j = 0; j < n; j += 2)  {
            register int t = i*n+j; register int tt = t+n; 
            register double c00 = c2[t]; register double c01 = c2[t+1];  register double c10 = c2[tt]; register double c11 = c2[tt+1];

            for(k = 0; k < n; k += 2) {
                /* 2 by 2 mini matrix multiplication using registers*/
                register int ta = i*n+k; register int tta = ta+n; register int tb = k*n+j; register int ttb = tb+n;
                register double a00 = a[ta]; register double a01 = a[ta+1]; register double a10 = a[tta]; register double a11 = a[tta+1];
                register double b00 = b[tb]; register double b01 = b[tb+1]; register double b10 = b[ttb]; register double b11 = b[ttb+1];
                c00 += a00*b00 + a01*b10;
                c01 += a00*b01 + a01*b11;
                c10 += a10*b00 + a11*b10;
                c11 += a10*b01 + a11*b11;
             }

             c2[t] = c00;
             c2[t+1] = c01;
             c2[tt] = c10;
             c2[tt+1] = c11;
        }
    }



    time2 = clock()-time2;
    printf ("it took me %d clicks (%f seconds).\n",time2,((float)time2)/clocks_per_sec);



/*dgem3: using up to 16 registers*/
    
    
    clock_t time3;
    time3 = clock();


    for(i = 0; i < n; i += 2){
        for(j = 0; j < n; j += 2) {
            register int t = i*n+j; register int tt = t+n;
            register double c00 = c2[t]; register double c01 = c2[t+1]; register double c10= c2[tt]; register double c11 = c2[tt+1];
            for(k = 0; k < n; k += 2) {
                /* 2 by 2 mini matrix multiplication using registers*/
                register int ta = i*n+k; register int tta = ta+n; register int tb = k*n+j;register int ttb = tb+n;
                register double a00 = a[ta]; register double a10 = a[tta]; register double b00 = b[tb]; register double b01 = b[tb+1];
                c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;
                a00 = a[ta+1]; a10 = a[tta+1]; b00 = b[ttb]; b01 = b[ttb+1];
                c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;
            }
            c2[t] = c00;
            c2[t+1] = c01;
            c2[tt] = c10;
            c2[tt+1] = c11;
        }
    }

    
    time3 = clock()-time3;
    printf ("it took me %d clicks (%f seconds).\n",time3,((float)time3)/clocks_per_sec);


    



//checking correctness
    double max_diff_of_matrix_c = 0.0;
    double max_diff_of_matrix_c1 = 0.0;
    double max_diff_of_matrix_c2 = 0.0;
    double max_diff_of_matrix_c3 = 0.0;

    double c_min = 99999.0;
    double c_max = 0.0;
    double c1_min = 99999.0;
    double c1_max = 0.0;
    double c2_min = 99999.0;
    double c2_max = 0.0;
    double c3_min = 99999.0;
    double c3_max = 0.0;


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
            if(c2[i*n+j]<c2_min)
                c2_min = c2[i*n+j];
            if(c2[i*n+j]> c2_max)
                c2_max = c2[i*n+j];
            if(c3[i*n+j] < c3_min)
                c3_min = c3[i*n+j];
            if(c3[i*n+j] > c3_max)
                c3_max = c3[i*n+j];
         }
    }
    
    max_diff_of_matrix_c = c_max - c_min;
    max_diff_of_matrix_c1 = c1_max - c1_min;    
    max_diff_of_matrix_c2 = c2_max - c2_min;    
    max_diff_of_matrix_c3 = c3_max - c3_min;    


   

//outputing time measurements: can be found in the [filename].txt or part1.txt
    printf("dgemm0 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time,((float)time)/clocks_per_sec, max_diff_of_matrix_c); 

    printf("dgemm1 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time1,((float)time1)/clocks_per_sec, max_diff_of_matrix_c1); 

    printf("dgemm2 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time2,((float)time2)/clocks_per_sec, max_diff_of_matrix_c2); 

    printf("dgemm3 went through %d clicks (%f seconds) to complete running and the matrix had a  maximum difference  of %f \n",time3,((float)time3)/clocks_per_sec, max_diff_of_matrix_c3); 
        

return 0;
}
