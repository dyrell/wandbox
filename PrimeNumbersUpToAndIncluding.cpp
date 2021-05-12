// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <vector>
#include <memory>
template<class T>
struct CheckPrime
{
   bool operator ()(T& num)
   {
       bool ifPrime = true;
       
       if (num < 2) //exit immediately
        { 
         ifPrime = false;
         return ifPrime;
         }
       
        for(T x=2; x*x<=num; x++)
         {
            if(num%x==0)
             {
                ifPrime = false;
                break;
             }   
             else
                continue;
          }
         return ifPrime;
      }
  };

template<class T>
    class PrintElems
    {
        public:
            void operator()(T& qlm) const {std::cout<<qlm<<"\t";}
    };

int main()
{
    int size = 1000;
    std::vector<int> xVec;
    CheckPrime<int> whatPrimes;
        
    for(int z=0; z<size; z++)
    {
        if(whatPrimes(z) == true)
          xVec.push_back(z);
    }
    
    std::cout << "print out all prime numbers up to: "<<size<< std::endl;
    PrintElems<int> printThem;
   std::for_each(xVec.begin(), xVec.end(), printThem);
}
