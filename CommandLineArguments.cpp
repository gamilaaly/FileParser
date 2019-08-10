#include <iostream>
#include "clara.hpp"
using namespace std;

// argc is counter for the arguments, including the application-name.
// argv is array of strings representing the arguments.
int main(int argc, char **argv)
{
    int width = 0;
    auto ignore =1;
    
    using namespace clara;
    auto parser = Opt(width, "width")
                   ["-w"]["--width"]("How wide should it be?") |
               Opt(ignore, "ignore")
                   ["-i"]["--ignore"]("Ignore conflicts") ;

    auto result = parser.parse(Args(argc, argv));
      if (!result)
      {
         std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
         return 1;
      }

  
    cout << width << endl;
    cout << ignore <<endl;
}
