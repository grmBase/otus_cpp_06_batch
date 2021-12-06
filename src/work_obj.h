//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <string>
#include <string_view>
#include <vector>
//---------------------------------------------------------------------------

// 
#define DBG_LOGGING


namespace tst
{

  class t_work_obj
  {
  public:

    static int handle(size_t aun_batch_size);
  private:
    static void print_batch(const std::vector<std::string>& avec_buf);

    static void logout(const std::string_view& astr_view);
  };
  //---------------------------------------------------------------------------
}
