/**
 *  @file logger.cpp
 *  @copyright defined in eosio/LICENSE.txt
 */

#include <iomanip>  // std::setw
#include <iostream> // std::cout|flush

#include "logger.hpp"

logger::logger()
   : _data_file{(boost::filesystem::current_path() /= std::string{"/data.csv"}).string()}
{
   _tps.reserve(1000);
   _ram_usage.reserve(1000);
   _cpu_load.reserve(1000);
}

void logger::print_progress(size_t n, size_t m) {
   if (m == 0) {
      std::cout << '[' << std::setw(3) << 0 << "%]\n";
      return;
   }
   std::cout << '[' << std::setw(3) << (static_cast<size_t>((static_cast<double>(n)/m)*100.0)) << "%]\n";
}

void logger::flush_all() {
   for (size_t i{}; i < _tps.size(); ++i) {
      _data_file << std::setw(10) << _tps[i]            << '\t';
      _data_file << std::setw(10) << _total_vm_usage[i] << '\n';
   }
}

void logger::log_cpu_load(const size_t& n) {
    _cpu_load.push_back(n);
}

void logger::log_ram_usage(const size_t& n) {
    _ram_usage.push_back(n);
}

void logger::log_total_vm_usage(const size_t& n) {
    _total_vm_usage.push_back(n);
}

void logger::log_tps(const size_t& n) {
    _tps.push_back(n);
}
