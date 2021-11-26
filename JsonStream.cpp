//
//  JsonStream.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonStream.hpp"
JsonStream::JsonStream(JsonStreamType type):lType(type){
    
}
const std::list<std::string> & JsonStream::getStringList(){
    return lListString;
} 
JsonStream & operator << (JsonStream & lout, std::string lin){
    switch (lout.lType) {
        case JsonStreamType::TerminalOut:{
            std::cout<<lin;
        }break;
        case JsonStreamType::ListOut:{
            lout.lListString.push_back(lin);
        }break;
        default:{ }break;
    }
    return lout;
}
JsonStream & operator << (JsonStream & lout, double lin){
    return lout<<std::to_string(lin);
}
JsonStream & operator << (JsonStream & lout, const char *lin){
    return lout<<std::string(lin);
}