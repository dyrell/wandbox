// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <vector>
#include <memory>

template<class T>
 class Add
 {
   private:
     T x;
   public:
     Add(T inx):x(inx){}
     void operator()(T& q) const {q += x;}
   };
 
template<class T>
    class PrintElems
    {
        public:
            void operator()(T& qlm) const {std::cout<<qlm<<" ";}
    };

int main()
{
    int size = 5;
    std::vector<int> xVec;
    for(int z=0; z<size; z++)
        xVec.push_back(z);
    
    std::cout << "Time to print out whats in the vector!" << std::endl;
    PrintElems<int> printThem;
    std::unique_ptr<Add<int>> uqadd = std::make_unique<Add<int>>(1000);
        
    std::for_each(xVec.begin(), xVec.end(), *uqadd);
    std::for_each(xVec.begin(), xVec.end(), printThem);
}

