//
// Created by mauro on 13/03/2024.
//
#include <iostream>

bool isNumber(std::string& s){
    for(char c : s ){
        if(!std::isdigit(c)){
            return false;
        }
    }
    return true;
}
