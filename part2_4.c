#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
  
       int n = 2048;
  
  
 
      double* a = (double*)calloc(sizeof(double),n*n);
 
      double* b = (double*)calloc(sizeof(double),n*n);
      double* c = (double*)calloc(sizeof(double),n*n);
      double* c1 = (double*)calloc(sizeof(double),n*n);
     
    
    
      
 
 
 
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
      
      
        int B = 256;  
    
         
        
          clock_t time0;
            
          time0 = clock();
     
          
          for (i = 0; i < n; i+=B){
             for (j = 0; j < n; j+=B){
                  for (k = 0; k < n; k+=B){
                      /* B x B mini matrix multiplications */
                      for (i1 = i; i1 < i+B; i1++){
                          for (j1 = j; j1 < j+B; j1++) {
                             register int t = i1*n+j1; register int tt = t+n; 
                            register double c00 = c[t]; register double c01 = c[t+1]; 
                            register double c10 = c[tt]; register double c11 = c[tt+1];


                               //register blocking
                             // register int t = i1*n+j1; register int tt = t+n; 
                              //register double c00 = c[t]; register double c01 = c[t+1];  
                              //register double c10 = c[tt]; register double c11 = c[tt+1];
                            for (k1 = k; k1 < k+B; k1++){
                                  
                                register int ta = i1*n+k1; register int tta = ta+n; register int tb = k1*n+j1; register int ttb = tb+n;
                                register double a00 = a[ta]; register double a01 = a[ta+1]; register double a10 = a[tta]; register double a11 = a[tta+1];
                                register double b00 = b[tb]; register double b01 = b[tb+1]; register double b10 = b[ttb]; register double b11 = b[ttb+1];
                                c00 += a00*b00 + a01*b10;
                                c01 += a00*b01 + a01*b11;
                                c10 += a10*b00 + a11*b10;
                                c11 += a10*b01 + a11*b11;

                                // register int ta = i1*n+k1; register int tta = ta+n; 
                                // register int tb = k1*n+j1; register int ttb = tb+n;
                                 //register double a00 = a[ta]; register double a10 = a[tta]; 
                                 //register double b00 = b[tb]; register double b01 = b[tb+1]; 
                
            //                     c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;
              //                   a00 = a[ta+1]; a10 = a[tta+1]; b00 = b[ttb]; b01 = b[ttb+1];
                //                 c00 += a00*b00 ; c01 += a00*b01 ; c10 += a10*b00 ; c11 += a10*b01 ;

                              }
                            c[t] = c00;
                             c[t+1] = c01;
                             c[tt] = c10;
                             c[tt+1] = c11;

                  //           c[t] = c00;
                    //         c[t+1] = c01;
                      //       c[tt] = c10;
                        //     c[tt+1] = c11;
 
                          }
                      }
                  }
              }
              
          }
     
          time0 = clock()-time0;
          
            
         
     
         
         printf("Blocked (B=%d) version (ijk) algorithm went through %f seconds to complete running\n", B,((float)time0)/CLOCKS_PER_SEC);
    
       
        
return 0;
}
