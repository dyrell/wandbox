#include <iostream>
#include <type_traits>
#include <vector>
#include <numeric>
#include <functional> 
#include <algorithm>
#include <math.h>

typedef struct Prime
{
    template<class X> requires std::is_integral<X>::value    
    bool operator()(X z) const
     {
        bool lclBl = true;
        if ((z <= 1)||(z%2 == 0))
        {
           lclBl = false;
        }
       if (z == 2)
          {
           lclBl = true;
          }
        else
        {   
         for(X x=3; x<=sqrt(z); x+=2)
          {
           if(z%x == 0)
           {
               lclBl = false;
               break;
           }
           else
               continue;
         }
        }   
       return lclBl;
    };
 }IsPrime;

typedef struct PrimeFaq
{
    template<class X> requires std::is_integral<X>::value    
   std::vector<X> constexpr operator()(X z) const
     {
        X vsize = z;
        IsPrime lclprime;
        std::vector<X> lclVec; 
        X resz;
                 
       if(lclprime(z)==true)
       {
         lclVec.emplace_back(1);
         lclVec.emplace_back(z);
       }
       else
       {        
        for(X x=2; x*x<=(vsize); x++)
        {
           while(vsize%x == 0) 
           {   
             if (lclprime(x)==true)
               {
                 resz = std::accumulate(std::begin(lclVec), std::end(lclVec), 1, std::multiplies<X>());                
                if(resz < z) 
                 {   
                  lclVec.emplace_back(x);
                  }   
                  vsize /= x;                  
               }
               if (lclprime(vsize)==true)
               {
                 resz = std::accumulate(std::begin(lclVec), std::end(lclVec), 1, std::multiplies<X>());                
                 if (resz < z)
                 { 
                  lclVec.emplace_back(vsize);
                 }   
               }               
             }                     
           }
          }
          return lclVec;
           }        
       }PrimeFactors;

int main()
{
    
   PrimeFactors lclPrmz;
   IsPrime checkPrime;
        
    long int q = 844379265313;
    std::vector<long int> mainVec;
    
     std::function<long int(long int)>funcPrime = checkPrime;
    
    if (funcPrime(q))
        std::cout<<"The number: "<<q<<" is prime\n\n";
    else
        std::cout<<"The number: "<<q<<" ain't prime\n\n";

    mainVec = lclPrmz(q);

   std::cout<<"The prime factors of: "<<q<<" are:\n\n";   
   std::string delim = "";
   for(auto x : mainVec)
    {
         std::cout<<delim<<x;
         delim = ",\n";
    }
}
