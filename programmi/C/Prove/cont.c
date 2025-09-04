#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(void) {


double  x = 41.93;

x = x /2.;
x = 21; //distanza tra due zeri  

for(int i = 0; i < 14; i++){//calcolatore dei doppi intervalli per i massimi del file Data_exp_5.ipynb

  //printf("%lf,", x * i * 4 + x );
 //printf("%d, ", 0);
  
}


for(int i = 0; i < 24; i++){//stesso ma per gli zeri


  //printf("%lf, ",2 * x * i );
}



for(int i = 0; i < 12; i++){//calcolatore dei doppi intervalli per i minimi del file Data_exp_5.ipynb

  printf("%lf,", x + x/2 +2*x*i  );

  
}
    return 0;

}
