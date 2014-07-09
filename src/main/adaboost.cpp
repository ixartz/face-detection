
# include "config.h"
# include "../adaboost/Matrix.h"
# include "../adaboost/adaboost-classifier.h"
# include "../adaboost/data_gen.h"
# include "../util/Benchmark.h"

void normalize(std::vector<float>& vect){
    float vect_sum = 0;
    for (auto it = vect.begin(); it != vect.end(); ++it){
        vect_sum += *it;
    }

    for (auto it = vect.begin(); it != vect.end(); ++it){
        *it = *it / vect_sum;
    }
}

int main(){
//  FIXME: only for testing
    Benchmark benchmark;
    
//  Haar classifiers - A
    std::vector<cv::Mat> classifiers;
    
    cv::Mat test(6, 3, CV_64FC1);
    for (int i = 0; i < test.rows; ++i) {
        for (int j = 0; j < test.cols; ++j) {
            if (i < 3){
                test.at<float>(i, j) = -1;
            }
            else{
                test.at<float>(i, j) = 1;
            }
        }
    }
//  FIXME code to remove
    for (int i = 0; i < 1; ++i)
        classifiers.push_back(test);
    
//    1st step Initialisation
    
//  weights are initialized.
//  FIXME: valeurs variables
    int nb_faces = 200;
    int nb_non_faces = 400;
    
//  weights for face images = 1/(2*l)
    double face_weight = 1. / nb_faces;
//  weights for non-face images = 1/(2*m)
    double non_face_weight = 1. / nb_non_faces;

//  weights=[ones(l,1)./(2*l);ones(m,1)./(2*m)];
    std::vector<float> weights;
    weights.reserve(nb_faces + nb_non_faces);
    for (int i = 0; i < nb_faces; ++i){
        weights.push_back(face_weight);
    }
    for (int i = 0; i < nb_non_faces; ++i){
        weights.push_back(non_face_weight);
    }
    
//    2nd step Main Adaboost Loop
    
    int nb_weak_level = 3;//FIXME : 25
    for (int weak_level_i = 0; weak_level_i < nb_weak_level; ++weak_level_i){
//      normalise the weights.
        normalize(weights);
        
        std::vector<float> error_list;
        std::vector<float> beta_list;//utilisation ?
        std::vector<float> threshold;
        std::vector<float> polarity_list;//int ?
        
        
//      beta_list=zeros(1,length(A));
//      threshold=zeros(1,length(A));
//      polarity_list=zeros(1,length(A));
    
//      select the best weak classifier with respect to the current weights.
        for (size_t i = 0; i < classifiers.size(); ++i) {
//          [facedata,nonfacedata, ]=data_gen(A{i});
            std::vector<float>* data = data_gen(classifiers[i]);
//
//          perform pocket on the data obtained from the present haar feature.
//          [x,error, polarity]= optimal(data, weights);
            optimal(data, weights);
//          beta=(error/(1-error));
//
//          error_list(i)=error;
//          beta_list(i)=beta;
//          threshold(i)=x;
//          polarity_list(i)=polarity;
//    
//          for a polarity value of 1, the images on the right side of threshold are faces
//          for a polarity value of 2, the images on the left side of threshold are faces
            delete data;
        }
        
//      form/define the classifier
//      a classifier is a haarfeature,threshold,polarity combination
        
//      [~,best_classifier_index]=min((error_list));
        int best_classifier_index = 0; //=min((error_list))
//      theta = (threshold(best_classifier_index));
//      feature = A{best_classifier_index};
//      classifier_polarity = polarity_list(best_classifier_index);
//      classifier_beta=beta_list(best_classifier_index);
//      alpha = log(1/classifier_beta)
//
//      update the respective weights of the misclassified points.
//      [facedata,nonfacedata, ]=data_gen(A{best_classifier_index});
        std::vector<float>* data = data_gen(classifiers[best_classifier_index]);
//      data=[facedata;nonfacedata]'; //vraiment nécessaire ?
        
//      if classifier_polarity==1
//         classifier_output=sign(data(1,:)-theta);
//      else
//         classifier_output=sign(theta-data(1,:));
//      end
//      classifier_output(find(classifier_output==-1))=0;
//
//      weights=weights.*(classifier_beta.^(classifier_output))';
//
//      A(best_classifier_index)=[];
    }
    
//  3rd step. Make a strong classifier
//  XML step
    
//  FIXME: only for testing
    std::cout << "Adaboost execution took " << benchmark << std::endl;
    
    return EXIT_SUCCESS;
}