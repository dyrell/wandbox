// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <cstdlib>
#include <memory>

template<typename T>
concept Int = std::is_integral_v<T>;

template<Int T>
class CpMv
{
    private:
        T anythng;
    public:
        CpMv() : anythng(0){}
         CpMv(const T& anythng) : anythng(anythng){std::cout<<"\nIn copy constructor\n";}
        CpMv(const CpMv& cpmv) : anythng(cpmv.getAnything()){std::cout<<"\nIn copy constructor\n";}
        CpMv(CpMv&& cpmv) : anythng(std::move(cpmv.getAnything())){std::cout<<"\nIn move constructor\n";}
        void squareAnything(void) {anythng *= anythng;}
        void orShiftAnything(void) {anythng |= anythng<<2;}  
        T getAnything() const {return anythng;}
    };
 
template<Int T>
CpMv<T> getWhatever(T zx)
   { 
    CpMv<T> gtObj(zx);
    gtObj.squareAnything();
    gtObj.orShiftAnything();
     return (gtObj);  
   }

int main()
{
    std::cout << "Hello, Wandbox!" << std::endl;
    
    int zx = 47;
    
    CpMv<int> mnObj1(zx);
    CpMv<int> mnObj2(mnObj1);
    CpMv<int> mnObj3(getWhatever(zx));
    std::cout<<"\nget anything is "<<mnObj3.getAnything()<<std::endl;

    float q = 144.38053;;
    CpMv<float> mnObj4(q);
    
    mnObj4.squareAnything(); 
}


