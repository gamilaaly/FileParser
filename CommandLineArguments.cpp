#include <iostream>
#include "clara.hpp"
#include <string>
using namespace clara;

int main(int argc, char **argv)
{
    
    auto source  = std::string{};
    auto destination = std::string{};

    
    auto parser = Arg(source, "source")("The path of the source file") |
                  Arg(destination, "destination")("The path to the output file") ;

    auto result = parser.parse(Args(argc, argv));
      if (!result)
      {
         std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
         return 1;
      }
      else 
      {
         std::cout <<
            "source:    " << source << std::endl <<
            "destination:      " << destination  << std::endl;
      }

 
}
