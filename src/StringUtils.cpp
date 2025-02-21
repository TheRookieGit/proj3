#include "StringUtils.h"

//for EditDistance:
#include <vector> 
using std::vector;
#include <algorithm>
using std::min;

//for Split:
#include <string>
#include <cctype>

// [ RUN      ] StringUtilsTest.SliceTest
// [       OK ] StringUtilsTest.SliceTest (0 ms)
// [ RUN      ] StringUtilsTest.Capitalize
// [       OK ] StringUtilsTest.Capitalize (0 ms)
// [ RUN      ] StringUtilsTest.Upper
// [       OK ] StringUtilsTest.Upper (0 ms)
// [ RUN      ] StringUtilsTest.Lower
// [       OK ] StringUtilsTest.Lower (0 ms)
// [ RUN      ] StringUtilsTest.LStrip
// [       OK ] StringUtilsTest.LStrip (0 ms)
// [ RUN      ] StringUtilsTest.RStrip
// [       OK ] StringUtilsTest.RStrip (0 ms)
// [ RUN      ] StringUtilsTest.Strip
// [       OK ] StringUtilsTest.Strip (0 ms)
// [ RUN      ] StringUtilsTest.Center
// [       OK ] StringUtilsTest.Center (0 ms)
// [ RUN      ] StringUtilsTest.LJust
// [       OK ] StringUtilsTest.LJust (0 ms)
// [ RUN      ] StringUtilsTest.RJust
// [       OK ] StringUtilsTest.RJust (0 ms)
// [ RUN      ] StringUtilsTest.Replace
// [       OK ] StringUtilsTest.Replace (0 ms)
// [ RUN      ] StringUtilsTest.Split
// [       OK ] StringUtilsTest.Split (0 ms)
// [ RUN      ] StringUtilsTest.Join
// [       OK ] StringUtilsTest.Join (0 ms)
// [ RUN      ] StringUtilsTest.ExpandTabs
// [       OK ] StringUtilsTest.ExpandTabs (0 ms)
// [ RUN      ] StringUtilsTest.EditDistance
// [       OK ] StringUtilsTest.EditDistance (0 ms)

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (str.empty()) return str;

    ssize_t length = static_cast<ssize_t>(str.length());

    if (start < 0){
        start += length;
        if (start < 0){
            start = 0;
        }
    }

    if (end < 0){
        end += length;
        if (end < 0){
            end = 0;
        }
    }

    if (start > length){
        start = length;
    }

    if (end > length || end == 0){
        end = length;
    }

    if (start >= end){
        return std::string();
    }

    return str.substr(start, end - start);
}

std::string Capitalize(const std::string &str) noexcept{
    if (str.empty()) return str;
    std::string output = str;
    for (char& lowercase_char: output){
        lowercase_char = std::tolower(lowercase_char);
    }
    output[0] = std::toupper(output[0]);

    return output;
}

std::string Upper(const std::string &str) noexcept{
    std::string output = str;
    for (size_t i = 0; i < output.size(); i++){
        output[i] = std::toupper(static_cast<unsigned char>(output[i]));
    }
    return output;
}

std::string Lower(const std::string &str) noexcept{
    std::string output = str;
    for (size_t i = 0; i < output.size(); i++){
        output[i] = std::tolower(static_cast<unsigned char>(output[i]));
    }
    return output;
}

std::string LStrip(const std::string &str) noexcept{
    size_t start = 0;

    while (start < str.length() && std::isspace(static_cast<unsigned char>(str[start]))){
        start ++;
    }

    if (start == str.length()){
        return "";
    } else {
        return str.substr(start);
    }

}

std::string RStrip(const std::string &str) noexcept{
    size_t start = 0;
    size_t end = str.length();

    while (end > 0 && std::isspace(static_cast<unsigned char>(str[end - 1]))){
        end --;
    }

    if (start == str.length()){
        return "";
    } else {
        return str.substr(0, end);
    }
}

