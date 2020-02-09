#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const int K = 10, M=20;

//Number class:
class Number{

    public:
    void set_value(int i){value = i;}
    int get_value() const{return value;}

    private:
    int value;

};

//NumberSet class:
class NumberSet{

    friend bool check_independence(NumberSet n); //Allow check_independece to access private members
    friend void Print(NumberSet &); //Allow Print to access private members

    public:
    //Default constructor:
    NumberSet()=default;
    
    //Constructor:
    NumberSet(const string &s){ 

        istringstream in(s);
        int i, count = 0;
        while(count<K && in>>i)
        {
            numbers[count].set_value(i); //Read values in Number array
            count++;
        }
    }

    //Check for independence with another set
    bool check_independence(NumberSet n){
        for(int i=0;i<K;i++){
            for(int k=0;k<K;k++){
                if(numbers[i].get_value()==n.numbers[k].get_value())
                    return false;
            }
        }
        return true;
    }

    private:
    Number numbers[K];

};

//Print NumberSet Objcet:
void Print(NumberSet &n){
    for(int i=0;i<K;i++){
        cout<<n.numbers[i].get_value()<<" ";
    }
    cout<<endl;
}

int main(){

    ifstream in_file("input.txt");
    
    string line;
    NumberSet sub_sets[M];
    int cnt=0;

    //Read input file
    while(in_file && cnt<M){
        getline(in_file,line); //Read subset elements
        if(in_file && !line.empty()){ //Make sure line is not empty
            sub_sets[cnt] = NumberSet(line); //Read in subsets
        }
        cnt++; 
    }

    //Test for independence:
    bool independent = true;
    for(int i=0;i<M && independent;i++){
        for(int k=i+1;k<M && independent;k++){
            if(!sub_sets[i].check_independence(sub_sets[k])){
                independent = false;
            }
        }
    }

    //Write results to file:
    ofstream out_file("output.txt");
    out_file<<((independent) ? "Y":"N");
    
    return 0;
}