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

#define TEST_SIZE (1L << 30)
#define N_THREADS 8

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
    des->process_partition(arr, from, to);
}

inline bool finished(descriptor **des)
{
    bool ret = true;
    
    for (int i = 0 ; i < N_THREADS ; ++i)
    {
        ret &= des[i]->finished();
    }
    
    return ret;
}

inline long get_result_parallel(int *array)
{
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
        
        t.detach();
    }
    
    while(!finished(des)) {}
    
    for (int i = 1 ; i < N_THREADS ; ++i)
    {
        des[i]->merge_partition(*des[i]);
    }
    
    long result = get_result_for_descriptor(*des[0]);
    
    return result;
}

inline long get_result_serial(int *arr)
{
    descriptor d(256);
    
    d.process_partition(arr, 0, TEST_SIZE);
    
    return get_result_for_descriptor(d);
}

#endif /* parallel_hpp */
