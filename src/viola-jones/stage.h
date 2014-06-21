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

class Stage
{
public:
    Stage(int nb_weak, float threshold);

protected:
    int nb_weak_;
    float threshold_;
};

#endif /* defined(__face_detection__stage__) */
