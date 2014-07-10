//
//  data_gen.cpp
//  face-detection
//
//  Created by Nicolas Meny on 23/06/2014.
//
//

#include "data_gen.h"

template<typename T>
void print_matrix(cv::Mat m){
    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
            std::cout << m.at<T>(k, j) << ", ";
        }
        std::cout << std::endl;
    }
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

// FIXME
void apply_filter(cv::Mat& m, cv::Mat& filter){
    int top_border = ceilf(filter.rows / 2. - 1);
    int bottom_border = floorf(filter.rows / 2.);
    int left_border = ceilf(filter.cols / 2. - 1);
    int right_border = floorf(filter.cols / 2.);

    cv::Mat m_filtered(m.rows + top_border + bottom_border,
                       m.cols + left_border + right_border, CV_64FC1);

//  add 0 borders to apply filter
//  cv::copyMakeBorder does not work with left/right border else we could use
//  cv::copyMakeBorder(m, m_filtered, top_border, bottom_border,
//                     left_border, right_border, cv::BORDER_CONSTANT, 0);
//  top
    for (int i = 0; i < top_border; ++i){
        for (int j = 0; j < m_filtered.cols; ++j){
            m_filtered.at<float>(i, j) = 0;
        }
    }

    for (int i = 0; i < m.rows; ++i) {
//      left
        for (int j = 0; j < left_border; ++j) {
            m_filtered.at<float>(i + top_border, j) = 0;
        }
        for (int j = 0; j < m.cols; ++j) {
            m_filtered.at<float>(i + top_border, j + left_border) = m.at<float>(i, j);
        }
//      right
        for (int j = m_filtered.cols - right_border; j < m_filtered.cols; ++j) {
            m_filtered.at<float>(i + top_border, j) = 0;
        }
    }

//  bottom
    for (int i = m_filtered.rows - bottom_border; i < m_filtered.rows; ++i){
        for (int j = 0; j < m_filtered.cols; ++j){
            m_filtered.at<float>(i, j) = 0;
        }
    }

//    std::cout << "matrix before filter" << std::endl;
//    print_matrix<float>(m_filtered);

    for (int i = 0; i < m.rows; ++i){
        for (int j = 0; j < m.cols; ++j){
            //for each pixels
            float pixel_val = 0;
            //apply_filter
            for (int k = 0; k < filter.rows; ++k){
                for (int l = 0; l < filter.cols; ++l){
                    pixel_val += filter.at<float>(k, l) * m_filtered.at<float>(i + k, j + l);
                }
            }
            m.at<float>(i, j) = pixel_val;
        }
    }
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

        //      FIXME perf : equalized after resize ?
        //      im=histeq(im); im=mat2gray(im); division par 255
        cv::Mat* im_equalized = histeq(im);

        //      im=imresize(im,[24 24]);

//      si jamais on devait avoir des images différentes de 24x24
//      il faudrait resize, néanmoins cette fonction a un soucis
//      d'accès concurrent créant des NaN donc il faudrait la refaire
//      cv::resize(*im_equalized, im_data_resize, cv::Size(24, 24));

//      im=(im-mean(mean(im)))./(var(im(:)));
        mean_var(*im_equalized);

//      you must be thinking that why we are using this step. We told you that
//      we will be using integral images for that. okay, we will develop the
//      workaround. no worries!!
//      im=imfilter(im,A,'same');
        apply_filter(*im_equalized, classifier);
        
//      face_data(i,1)=mean(mean(im));
        (*data)[i * 3] = mean_vector(*im_equalized);

        delete im_equalized;
        
        ++i;
    }
    
    delete nonfacefiles;
    delete facefiles;
    
    return data;
}