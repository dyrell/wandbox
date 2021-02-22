// This file is a "Insert values" in C++ language by GCC for wandbox.
#include <iostream>
#include <vector>

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
      
   void printOut()
   {
     for(auto z : vecVals)
        std::cout<<z<<"\n";
   }
  };  

int main()
{
    std::cout << "Hello, time to insert!\n" << std::endl;
    Compact<int> mainComp;
    
    int a = -1, b = -2, c = -3, d = -4, e = -5, f= -6, g = -7, h = -8, i = -9;
    
    mainComp.insertFunc(0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f,g,h,i);
    mainComp.printOut(); 
    return 0;
}

