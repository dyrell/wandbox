// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <type_traits>
#include <vector>

typedef struct Prime
{
    template<class X> requires std::is_integral<X>::value    
    bool operator()(X z) const
     {
        bool lclBl = true;        
        for(X x=2; x<=(z/2); x++)
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

typedef struct PrimeFaq
{
    template<class X> requires std::is_integral<X>::value    
   std::vector<X> operator()(X z) const
     {
        X vsize = z/2;
        IsPrime lclprime;
        std::vector<X> lclVec;        
        for(X x=2; x<=vsize; x++)
        {
           if( (lclprime(x)==true) && (z%x == 0) )           
               lclVec.push_back(x);       
           else if( (lclprime(x)==false) && (z%x == 0) )
           {
               std::vector<X> ifVec;
               PrimeFaq ifPrmFaq;
               ifVec = ifPrmFaq(x);
               lclVec.insert(lclVec.end(), ifVec.begin(), ifVec.end());
            }
           else               
               lclVec.push_back(0); 
         }
        return lclVec;
      };
 }PrimeFactors;

int main()
{
    long x = 9698990;
    long z = 6909989;
    
    IsPrime lclIsprm;
    PrimeFactors lclPrmz;
    
    long q = 49;
    std::vector<long int> mainVec;
    
    mainVec = lclPrmz(q);
    
    auto tmpLmbd = []<typename T>requires std::is_integral<T>::value(T x, T z){ return(1<<(x ^ z)); };
    std::cout<<tmpLmbd(x,z)<<"\n";
    std::cout<<lclIsprm(q)<<"\n";
    
    for(auto x : mainVec)
    {
        if(x!=0)
         std::cout<<x<<"\n";
    }
}

// GCC reference:
//   https://gcc.gnu.org/

// C++ language references:
//   https://cppreference.com/
//   https://isocpp.org/
//   http://www.open-std.org/jtc1/sc22/wg21/

// Boost libraries references:
//   https://www.boost.org/doc/
