//
//  partition.cpp
//  interview
//
//  Created by Livecode on 9/16/17.
//  Copyright © 2017 alexbrisan. All rights reserved.
//

#include "partition.hpp"
#include <assert.h>

descriptor::descriptor(int const &max_elem)
{
    this->pos = new int[max_elem + 1];
    this->freqs = new int[max_elem + 1];
    this->max_index = max_elem + 1;
    
    int i = 0;
    for(;;++i)
    {
        if (i == this->max_index) return;
        pos[i] = -1;
        freqs[i] = -1;
    }
}

descriptor::~descriptor()
{
    delete[] this->pos;
    delete[] this->freqs;
}

void descriptor::process_partition(int const *arr,
                                   int const &from,
                                   int const &to)
{
    for (int i = from ; i < to ; ++i)
    {
        assert (arr[i] < this->max_index);
        if (this->pos[arr[i]] != -1)
        {
            ++this->freqs[arr[i]];
        }
        else
        {
            this->pos[arr[i]] = i;
            this->freqs[arr[i]] = 1;
        }
    }
}

void descriptor::merge_partition(descriptor const &other)
{
    assert (this->max_index == other.max_index);
    for (int i = 0 ; i < this->max_index ; ++i)
    {
        if (other.pos[i] != -1)
        {
            if (this->pos[i] == -1)
            {
                this->pos[i] = other.pos[i];
                this->freqs[i] = other.freqs[i];
            }
            else
            {
                this->freqs[i] += other.freqs[i];
                this->pos[i] = std::min(this->pos[i], other.pos[i]);
            }
        }
    }
}
