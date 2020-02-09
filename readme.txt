Nick Mehlman
4013794753

Fot this lab, I created the number class, with the two functions. I also created the numberSet class, and elected
to use a constructor that took a string parameter, so as to facilite reading from the file. The check independence
function uses a simple nested for loop test of all element pairs. My main function simply reads the file line by 
line and passes each line to a numberSet constructor. It then uses nested for loops to call check independece for
all pairs of sets, and writes the result to the output.txt file

Please compile using '-std=c++11'.

Sources:

1. https://en.cppreference.com/w/cpp/language/copy_assignment
Used as a reference for redinfining the copy assignment operator.

2. https://docs.microsoft.com/en-us/cpp/cpp/destructors-cpp?view=vs-2019
Used to learn how to define a class destructor.

3. https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html
Used as a reference for the proper use of dynamic memory and functions

4. http://courses.washington.edu/css501/zander/Notes/dynamic
Used as a refernce for the proper treatment of classes than allocate dynamic memory

5. https://www.tutorialspoint.com/cplusplus/cpp_copy_constructor.htm
Used as a reference for defining copy contructors

6. https://en.cppreference.com/w/cpp/language/move_assignment
Used as a reference fo defining move operators