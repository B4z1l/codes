#include<iostream>

using namespace std;

bool acc(){
    cout<<"Do you proceed? (y or n)\n";

    char ans = 0;
    cin>>ans;

    if(ans=='y'){
        return true;
    }
    return false;
}

bool acc3(){
    int tries = 1;
    while(tries<4){
        cout<<"Do you want to proceed (Y or N)?\n";
        char ans = 0;
        cin >> ans;

        switch(ans){
            case 'y':
            return true;
            case 'n':
            return false;
            default:
            cout << "Retry, nonsense written\n " << 3 - tries << " Attempt remaining\n ";
            ++tries;
        }
    }
    cout<<"You are so dumb that you failed 3 times to say something meaningful. I'll take it for a no!\n";
    return false;
}

int main(){
  //bool risp = acc();

  //cout << risp << "\n";

  bool risp3 = acc3();

  cout << risp3 << "\n";
}


