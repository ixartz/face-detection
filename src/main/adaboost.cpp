
# include "config.h"
# include "../adaboost/Matrix.h"
# include "../adaboost/adaboost-classifier.h"
# include "boost/filesystem.hpp"
# include <opencv2/opencv.hpp>

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

std::ostream& operator<< (std::ostream& o, Benchmark& bench){
    double seconds = (clock() - bench.get_init()) / (double)CLOCKS_PER_SEC;
    int hours = seconds / 3600;
    int minutes = seconds / 60 - hours * 60;
    seconds -= (minutes + hours * 60) * 60;
    o << hours << " hours " << minutes << " minutes " << seconds << " seconds";
    
    return o;
}

template<typename T>
void print_matrix(cv::Mat m){
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            std::cout << m.at<T>(k, j) << ", ";
        }
        std::cout << std::endl;
    }
}

void normalize(std::vector<float>& vect){
    float vect_sum = 0;
    for (auto it = vect.begin(); it != vect.end(); ++it){
        vect_sum += *it;
    }

    for (auto it = vect.begin(); it != vect.end(); ++it){
        *it = *it / vect_sum;
    }
}

// FIXME
cv::Mat* apply_filter(cv::Mat& m, cv::Mat& filter){
    cv::Mat* m_filtered = new cv::Mat(m);
    return m_filtered;
}

std::vector<std::string>* get_files(std::string input_dir,
                                    std::string extension){
    boost::filesystem::directory_iterator end;
    std::vector<std::string>* filenames = new std::vector<std::string>();
    
    if (boost::filesystem::exists(input_dir)
        && boost::filesystem::is_directory(input_dir))
    {
        for (boost::filesystem::directory_iterator it(input_dir);
             it != end; ++it)
        {
            if (it->path().extension().string().compare(extension) == 0){
                filenames->push_back(it->path().string());
            }
        }
    }
    return filenames;
}

float mean_vector(cv::Mat& m){
    float mean = 0;
    float size = m.rows * m.cols;
    
    if (size == 0)
        return mean;
    
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            mean += m.at<float>(k, j);
        }
    }
    
    return mean / size;
}

float variance(cv::Mat& m, float mean){
    float var = 0;
    float size = m.rows * m.cols;
    
    if (size == 0)
        return var;
    
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            var += cv::pow(m.at<float>(k, j) - mean, 2);
        }
    }
    
    return var / size;
}

void mean_var(cv::Mat& m){
    float mean = mean_vector(m);
    float var = variance(m, mean);
    
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            m.at<float>(k, j) = (m.at<float>(k, j) - mean) / var;
        }
    }
}

// FIXME perf : parrallel
cv::Mat* histeq(cv::Mat& m){
    std::vector<float> pixel_counter(256, 0);
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            pixel_counter[m.at<uchar>(k, j)] += 1;
        }
    }
    
    float nb_pixels = m.rows * m.cols;
    float hist_curr = 0;
    std::vector<float> hist_cum;
    hist_cum.reserve(256);
    
    for (int i = 0; i < 256; ++i){
        hist_curr += pixel_counter[i] / nb_pixels;
        hist_cum.push_back(hist_curr);
    }
    
    cv::Mat* m_histeq = new cv::Mat(m.rows, m.cols, CV_64FC1);
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            m_histeq->at<float>(k, j) = hist_cum[m.at<uchar>(k, j)];
        }
    }
    
    //print_matrix<float>(*m_histeq);
    return m_histeq;
}

std::vector<float>* data_gen(cv::Mat& classifier){
    std::vector<float>* data = new std::vector<float>();
    
//  data generation.
//  facefiles=dir('face/*.pgm');
    std::vector<std::string>*
    facefiles = get_files(std::string(PROJECT_SRC_DIR) + "/face", ".pgm");
    
//  nonfacefiles=dir('nonface/*.png');
    std::vector<std::string>*
    nonfacefiles = get_files(std::string(PROJECT_SRC_DIR) + "/nonface", ".png");
    
//  FIXME : 3 ou nb_boucles ?
    int l = facefiles->size() * 3;
    int m = nonfacefiles->size() * 3;
    data->reserve(l + m);
    
//  face_data=ones(length(facefiles),3);
    for (int i = 0; i < l; ++i){
        data->push_back(1);
    }
    
//  nonface_data=ones(length(nonfacefiles),3);
//  nonface_data(:,3)=-1.*ones(length(nonface_data),1);
    for (int i = l; i < l + m; ++i){
        if (i % 3 == 2){
            data->push_back(-1);
        }
        else{
            data->push_back(1);
        }
    }

    facefiles->insert(facefiles->end(), nonfacefiles->begin(),
                      nonfacefiles->end());

//  for i=1:length(facefiles); for i=1:length(facefiles)
    int i = 0;
    for (std::string facefile : *facefiles){
        cv::Mat im = cv::imread(facefile, cv::IMREAD_GRAYSCALE);
        //cv::filter2D(im2, im2, 0, classifier);

//        if (facefile.compare(std::string(PROJECT_SRC_DIR) + "/face/1.pgm") == 0){
//            cv::Mat im2(im.rows, im.cols, CV_64FC1);
//            std::cout << im << std::endl;
//            //cv::filter2D(im, im2, 0, classifier);
//            print_matrix<float>(classifier);
//            std::cout << "im2" << std::endl;
//            std::cout << im2 << std::endl;
//        }

//      FIXME perf : equalized after resize ?
//      im=histeq(im); im=mat2gray(im); division par 255
        cv::Mat* im_equalized = histeq(im);
        
//      im=imresize(im,[24 24]);
        cv::Mat im_data_resize(24, 24, CV_64FC1);
        cv::resize(*im_equalized, im_data_resize,
                   cv::Size(im_data_resize.rows, im_data_resize.cols));
        
        delete im_equalized;
    
//      im=(im-mean(mean(im)))./(var(im(:)));
        mean_var(im_data_resize);
        
//      you must be thinking that why we are using this step. We told you that
//      we will be using integral images for that. okay, we will develop the
//      workaround. no worries!!
//      im=imfilter(im,A,'same');
        cv::Mat* im_filtered = apply_filter(im_data_resize, classifier);
        
        //cv::filter2D(im_data_resize, im_data_resize, 0, classifier);
//        if (facefile.compare(std::string(PROJECT_SRC_DIR) + "/face/1.pgm") == 0){
//            cv::Mat m_test(im.rows, im.cols, CV_64FC1);
//            for (int k = 0; k < im.rows; ++k){
//                for (int j = 0; j < im.cols; ++j){
//                    m_test.at<float>(k, j) = im.at<uchar>(k, j) / 255.;
//                }
//            }
//            mean_var(m_test);
//            std::cout << "mean_var" << std::endl;
//            print_matrix<float>(m_test);
//        }
        
//      face_data(i,1)=mean(mean(im));
        (*data)[i * 3] = mean_vector(*im_filtered);
        delete im_filtered;
        
        ++i;
    }
    
    delete nonfacefiles;
    delete facefiles;

    return data;
}

int main(int argc, char* argv[]){
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