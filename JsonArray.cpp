//
//  JsonArray.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonString.hpp"
#include "JsonNumber.hpp"
#include "JsonBoolean.hpp"
#include "JsonNull.hpp"
JsonArray::JsonArray():JsonBase(){
    lType=JsonType::Array;
}
JsonArray::~JsonArray(){
    for ( auto i:lArray) {
        if (i != nullptr) { delete i; }
    }
}
void JsonArray::additem(JsonBase * lValue){
    lArray.push_back(lValue);
}
JsonStream & operator <<(JsonStream & lout, const JsonArray &lin){
    auto iBegin=lin.lArray.begin();
    lout<<"[";
    if (iBegin !=lin.lArray.end()) {
        while (true) {
            if (*iBegin) {
                switch ((*iBegin)->getType()) {
                    case JsonType::Object:{
                        const JsonObject  *obj=static_cast<const JsonObject*>((*iBegin));
                        lout<<(*obj);
                    }break;
                    case JsonType::Array:{
                        const JsonArray   *obj=static_cast<const JsonArray*  >((*iBegin));
                        lout<<(*obj);
                    }break;
                    case JsonType::String:{
                        const JsonString  *obj=static_cast<const JsonString* >((*iBegin));
                        lout<<(*obj);
                    }break;
                    case JsonType::Number:{
                        const JsonNumber  *obj=static_cast<const JsonNumber* >((*iBegin));
                        lout<<(*obj);
                    }break;
                    case JsonType::Boolean:{
                        const JsonBoolean *obj=static_cast<const JsonBoolean*>((*iBegin));
                        lout<<(*obj);
                    }break;
                    case JsonType::Null:{
                        const JsonNull    *obj=static_cast<const JsonNull*   >((*iBegin));
                        lout<<(*obj);
                    }break;
                    default:{}break;
                }
            }else{

            }
            iBegin++;
            if (iBegin !=lin.lArray.end()) {
                lout<<",";
            }else{
                break;
            }
        }
    }
    lout<<"]";
    return lout;
}
