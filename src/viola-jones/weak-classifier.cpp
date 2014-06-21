//
//  weak-classifier.cpp
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#include "weak-classifier.h"

WeakClassifier::WeakClassifier(float threshold,
                               float left_val,
                               float right_val)
    : threshold_(threshold)
    , left_val_(left_val)
    , right_val_(right_val)
{

}