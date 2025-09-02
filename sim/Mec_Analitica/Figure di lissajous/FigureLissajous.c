/************************************
********LISSAJOUS FIGURES **********
************************************/
#include<stdio.h>
#include<math.h>
#define M_PI 3.14152965
double x(double theta){
    return sin(theta);
}
double y(double theta, double A,double n, double delta){
    return A*sin(n*theta+delta);
}

main(){
    double theta;
    FILE *fp=NULL;
    double A,n,delta;
    fp=fopen("lissajous.txt","w");
    /*Loop to calculate and store data-points*/
    for(theta=0;theta<=500*M_PI;theta=theta+0.01){
        /*Change A, n or delta here*/
        A=1;
        n=M_PI;
        delta=M_PI/4;
        fprintf(fp,"%lf\t%lf\n",x(theta),y(theta,A,n,delta));
    }
}