std::string Strip(const std::string &str) noexcept{
    return LStrip(RStrip(str));

}

std::string Center(const std::string &str, int width, char fill) noexcept{
    if (str.length() >= width){
        return str;
    }

    int fill_size = width - str.length();

    int left_fill = (fill_size) / 2;
    int right_fill = (fill_size + 1) / 2;

    return std::string(left_fill, fill) + str + std::string(right_fill, fill);


}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    if (str.length() >= width){
        return str;
    }

    int adding_size = width - str.length();
    std::string adding_char = "";
    for (int i = 0; i < adding_size; i++){
        adding_char += fill;
    }

    return str + adding_char;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
        if (str.length() >= width){
        return str;
    }

    int adding_size = width - str.length();
    std::string adding_char = "";
    for (int i = 0; i < adding_size; i++){
        adding_char += fill;
    }

    return adding_char + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    if (old.empty()) return str;

    std::string output = "";
    size_t start = 0;
    size_t find_old = str.find(old, start);  

    while (find_old != -1){
        output += str.substr(start, find_old - start);
        output += rep;
        start = find_old + old.length();
        find_old = str.find(old, start);
    }  

    output += str.substr(start);

    return output;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> output;

    // if (str.empty() && !splt.empty()){
    //     output.push_back("");

    // }
    if (str.empty()){
        output.push_back("");

    }


    if (splt.empty()){
        std::string temp_output;
        // for (char char_now: str){
        //     if (char_now ==' '){

        for (size_t i =0; i < str.length(); i++){
            if (std::isspace(static_cast<unsigned char>(str[i]))){
                if (!temp_output.empty()){
                    output.push_back(temp_output);
                    temp_output.clear();
                }
            }else{
                temp_output += str[i];
            }
        }
        if (!temp_output.empty()){ //adding last part after split "splt"
            output.push_back(temp_output);
        }


    } else {
        size_t current_position = 0;
        size_t split_length = splt.length();

        for (size_t i = 0; i < str.length(); i++){
            if (str.substr(i, split_length) == splt){
                output.push_back(str.substr(current_position, i - current_position));
                current_position = i + split_length;
                i += split_length - 1;
            }

    }
        //if (!temp_output.empty()){ //adding last part after split "splt"
        if (current_position < str.length()){
                    output.push_back(str.substr(current_position));
                }
        }


    

    return output;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    if (vect.empty()) return "";

    std::string output = vect[0];
    
    for (size_t i = 1; i < vect.size(); i++){
        output += str;
        output += vect[i];
    }

    return output;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    if (str.empty()) return "";

    //if(tabsize == 0) return str;

    if (tabsize < 0) return str; 



    std::string output;
    size_t new_position = 0;


    for (size_t i = 0; i < str.size(); i++){
        char character = str[i];

        if (character == '\t'){
            int new_tabsize = tabsize - (new_position%tabsize);
            output += std::string(new_tabsize, ' ');
            new_position += new_tabsize;
        } else {
            output += character;
            new_position++;
        }

    }
    return output;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    size_t left_size = left.size(), right_size = right.size();
    vector<vector<size_t>> table (left_size + 1, vector<size_t>(right_size + 1));

    for (size_t i = 0; i <= left_size; i++){
        table[i][0] = i;
    }
    for (size_t j = 0; j <= right_size; j++){
        table[0][j] = j;
    }

    for (size_t i = 1; i <= left_size; i++){
        for(size_t j = 1; j <= right_size; j++){
            char left_case = left[i-1];
            char right_case = right[j-1];

            if (ignorecase){
                left_case = std::tolower(static_cast<unsigned char>(left_case));
                right_case = std::tolower(static_cast<unsigned char>(right_case));
            }


            //if(left[i-1] == right[j-1]){
            if(left_case == right_case){
                table[i][j] = table[i - 1][j - 1];

            }
            else{
                table[i][j] = min({table[i-1][j-1], table[i-1][j],table[i][j-1]}) + 1;
            }
        }
    }
    return table[left_size][right_size];

}

};