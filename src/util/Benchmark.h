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

class Benchmark{
public:
    Benchmark()
    :init_(clock())
    {}

    clock_t get_init(){
        return init_;
    };
private:
    clock_t init_;
};

std::ostream& operator<< (std::ostream& o, Benchmark& bench);

#endif /* defined(__face_detection__Benchmark__) */
