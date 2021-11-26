//
//  JsonBoolean.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonBoolean_hpp
#define JsonBoolean_hpp

#include "JsonStream.hpp"

class JsonBoolean:public JsonBase{

public:
    JsonBoolean()=delete;
    JsonBoolean(const JsonBoolean&) = delete;
    JsonBoolean(JsonBoolean&&) = delete;
    JsonBoolean& operator =(const JsonBoolean&)=delete;
    JsonBoolean& operator =(JsonBoolean&&)=delete;
protected: 
    JsonBoolean(bool vBool);
    ~JsonBoolean();
    friend JsonDocument;
private:
    bool lBool;
    friend JsonStream & operator <<(JsonStream & lout, const JsonBoolean &lin);
};
#endif /* JsonBoolean_hpp */
