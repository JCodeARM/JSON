//
//  JsonNull.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonNull_hpp
#define JsonNull_hpp

#include "JsonStream.hpp"
class JsonNull:public JsonBase{

public:
    
    JsonNull(const JsonNull&) = delete;
    JsonNull(JsonNull&&) = delete;
    JsonNull& operator =(const JsonNull&)=delete;
    JsonNull& operator =(JsonNull&&)=delete;
protected:
    JsonNull();
    ~JsonNull();
    friend JsonDocument;
private:
    friend JsonStream & operator <<(JsonStream & lout, const JsonNull &lin);
};
#endif /* JsonNull_hpp */
