// This file is a simple demonstration on how blockchain works
#include <iostream>
#include <cassert>
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
                return(this->hashTrans);
              }
          void printHash(void) 
             {
                std::cout<<"The hash number is: "<<hashTrans<<std::endl;
             }
       };

int main()
{
    std::cout << "Hello, Wandbox time to blockchain" << std::endl;
    
    std::string trans0 {"block0"};
    std::string trans1 {"block1"};
    std::string trans2 {"block2"};
    std::string trans3 {"block3"};
           
    std::unique_ptr<Block> uPtr0 = std::make_unique<Block>(trans0);
    std::unique_ptr<Block> uPtr1 = std::make_unique<Block>(trans1, *uPtr0) ;
    std::unique_ptr<Block> uPtr2 = std::make_unique<Block>(trans2, *uPtr1);
    std::unique_ptr<Block> uPtr3 = std::make_unique<Block>(trans3, *uPtr2);
    
   (*uPtr3).printHash();
   
     
}
