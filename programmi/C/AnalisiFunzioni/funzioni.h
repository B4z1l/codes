
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.1415926536




double radice(double x, double n){
 double y;
   y = pow(x, 1./n);
 return y;
}

double fact(double x){
 if(x == 0){
  return 1.;
 } else {
  return x * (x-1.);
 }
}


int sgn(double y){
  int l;
  if(y >= 0){
    l = 1;
  } else if(y < 0){
    l = -1;
  } else if(y == 0){
    l = 0;
  }
  return l;
}


double f(double x){
    return log((sqrt(x*x-1)+x*x+1)/(x*x+sin(x)+1));

}


double incr(double x, double ddx){
 double df;
  df = (f(x+ddx)-f(x))/ddx;
 return df;
}



