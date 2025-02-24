#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "StringDataSource.h"

#include "OpenStreetMap.h"
#include "XMLReader.h"


#include <string>
#include <memory>
using std::string;

using std::shared_ptr;

//added for ifstream and fileread
#include <sstream>
#include <fstream>

std::shared_ptr<CXMLReader> CreateXMLReader_proj3(const std::string& input_file){
    
    // -----------------

    std::ifstream reading_file(input_file);

    std::string reading_content;
    std::string reading_lines;

    while(std::getline(reading_file, reading_lines)){
        reading_content += reading_lines;
        reading_content += "\n";
    }
    // above copyed from BusSystemTest

    auto datasource = std::make_shared<CStringDataSource>(reading_content);
    return std::make_shared<CXMLReader>(datasource);
}

//! **************************************************************************
//! Wait Until CSVBusSystem function complete then uncomment everything below
//! Otherwise had segment fault
//! **************************************************************************




// TEST(OpenStreetMapTest, Node_andWay_Counts){
//     //auto datasource = std::make_shared<CStringDataSource>("data/davis.osm");

//     //auto read_xmldata = std::make_shared<CXMLReader>(datasource);

//     auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");

//     //CXMLReader CreateXMLReader_proj3(datasource);

//     COpenStreetMap OpenStreetMap(read_xmldata);

//     EXPECT_EQ(OpenStreetMap.NodeCount(), 10259);
//     EXPECT_EQ(OpenStreetMap.WayCount(), 1644);
// }

// TEST(OpenStreetMapTest, NodeIndex_andID){
//     //auto datasource = std::make_shared<CStringDataSource>("data/davis.osm");

//     //auto read_xmldata = std::make_shared<CXMLReader>(datasource);
    
//     auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");

//     //CXMLReader CreateXMLReader_proj3(datasource);

//     COpenStreetMap OpenStreetMap(read_xmldata);

//     auto node_index0 = OpenStreetMap.NodeByIndex(0);

//     EXPECT_EQ(node_index0->ID(), 62208369);

//     // EXPECT_EQ(node_index0->Location().first, 38.5178523);
//     // EXPECT_EQ(node_index0->Location().second, -121.7712408);

//     EXPECT_NEAR(node_index0->Location().first, 38.5178523, 1e-6);
//     EXPECT_NEAR(node_index0->Location().second, -121.7712408, 1e-6);

//     auto node_id0 = OpenStreetMap.NodeByID(62209104);

//     EXPECT_EQ(node_id0->ID(), 62209104);

    
//     // EXPECT_EQ(node_index0->Location().first, 38.535052);
//     // EXPECT_EQ(node_index0->Location().second, -121.7408606);


//     EXPECT_NEAR(node_id0->Location().first, 38.535052, 1e-6);
//     EXPECT_NEAR(node_id0->Location().second, -121.7408606, 1e-6);


//     EXPECT_EQ(OpenStreetMap.NodeByID(9999999999), nullptr);
// }


// TEST(OpenStreetMapTest, Node_Attributes){
//     //auto datasource = std::make_shared<CStringDataSource>("data/davis.osm");

//     //auto read_xmldata = std::make_shared<CXMLReader>(datasource);
    
//     auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");

//     //CXMLReader CreateXMLReader_proj3(datasource);

//     COpenStreetMap OpenStreetMap(read_xmldata);


//     auto node_id0 = OpenStreetMap.NodeByID(62224641);

//     EXPECT_TRUE(node_id0->HasAttribute("highway"));
//     EXPECT_TRUE(node_id0->HasAttribute("ref"));



//     EXPECT_EQ(node_id0->GetAttribute("highway"), "motorway_junction");
//     EXPECT_EQ(node_id0->GetAttribute("ref"), "71");
// }