//
//  JsonDocument.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include "JsonDocument.hpp"

#define SHOW_LIST( list ) for (auto iteratorBeing=list.begin(); iteratorBeing != list.end(); iteratorBeing++) {\
std::cout<<(*iteratorBeing)<<std::endl;}

#define SHOW_LIST_POINT( list ) for (auto iteratorBeing=list->begin(); iteratorBeing != list->end(); iteratorBeing++) {\
std::cout<<(*iteratorBeing)<<std::endl;}
enum class TokenNext{
    None,
    Start,
    End,
};
JsonDocument::JsonDocument():lJsonRootObject(nullptr){
    
}
JsonDocument::~JsonDocument(){
    if (lJsonRootObject != nullptr) {
        delete lJsonRootObject;
        lJsonRootObject=nullptr;
    }
}
JsonDocument::JsonDocument(JsonDocument & ldoc){
    lJsonRootObject=ldoc.lJsonRootObject;
    ldoc.lJsonRootObject=nullptr;
}
JsonDocument::JsonDocument(JsonDocument && ldoc){
    lJsonRootObject=ldoc.lJsonRootObject;
    ldoc.lJsonRootObject=nullptr;
}
JsonObject * JsonDocument::getNodeRoot(){
    if (lJsonRootObject == nullptr) {
        lJsonRootObject=new JsonObject();
    }
    return lJsonRootObject;
}
JsonObject  * JsonDocument::addObject(JsonObject  * lObject,std::string &lProperty){
    JsonObject *lReturn;
    lReturn=new JsonObject();
   std::string s("\""+lProperty+"\"");
    lObject->addProperty(s, lReturn);
    return lReturn;
}
JsonArray   * JsonDocument::addArray(JsonObject   * lObject,std::string &lProperty){
    JsonArray *lReturn;
    lReturn=new JsonArray();
    std::string s("\""+lProperty+"\"");
    lObject->addProperty(s, lReturn);
    return lReturn;
}
void JsonDocument::addNumber(JsonObject  * lObject,std::string &lProperty,double lValue){

    std::string s("\""+lProperty+"\"");
    lObject->addProperty(s, new JsonNumber(lValue));
}
void JsonDocument::addString(JsonObject  * lObject,std::string &lProperty,std::string &lValue){

    std::string s("\""+lProperty+"\"");
    lObject->addProperty(lProperty, new JsonString(s));
}
void JsonDocument::addBoolean(JsonObject * lObject,std::string &lProperty,bool lValue){

    std::string s("\""+lProperty+"\"");
    lObject->addProperty(s, new JsonBoolean(lValue));
}
void JsonDocument::addNull(JsonObject    * lObject,std::string &lProperty){

    std::string s("\""+lProperty+"\"");
    lObject->addProperty(s, new JsonNull());
}

JsonObject  * JsonDocument::addObject(JsonArray   * lArray){
    JsonObject *lReturn;
    lReturn=new JsonObject();
    lArray->additem(lReturn);
    return lReturn;
}
JsonArray   * JsonDocument::addArray(JsonArray    * lArray){
    JsonArray *lReturn;
    lReturn=new JsonArray();
    lArray->additem(lReturn);
    return lReturn;
}
void JsonDocument::addNumber(JsonArray   * lArray,double lValue){

    lArray->additem(new JsonNumber(lValue));
}
void JsonDocument::addString(JsonArray   * lArray,std::string &lValue){

    std::string s("\""+lValue+"\"");
    lArray->additem(new JsonString(s));
}
void JsonDocument::addBoolean(JsonArray  * lArray,bool lValue){

    lArray->additem(new JsonBoolean(lValue));
}
void  JsonDocument::addNull(JsonArray     * lArray){

    lArray->additem(new JsonNull()); 
}

