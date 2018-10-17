#include<stdio.h>
 #include<stdlib.h>
 #include<time.h>

  int main(){
  
       int n = 256;
  
  
 
      double* a = (double*)calloc(sizeof(double),n*n);
 
      double* b = (double*)calloc(sizeof(double),n*n);
      double* c = (double*)calloc(sizeof(double),n*n);
      double* c1 = (double*)calloc(sizeof(double),n*n);
    
    
      double max_diff_of_matrix = 0.0;
      
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
 

    clock_t time0;
 
/* ijk – blocked version algorithm*/
    printf("\nBlocked Version with differeing block size:\n\n");
    
        int B = 256; 
    
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
          
          for (i = 0; i < n; i+=B){
             for (j = 0; j < n; j+=B){
                  for (k = 0; k < n; k+=B){
                      /* B x B mini matrix multiplications */
                      for (i1 = i; i1 < i+B; i1++){
                          for (j1 = j; j1 < j+B; j1++) {
                              register double r=c[i1*n+j1];
                              for (k1 = k; k1 < k+B; k1++){
                                 c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                              }
                              
                          }
                      }
                  }
              }
              
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked (B=%d) version (ijk) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n", B,((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
    
    /* ikj – blocked version algorithm*/
      
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
         
          for (i = 0; i < n; i+=B){
             for (k = 0; k < n; k+=B){
                  for (j = 0; j < n; j+=B){
                      /* B x B mini matrix multiplications */
                      for (i1 = i; i1 < i+B; i1++){
                          for (k1 = k; k1 < k+B; k1++) {
                              register double r=a[i1*n+k1];
                              for (j1 = j; j1 < j+B; j1++){
                                  c[i1*n+j1] += r*b[k1*n + j1];
                              }
                              
                          }
                      }
                  }
              }
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked ((B=%d) version (ikj) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n",B, ((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
    
    
    
    /* jik – blocked version algorithm*/
      
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
          
          for (j = 0; j < n; j+=B){
             for (i = 0; i < n; i+=B){
                  for (k = 0; k < n; k+=B){
                      /* B x B mini matrix multiplications */
                      for (j1 = j; j1 < j+B; j1++){
                          for (i1 = i; i1 < i+B; i1++) {
                              register double r=0.0;
                              for (k1 = k; k1 < k+B; k1++){
                                  c[i1*n+j1] += a[i1*n + k1]*b[k1*n+j1];
                              }
                              
                          }
                      }
                  }
              }
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked (B=%d) version (jik) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n",B, ((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
    
    
    
    /* jki – blocked version algorithm*/
      
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
         
          for (j = 0; j < n; j+=B){
             for (k = 0; k < n; k+=B){
                  for (i = 0; i < n; i+=B){
                      /* B x B mini matrix multiplications */
                      for (j1 = j; j1 < j+B; j1++){
                          for (k1 = k; k1 < k+B; k1++) {
                              register double r=b[k1*n+j1];
                              for (i1 = i; i1 < i+B; i1++){
                                  c[i1*n+j1]+= a[i1*n + k1]*r;
                              }
                              
                          }
                      }
                  }
              }
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked ((B=%d))version (jki) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n",B,((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
    
    
    
    /* kij – blocked version algorithm*/
      
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
        
          for (k = 0; k < n; k+=B){
             for (i = 0; i < n; i+=B){
                  for (j = 0; j < n; j+=B){
                      /* B x B mini matrix multiplications */
                      for (k1 = k; k1 < k+B; k1++){
                          for (i1 = i; i1 < i+B; i1++) {
                              register double r=a[i1*n+k1];
                              for (j1 = j; j1 < j+B; j1++){
                                  c[i1*n+j1]+= r*b[k1*n + j1];
                              }
                              
                          }
                      }
                  }
              }
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked (B=%d) version (kij) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n",B,((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
    
    
    /* kji – blocked version algorithm*/
      
          for(i = 0; i < n*n; i++) //clear old c[] values because i'm reusing the matrix
                c[i] = 0.0;
                
          time0 = clock();
     
          for (k = 0; k < n; k+=B){
             for (j = 0; j < n; j+=B){
                  for (i = 0; i < n; i+=B){
                      /* B x B mini matrix multiplications */
                      for (k1 = k; k1 < k+B; k1++){
                          for (j1 = j; j1 < j+B; j1++) {
                              register double r=b[k1*n+j1];
                              for (i1 = i; i1 < i+B; i1++){
                                  c[i1*n+j1] += a[i1*n + k1]*r;
                              }
                              
                          }
                      }
                  }
              }
          }
     
          time0 = clock()-time0;
          
          max_diff_of_matrix = 0.0;
          min = 99999.0;
          max = 0.0;
          
          for(i =0; i<n;i++){ //this block is to determine correctness by finding the maximum difference in each matrix(should all be the same because w    e dont change a &b
              for(j = 0; j<n;j++){
                  if(c[i*n+j] < min)
                       min = c[i*n+j];
                  if(c[i*n+j] > max)
                       max= c[i*n+j];
              }     
          }
            
          max_diff_of_matrix = max - min;
     
     
         
         printf("Blocked (B=%d) version (kji) algorithm went through %f seconds to complete running and the matrix had a  maximum difference  of %f \n\n",B, ((float)time0)/CLOCKS_PER_SEC, max_diff_of_matrix);
    
  

return 0;

}

