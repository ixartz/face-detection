//
//  Benchmark.cpp
//  face-detection
//
//  Created by Nicolas Meny on 09/07/2014.
//
//

#include "Benchmark.h"

Benchmark::Benchmark()
    : init_(clock())
{
}

std::ostream& operator<<(std::ostream& o, Benchmark& bench)
{
    double seconds = (clock() - bench.get_init()) / (double)CLOCKS_PER_SEC;
    int hours = seconds / 3600;
    int minutes = seconds / 60 - hours * 60;
    seconds -= (minutes + hours * 60) * 60;
    o << hours << " hours " << minutes << " minutes " << seconds << " seconds";

    return o;
}