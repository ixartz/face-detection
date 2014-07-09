//
//  classifier.cpp
//  face-detection
//
//  Created by Nicolas Meny on 09/07/2014.
//
//

#include "adaboost-classifier.h"

//function [ best_x, min_error, polarity ] = optimal( mydata,weights )
std::vector<float> optimal(std::vector<float>* mydata,
                           std::vector<float>& weights){

    int data_size = mydata->size() / 3;

//  tableau d'index au départ
    std::vector<valIndexed<float>> data;
    data.reserve(data_size);

//  prend la colonne 1 de mydata
//  + cherche le pivot (premier -1)
    int pivot = -1;

    for (int i = 0; i < data_size; ++i){
        data.push_back({(*mydata)[i * 3], i});
        if (pivot == -1 && (*mydata)[2 + i * 3] == -1) {
            pivot = i;
        }
    }
    if (pivot == -1)
        pivot = data_size;

//  simple sort croissant
//  [data,index]=sort(mydata(1,:));
    sortIndex(data);

//    for (int i = 0; i < data_size; ++i){
//        std::cout << data[i].val << std::endl;
//    }

//  crée un vecteur de 1, -1 via le sort
//  y=mydata(3,index);
//  y ne sert pas ailleurs => opti faire direct les indices faces/nonface
//  indice des faces dans le sort
//  total_pos_idx = find(y==+1);
//  indice des non faces dans le sort
//  total_neg_idx = find(y==-1);
//  les 1 sont au début et les -1 à la fin
//  du coup il suffit d'avoir le pivot
    std::vector<int> tot_pos_idx;
    std::vector<int> tot_neg_idx;
    tot_pos_idx.reserve(pivot);
    int tot_neg_size = data_size - pivot;
    tot_neg_idx.reserve(tot_neg_size);

//  poids triés
//  weights1=weights(index);
    std::vector<float> weightSort;
    weightSort.reserve(data_size);

    tot_pos_idx.reserve(pivot);
    for (int i = 0; i < data_size; ++i){
        int index_i = data[i].index;
        weightSort.push_back(weights[index_i]);
        if (index_i < pivot){
            tot_pos_idx.push_back(i);
        }
        else{
            tot_neg_idx.push_back(i);
        }
    }

//  somme des poids faces
//  T_plus = sum(weights1(total_pos_idx));
//  somme des poids nonfaces
//  T_minus = sum(weights1(total_neg_idx));
    float t_plus = 0;
    float t_minus = 0;
    for (int i = 0; i < pivot; ++i){
        t_plus += weights[i];
    }
    for (int i = pivot; i < data_size; ++i){
        t_minus += weights[i];
    }

    float basic_sum = 0;
    for (int i = 0; i < data_size; ++i){
        basic_sum += weights[i];
    }

    std::vector<int> polarity;
    polarity.reserve(data_size);
    std::vector<float> error_list;
    error_list.reserve(data_size);
//  for i = 1:length(mydata)
    for (int i = 0; i < data_size; ++i){
//      Somme des poids sort en prenant les index de total ou i > val
//      Attention probablement une erreur sinon on ignore la fin de
//      weights1, je pense que c'est plutôt:
//      %S_plus = sum(weights1(total_pos_idx(find(i>total_pos_idx))));
        float s_plus = 0;
        float s_minus = 0;
        int pos_idx = -1;
        int neg_idx = -1;

        for (int j = 0; j < pivot/* tot_pos_idx.size() */; ++j){
            if (i <= tot_pos_idx[j]) {
                pos_idx = j;
                break;
            }
        }
        if (pos_idx == -1)
            pos_idx = pivot;

        for (int j = 0; j < tot_neg_size; ++j){
            if (i <= tot_neg_idx[j]) {
                neg_idx = j;
                break;
            }
        }
        if (neg_idx == -1)
            neg_idx = tot_neg_size;

//      S_plus = sum(weights1(find(i>total_pos_idx)));
        for (int j = 0; j < pos_idx; ++j){
            s_plus += weightSort[j];
        }
//      S_minus = sum(weights1(find(i>total_neg_idx)));
        for (int j = 0; j < neg_idx; ++j){
            s_minus += weightSort[j];
        }

//      polarity = index du min (gauche/droite) donc ici 1 2
//      mais on veut -1 1
//      [error_list(i),polarity(i)]=min([S_plus+(T_minus - S_minus), S_minus+(T_plus - S_plus)]);
        float left_val = s_plus + t_minus - s_minus;
        float right_val = s_minus + t_plus - s_plus;

        float error_i = std::min(left_val, right_val);
        error_list.push_back(error_i);

        if (error_i == left_val){
            polarity.push_back(-1);
        }
        else{
            polarity.push_back(1);
        }
//  end
    }

//  [min_error,min_error_idx] = min(error_list);
    float min_error;
    float min_error_idx = 0;
    if (data_size > 0)
        min_error = error_list[0];

    for (int i = 1; i < data_size; ++i){
        if (error_list[i] < min_error){
            min_error = error_list[i];
            min_error_idx = i;
        }
    }

    float best_x = 0;
    float polarity_val = 0;
    if (data_size > 0){
//      best_x=data(min_error_idx);
        best_x = data[min_error_idx].val;
//      polarity=polarity(min_error_idx);
        polarity_val = polarity[min_error_idx];
    }
    
    std::vector<float> result;
    result.push_back(best_x);
    result.push_back(min_error);
    result.push_back(polarity_val);
    return result;
}