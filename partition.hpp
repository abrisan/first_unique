//
//  partition.hpp
//  interview
//
//  Created by Livecode on 9/16/17.
//  Copyright © 2017 alexbrisan. All rights reserved.
//

#ifndef partition_hpp
#define partition_hpp

#include <iostream>

class descriptor
{
private:
    long *pos;
    int *freqs;
    int max_index;
    bool done = false;
public:
    descriptor(int const & max_elem);
    ~descriptor();
    void process_partition(int const *arr,
                           long const &from,
                           long const &to);
    void merge_partition(descriptor const &other);
    
    
    int const &get_max() const {return this->max_index;}
    long const *get_pos() const {return this->pos;}
    int const *get_freqs() const {return this->freqs;}
    bool const finished() const {return this->done;}
};

inline std::ostream &operator<<(std::ostream &cout,
                         descriptor const &my_obj)
{
    cout << " == Descriptor ==\n";
    int i = 0;
    
    int max = my_obj.get_max();
    long const *pos = my_obj.get_pos();
    int const *freqs = my_obj.get_freqs();
    
    for(;;++i)
    {
        if (i == max) break;
        cout << pos[i] << " ";
    }
    cout << "\n";
    
    i = 0;
    for(;;++i)
    {
        if (i==max) return cout;
        cout << freqs[i] << " ";
    }
    
}


inline long get_result_for_descriptor(descriptor const &des)
{
    long const *pos = des.get_pos();
    int const *freqs = des.get_freqs();
    int const max_index = des.get_max();
    
    long result = std::numeric_limits<long>::max();
    
    for (int i = 0 ; i < max_index ; ++i)
    {
        if (freqs[i] == 1)
        {
            result = std::min(pos[i], result);
        }
    }
    
    return result;
}
#endif /* partition_hpp */
