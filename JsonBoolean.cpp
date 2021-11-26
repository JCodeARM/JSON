//
//  JsonBoolean.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonBoolean.hpp"

 
JsonBoolean::JsonBoolean(bool vBool):JsonBase(),lBool(vBool){
    lType=JsonType::Boolean;
}
JsonBoolean::~JsonBoolean(){
    
}
JsonStream & operator <<(JsonStream & lout, const JsonBoolean &lin){
    lout<<(lin.lBool ? "true" : "false");
    return lout;
}
