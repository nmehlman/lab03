#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

//Number class:
class Number{

    public:
    void set_value(int i){value = i;}
    int get_value(){return value;}

    private:
    int value;

};

//NumberSet class:
class NumberSet{

    friend bool check_independence(NumberSet n); //Allow check_independece to access private members
    friend void Print(NumberSet &); //Allow Print to access private members

    public:
    //Default constructor:
    NumberSet():size(0),numbers(nullptr){}
    
    //Constructor:
    NumberSet(int sz,const string &s): size(sz){ 
        
        numbers = new Number[size]; //Allocate memory for Number array
        
        istringstream in(s);
        int i, count = 0;
        while(in>>i)
        {
            numbers[count].set_value(i); //Read values in Number array
            count++;
        }
    }

    //Copy construcotr:
    NumberSet(const NumberSet &n): size(n.size){ 
        
        numbers = new Number[size]; //Allocate memory for Number array
        
        numbers = new Number[size];
            for(int i=0;i<size;i++){
                numbers[i] = n.numbers[i];
            }

    }

    //Move constructor:
    NumberSet(NumberSet &&n){
            size = n.size;
            delete []numbers; 
            numbers = n.numbers;
            n.numbers=nullptr;
    }

    //Destructor:
    ~NumberSet(){
        delete[] numbers;
    }
    
    //Copy assignment operator
    NumberSet &operator = (NumberSet n){
            size = n.size;
            numbers = new Number[size];
            for(int i=0;i<size;i++){
                numbers[i] = n.numbers[i];
            }
            return *this;
    }

    //Move operator
    NumberSet &operator = (NumberSet &&n){
            size = n.size;
            delete []numbers; 
            numbers = n.numbers;
            n.numbers=nullptr;
            return *this;
    }

    //Check for independence with another set
    bool check_independence(NumberSet n){
        for(int i=0;i<size;i++){
            for(int k=0;k<n.size;k++){
                if(numbers[i].get_value()==n.numbers[k].get_value())
                    return false;
            }
        }
        return true;
    }

    private:
    int size;
    Number *numbers;

};

//Print NumberSet Objcet:
void Print(NumberSet &n){
    for(int i=0;i<n.size;i++){
        cout<<n.numbers[i].get_value()<<" ";
    }
    cout<<endl;
}

int main(){

    ifstream in_file("input.txt");
    
    string line;
    int num_subsets,subset_size,cnt=0;
    
    getline(in_file,line); //Read number of subsets in file
    num_subsets = stoi(line);
    NumberSet *sub_sets = new NumberSet[num_subsets]; //Allocate array of NumberSets to hold subsets
    
    //Read input file
    while(in_file && cnt<num_subsets){
        getline(in_file,line); //Read subset size
        if(in_file && !line.empty()) //Make sure line is not empty
            subset_size = stoi(line);
        
        getline(in_file,line); //Read subset elements
        if(in_file && !line.empty()){ //Make sure line is not empty
            NumberSet temp(subset_size,line);
            sub_sets[cnt]= temp;
        }
        cnt++; 
    }

    //Test for independence:
    bool independent = false;
    for(int i=0;i<num_subsets;i++){
        for(int k=i+1;k<num_subsets;k++){
            if(sub_sets[i].check_independence(sub_sets[k])){
                independent = true;
            }
        }
    }

    //Write results to file:
    ofstream out_file("output.txt");
    out_file<<((independent) ? "Y":"N");
    
    return 0;
}