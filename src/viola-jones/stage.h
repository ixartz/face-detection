//
//  stage.h
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#ifndef __face_detection__stage__
#define __face_detection__stage__

#include <iostream>
#include "weak-classifier.h"

class Stage
{
public:
    Stage(int nb_weak, float threshold);
    std::vector<WeakClassifier>& get_weak_classifier_array();

protected:
    int nb_weak_;
    float threshold_;
    std::vector<WeakClassifier> weak_classifier_array_;
};

#endif /* defined(__face_detection__stage__) */
