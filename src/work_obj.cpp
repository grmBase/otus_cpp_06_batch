//------------------------------
#include <string>
#include <iostream>
#include <fstream> // пишем в файл
#include <iomanip> //getline
#include <vector>
#include <chrono> // засекаем время
//------------------------------
#include "work_obj.h"
//------------------------------


auto tst::t_work_obj::get_tick_count()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}
//------------------------------


int tst::t_work_obj::handle(size_t aun_batch_size)
{

  // Текущий файл, куда будем дублировать вывод:
  std::ofstream write_file;


  std::vector<std::string> vec_buffer;

  // probably we'll have at least such number in row:
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

        print_batch(vec_buffer, write_file);
        vec_buffer.clear();

        //logout("creating new file: " + std::to_string(get_tick_count()));
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
        print_batch(vec_buffer, write_file);
        vec_buffer.clear();
      }

      continue;
    }



    // если это первая запись, то закроем старый файл, откроем новый:
    if(vec_buffer.size() == 0) {

      if (write_file.is_open()) {
        write_file.close();
      }

      const std::string c_str_file_name = std::to_string(get_tick_count()) + ".txt";
      write_file.open(c_str_file_name);
      if (!write_file.is_open()) {
        std::cout << "Error opening file for writing: " << c_str_file_name << std::endl;
        return -33;
      }
    }
    vec_buffer.push_back(std::move(str_curr));

    if (n_dyn_block_depth == 0) {
      if (vec_buffer.size() >= aun_batch_size) {

        logout("<< regular batch ready. purging:");
        print_batch(vec_buffer, write_file);
        vec_buffer.clear();
      }
    }
    
  };
  
  if (vec_buffer.size())
  {
    logout("<< eof detected. so purging final batch if any:");
    print_batch(vec_buffer, write_file);
    vec_buffer.clear();
  }


  return 0;
}
//------------------------------



void tst::t_work_obj::print_batch(const std::vector<std::string>& avec_buf, std::ofstream& a_write_file)
{
  for (auto& curr : avec_buf)
  {
    std::cout << curr << std::endl;
    a_write_file << curr << std::endl;
  }

  a_write_file.close();
}
//------------------------------


void tst::t_work_obj::logout(const std::string_view& astr_view)
{
#ifdef DBG_LOGGING
  std::cout << astr_view << std::endl;
#endif
}
//------------------------------


