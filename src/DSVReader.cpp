#include "DSVReader.h"
#include <vector>
#include <string>

struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> dataSource;
    char delimiter;

    SImplementation(std::shared_ptr<CDataSource> src, char delim)
        : dataSource(src), delimiter(delim) {}

    bool End() const {
        return dataSource -> End();
    }

    bool ReadRow(std::vector<std::string>& row) {
        if (dataSource->End()){
            return false;

        }

        row.clear();
        std::string working_character;
        bool if_qoute = false;
        char reading_character;

        while (dataSource->Get(reading_character)){

            //did not regonize "" in gradescope test
            if (reading_character == '"'){
                char detect_quote;

                if (if_qoute && dataSource->Peek(detect_quote) && detect_quote == '"'){
                    working_character += '"';

                    dataSource->Get(detect_quote);
                }else{
                    if_qoute = !if_qoute;
                }
            }

            // if (reading_character == '"'){
            //     if (if_qoute && dataSource->Peek(reading_character) && reading_character == '"'){
            //         working_character += '"';

            //         dataSource->Get(reading_character);
            //     }else{
            //         if_qoute = !if_qoute;
            //     }
            // }
            else if(reading_character == delimiter && !if_qoute){

                row.push_back(working_character);
                working_character.clear();
            }
            else if (reading_character == '\n' && !if_qoute){
                row.push_back(working_character);
                // working_character.clear();
                return true;
            }
            else{
                working_character += reading_character;
            }
        }


        if(!working_character.empty() || !row.empty()){
            row.push_back(working_character);
        }
    


        return !row.empty();
    }
};


// Constructor for DSV reader, src specifies the data source and delimiter  
// specifies the delimiting character
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter)
    : DImplementation(new SImplementation(src, delimiter)) {
}

// Destructor for DSV reader
CDSVReader::~CDSVReader() {
}

// Returns true if all rows have been read from the DSV
bool CDSVReader::End() const {
    return DImplementation->End();
}

// Returns true if the row is successfully read, one string will be put in  
// the row per column
bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    return DImplementation -> ReadRow(row);
}
