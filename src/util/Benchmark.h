//
//  Benchmark.h
//  face-detection
//
//  Created by Nicolas Meny on 09/07/2014.
//
//

#ifndef __face_detection__Benchmark__
#define __face_detection__Benchmark__

#include <iostream>

class Benchmark
{
public:
    Benchmark();

    clock_t get_init();
private:
    clock_t init_;
};

inline clock_t
Benchmark::get_init()
{
    return init_;
}

std::ostream& operator<<(std::ostream& o, Benchmark& bench);

#endif /* defined(__face_detection__Benchmark__) */
