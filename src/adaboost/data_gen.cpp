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
    cv::Mat m_filtered;

//  add 0 borders
    cv::copyMakeBorder(m, m_filtered, top_border, bottom_border,
                       left_border, right_border, cv::BORDER_CONSTANT, 0);


    for (int k = 0; k < m.rows; ++k){
        for (int j = 0; j < m.cols; ++j){
        }
    }

    //std::cout << m << std::endl;
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
        apply_filter(im_data_resize, classifier);

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
        (*data)[i * 3] = mean_vector(im_data_resize);
        
        ++i;
    }
    
    delete nonfacefiles;
    delete facefiles;
    
    return data;
}