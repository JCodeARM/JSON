//
//  JsonStream.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonStream_hpp
#define JsonStream_hpp

#include "JsonBase.hpp"

enum class JsonStreamType{

    TerminalOut,
    ListOut
};
class JsonStream{

public:

    JsonStream(JsonStreamType type = JsonStreamType::TerminalOut);

    JsonStream(const JsonStream &)=delete;
    JsonStream(JsonStream && )=delete;

    JsonStream & operator =(const JsonStream &)=delete;
    JsonStream & operator =(JsonStream &&)=delete;

    const std::list<std::string> & getStringList();
private:
    JsonStreamType lType;
    std::list<std::string>  lListString;
    friend JsonStream & operator << (JsonStream & lout, std::string lin);
    friend JsonStream & operator << (JsonStream & lout, const char *lin);
    friend JsonStream & operator << (JsonStream & lout, double lin);

};
#endif /* JsonStream_hpp */
