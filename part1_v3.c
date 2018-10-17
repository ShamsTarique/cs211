#include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <math.h>
  
int main(){
       //todo: test correctness
  
     int sizes_for_n [] = {64,128,256,512,1024,2048}; //want to use these sizes for n in the nxn matrices 
     int f;
     
     printf("Timing and Correctness Test:\n\n");
     
     
         
     
     
    
     for(f = 0; f < 6; f++){ //NOTE/TODO: for each different n a new random matrix is generated, if wanting to compare 
                             //different n values to each other change the initialization of the matrices or something
      
         int n = sizes_for_n[f];
        
            
         double* a = (double*)calloc(sizeof(double),n*n);//input used for a for all algorithms
         double* b = (double*)calloc(sizeof(double),n*n);//input used for b for all algorithms
         double* c = (double*)calloc(sizeof(double),n*n); //output for dgemm0 algorithm
         double* c1 = (double*)calloc(sizeof(double),n*n);//output for dgemm1 ''
         double* c2 = (double*)calloc(sizeof(double),n*n);//output for dgemm2'''
         double* c3=  (double*)calloc(sizeof(double),n*n);//output for dgemm3'''
         
         //filling matrix a and b with random doubles
         int i,j,k =0;
         for(i=0; i<n; i++){
             for(j=0; j<n; j++){
                
                a[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0); //generate random double 0.00-100.00
                b[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0);
             }
         }
        
        
        
         /*dgemm0: simple ijk version triple loop algorithm*/
           //   std::chrono::time_point<std::chrono::system_clock> start, end;
           //  start = std::chrono::stystem_clock::now();
            clock_t time0;
              time0 = clock();
         
         
         
              time0 = clock();  //clock returns the # of clock ticks elapsed sicne an epoch related to the particular p    rogram execution
         
               i,j,k =0; //reseting counters....had to include these counters because pre c++99 we could not declare v    ariables inside a for loop, compiler problems
               for (i=0; i<n; i++)
                  for (j=0; j<n; j++)
                      for (k=0; k<n; k++)
                          c[i*n+j] += a[i*n+k] * b[k*n+j];
            //  end = std::chrono:system_clock::now();
            //  std::chrono::duration<double> elapsed_seconds = end - start;
              time0 = clock()-time0;
              
         
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
             
            // end1 = std::chrono:system_clock::now();
            // std::chrono::duration1<double> elapsed_seconds = end1 - start1;
         
         
        
         
               
              
              
               
        
         /*dgemm2: more aggressive register reuse*/
        
             clock_t time2;
             time2 = clock();
        
             for(i = 0; i < n; i += 2){
                 for(j = 0; j < n; j += 2)  {
                     register int t = i*n+j; register int tt = t+n;
                      register double c00 = c2[t]; register double c01 = c2[t+1]; register double c10= c2[tt]; register double c11 = c2[tt+1];
        
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
             
        
        
        
         /*dgem3: using up to 16 registers*/
        
        
             clock_t time3;
             time3 = clock();
        
        
             for(i = 0; i < n; i += 2){
                 for(j = 0; j < n; j += 2) {
                     register int t = i*n+j; register int tt = t+n;
                     register double c00 = c3[t]; register double c01 = c3[t+1]; register double c10= c3[tt]; register double c11 = c3[tt+1];
                     for(k = 0; k < n; k += 2) {
                         /* 2 by 2 mini matrix multiplication using registers*/
                         register int ta = i*n+k; register int tta = ta+n; register int tb = k*n+j;register int ttb =     tb+n;               
                         register double a00 = a[ta]; register double a10 = a[tta]; register double b00 = b[tb]; register double b01 = b[tb+1];
                         c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;
                         a00 = a[ta+1]; a10 = a[tta+1]; b00 = b[ttb]; b01 = b[ttb+1];
                        c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;
                     }
                     c3[t] += c00;
                     c3[t+1] += c01;
                     c3[tt] += c10;
                     c3[tt+1] += c11;
                 }
             }
        
        
             time3 = clock()-time3;
            
        
        
        
        
        
        
         //checking correctness
             double max_diff_of_matrix_c_and_c1 = 0.000000000000000;
             double max_diff_of_matrix_c_and_c2 = 0.000000000000000;
             double max_diff_of_matrix_c_and_c3 = 0.000000000000000;
        
            
        
             for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each m    atrix(should all be the same because we dont change a &b
                 for(j = 0; j<n;j++){
                    if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix_c_and_c1)
                          max_diff_of_matrix_c_and_c1 = fabs(c[i*n+j] - c1[i*n+j]);
                    if(fabs(c[i*n+j] - c2[i*n+j]) >= max_diff_of_matrix_c_and_c2)
                          max_diff_of_matrix_c_and_c2 = fabs(c[i*n+j] - c2[i*n+j]);
                    if(fabs(c[i*n+j] - c3[i*n+j]) >= max_diff_of_matrix_c_and_c3)
                          max_diff_of_matrix_c_and_c3 = fabs(c[i*n+j] - c3[i*n+j]);
               
                     
                  }
             }
        
            
             //outputing time measurements: can be found in the [filename].txt or part1.txt
             
             
             printf("For n = %d\n:", sizes_for_n[f]);
             printf("\tAlgorithm dgemm0 went through  (%.15f seconds) to complete running . \n",((float)time0)/CLOCKS_PER_SEC);
        
             printf("\tAlgorithm dgemm1 went through  (%.15f seconds) to complete running . \n",((float)time1)/CLOCKS_PER_SEC);
        
             printf("\tAlgorithm dgemm2 went through  (%.15f seconds) to complete running . \n",((float)time2)/CLOCKS_PER_SEC);
        
             printf("\tAlgorithm dgemm3 went through  (%.15f seconds) to complete running .\n",((float)time3)/CLOCKS_PER_SEC);
        
        
             printf("\nCorrectness Testing:\n");
             printf("Matrix C from dgemm0 and Matrix c1 from dgemm1 had a max difference of: %.15f\n", max_diff_of_matrix_c_and_c1);
             printf("Matrix C from dgemm0 and Matrix c2 from dgemm2 had a max difference of: %.15f\n", max_diff_of_matrix_c_and_c2);
             printf("Matrix C from dgemm0 and Matrix c3 from dgemm3 had a max difference of: %.15f\n", max_diff_of_matrix_c_and_c3);
            /* 
            //used for testing and looking inside matrices
        
             printf("\n\n\n\nmatrix: a\n");
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
              for(i = 0; i<n*n;i++)
                printf("%f,", c1[i]);
                
                 printf("\nmatrix: c2\n");
              for(i = 0; i<n*n;i++)
                printf("%f,", c2[i]);
                
                  printf("\nmatrix: c3\n");
              for(i = 0; i<n*n;i++)
                printf("%f,", c3[i]);
                
            */ 
            
        printf("\n");
     
                
     }
     
     
     return 0;
 }


