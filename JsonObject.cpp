//
//  JsonObject.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include "JsonString.hpp"
#include "JsonNumber.hpp"
#include "JsonBoolean.hpp"
#include "JsonNull.hpp"

JsonObject::JsonObject():JsonBase(){
    lType=JsonType::Object;
}
JsonObject::~JsonObject(){
    for (auto iBegin=lObject.begin(); iBegin != lObject.end(); iBegin++) {
            delete  (*iBegin);
    }
    lObject.clear();
}
void JsonObject::addProperty(std::string & lKey,JsonBase * lValue){

    for (auto iBegin=lObject.begin(); iBegin != lObject.end(); iBegin++) {
        if ((*iBegin)->getKey() == lKey) {
            throw  std::string("Error Dublicate Key "+lKey);
        }
    }
    lObject.push_back(new JsonObjectItem(lKey,lValue));
}
const JsonBase * JsonObject::operator [](std::string &key){
    const JsonBase *lReatur=nullptr;

    for (auto iBegin=lObject.begin(); iBegin != lObject.end(); iBegin++) {
        if((*iBegin)->getKey() == key){
            lReatur=(*iBegin)->getValue();
            break;
        }
    }
    return lReatur;
}
JsonStream & operator << (JsonStream & lout,const JsonObject & lin){
    auto iBegin=lin.lObject.begin();
    lout<<"{";
    if(iBegin != lin.lObject.end()){
        while (true) {
            lout<<(*iBegin)->getKey();
            lout<<":";

            if ((*iBegin)->getValue()) {
                switch ((*iBegin)->getValue()->getType()) {
                    case JsonType::Object:{
                        const JsonObject *obj=static_cast<const JsonObject*>((*iBegin)->getValue());
                        lout<<(*obj);
                    }break;
                    case JsonType::Array:{
                        const JsonArray *obj=static_cast<const JsonArray*>((*iBegin)->getValue());
                        lout<<(*obj); 
                    }break;
                    case JsonType::String:{
                        const JsonString *obj=static_cast<const JsonString*>((*iBegin)->getValue());
                        lout<<(*obj);
                    }break;
                    case JsonType::Number:{
                        const JsonNumber *obj=static_cast<const JsonNumber*>((*iBegin)->getValue());
                        lout<<(*obj);
                    }break;
                    case JsonType::Boolean:{
                        const JsonBoolean *obj=static_cast<const JsonBoolean*>((*iBegin)->getValue());
                        lout<<(*obj);
                    }break;
                    case JsonType::Null:{
                        const JsonNull *obj=static_cast<const JsonNull*>((*iBegin)->getValue());
                        lout<<(*obj);
                    }break;
                    default:{}break;
                }
            }else{

            }
            iBegin++;
            if (iBegin !=lin.lObject.end()) {
                lout<<",";
            }else{
                break;
            }
        }
    }
    lout<<"}";
    return lout;
}
