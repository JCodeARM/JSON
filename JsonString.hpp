//
//  JsonString.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonString_hpp
#define JsonString_hpp

#include "JsonStream.hpp"

class JsonString:public JsonBase{

public:
    JsonString()=delete;
    JsonString(const JsonString&) = delete;
    JsonString(JsonString&&) = delete;
    JsonString& operator =(const JsonString&)=delete;
    JsonString& operator =(JsonString&&)=delete;

    inline const std::string & getStaing()const {return lString;}
protected: 
    JsonString(std::string &vString);
    ~JsonString();
    friend JsonDocument;
private:
    std::string lString;
    friend JsonStream & operator <<(JsonStream & lout, const JsonString &lin);
};
#endif /* JsonString_hpp */
