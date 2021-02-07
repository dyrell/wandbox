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
                 
        for(X x=2; x*x<=(vsize); x++)
        {
           while(vsize%x == 0) 
           {   
             if (lclprime(x)==true)
               {
                 std::cout<<"value of x is: "<<x<<"\n";   
                 lclVec.emplace_back(x); 
                 vsize /= x;
               }
               //vsize /= x;  
             }
           // vsize /= x;  
            
           }
            X resz = std::accumulate(std::begin(lclVec), std::end(lclVec), 1, std::multiplies<X>());
         std::cout<<"value of resz outside if is: "<<resz<<"\n";    
            if(resz == z)
              {  
               std::cout<<"value of resz is: "<<resz<<"\n";                
              } 
             return lclVec;
           }        
       }PrimeFactors;

int main()
{
    
   PrimeFactors lclPrmz;

    int q = 1739;
    std::vector<int> mainVec;

    mainVec = lclPrmz(q);

   for(auto x : mainVec)
    {
        if(x!=0)
         std::cout<<x<<"\n";
    }
}
