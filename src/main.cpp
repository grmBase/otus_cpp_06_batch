//#include <cstdio>
#include <iostream>
//-----------------------------------------------------------------------------
#include "work_obj.h"
//-----------------------------------------------------------------------------



int main()
{

  int n_batch_size = 0;
  std::cin >> n_batch_size;

  tst::t_work_obj workObj;


  int nResult = workObj.handle(n_batch_size);
  if (nResult) {
    std::cout << "Error in handle(), code: " << nResult << std::endl;
    return nResult;
  }

  return 0;
}