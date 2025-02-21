#include "XMLWriter.h"
#include <stack>
#include <vector>
#include <string>

struct CXMLWriter::SImplementation {
    std::shared_ptr<CDataSink> dataSink;

    std::stack<std::string> opened_stack;

    SImplementation(std::shared_ptr<CDataSink> sink)
        : dataSink(sink) {}

    std::vector<char> convert_stringto_vector(const std::string& str) {
        return std::vector<char>(str.begin(), str.end());
    }

    bool Flush() {
        bool success = true;
        while(!opened_stack.empty()){
            std::string end_tag = "</" + opened_stack.top() + ">";
            
            if (!dataSink->Write(convert_stringto_vector(end_tag))){
                return false;
            }

            opened_stack.pop();
        }

        return success;



        //return false;
    }

    bool WriteEntity(const SXMLEntity& entity) {
        std::string output;

        if(entity.DType == SXMLEntity::EType::StartElement){
            output = "<" + entity.DNameData;

            for (const auto& attribute:entity.DAttributes){
                output += " " + attribute.first + "=\"" + attribute.second + "\"";
            }

            output += ">";

            opened_stack.push(entity.DNameData);
        }

        else if(entity.DType == SXMLEntity::EType::EndElement){
            if(opened_stack.empty() || opened_stack.top() != entity.DNameData){
                return false;
            }

            output = "</" + entity.DNameData + ">";
            opened_stack.pop();


        }

        else if(entity.DType == SXMLEntity::EType::CompleteElement){
            output = "<" + entity.DNameData;

            for (const auto& attribute:entity.DAttributes){
                output += " " + attribute.first + "=\"" + attribute.second + "\"";
            }

            output += "/>";

            //opened_stack.push(entity.DNameData);
        }

        else if(entity.DType == SXMLEntity::EType::CharData){ //https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents
            std::string text = entity.DNameData;
            size_t position = 0;
            bool check_notlast = true;

            while(check_notlast){
                position = text.find_first_of("<>&\"'", position); //https://en.cppreference.com/w/cpp/algorithm/find_first_of

                if(position == std::string::npos){
                    check_notlast = false;
                    continue;
                }

                else if (text[position] == '<'){
                    text.replace(position, 1, "&lt;");
                    position += 4;
                }

                else if (text[position] == '>'){
                    text.replace(position, 1, "&gt;");
                    position += 4;
                }

                else if (text[position] == '&'){
                    text.replace(position, 1, "&amp;");
                    position += 5;
                }

                else  if (text[position] == '"'){
                    text.replace(position, 1, "&quot;");
                    position += 6;
                }

                else if (text[position] == '\''){
                    text.replace(position, 1, "&apos;");
                    position += 6;
                }
            }
        }




        return dataSink->Write(convert_stringto_vector(output));
        //return false;
    }
};

// Constructor for XML writer, sink specifies the data destination 
CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
    : DImplementation(std::make_unique<SImplementation>(sink)) {}


// Destructor for XML writer
CXMLWriter::~CXMLWriter() {}

// Outputs all end elements for those that have been started
bool CXMLWriter::Flush() {
    return DImplementation->Flush();
}

// Writes out the entity to the output stream
bool CXMLWriter::WriteEntity(const SXMLEntity& entity) {
    return DImplementation->WriteEntity(entity);
}
