#include <fstream>
#ifndef EE355_BOOK_CLASS_H
#define EE355_BOOK_CLASS_H


class Book{

    private:
    int Bookid;
    std::string bookName;
    std::string bookAuthor;
    int YearofPub;
    double price;
    bool status;

    public:
    Book() = default; //Default constructor
    Book(std::ifstream &in); //Constuctor from file
    std::ostream &Print(std::ostream &out) const; //Print book  
    int getID()const {return Bookid;} //Get ID
    std::string getName()const{return bookName;} //Get name
    std::string getAuthor()const{return bookAuthor;} //Get name

};

#endif //EE355_BOOK_CLASS_H