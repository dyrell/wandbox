// This file is a "Insert values" in C++ language by GCC for wandbox.
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>
#include <ranges>

template<class T>
  class Compact
  {
   private:
    std::vector<T> vecVals;
   public:
      Compact()=default;
    
   template<typename... U>
    void insertFunc(U&&... v)
      {
       auto pushVals = [&](auto&& x){ vecVals.push_back(std::forward<decltype(x)>(x));};
      (..., pushVals(std::forward<U>(v)));
      }
  
 std::vector<T> getCompactVect(void)
    {
     std::vector<T> lclVec;
    int vSize = vecVals.size();
      std::cout << "What is the size:  " <<vecVals.size()<<std::endl;
     for(int x=0; x < vSize; x++)
     {
        // std::cout << "What is the vecVals[x]:  " <<vecVals[x]<<std::endl;
         lclVec.push_back(vecVals[x]);         
      }
        return(lclVec);
     }   
           
   void printOut()
   {
     for(auto z : vecVals)
        std::cout<<z<<"\n";
   }
  };  
//pointer Specialisation
template<class T>
  class Compact<T*>
  {
   private:
    std::vector<T*> vecVals;
   public:
      Compact()=default;
    
   template<typename... U>
    void insertFunc(U*&&... v)
      {
       auto pushVals = [&](auto&& x){ vecVals.push_back(std::forward<decltype(x)>(x));};
      (..., pushVals(std::forward<U*>(v)));
   }
   
std::vector<T> getCompactVect(void)
    {
     std::vector<T> lclVec;
     int vSize = vecVals.size();;
     
     for(int x=0; x<vSize; x++)
     {
       // std::cout << "What is the *vecVals[x]:  " <<*vecVals[x]<<std::endl;
        lclVec.push_back(*vecVals[x]);      
      }
        return(lclVec);
     } 
     
   void printOut()
   {
     for(auto z : vecVals)
        std::cout<<*z<<"\n";
   }
      
  };  

int main()
{
    std::cout << "Hello, time to insert!\n" << std::endl;
    Compact<int> mainComp;
    Compact<int*> ptrComp;
    std::vector<int> finalCompVect;
    std::vector<int> forCompVect;
    
   int a = -1, b = -2, c = -3, d = -4, e = -5, f= -6, g = -7, h = -8, i = -9;
    
    mainComp.insertFunc(a,b,c,d,e,f,g,h,i);
    ptrComp.insertFunc(&a,&b,&c,&d,&e,&f,&g,&h,&i);
    
    mainComp.printOut(); 
    std::cout << "\n\nHello, insert from pointer!\n" << std::endl;
    ptrComp.printOut(); 
    
    std::vector<int> mainCompVect = mainComp.getCompactVect();
    std::vector<int> ptrCompVect = ptrComp.getCompactVect();    
    
     std::cout << "\n\nOutput contents 1!\n" << std::endl; 
    for(auto z : mainCompVect)
    {
        std::cout<<z<<"\n";
    }
    
     std::cout << "\n\nOutput contents 2!\n" << std::endl;
     for(auto z : ptrCompVect)
     {
        std::cout<<z<<"\n";
     }
    finalCompVect.resize(ptrCompVect.size());
    forCompVect.resize(mainCompVect.size());
    
    std::transform(mainCompVect.begin(), mainCompVect.end(), ptrCompVect.begin(), finalCompVect.begin(), std::multiplies<int>());
    std::for_each(ptrCompVect.begin(), ptrCompVect.end(), [](int& x)mutable{x*=x;});
          
     std::cout << "\n\nDot product of both vectors is \n" << std::endl;
     for(auto z : finalCompVect)
     {
        std::cout<<z<<"\n";
     }
    
    std::cout << "\n\noutput from mainCompVect is \n" << std::endl;
     for(auto z : mainCompVect)
     {
        std::cout<<z<<"\n";
     }
    
     std::cout << "\n\noutput from ptrCompVect is \n" << std::endl;
     for(auto z : ptrCompVect)
     {
        std::cout<<z<<"\n";
     }
    
   
    return 0;
}
