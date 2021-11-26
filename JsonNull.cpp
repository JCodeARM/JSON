//
//  JsonNull.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonNull.hpp"

JsonNull::JsonNull():JsonBase(){
    lType=JsonType::Null;
}
JsonNull::~JsonNull(){

}
JsonStream & operator <<(JsonStream & lout, const JsonNull &lin){
    const char * s="null";
    lout<<s;
    return lout;
}
