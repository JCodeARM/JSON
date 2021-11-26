//
//  JsonArray.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonArray_hpp
#define JsonArray_hpp

#include "JsonStream.hpp"

class JsonArray:public JsonBase{

public:
 
    JsonArray(const JsonArray &) = delete;
    JsonArray(JsonArray &&) = delete;
    JsonArray & operator =(const JsonArray &)=delete;
    JsonArray & operator =(JsonArray &&)=delete;

 
    std::size_t size();



    

protected:
    JsonArray();
    ~JsonArray();
    void additem(JsonBase * lValue);
    friend JsonDocument;
private:
    std::vector<JsonBase *> lArray;
    friend JsonStream & operator <<(JsonStream & lout, const JsonArray &lin);
};
#endif /* JsonArray_hpp */
