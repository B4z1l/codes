
#include<iostream>

//int main()
//{
//    std::cout<<"Hello World!\n";
//}



//namespace ???
using namespace std;

//funzioni
//--------------------------------------------------------
double square(double x){
    return x*x;
}

void p_sq(double x){                                          // in C si ha in stdlib: printf("The square of %lf is %lf", x, square(x));
    cout<<"The square of "<<x<<" is "<<square(x)<<"\n";
}
//--------------------------------------------------------

//main

int main(){
    p_sq(1.234);
}

