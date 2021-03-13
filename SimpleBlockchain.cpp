// This file is a simple demonstration on how blockchain works
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>

class Block
    {
        private:
            std::string transaction;
            std::size_t hashTrans;
        public:
            Block(const std::string& trans) : transaction(trans) 
               {
                std::hash<std::string> cnstrctHsh;
                hashTrans = cnstrctHsh(transaction);
               }
            Block(const std::string& trans, const Block& blck) : transaction(trans) 
               {
                std::hash<std::string> cnstrctHsh;
                hashTrans = (cnstrctHsh(transaction))^blck.getHash();
               }
            std::size_t getHash() const
              {
                return(hashTrans);
              }
            void printHash(void) 
             {
                std::cout<<"The hash number is: "<<hashTrans<<std::endl;
             }
       };


int main()
{
    std::cout << "Hello, Wandbox time to blockchain" << std::endl;
    
    std::string trans0 {"blah0"};
    std::string trans1 {"blah1"};
    std::string trans2 {"blah2"};
    std::string trans3 {"blah3"};
    
   Block *gen = new Block(trans0);
   Block *blck1 = new Block(trans1, *gen); 
   Block *blck2 = new Block(trans2, *blck1); 
   Block *blck3 = new Block(trans3, *blck2);
    
   (*blck3).printHash();
   
   delete gen;
   delete blck1;
   delete blck2;
   delete blck3;
     
}


