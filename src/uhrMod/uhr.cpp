/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <climits>

#include "../../include/recursiveEditDistance.h"
#include "../../include/memoizationEditDistance.h"
#include "../../include/editDistanceDP.h"
#include "../../include/editDistanceDPO.h"
#include "utils.cpp"

// Include to be tested files here

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs;
    std::string files[4];
    std::string S, T;
    bool acceptRecursive;
    validate_input(argc, argv, runs, files[0], files[1], files[2], files[3], acceptRecursive);

    // Set up clock variables
    std::int64_t i, executed_runs;
    std::int64_t total_runs_additive = runs;
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;

    // Set up random number generation
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<std::int64_t> u_distr; // change depending on app

    int limit = 5;
    if (!acceptRecursive) limit=4;
    for (int a=1 ; a<limit ; a++){
        std::string csv = "resultados_experimentacion/editDistance";
        switch (a){
        case 1:
            csv += "Memo.csv";
            break;
        case 2:
            csv += "DP.csv";
            break;
        case 3:
            csv += "DPO.csv";
            break;
        case 4:
            csv += "Recursive.csv";
            break;
        default:
            std::exit(EXIT_FAILURE);
            break;
        }
        // File to write time data
        std::ofstream time_data;
        time_data.open(csv);
        time_data << "S,T,result,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;
    
        // Begin testing
        int result;
        std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
        executed_runs = 0;
        for (int j=0 ; j<4 ; j++){
            for (int k=0 ; k<4 ; k++){
                if (j == k) continue;
                mean_time = 0;
                time_stdev = 0;
                read_file(files[j], files[k], S, T);
            
                // Run to compute elapsed time
                for (i = 0; i < runs; i++) {
                    // Remember to change total depending on step type
                    display_progress(++executed_runs, total_runs_additive);
            
                    begin_time = std::chrono::high_resolution_clock::now();
                    
                    switch (a){
                    case 1: {
                        std::vector<std::vector<ll>> resultados(S.length()+1, std::vector<ll>(T.length()+1, LLONG_MAX));
                        result = editDistanceMemo(S, T, S.length(), T.length(), resultados);
                        break;
                    }
                    case 2:
                        result = editDistanceDP(S, T, S.length(), T.length());
                        break;
                    case 3:
                        result = editDistanceDPOptimized(S, T, S.length(), T.length());
                        break;
                    case 4:
                        result = editDistanceRecursive(S, T, S.length(), T.length());
                        break;
                    default:
                        std::exit(EXIT_FAILURE);
                        break;
                    }
                    end_time = std::chrono::high_resolution_clock::now();

                    elapsed_time = end_time - begin_time;
                    times[i] = elapsed_time.count();
            
                    mean_time += times[i];
                }
            
                // Compute statistics
                mean_time /= runs;
            
                for (i = 0; i < runs; i++) {
                    dev = times[i] - mean_time;
                    time_stdev += dev * dev;
                }
            
                time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
                time_stdev = std::sqrt(time_stdev);
            
                quartiles(times, q);
            
                time_data << files[j] << "," << files[k] << "," << result << "," << mean_time << "," << time_stdev << ",";
                time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
            }
        }
        
    
        // This is to keep loading bar after testing
        std::cerr << std::endl << std::endl;
        std::cerr << "\033[1;32mDone!\033[0m" << std::endl;
    
        time_data.close();
    }

    return 0;
}