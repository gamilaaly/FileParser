#include <iostream>
#include "clara.hpp"
#include <string>
using namespace clara;

int main(int argc, char **argv)
{
    
    auto source1  = std::string{};
    auto source2 =std::string{};
    auto destination = std::string{};

    
    auto parser = Arg(source1, "source")("The path of the source file") |
                  Arg(source2, "source")("The path of the source file") |
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
            "source1:    " << source1 << std::endl <<
            "source2:    " << source2 << std::endl <<
            "destination:      " << destination  << std::endl;
      }

 
}
