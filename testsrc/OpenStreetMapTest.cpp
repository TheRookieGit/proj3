#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "StringDataSource.h"
#include "OpenStreetMap.h"
#include "XMLReader.h"

#include <string>
#include <memory>
#include <sstream>
#include <fstream>

using std::string;
using std::shared_ptr;

// Improved function to create XML Reader
std::shared_ptr<CXMLReader> CreateXMLReader_proj3(const std::string& input_file) {
    std::ifstream reading_file(input_file);
    
    if (!reading_file) {
        throw std::runtime_error("Failed to open file: " + input_file);
    }

    std::stringstream buffer;
    buffer << reading_file.rdbuf();
    
    auto datasource = std::make_shared<CStringDataSource>(buffer.str());
    return std::make_shared<CXMLReader>(datasource);
}

// TEST CASE: Node and Way Counts
TEST(OpenStreetMapTest, Node_andWay_Counts) {
    auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");
    COpenStreetMap OpenStreetMap(read_xmldata);

    EXPECT_EQ(OpenStreetMap.NodeCount(), 10259);
    EXPECT_EQ(OpenStreetMap.WayCount(), 1644);
}

// TEST CASE: Node Index and ID
TEST(OpenStreetMapTest, NodeIndex_andID) {
    auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");
    COpenStreetMap OpenStreetMap(read_xmldata);

    auto node_index0 = OpenStreetMap.NodeByIndex(0);
    ASSERT_NE(node_index0, nullptr);  // Ensure node exists before accessing

    EXPECT_EQ(node_index0->ID(), 62208369);
    EXPECT_NEAR(node_index0->Location().first, 38.5178523, 1e-6);
    EXPECT_NEAR(node_index0->Location().second, -121.7712408, 1e-6);

    auto node_id0 = OpenStreetMap.NodeByID(62209104);
    ASSERT_NE(node_id0, nullptr);  // Ensure node exists

    EXPECT_EQ(node_id0->ID(), 62209104);
    EXPECT_NEAR(node_id0->Location().first, 38.535052, 1e-6);
    EXPECT_NEAR(node_id0->Location().second, -121.7408606, 1e-6);

    EXPECT_EQ(OpenStreetMap.NodeByID(9999999999), nullptr);
}

// TEST CASE: Node Attributes
TEST(OpenStreetMapTest, Node_Attributes) {
    auto read_xmldata = CreateXMLReader_proj3("data/davis.osm");
    COpenStreetMap OpenStreetMap(read_xmldata);

    auto node_id0 = OpenStreetMap.NodeByID(62224641);
    ASSERT_NE(node_id0, nullptr);  // Ensure node exists

    EXPECT_TRUE(node_id0->HasAttribute("highway"));
    EXPECT_TRUE(node_id0->HasAttribute("ref"));

    EXPECT_EQ(node_id0->GetAttribute("highway"), "motorway_junction");
    EXPECT_EQ(node_id0->GetAttribute("ref"), "71");
}