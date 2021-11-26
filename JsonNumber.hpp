//
//  JsonNumber.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonNumber_hpp
#define JsonNumber_hpp

#include "JsonStream.hpp"
class JsonNumber:public JsonBase{

public:
    JsonNumber()=delete;
    JsonNumber(const JsonNumber &) = delete;
    JsonNumber(JsonNumber &&) = delete;
    JsonNumber & operator =(const JsonNumber &)=delete;
    JsonNumber & operator =(JsonNumber &&)=delete;

protected:
    JsonNumber(double vDouble);
    ~JsonNumber();
    friend JsonDocument;
private:
    double lDouble;
    friend JsonStream & operator <<(JsonStream & lout, const JsonNumber &lin);
};
#endif /* JsonNumber_hpp */
