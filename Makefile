PROJECT_NAME=json
SOURCE= JsonArray.cpp\
		JsonBoolean.cpp\
		JsonDocument.cpp\
		JsonNull.cpp\
		JsonStream.cpp\
		JsonNumber.cpp\
		JsonObject.cpp\
		JsonString.cpp



SOURCE_OBJECT= $(SOURCE:.cpp=.o)
 
CXXFLAGS = -std=c++11
CPP = g++

all:$(SOURCE_OBJECT)
	$(CPP) $(CXXFLAGS) main.cpp $(SOURCE_OBJECT)   -o $(PROJECT_NAME)

%.o:%.cpp
	$(CPP) -c $(CXXFLAGS) $< -o  $@

clear:
	rm $(PROJECT_NAME)
	rm *.o