//
//  classifier.h
//  face-detection
//
//  Created by Nicolas Meny on 09/07/2014.
//
//

#ifndef __face_detection__adaboost_classifier__
#define __face_detection__adaboost_classifier__

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
struct valIndexed{
    T val;
    int index;
};

template<typename T>
bool indexSwap (valIndexed<T> i, valIndexed<T> j) {
    return (i.val < j.val);
}

template<typename T>
void sortIndex(std::vector<valIndexed<T>>& data){
    std::sort(data.begin(), data.end(), indexSwap<T>);
}

// return a vector containing [threshold, error, polarity]
std::vector<float> optimal(std::vector<float>* mydata,
                           std::vector<float>& weights);

#endif /* defined(__face_detection__adaboost_classifier__) */
