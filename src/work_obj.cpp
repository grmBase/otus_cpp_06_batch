//------------------------------
#include <map>
#include <string>
#include <iostream>
#include <iomanip> //getline
#include <array>
#include <vector>
//------------------------------
#include "work_obj.h"
//------------------------------



int tst::t_work_obj::handle(size_t aun_batch_size)
{


  std::vector<std::string> vec_buffer;
  vec_buffer.reserve(aun_batch_size);

  std::string str_curr;
  int n_dyn_block_depth = 0;

  while(std::getline(std::cin, str_curr))
  {
    if (!str_curr.length()) {
      continue;
    };


    if (str_curr == "{") {

      // if we were in regular block:
      if (n_dyn_block_depth == 0) {
        logout("comming dyn block, so purgint regular one if any:");
        print_batch(vec_buffer);
        vec_buffer.clear();
      }

      n_dyn_block_depth++;
      logout("new dyn depth: " + std::to_string(n_dyn_block_depth));
      continue;
    }

    if (str_curr == "}") {
      if (n_dyn_block_depth >= 1) {
        n_dyn_block_depth--;
        logout("} detected. new depth: " + std::to_string(n_dyn_block_depth));
      }
      else {
        // todo: hope test input will come in correct order. Otherwise ask how to handle such case
        logout("some protocol violation detected. extra closing bracket. just ignored so far");
      }

      if (n_dyn_block_depth == 0) {
        logout("dyn block is finished. printing content: ");
        print_batch(vec_buffer);
        vec_buffer.clear();
      }

      continue;
    }

    vec_buffer.push_back(std::move(str_curr));

    if (n_dyn_block_depth == 0) {
      if (vec_buffer.size() >= aun_batch_size) {

        logout("<< regular batch ready ----------");
        print_batch(vec_buffer);
        vec_buffer.clear();
      }
    }
    
  };
  
  if (vec_buffer.size())
  {
    logout("<< eof detected. so purging final batch if any:");
    print_batch(vec_buffer);
    vec_buffer.clear();
  }


  return 0;
}
//------------------------------



void tst::t_work_obj::print_batch(const std::vector<std::string>& avec_buf)
{
  for (auto& curr : avec_buf)
  {
    std::cout << curr << std::endl;
  }
}
//------------------------------


void tst::t_work_obj::logout(const std::string_view& astr_view)
{
#ifdef DBG_LOGGING
  std::cout << astr_view << std::endl;
#endif
}
//------------------------------