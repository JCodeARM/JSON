//
//  JsonString.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonString.hpp"

 
JsonString::JsonString(std::string &vString):JsonBase(),lString(vString){
    lType=JsonType::String;
}
JsonString::~JsonString(){
    
}
JsonStream & operator <<(JsonStream & lout, const JsonString &lin){
    lout<<lin.lString;
    return lout;
}
