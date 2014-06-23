//
//  stage.cpp
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#include "stage.h"

Stage::Stage(int nb_weak, float threshold)
    : nb_weak_(nb_weak)
    , threshold_(threshold)
{
}

std::vector<WeakClassifier>& Stage::get_weak_classifier_array()
{
    return weak_classifier_array_;
}