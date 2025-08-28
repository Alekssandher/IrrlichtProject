#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>
#include "../headers/perfomance_infos.hpp"

void print_memory_usage()
{
    std::ifstream statm("/proc/self/statm");

    size_t size {};
    size_t resident {};

    statm >> size >> resident;

    size_t page_size_kb = static_cast<size_t>(sysconf(_SC_PAGE_SIZE) / 1024);

    size_t mem_usage { resident * page_size_kb};

    std::cout << "RAM: " << mem_usage << " KB\n";

    return;
}

