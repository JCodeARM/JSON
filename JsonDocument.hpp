//
//  JsonDocument.hpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#ifndef JsonDocument_hpp
#define JsonDocument_hpp

#include "JsonObject.hpp" 
#include "JsonArray.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonBoolean.hpp"
#include "JsonNull.hpp"


enum class JsonDocumentFormat{
    Inndenter,
    Compact
};

class JsonDocument{

public:
    JsonDocument();
    JsonDocument(JsonDocument & ldoc); 
    JsonDocument(JsonDocument && ldoc);

    JsonDocument & operator = (const JsonDocument &)=delete;
    JsonDocument & operator = (JsonDocument &&)=delete;

    static JsonDocument fromVecotr(std::vector<char> & lArray);
    std::vector<char>   getVectorJson(JsonDocumentFormat lFormat=JsonDocumentFormat::Inndenter);

    
    ~JsonDocument();

    JsonObject *getNodeRoot();

    JsonObject  * addObject(JsonObject  * lObject,std::string &lProperty);
    JsonArray   * addArray(JsonObject   * lObject,std::string &lProperty);
    JsonNumber  * addNumber(JsonObject  * lObject,std::string &lProperty,double lValue);
    JsonString  * addString(JsonObject  * lObject,std::string &lProperty,std::string &lValue);
    JsonBoolean * addBoolean(JsonObject * lObject,std::string &lProperty,bool lValue);
    JsonNull    * addNull(JsonObject    * lObject,std::string &lProperty);

    JsonObject  * addObject(JsonArray   * lArray);
    JsonArray   * addArray(JsonArray    * lArray);
    JsonNumber  * addNumber(JsonArray   * lArray,double lValue);
    JsonString  * addString(JsonArray   * lArray,std::string &lValue);
    JsonBoolean * addBoolean(JsonArray  * lArray,bool lValue);
    JsonNull    * addNull(JsonArray     * lArray);

protected:
    void parseJson(const char* iBegin , const char* iEnd);

    void parseObject(JsonObject *lObject,std::list<std::string_view>  *listStringView);
    void parseArray(JsonArray *lArray,std::list<std::string_view>  *listStringView);
    
private:

    friend JsonStream & operator << (JsonStream & lout, JsonDocument & lin); 
    JsonObject *lJsonRootObject;
 
};

#endif /* JsonDocument_hpp */
