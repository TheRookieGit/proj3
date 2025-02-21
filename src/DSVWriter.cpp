#include "DSVWriter.h"
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>  // std::count

struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> dataSink;
    char delimiter;
    bool quoteAll;

    SImplementation(std::shared_ptr<CDataSink> sink, char delim, bool quote)
        : dataSink(sink), delimiter(delim), quoteAll(quote) {}

    bool WriteRow(const std::vector<std::string>& row) {
        // if (!dataSink){
        //     return false;
        // }

        std::string output;

        for (size_t i = 0; i< row.size(); i++){
            std::string input = row[i];

            bool if_delimiter = std::count(input.begin(), input.end(), delimiter) > 0;
            bool if_quote = std::count(input.begin(), input.end(), '"') > 0;
            bool if_newline = std::count(input.begin(), input.end(), '\n') > 0;

            bool ifneed_quote = quoteAll || if_delimiter || if_quote || if_newline;


            if (ifneed_quote){
                std::string output_quote = "\"";

                for (size_t j = 0; j < input.length(); j++){
                    if (input[j] == '"') {
                        output_quote += "\"\"";
                    } else {
                        output_quote += input[j];
                    }
                }

                output_quote += "\"";
                input = output_quote;
            }

            output += input;

            if (i < row.size()- 1){
                output += delimiter;
            }

            
        }
        output += "\n";

        std::vector<char> output_splitdata(output.begin(), output.end());
        return dataSink -> Write(output_splitdata);
        
        //return false;
    }
};


// Constructor for DSV writer, sink specifies the data destination, delimiter 
// specifies the delimiting character, and quoteall specifies if all values 
// should be quoted or only those that contain the delimiter, a double quote, 
// or a newline  
CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteAll)
    :DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteAll)) {}


// Destructor for DSV writer
CDSVWriter::~CDSVWriter() {}

// Returns true if the row is successfully written, one string per column  
// should be put in the row vector
bool CDSVWriter::WriteRow(const std::vector<std::string>& row) {
    return DImplementation -> WriteRow(row);
}
