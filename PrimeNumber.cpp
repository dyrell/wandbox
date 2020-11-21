// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <type_traits>


typedef struct Prime
{
    template<class X> requires std::is_integral<X>::value    
    bool operator()(X z) const
     {
        bool lclBl = true;        
        for(X x=2; x<(z/2); x++)
        {
           if(z%x == 0)
           {
               lclBl = false;
               break;
           }
           else
               continue;
         }
        return lclBl;
    };
 }IsPrime;

int main()
{
    long x = 9698990;
    long z = 6909989;
    
    IsPrime lclIsprm;
    long q = 241;
    
    
    
    auto tmpLmbd = []<typename T>requires std::is_integral<T>::value(T x, T z){ return(1<<(x ^ z)); };
    std::cout<<tmpLmbd(x,z)<<"\n";
    std::cout<<lclIsprm(q)<<"\n";
}

// GCC reference:
//   https://gcc.gnu.org/

// C++ language references:
//   https://cppreference.com/
//   https://isocpp.org/
//   http://www.open-std.org/jtc1/sc22/wg21/

// Boost libraries references:
//   https://www.boost.org/doc/
