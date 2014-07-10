
# include "config.h"
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

int get_files_count(std::string input_dir, std::string extension){
    boost::filesystem::directory_iterator end;
    int count = 0;

    if (boost::filesystem::exists(input_dir)
        && boost::filesystem::is_directory(input_dir))
    {
        for (boost::filesystem::directory_iterator it(input_dir);
             it != end; ++it)
        {
            if (it->path().extension().string().compare(extension) == 0){
                ++count;
            }
        }
    }
    return count;
}

int main(){
//  FIXME: only for testing
    Benchmark benchmark;

//  FIXME: classifieurs à générer
//  Init Haar classifiers - A
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
    
//  1st step Initialisation
    
//  weights are initialized.
    int nb_faces = get_files_count(std::string(PROJECT_SRC_DIR)
                                   + "/face", ".pgm");
    int nb_non_faces = get_files_count(std::string(PROJECT_SRC_DIR)
                                       + "/nonface", ".png");
    
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

//  FIXME : 25, doit être inférieur au nombre de classifieurs
//  (car on vire les classifieurs au fur à mesure)
    int nb_weak_level = 1;//FIXME : 25, doit être inférieur au nombre de classifieurs
    for (int weak_level_i = 0; weak_level_i < nb_weak_level; ++weak_level_i){
//      normalise the weights.
        normalize(weights);
        
        std::vector<float> error_list;
        std::vector<float> beta_list;//utilisation ?
        std::vector<float> threshold;
        std::vector<float> polarity_list;//int ?

        int nb_features = classifiers.size();
        
//      beta_list=zeros(1,length(A));
//      threshold=zeros(1,length(A));
//      polarity_list=zeros(1,length(A));
        error_list.reserve(nb_features);
        beta_list.reserve(nb_features);
        threshold.reserve(nb_features);
        polarity_list.reserve(nb_features);
    
//      select the best weak classifier with respect to the current weights.
        for (size_t i = 0; i < classifiers.size(); ++i) {
//          [facedata,nonfacedata, ]=data_gen(A{i});
            std::vector<float>* data = data_gen(classifiers[i]);
//
//          perform pocket on the data obtained from the present haar feature.
//          [x,error, polarity]= optimal(data, weights);
            std::vector<float> values = optimal(data, weights);

            float error = values[1];
            if (error == 1)
                error -= 0.0001;

//          beta=(error/(1-error));
//          beta_list(i)=beta;
            beta_list.push_back(error/(1 - error));
//          error_list(i)=error;
            error_list.push_back(error);
//          threshold(i)=x;
            threshold.push_back(values[0]);
//          polarity_list(i)=polarity;
            polarity_list.push_back(values[2]);

//          for a polarity value of 1, the images on the right side of threshold are faces
//          for a polarity value of 2, the images on the left side of threshold are faces
            delete data;
        }
        
//      form/define the classifier
//      a classifier is a haarfeature,threshold,polarity combination

        
//      [~,best_classifier_index]=min((error_list));
        int best_classifier_index = 0;
        float min = error_list[0];

        for (int i = 1; i < nb_features; ++i){
            if (error_list[i] < min){
                min = error_list[i];
                best_classifier_index = i;
            }
        }

//      theta = (threshold(best_classifier_index));
//      feature = A{best_classifier_index};
//      classifier_polarity = polarity_list(best_classifier_index);
//      classifier_beta=beta_list(best_classifier_index);
//      alpha = log(1/classifier_beta)
        float theta = threshold[best_classifier_index];
        cv::Mat feature = classifiers[best_classifier_index];
        float polarity = polarity_list[best_classifier_index];
        float beta = beta_list[best_classifier_index];
        if (beta == 0)
            beta += 0.00001;
        //float alpha = logf(1 / beta);

//      update the respective weights of the misclassified points.
//      [facedata,nonfacedata, ]=data_gen(A{best_classifier_index});
        std::vector<float>* data = data_gen(classifiers[best_classifier_index]);
//      data=[facedata;nonfacedata]'; //vraiment nécessaire ?

        int data_size = data->size() / 3;
        std::vector<int> output;
        output.reserve(data_size);
//      if classifier_polarity==1 (pour nous -1)
        if (polarity < 0){
//          classifier_output=sign(data(1,:)-theta);
//          classifier_output(find(classifier_output==-1))=0;
            for (int i = 0; i < data_size; ++i){
                if ((*data)[i * 3] - theta > 0){
                    output.push_back(1);
                }
                else{
                    output.push_back(0);
                }
            }
        }
        else{
//          classifier_output=sign(theta-data(1,:));
//          classifier_output(find(classifier_output==-1))=0;
            for (int i = 0; i < data_size; ++i){
                if ((*data)[i * 3] - theta > 0){
                    output.push_back(1);
                }
                else{
                    output.push_back(0);
                }
            }
        }

//      weights=weights.*(classifier_beta.^(classifier_output))';
        for (int i = 0; i < data_size; ++i){
            weights[i] *= (output[i] == 1)? beta : 1;
        }

//      A(best_classifier_index)=[];
        classifiers.erase(classifiers.begin() + best_classifier_index);

        delete data;
    }
    
//  3rd step. Make a strong classifier
//  XML step
    
//  FIXME: only for testing
    std::cout << "Adaboost execution took " << benchmark << std::endl;
    
    return EXIT_SUCCESS;
}