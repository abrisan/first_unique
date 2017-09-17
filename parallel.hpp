//
//  parallel.hpp
//  interview
//
//  Created by Livecode on 9/16/17.
//  Copyright © 2017 alexbrisan. All rights reserved.
//

#ifndef parallel_hpp
#define parallel_hpp
#include <thread>
#include <deque>
#include <vector>
#include "partition.hpp"

#define TEST_SIZE (1L << 31)
#define N_THREADS 4

inline void populate_array(int *arr,
                    long const from,
                    long const to)
{
    for (long i = from ; i < to ; ++i)
    {
        arr[i] = std::rand() % 256;
    }
}

inline void execute_function(descriptor *des,
                      int *arr,
                      long const from,
                      long const to)
{
    populate_array(arr, from, to);
    des->process_partition(arr, from, to);
}

inline long get_result_parallel()
{
    int *array = new int[TEST_SIZE];
    long const part_size = TEST_SIZE / N_THREADS;
    
    descriptor **des = new descriptor*[N_THREADS];
    
    for (int i = 0 ; i < N_THREADS; ++i)
    {
        des[i] = new descriptor(256);
    }
    
    for (long i = 0 ; i < N_THREADS; ++i)
    {
        long const start = i * part_size;
        long const end_start = i * part_size + part_size;
        long const end = end_start > TEST_SIZE ? TEST_SIZE : end_start;
        
        std::thread t(execute_function, des[i], array, start, end);
        if (t.joinable()) t.join();
    }
    
    for (int i = 1 ; i < N_THREADS ; ++i)
    {
        des[0]->merge_partition(*des[i]);
    }
    
    long result = get_result_for_descriptor(*des[0]);
    
    delete[] array;
    delete[] des;
    
    return result;
}

inline long get_result_serial()
{
    int *arr = new int[TEST_SIZE];
    descriptor d(256);
    
    for (long i = 0 ; i < TEST_SIZE; ++i)
    {
        arr[i] = std::rand() % 256;
    }
    
    d.process_partition(arr, 0, TEST_SIZE);
    
    delete[] arr;
    
    return get_result_for_descriptor(d);
}

#endif /* parallel_hpp */
