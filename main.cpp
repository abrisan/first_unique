//
//  main.cpp
//  interview
//
//  Created by Livecode on 9/16/17.
//  Copyright © 2017 alexbrisan. All rights reserved.
//

#include <iostream>
#include "partition.hpp"
#include "parallel.hpp"
#include <chrono>


int main()
{
    int *arr = new int[TEST_SIZE];
    
    populate_array(arr, 0, TEST_SIZE);
    
    using namespace std::chrono;
    
    high_resolution_clock::time_point s1 = high_resolution_clock::now();
    long result_serial = get_result_serial(arr);
    high_resolution_clock::time_point s2 = high_resolution_clock::now();
    
    high_resolution_clock::time_point s3 = high_resolution_clock::now();
    long result_parallel = get_result_parallel(arr);
    high_resolution_clock::time_point s4 = high_resolution_clock::now();
    
    auto serial_duration = duration_cast<microseconds>(s2-s1).count();
    auto parallel_duration = duration_cast<microseconds>(s4-s3).count();
    
    std::cout << "Serial algo took : " << serial_duration << std::endl;
    std::cout << "Parallel algo took : " << parallel_duration << std::endl;
    
    delete[] arr;
}

