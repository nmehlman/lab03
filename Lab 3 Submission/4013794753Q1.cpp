#include "book.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

typedef vector<Book>::const_iterator bookIter;

string allLower(const string &s){
    string res;
    for(auto &c:s){
        res.push_back(tolower(c));
    }
    return res;
}

Book::Book(ifstream &in){
    
    string line;
    while(line.size()<=1 && in){
        getline(in,line); //Skip blanks
        if(!in){
            Bookid = -1;
            return;
        }
    }
    
    auto last_char = line.find_last_not_of(" ");
    line = line.substr(0,last_char+1); //Remove blank spaces at end
    bookName = line; //Read name

    getline(in,line); //Read ID
    Bookid = stoi(line);

    getline(in,line); 
    last_char = line.find_last_not_of(" ");
    line = line.substr(0,last_char+1); //Remove blank spaces at end
    bookAuthor = line; //Read author

    getline(in,line); //Read year
    auto loc = line.rfind("/");
    YearofPub = stoi(line.substr(loc+1));

    getline(in,line); //Read price
    price = stod(line.substr(1));

    getline(in,line);//Read status
    status = (line == "Available")? true:false;   

}

ostream &Book::Print(ostream &out) const{
    
    out<<bookName<<endl<<"By "<<bookAuthor<<endl;
    out<<Bookid<<endl;
    out<<"Published in "<<YearofPub<<endl;
    out<<"Price is $"<<price<<endl;
    out<<"This title is "<<((status == true)? "avaliable.":"not avaliable.")<<endl;

    return out;

}

bookIter findBook(vector<Book> const &vec, string name,bool print=false){
    name = allLower(name);
    bookIter result = vec.cbegin();
    while (result<vec.end()&& allLower(result->getName()) != name){
        result++;
    }
    if(result==vec.end() && print)
        cerr<<"No book found with title \""<<name<<"\""<<endl;
    else if(print)
        result->Print(cout)<<endl;
    return result;
     
    

}

bookIter findBook(const vector<Book> &vec, int id, bool print=false){

    bookIter result = vec.cbegin();
    while (result<vec.cend()&&result->getID() != id){
        result++;
    }
    if(result==vec.cend()&&print)
        cerr<<"No book found with ID "<<id<<"."<<endl;
    else if(print)
        result->Print(cout)<<endl;
    return result;    

}

vector<Book> findByAuthor(const vector<Book> &vec, string author, bool print=false){

    author = allLower(author);
    vector<Book> result;
    for(auto &i:vec){
        if(allLower(i.getAuthor()) == author){
            result.push_back(i);
            if(print)
                i.Print(cout)<<endl;
        }
    }
    if(result.size()==0 && print)
        cerr<<"No book found by "<<author<<"."<<endl;

    return result;
}

int main(){

    //Read books from txt file:
    ifstream in("inputList.txt");
    vector<Book> collection;
    while(true){
        Book temp(in);
        if(temp.getID()==-1)
            break;
        else
            collection.push_back(temp);  
    }
    in.close();

    
    string search;
    while(true){ //Search loop
        
        //Read search term
        cout<<"Enter search query, or enter 'q' to quit: ";
        getline(cin,search);
        if(search=="q")
            return 0;
        cout<<endl;

        //Search by title:
        auto res1 = findBook(collection,search);
        if(res1!=collection.cend()){
            cout<<"Result for title "<<search<<endl<<endl;
            res1->Print(cout)<<endl;
            continue;
        }
        //Search by author:
        vector<Book> res2 = findByAuthor(collection,search);
        if(res2.size()>0){
            cout<<"Books by "<<search<<":"<<endl<<endl;
            for(auto i:res2)
                i.Print(cout)<<endl;
            continue;
        }
        
        //Search by ID:
        if(search.find_first_not_of("0123456789")>=search.size()){
            int id = stoi(search);
            bookIter res3 = findBook(collection,id);
            if(res3!=(collection.cend())){
                cout<<"Result for ID "<<search<<":"<<endl<<endl;
                res3->Print(cout)<<endl;
                continue;
            }
        } 

        cout<<"No result found for \""<<search<<"\""<<endl<<endl;
    }

    return 0;
}