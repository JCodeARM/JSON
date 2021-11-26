//
//  main.cpp
//  JSON
//
//  Created by Iulian on 13.03.2013.
//

#include <iostream>
#include "JsonDocument.hpp"

void vSignal(int i){

}
int main(int argc, const char * argv[]) {

    signal(SIGABRT, vSignal);

    std::string pathFile(getenv("PWD"));
    pathFile.append("/file/may.json");

    std::vector<char> lArray;
    FILE *lFile=fopen(pathFile.data(), "r");

    if (lFile) {
        fseek(lFile, 0, SEEK_END);
        lArray.reserve(ftell(lFile));
        fseek(lFile, 0, SEEK_SET);


        if(lFile){
            char buffer[1024];
            std::size_t readSize;
            while ((readSize=fread(buffer, 1, 1024, lFile)) > 0) {
                for (int var=0; var < readSize; var++) {
                    lArray.push_back(buffer[var]);
                }
            }
        }
        {
            std::cout<<"Read Json"<<std::endl;
            try {

                JsonDocument docParse=JsonDocument::fromVecotr(lArray);

                JsonStream stream(JsonStreamType::ListOut);
                stream<<docParse;

                auto flit=stream.getStringList();
                for (auto iBegin=flit.begin(); iBegin != flit.end(); iBegin++) {
                    std::cout<<(*iBegin);
                }
            } catch (std::string e) {
                std::cerr<<e<<std::endl;
            }
            std::cout<<std::endl;
        }
        {
            std::cout<<"Parse Json"<<std::endl;

            JsonDocument docCreate;
            JsonObject *root=docCreate.getNodeRoot();

            std::string mayProperty1("Property null");
            docCreate.addNull(root,mayProperty1);

            std::string mayProperty2("Property Number");
            docCreate.addNumber(root, mayProperty2, 888.65);

            std::string mayPropertyObject("Property Object");
            docCreate.addObject(root, mayPropertyObject);


            JsonStream stream(JsonStreamType::TerminalOut);

            stream<<docCreate;

            std::cout<<std::endl;
        }


    }else{
        std::cerr<<std::string(std::strerror(errno))<<std::endl;
    }




    return 0;
}