std::vector<char> JsonDocument::getVectorJson(JsonDocumentFormat lFormat){
    std::vector<char> lReturn;
    switch (lFormat) {
        case JsonDocumentFormat::Inndenter:{
        }break;
        case JsonDocumentFormat::Compact:{
        }break;
        default:
            break;
    }
    return lReturn;
}
void JsonDocument::parseJson(const char* iBegin , const char* iEnd){

    // BEGIN PARSS TOKEN
    const char *iSearch=iBegin;
    std::list<std::string_view> listToken;

    while (iSearch < iEnd) {

        if((*iSearch) == ':' || (*iSearch) == '{' || (*iSearch) == '}' ||
           (*iSearch) == '[' || (*iSearch) == ']' || (*iSearch) == ','){
            listToken.push_back(std::string_view(iSearch,1));
            iSearch++;
            continue;
        }else if ((*iSearch) == '"'){
            const char *iStart=iSearch;
            iSearch++;
            while (iSearch < iEnd) {
                if (std::strncmp(iSearch, "\\\"", 2) == 0){
                    iSearch+=2;
                    continue;
                }else if((*iSearch) == '"'){
                    listToken.push_back(std::string_view(iStart,(iSearch-iStart)+1));
                    iSearch++;
                    break;
                }
                iSearch++;
            }
            continue;
        }else if ((std::strncmp(iSearch, "null", 4) == 0)  || (std::strncmp(iSearch, "true", 4) == 0)){
            listToken.push_back(std::string_view(iSearch,4));
            iSearch+=4;
            continue;
        }else if ( std::strncmp(iSearch, "false", 5) == 0){
            listToken.push_back(std::string_view(iSearch,5));
            iSearch+=5;
            continue;
        }else if (std::isdigit(*iSearch)){
            const char *iStart=iSearch;
            int pointSize=0;
            while (iSearch < iEnd && ((std::isdigit(*iSearch)) || (*iSearch == '.' && ++pointSize)) ) {
                if (pointSize > 1) {
                    throw std::string("Error Token Multi Point: File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                }
                iSearch++;
            }
            listToken.push_back(std::string_view(iStart,(iSearch-iStart)));
            continue;
        }
        iSearch++;
    }
    // END   PARSS  TOKEN
    // BEGIN SHOW PARSS  TOKEN
#ifdef SHOW_TOKEN_TERMINAL
    SHOW_LIST(listToken)
#endif
    // END   SHOW PARSS  TOKEN
    // BEGIN CREATE THREE OBJECT

    if (listToken.size() > 1 ) {
        if (listToken.front() == "{" && listToken.back() == "}" ) {
            listToken.pop_back();
            listToken.pop_front();
            lJsonRootObject=new JsonObject();
            parseObject(lJsonRootObject,&listToken);
        }else{
            throw  std::string("Error root ");
        }
    }
    // END   CREATE TREE OBJECT
}
void JsonDocument::parseObject(JsonObject *lObject,std::list<std::string_view>  *listStringView){


    TokenNext lNextItem=TokenNext::None;

    for (auto iBegin=listStringView->begin(); iBegin != listStringView->end(); iBegin++) {
        auto iSearch=&(*iBegin);
        if((*iSearch).length() > 1 && (*iSearch).back() == '"'  && (*iSearch).front() == '"'){
            iBegin++;

            if ( iBegin != listStringView->end()) {
                if ((*iBegin) == ":") {
                    iBegin++;
                    if(iBegin != listStringView->end()){

                        if ((*iBegin) == "{"){
                            std::list<std::string_view> sObjectList;
                            int tNumber=1;
                            for ( iBegin++; iBegin != listStringView->end(); iBegin++) {

                                if ((*iBegin) == "{") {
                                    tNumber++;
                                }else if ((*iBegin) == "}"){
                                    tNumber--;
                                    if (tNumber == 0) {
                                        break;
                                    }
                                }
                                sObjectList.push_back(*iBegin);
                            }
                            if (tNumber == 0 ) {

                                std::string s(*iSearch);
                                JsonObject *tObject= new JsonObject();
                                lObject->addProperty(s, tObject);
                                parseObject(tObject,&sObjectList);
                                lNextItem=TokenNext::End;
                                
                            }else{
                                throw std::string("Error Token {}: File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                            }
                        }else if ((*iBegin) == "["){
                            std::list<std::string_view> sArrayList;
                            int tNumber=1;
                            for ( iBegin++; iBegin != listStringView->end(); iBegin++) {

                                if ((*iBegin) == "[") {
                                    tNumber++;
                                }else if ((*iBegin) == "]"){
                                    tNumber--;
                                    if (tNumber == 0) {
                                        break;
                                    }
                                }
                                sArrayList.push_back(*iBegin);
                            }
                            if (tNumber == 0 ) {

                                std::string s(*iSearch);
                                JsonArray *tArray= new JsonArray();
                                lObject->addProperty(s, tArray);
                                parseArray(tArray,&sArrayList);
                                lNextItem=TokenNext::End;
                            }else{
                                throw std::string("Error Token []: File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                            }
                        }else if ((*iBegin).length() > 1 && (*iBegin).front() == '"' && (*iBegin).back()){
                            std::string s(*iSearch);
                            std::string v(*iBegin);
                            lObject->addProperty(s, new JsonString(v));
                            lNextItem=TokenNext::End;
                        }else if ((*iBegin) == "null"){
                            std::string s(*iSearch);
                            lObject->addProperty(s, new JsonNull());
                            lNextItem=TokenNext::End;
                        }else if((*iBegin) == "true" ){
                            std::string s(*iSearch);
                            lObject->addProperty(s, new JsonBoolean(true));
                            lNextItem=TokenNext::End;
                        }else if ((*iBegin) == "false"){
                            std::string s(*iSearch);
                            lObject->addProperty(s, new JsonBoolean(false));
                            lNextItem=TokenNext::End;
                        }else if ((*iBegin).length() > 0 && std::isdigit((*iBegin).front()) ){
                            std::string s(*iSearch);
                            double d=std::atof(std::string(*iBegin).data());
                            lObject->addProperty(s, new JsonNumber(d));
                            lNextItem=TokenNext::End;
                        }else if ((*iBegin) == ",") {
                            throw std::string("Error Token (,): File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                        }

                        auto iteratorNextItem=iBegin;
                        iteratorNextItem++;
                        if (TokenNext::End == lNextItem && iteratorNextItem != listStringView->end() && (*iteratorNextItem) == ",") {
                            iBegin=iteratorNextItem;
                            lNextItem=TokenNext::Start;
                        }

                    }else{
                        throw std::string("Error Token : File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                    }
                }else{

                    throw std::string("Error Token : File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                }
            }else{
                throw std::string("Error Token : File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
            }

        }else{
            throw std::string("Error Token ("+std::string(*iSearch)+"): File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
        }
    }

    if (lNextItem == TokenNext::Start) {
        throw std::string("Error Token (,): File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
    }
}
void JsonDocument::parseArray(JsonArray *lArray,std::list<std::string_view>  *listStringView){

    TokenNext lNextItem=TokenNext::None;

    for (auto iBegin=listStringView->begin(); iBegin != listStringView->end(); iBegin++) {

        if ((*iBegin).length() > 0) {

            if ((*iBegin).front() == '{') {
                std::list<std::string_view> sObjectList;
                int tNumber=1;
                for ( iBegin++; iBegin != listStringView->end(); iBegin++) {

                    if ((*iBegin) == "{") {
                        tNumber++;
                    }else if ((*iBegin) == "}"){
                        tNumber--;
                        if (tNumber == 0) {
                            break;
                        }
                    }
                    sObjectList.push_back(*iBegin);
                }
                if (tNumber == 0) {

                    JsonObject *tObject= new JsonObject();
                    lArray->additem(tObject);
                    parseObject(tObject,&sObjectList);
                    lNextItem=TokenNext::End;
                }else{
                    throw std::string("Error Token {}: File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                }
            }else if((*iBegin).front() == '['){
                std::list<std::string_view> sArrayList;
                int tNumber=1;
                for ( iBegin++; iBegin != listStringView->end(); iBegin++) {

                    if ((*iBegin) == "[") {
                        tNumber++;
                    }else if ((*iBegin) == "]"){
                        tNumber--;
                        if (tNumber == 0) {
                            break;
                        }
                    }
                    sArrayList.push_back(*iBegin);
                }
                if (tNumber == 0) {


                    JsonArray *tArray= new JsonArray();
                    lArray->additem( tArray);
                    parseArray(tArray,&sArrayList);
                    lNextItem=TokenNext::End;
                }else{
                    throw std::string("Error Token []: File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
                }
            }else if ((*iBegin).front() == '"'){
                std::string s(*iBegin);
                lArray->additem(new JsonString(s));
                lNextItem=TokenNext::End;
            }else if (std::isdigit((*iBegin).front())){
                double d=std::atof(std::string(*iBegin).data());
                lArray->additem(new JsonNumber(d));
                lNextItem=TokenNext::End;
            }else if ((*iBegin) == "true"){
                lArray->additem(new JsonBoolean(true));
                lNextItem=TokenNext::End;
            }else if ((*iBegin) == "false"){
                lArray->additem(new JsonBoolean(false));
                lNextItem=TokenNext::End;
            }else if ((*iBegin) == "null"){
                lArray->additem(new JsonNull());
                lNextItem=TokenNext::End;
            }else if ((*iBegin) == ","){
                throw std::string("Error Token , : File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
            }
        }else{
            throw std::string("Error Token : File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
        }

        auto iteratorNextItem=iBegin;
        iteratorNextItem++;
        if (TokenNext::End == lNextItem && iteratorNextItem != listStringView->end() && (*iteratorNextItem) == ",") {
            iBegin=iteratorNextItem;
            lNextItem=TokenNext::Start;
        }
    }

    if (lNextItem == TokenNext::Start) {
        throw std::string("Error Token (,): File Name:"+std::string(__FILE_NAME__)+" Line:"+std::to_string(__LINE__));
    }
}
JsonDocument JsonDocument::fromVecotr(std::vector<char> & lArray){
    JsonDocument lReturnDoc;

    if(lArray.empty() == false){
        const char *iBegine=lArray.data();
        const char *iEnd=iBegine+lArray.size();
        lReturnDoc.parseJson(iBegine, iEnd);

    }
    return lReturnDoc;
}
// BEGIN OPERATOR <<
JsonStream & operator <<(JsonStream & lout, JsonDocument & lin){

    if (lin.lJsonRootObject) {
        lout<<(*lin.lJsonRootObject);
    }
    return lout;
}
// END   OPERATOR OSTREAM <<
 
