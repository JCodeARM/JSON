//
//  JsonBase.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonBase_hpp
#define JsonBase_hpp

#include "config.hpp"

#include <vector>
#include <list>
#include <string>
#include <iostream>

class JsonDocument;
enum class JsonType:int{
    Empty,
    Object,
    Array,
    String,
    Number,
    Boolean,
    Null
};
 
class JsonBase{

public:
    JsonBase(JsonBase &)  =delete;
    JsonBase(JsonBase &&) =delete;

    inline JsonType getType()const{return lType;}
protected:
    JsonBase(){}
    JsonType lType={JsonType::Empty};
};
#endif /* JsonBase_hpp */
