//
//  JsonNumber.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonNumber.hpp"

 
JsonNumber::JsonNumber(double vDouble):JsonBase(),lDouble(vDouble){
    lType=JsonType::Number;
}
JsonNumber::~JsonNumber(){
    
}
JsonStream & operator <<(JsonStream & lout, const JsonNumber &lin){
    lout<<lin.lDouble;
    return lout;
}
