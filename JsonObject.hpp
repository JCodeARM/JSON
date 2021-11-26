//
//  JsonObject.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonObject_hpp
#define JsonObject_hpp

 
#include "JsonStream.hpp"

class JsonObject:public JsonBase{

public:

    JsonObject(JsonObject &)=delete;
    JsonObject(JsonObject &&)=delete;

    JsonObject & operator = (const JsonObject &)=delete;
    JsonObject & operator = (JsonObject &&)=delete;
    
    const JsonBase * operator [](std::string &key);


protected:
    JsonObject();
    ~JsonObject();
    
    void addProperty(std::string & lKey,JsonBase * lValue);
    friend JsonDocument;
private:

    class JsonObjectItem{
        std::string lKey;
        JsonBase *   lValue;
    public:
        JsonObjectItem()=delete;
        JsonObjectItem(JsonObjectItem &&)=delete;
        JsonObjectItem & operator = (const JsonObjectItem & )=delete;
        JsonObjectItem & operator = (JsonObjectItem && )=delete;

        JsonObjectItem(std::string & key,JsonBase * value ):lKey(key),lValue(value){}
        ~JsonObjectItem(){
            if(lValue){
                delete lValue;
                lValue=nullptr;
            }
        }
        inline const std::string & getKey()  const {return lKey;  }
        inline const JsonBase *    getValue()const {return lValue;}
    };


    std::list<JsonObjectItem *> lObject;
    friend JsonStream & operator << (JsonStream & lout,const JsonObject & lin);
};
#endif /* JsonObject_hpp */
