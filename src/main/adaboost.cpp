
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
//  FIXME: only for perf tests
    Benchmark benchmark;

//  FIXME: generate features
    std::vector<cv::Mat> classifiers;
    
    cv::Mat haar1(6, 3, CV_64FC1);
    for (int i = 0; i < haar1.rows; ++i) {
        for (int j = 0; j < haar1.cols; ++j) {
            if (i < 3){
                haar1.at<float>(i, j) = -1;
            }
            else{
                haar1.at<float>(i, j) = 1;
            }
        }
    }

    classifiers.push_back(haar1);

    cv::Mat haar2(6, 6, CV_64FC1);
    for (int i = 0; i < haar2.rows; ++i) {
        for (int j = 0; j < haar2.cols; ++j) {
            if (i < 3){
                haar2.at<float>(i, j) = -1;
            }
            else{
                haar2.at<float>(i, j) = 1;
            }
        }
    }

    classifiers.push_back(haar2);

    cv::Mat haar3(6, 9, CV_64FC1);
    for (int i = 0; i < haar3.rows; ++i) {
        for (int j = 0; j < haar3.cols; ++j) {
            if (i < 3){
                haar3.at<float>(i, j) = -1;
            }
            else{
                haar3.at<float>(i, j) = 1;
            }
        }
    }

    classifiers.push_back(haar3);

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

//  weights = (1/(2*l))(1/(2*m));
    std::vector<float> weights;
    weights.reserve(nb_faces + nb_non_faces);
    for (int i = 0; i < nb_faces; ++i){
        weights.push_back(face_weight);
    }
    for (int i = 0; i < nb_non_faces; ++i){
        weights.push_back(non_face_weight);
    }
    
//    2nd step Main Adaboost Loop

//  FIXME : must be inferior to features number
//  (because a feature cannot be in more than one weak classifier)
    int nb_weak_level = 1;
    for (int weak_level_i = 0; weak_level_i < nb_weak_level; ++weak_level_i){
//      normalise the weights.
        normalize(weights);
        
        std::vector<float> error_list;
        std::vector<float> beta_list;
        std::vector<float> threshold;
        std::vector<float> polarity_list;

        int nb_features = classifiers.size();

        error_list.reserve(nb_features);
        beta_list.reserve(nb_features);
        threshold.reserve(nb_features);
        polarity_list.reserve(nb_features);
    
//      select the best weak classifier with respect to the current weights.
        for (size_t i = 0; i < classifiers.size(); ++i) {
            std::vector<float>* data = data_gen(classifiers[i]);

//          [x,error, polarity]= optimal(data, weights);
            std::vector<float> values = optimal(data, weights);

            float error = values[1];
            if (error == 1)
                error -= 0.0001;

//          beta=(error/(1-error));
            beta_list.push_back(error/(1 - error));
            error_list.push_back(error);
            threshold.push_back(values[0]);
//          for a polarity value of -1, the images on the right side of threshold are faces
//          for a polarity value of 1, the images on the left side of threshold are faces
            polarity_list.push_back(values[2]);

            delete data;
        }
        
//      define the classifier
//      a classifier is a haarfeature,threshold,polarity combination

//      get index that minimize error
        int best_classifier_index = 0;
        float min = error_list[0];
        for (int i = 1; i < nb_features; ++i){
            if (error_list[i] < min){
                min = error_list[i];
                best_classifier_index = i;
            }
        }

        float theta = threshold[best_classifier_index];
        cv::Mat feature = classifiers[best_classifier_index];
        float polarity = polarity_list[best_classifier_index];
        float beta = beta_list[best_classifier_index];
        if (beta == 0)
            beta += 0.00001;

//      alpha = log(1/beta)
        float alpha = logf(1 / beta);

//      FIXME: keep the values in a weak classifier

//      update the respective weights of the misclassified points.
        std::vector<float>* data = data_gen(classifiers[best_classifier_index]);

        int data_size = data->size() / 3;
        std::vector<int> output;
        output.reserve(data_size);

        if (polarity < 0){
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
            for (int i = 0; i < data_size; ++i){
                if (theta - (*data)[i * 3] > 0){
                    output.push_back(1);
                }
                else{
                    output.push_back(0);
                }
            }
        }

//      w(t + 1, i) = w(t, i) * (beta^(1 - e(i))) with e(i) == 1 or 0
        for (int i = 0; i < data_size; ++i){
            weights[i] *= (output[i] == 1)? beta : 1;
        }

//      We do not need a feature previously selected for next step
        classifiers.erase(classifiers.begin() + best_classifier_index);

        delete data;
    }
    
//  3rd step. Make a strong classifier
//  Generate XML
    
//  FIXME: only for perf tests
    std::cout << "Adaboost execution took " << benchmark << std::endl;
    
    return EXIT_SUCCESS;
}