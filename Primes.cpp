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
        
    int q = 841;
    std::vector<int> mainVec;

    mainVec = lclPrmz(q);

   std::cout<<"The prime factors of: "<<q<<" are:\n\n";   
   std::string delim = "";
   for(auto x : mainVec)
    {
         std::cout<<delim<<x;
         delim = ",\n";
    }
}
