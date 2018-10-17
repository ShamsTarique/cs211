#include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
#include<math.h>


  int main(){
  
       int n = 2048;
  
  
 
      double* a = (double*)calloc(sizeof(double),n*n);
 
      double* b = (double*)calloc(sizeof(double),n*n);
      double* c = (double*)calloc(sizeof(double),n*n);
      double* c1 = (double*)calloc(sizeof(double),n*n);
    
    
      double max_diff_of_matrix = 0.00000000000000;
      
      double min = 99999.0;
      double max = 0.0;
 
 
 
 
  //filling matrix a and b with random doubles
      int i,j,k,i1,j1,k1 =0;
      for(i=0; i<n; i++){
          for(j=0; j<n; j++){
                a[i*n+j] = 1.0 *(i+j);
                b[i*n+j] = 1.0 *(i+j);
              //a[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0); //generate random double 0.00-100.00
              //b[i*n+j] = ((double)rand()*100)/((double)RAND_MAX + 0);
          }
      }
 
/* ijk – simple triple loop algorithm with simple single register reuse*/
        printf("Simple tripe loop algorithm with n= 2048:\n\n");
 
  
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c1[i] = 0.0;
            
      clock_t time0;
      time0 = clock();
 
 
 
      for (i=0; i<n; i++){
         for (j=0; j<n; j++) {
              register double r=c1[i*n+j];
               for (k=0; k<n; k++){
                    r += a[i*n+k] * b[k*n+j];
              }
               c1[i*n+j]=r;
          }
       }
 
      time0 = clock()-time0;
      
     max_diff_of_matrix = 0.000000000000000;
      
      
              
   
      printf("Simple triple loop (ijk) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %f \n",((float)time0)/CLOCKS_PER_SEC);
      
/* ikj – simple triple loop algorithm with simple single register reuse*/
       
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c[i] = 0.0;
       
       time0 = clock();
       
      for (i=0; i<n; i++){
         for (k=0; k<n; k++) {
              register double r=a[i*n+k];
               for (j=0; j<n; j++){
                    c[i*n+j] += r* b[k*n+j];
              }
               
          }
       }
       
        time0 = clock()-time0;
    
 
     max_diff_of_matrix = 0.000000000000000;
      
      
      for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
          for(j = 0; j<n;j++){
              if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix)
                   max_diff_of_matrix = fabs(c[i*n+j] - c1[i*n+j]);
              
          } 
      } 
      
   
      printf("Simple triple loop (ikj) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %.16f \n",((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
     
      
       
/* jik – simple triple loop algorithm with simple single register reuse*/
         
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c[i] = 0.0;
            
        time0 = clock();
        
       for (j=0; j<n; j++){
         for (i=0; i<n; i++) {
              register double r=0.0;
               for (k=0; k<n; k++){
                    r += a[i*n+k] * b[k*n+j];
              }
               c[i*n+j]=r;
          }
       }
       
       
        time0 = clock()-time0;
    
     max_diff_of_matrix = 0.000000000000000;
      
      
      for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
          for(j = 0; j<n;j++){
              if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix)
                   max_diff_of_matrix = fabs(c[i*n+j] - c1[i*n+j]);
              
          } 
      } 
   
      printf("Simple triple loop (jik) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %.16f \n",((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
     
      
      
       
/* jki – simple triple loop algorithm with simple single register reuse*/
        
         
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c[i] = 0.0;
            
        time0 = clock();
       
       for (j=0; j<n; j++){
         for (k=0; k<n; k++) {
              register double r=b[k*n+j];
               for (i=0; i<n; i++){
                    c[i*n+j]+= a[i*n+k] * r;
              }
               
          }
       }
       
        time0 = clock()-time0;
   
      
     max_diff_of_matrix = 0.000000000000000;
      
      
      for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
          for(j = 0; j<n;j++){
              if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix)
                   max_diff_of_matrix = fabs(c[i*n+j] - c1[i*n+j]);
              
          } 
      } 
   
      printf("Simple triple loop (jki) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %.16f \n",((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
      
      
      
       
/* kij – simple triple loop algorithm with simple single register reuse*/
         
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c[i] = 0.0;
            
        time0 = clock();
        
       for (k=0; k<n; k++){
         for (i=0; i<n; i++) {
              register double r=a[i*n+k];
               for (j=0; j<n; j++){
                    c[i*n+j]+= r * b[k*n+j];
              }
               
          }
       }
       
        time0 = clock()-time0;
   
     max_diff_of_matrix = 0.000000000000000;
      
      
      for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
          for(j = 0; j<n;j++){
              if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix)
                   max_diff_of_matrix = fabs(c[i*n+j] - c1[i*n+j]);
              
          } 
      } 
      
   
      printf("Simple triple loop (kij) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %.16f \n",((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
      
      
      
/* kji– simple triple loop algorithm with simple single register reuse*/
         
       for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
            c[i] = 0.0;
            
        time0 = clock();
        
       
       for (k=0; k<n; k++){
         for (j=0; j<n; j++) {
              register double r=b[k*n+j];
               for (i=0; i<n; i++){
                    c[i*n+j]+= a[i*n+k] * r;
              }
               
          }
       }
      
      
      
       time0 = clock()-time0;
   
      
     
max_diff_of_matrix = 0.000000000000000;
      
      
      for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
          for(j = 0; j<n;j++){
              if(fabs(c[i*n+j] - c1[i*n+j]) >= max_diff_of_matrix)
                   max_diff_of_matrix = fabs(c[i*n+j] - c1[i*n+j]);
              
          } 
      }
   
      printf("Simple triple loop (kji) algorithm went through %f seconds to complete running and the matrix had a  maximum difference of %.16f \n",((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
      

return 0;

}

