#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "StringDataSource.h"

#include <string>
#include <memory>
using std::string;

using std::shared_ptr;

//added for ifstream and fileread
#include <sstream>
#include <fstream>


std::shared_ptr<CDSVReader> CreateDSVReader_proj3(const std::string& input_file) {
    std::ifstream reading_file(input_file);

    std::string reading_content;
    std::string reading_lines;

    while(std::getline(reading_file, reading_lines)){
        reading_content += reading_lines;
        reading_content += "\n";
    }
    
    auto datasource = std::make_shared<CStringDataSource>(reading_content);
    return std::make_shared<CDSVReader>(datasource, ',');
}

// TEST(CSVBusSystemTest, Stop_andRoute_Counts){
//     // string test_stops = "stop_id, node_id\n1,100\n2,200\n3,300\n";
    
//     string test_stops =
//     "stop_id,node_id\n"
//     "22043,2849810514\n"
//     "22358,2849805223\n"
//     "22105,3954294407\n";

//     string test_routes =
//         "route,stop_id\n"
//         "A,22258\n"
//         "A,22169\n"
//         "A,22000\n"
//         "B,22185\n"
//         "B,22189\n"
//         "B,22188\n";

//         auto read_stops = CreateDSVReader_proj3(test_stops); 
//         auto read_routes = CreateDSVReader_proj3(test_routes);
        
//         CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     EXPECT_EQ(CSVBusSystem.StopCount(), 3);
//     EXPECT_EQ(CSVBusSystem.RouteCount(), 2);
// }

//! **************************************************************************
//! Wait Until CSVBusSystem function complete then uncomment everything below
//! Otherwise had segment fault
//! **************************************************************************


// TEST(CSVBusSystemTest, Stop_andRoute_Counts){

//     auto read_stops = CreateDSVReader_proj3("data/stops.csv");
//     auto read_routes = CreateDSVReader_proj3("data/routes.csv");

//     CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     EXPECT_EQ(CSVBusSystem.StopCount(), 298);
//     //EXPECT_EQ(CSVBusSystem.RouteCount(), 394);
//     EXPECT_EQ(CSVBusSystem.RouteCount(), 17);
    
// }

// TEST(CSVBusSystemTest, StopIndex_andStopID){
//     auto read_stops = CreateDSVReader_proj3("data/stops.csv");
//     auto read_routes = CreateDSVReader_proj3("data/routes.csv");

//     CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     auto stop_index0 = CSVBusSystem.StopByIndex(0);

//     EXPECT_EQ(stop_index0 -> ID(), 22043);
//     EXPECT_EQ(stop_index0 -> NodeID(), 2849810514);

//     auto stop_ID0 = CSVBusSystem.StopByID(22358);
    
//     EXPECT_EQ(stop_ID0 -> ID(), 22358);
//     EXPECT_EQ(stop_ID0 -> NodeID(), 2849805223);

// }

// TEST(CSVBusSystemTest, null_index_andID){

//     auto read_stops = CreateDSVReader_proj3("data/stops.csv");
//     auto read_routes = CreateDSVReader_proj3("data/routes.csv");

//     CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     EXPECT_EQ(CSVBusSystem.StopByIndex(299), nullptr);
//     EXPECT_EQ(CSVBusSystem.StopByID(99999), nullptr);

//     EXPECT_EQ(CSVBusSystem.RouteByName("FAKERoute"), nullptr);
//     EXPECT_EQ(CSVBusSystem.RouteByIndex(999), nullptr);
// }

// TEST(CSVBusSystemTest, RouteIndex_andRouteName){
//     auto read_stops = CreateDSVReader_proj3("data/stops.csv");
//     auto read_routes = CreateDSVReader_proj3("data/routes.csv");

//     CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     auto route_index0 = CSVBusSystem.RouteByIndex(0);
    
//     EXPECT_EQ(route_index0 -> Name(), "A");
//     EXPECT_NE(route_index0 -> StopCount(), 0);


//     auto route_nameA = CSVBusSystem.RouteByName("A");
    
//     EXPECT_EQ(route_nameA -> Name(), "A");
//     EXPECT_NE(route_nameA -> StopCount(), 0);

    
//     EXPECT_EQ(CSVBusSystem.RouteByIndex(395), nullptr);
//     EXPECT_EQ(CSVBusSystem.RouteByName("NonExistent"), nullptr);

// }


// TEST(CSVBusSystemTest, Route_StopCounts) {
//     auto read_stops = CreateDSVReader_proj3("data/stops.csv");
//     auto read_routes = CreateDSVReader_proj3("data/routes.csv");
    
//     CCSVBusSystem CSVBusSystem(read_stops, read_routes);

//     auto route_nameA = CSVBusSystem.RouteByName("A");

//     EXPECT_EQ(route_nameA -> StopCount(), 22);
//     EXPECT_EQ(route_nameA -> GetStopID(0), 22258);

//     auto stop_byID = CSVBusSystem.StopByID(22258);

//     EXPECT_EQ(stop_byID -> ID(), 22258);

    
// }