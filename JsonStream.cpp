//
//  JsonStream.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonStream.hpp"
JsonStream::JsonStream(){
    
} 
JsonStream & operator << (JsonStream & lout, std::string lin){
            lout.lListString.push_back(lin);
    return lout;
}
JsonStream & operator << (JsonStream & lout, double lin){
    return lout<<std::to_string(lin);
}
JsonStream & operator << (JsonStream & lout, const char *lin){
    return lout<<std::string(lin);
}
std::ostream & operator << (std::ostream & lout, JsonStream &lin){
    for (auto iBegin=lin.lListString.begin(); iBegin != lin.lListString.end(); iBegin++) {
        std::cout<<(*iBegin);
    }
    return lout;
}
