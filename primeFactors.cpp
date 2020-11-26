#include <iostream>
#include <type_traits>
#include <vector>
#include <numeric>
#include <functional> 
#include <algorithm>

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
        if (z==1)
            lclBl = false;
        return lclBl;
    };
 }IsPrime;

typedef struct PrimeFaq
{
    template<class X> requires std::is_integral<X>::value    
   std::vector<X> operator()(X z) const
     {
        X vsize = z;
        IsPrime lclprime;
        std::vector<X> lclVec; 
        
          
        for(X x=2; x<=(vsize); x++)
        {
           if( (lclprime(x)==true) && (z%x == 0) )  
           {   
             if(x > 1)
               {
               //std::cout<<"value of x is: "<<x<<"\n";   
               lclVec.emplace_back(x); 
               X q;
               q = (z/x);
               //for(X y=q; y<vsize; y++)
               if (q == 1)
                break;
               else
               {
               //std::cout<<"value of q is: "<<q<<"\n";    
               std::vector<X> ifVec;
               PrimeFaq ifPrmFaq;
               ifVec = ifPrmFaq(q);                  
               lclVec.insert(lclVec.end(), ifVec.begin(), ifVec.end()); 
               X resz = std::accumulate(std::begin(lclVec), std::end(lclVec), 1, std::multiplies<X>());
               if(resz == vsize)
               {  
                   std::cout<<"value of resz is: "<<resz<<"\n"; 
                   break;
               }   
                }               
               //continue;
               }
              }
             } 
        //}
        return lclVec;
      };
 }PrimeFactors;

int main()
{
    long x = 9698990;
    long z = 6909989;

    IsPrime lclIsprm;
    PrimeFactors lclPrmz;

   int q = 4096;
    std::vector<int> mainVec;

    mainVec = lclPrmz(q);

    auto tmpLmbd = []<typename T>requires std::is_integral<T>::value(T x, T z){ return(1<<(x ^ z)); };
    std::cout<<tmpLmbd(x,z)<<"\n";
    std::cout<<lclIsprm(q)<<"\n";
    
    for(auto x : mainVec)
    {
       // if(x!=0)
         std::cout<<x<<"\n";
    }
}
