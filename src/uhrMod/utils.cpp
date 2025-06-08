/** Author: LELE */

#ifndef UTILS
#define UTILS

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

inline void validate_input(int argc, char *argv[], std::int64_t& runs, std::string& file1, std::string& file2, std::string& file3,
 std::string& file4, bool& acceptRecursive)
{
    if (argc != 7) {
        std::cerr << "Usage: <RUNS> <file string 1> <file string 2> <file string 3> <file string 4> <recursive(s/n)>" << std::endl;
        std::cerr << "<RUNS>: numbers of runs per test case: should be >= 32." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Read command line arguments
    try {
        runs = std::stoll(argv[1]);
        file1 = argv[2];
        file2 = argv[3];
        file3 = argv[4];
        file4 = argv[5];
        if (std::string(argv[6]) == "s" || std::string(argv[6]) == "S"){
            acceptRecursive = true;
        } else {acceptRecursive = false;}

    } catch (std::invalid_argument const& ex) {
        std::cerr << "std::invalid_argument::what(): " << ex.what() << std::endl;
        std::exit(EXIT_FAILURE);
    } catch (std::out_of_range const& ex) {
        std::cerr << "std::out_of_range::what(): " << ex.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

inline void display_progress(std::int64_t u, std::int64_t v)
{
    const double progress = u / double(v);
    const std::int64_t width = 70;
    const std::int64_t p = width * progress;
    std::int64_t i;

    std::cerr << "\033[1m[";
    for (i = 0; i < width; i++) {
        if (i < p)
            std::cerr << "=";
        else if (i == p)
            std::cerr << ">";
        else
            std::cerr << " ";
    }
    std::cerr << "] " << std::int64_t(progress * 100.0) << "%\r\033[0m";
    std::cerr.flush();
}

inline void quartiles(std::vector<double>& data, std::vector<double>& q)
{
    q.resize(5);
    std::size_t n = data.size();
    std::size_t p;

    std::sort(data.begin(), data.end());

    if (n < 4) {
        std::cerr << "quartiles needs at least 4 data points." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Get min and max
    q[0] = data.front();
    q[4] = data.back();

    // Find median
    if (n % 2 == 1) {
        q[2] = data[n / 2];
    } else {
        p = n / 2;
        q[2] = (data[p - 1] + data[p]) / 2.0;
    }

    // Find lower and upper quartiles
    if (n % 4 >= 2) {
        q[1] = data[n / 4];
        q[3] = data[(3 * n) / 4];
    } else {
        p = n / 4;
        q[1] = 0.25 * data[p - 1] + 0.75 * data[p];
        p = (3 * n) / 4;
        q[3] = 0.75 * data[p - 1] + 0.25 * data[p];
    }
}

inline void read_file(const std::string& file1, const std::string& file2, std::string& S, std::string& T){
    std::ifstream f1(file1);
    if (!f1.is_open()){
        std::cerr << "file " << file1 << " could not be open" << std::endl;
        return;
    }
    std::stringstream ss1;
    ss1 << f1.rdbuf();
    S = ss1.str();

    std::ifstream f2(file2);
    if (!f2.is_open()) {
        std::cerr << "file " << file2 << " could not be open" << std::endl;
        return;
    }
    std::stringstream ss2;
    ss2 << f2.rdbuf();  
    T = ss2.str();  
}

#endif
