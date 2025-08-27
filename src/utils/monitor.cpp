#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>

size_t get_memory_usage()
{
    std::ifstream statm("/proc/self/statm");

    size_t size {};
    size_t resident {};

    statm >> size >> resident;

    size_t page_size_kb = static_cast<size_t>(sysconf(_SC_PAGE_SIZE) / 1024);

    return resident * page_size_kb;
}

