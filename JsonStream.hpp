//
//  JsonStream.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonStream_hpp
#define JsonStream_hpp

#include "JsonBase.hpp"
 
class JsonStream{

public:

    JsonStream();
    JsonStream(const JsonStream &)=delete;
    JsonStream(JsonStream && )=delete;

    JsonStream & operator =(const JsonStream &)=delete;
    JsonStream & operator =(JsonStream &&)=delete;
 
private: 
    std::list<std::string>  lListString;
    friend JsonStream & operator << (JsonStream & lout, std::string lin);
    friend JsonStream & operator << (JsonStream & lout, const char *lin);
    friend JsonStream & operator << (JsonStream & lout, double lin);

    friend std::ostream & operator << (std::ostream & lout, JsonStream &lin);

};
#endif /* JsonStream_hpp */
