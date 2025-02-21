#include "XMLReader.h"
#include <expat.h>
#include <queue> //https://www.geeksforgeeks.org/difference-between-queue-and-deque-queue-vs-deque/
#include <deque>
#include <vector>

struct CXMLReader::SImplementation {
    std::shared_ptr<CDataSource> dataSource;

    XML_Parser xml_parser;
    //std::queue<SXMLEntity> saved_entity;
    std::deque<SXMLEntity> saved_entity;
    
    bool success = false;
    //std::vector<char> buffer;

//https://libexpat.github.io/doc/api/latest/#XML_SetCharacterDataHandler
    SImplementation(std::shared_ptr<CDataSource> src) : dataSource(src) {
            xml_parser = XML_ParserCreate(nullptr);
            XML_SetUserData(xml_parser, this);
            XML_SetElementHandler(xml_parser, XML_StartElementHandler, XML_EndElementHandler);
            XML_SetCharacterDataHandler(xml_parser, XML_CharacterDataHandler);


        }


    ~SImplementation(){
        if(xml_parser){
            XML_ParserFree(xml_parser);
        }
    }

    //static void 

    // bool End() {



    //     return success && saved_entity.empty();
    // }

    bool ReadEntity(SXMLEntity& entity, bool skipcdata) {





        while (!success&& saved_entity.empty()){
            //std::vector<char> input_character;
            
            const std::size_t buffer = 4096;
            std::vector<char> input_character(buffer);


            if(!dataSource->Read(input_character, buffer)){
                success = true;
                XML_Parse(xml_parser, nullptr, 0, 1);
                break;
            }

            if(!XML_Parse(xml_parser, input_character.data(), input_character.size(), 0)){
                success = true;
                //return true;
                return false;
            }
        }

        if (saved_entity.empty()){
            return false;
        }



        entity = saved_entity.front();
        //saved_entity.pop();
        saved_entity.pop_front();

        // last note: added complete element check
        if (entity.DType == SXMLEntity::EType::StartElement){
            if(!saved_entity.empty()){
                SXMLEntity ending_merge = saved_entity.front();

                if (ending_merge.DType == SXMLEntity::EType::EndElement && ending_merge.DNameData == entity.DNameData){
                    saved_entity.pop_front();
                    entity.DType = SXMLEntity::EType::CompleteElement;
                }
            }
        }
        //****** */

        if (skipcdata && !saved_entity.empty() && saved_entity.front().DType == SXMLEntity::EType::CharData){
            saved_entity.pop_front();
            return ReadEntity(entity, skipcdata);
        }
        return true;
    }

    static void XML_StartElementHandler(void* userData, const XML_Char* tag_name, const XML_Char** attributes){
        auto* parser_data = static_cast<SImplementation*>(userData);
        SXMLEntity entity;

        entity.DType = SXMLEntity::EType::StartElement;
        entity.DNameData = tag_name;


        for (int i = 0; attributes[i]; i += 2){
            entity.SetAttribute(attributes[i], attributes[i+1]);
        }
        parser_data->saved_entity.push_back(entity);
    }

    

    static void XML_CharacterDataHandler(void* userData, const XML_Char* chartacter_data, int length){
        auto* parser_data = static_cast<SImplementation*>(userData);
        
        if (std::string(chartacter_data, length).find_first_not_of(" \t\n\r") != std::string::npos){
        
        SXMLEntity entity;

        entity.DType = SXMLEntity::EType::CharData;
        //entity.DNameData = tag_name;
        entity.DNameData = std::string(chartacter_data, length);

        parser_data->saved_entity.push_back(entity);
        }
    }

    static void XML_EndElementHandler(void* userData, const XML_Char* tag_name){
        auto* parser_data = static_cast<SImplementation*>(userData);
        SXMLEntity entity;

        entity.DType = SXMLEntity::EType::EndElement;
        entity.DNameData = tag_name;

        parser_data->saved_entity.push_back(entity);
    }



    bool End() {



        return success && saved_entity.empty();
    }
};


// Constructor for XML reader, src specifies the data source 
CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src)
    : DImplementation(std::make_unique<SImplementation>(src)) {}


// Destructor for XML reader
CXMLReader::~CXMLReader() {}

// Returns true if all entities have been read from the XML
bool CXMLReader::End() const{
    return DImplementation->End();
}

// Returns true if the entity is successfully read if skipcdata 
// is true only element type entities will be returned
bool CXMLReader::ReadEntity(SXMLEntity& entity, bool skipcdata) {
    return DImplementation->ReadEntity(entity, skipcdata);
}
