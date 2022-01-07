//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
#include "work_obj.h"
//-----------------------------------------------------------------------------



int main(int argc, char* argv[])
{

  if (argc < 2) {
    std::cout << "Wrong number of arguments. Use: this_utility.exe batch_size" << std::endl;
    return -33;
  }

  size_t un_batch_size = atoi(argv[1]);




  tst::t_work_obj workObj;

  try 
  {
    int nResult = workObj.handle(un_batch_size);
    if (nResult) {
      std::cout << "Error in handle(), code: " << nResult << std::endl;
      return nResult;
    }
  }
  catch(const std::exception& exc)
  {
    std::cout << "Exception caught. Info: " << exc.what() << std::endl;
    return -33;
  }



  return 0;
}