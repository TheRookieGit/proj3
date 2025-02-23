#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "StringDataSource.h"

#include <string>
#include <memory>
using std::string;

using std::shared_ptr;


std::shared_ptr<CDSVReader> CreateDSVReader_proj3(const std::string& input) {
    auto datasource = std::make_shared<CStringDataSource>(input);
    return std::make_shared<CDSVReader>(datasource, ',');
}

TEST(CSVBusSystemTest, Stop_andRoute_Counts){
    // string test_stops = "stop_id, node_id\n1,100\n2,200\n3,300\n";
    
    string test_stops =
    "stop_id,node_id\n"
    "22043,2849810514\n"
    "22358,2849805223\n"
    "22105,3954294407\n";

    string test_routes =
        "route,stop_id\n"
        "A,22258\n"
        "A,22169\n"
        "A,22000\n"
        "B,22185\n"
        "B,22189\n"
        "B,22188\n";

        auto read_stops = CreateDSVReader_proj3(test_stops); 
        auto read_routes = CreateDSVReader_proj3(test_routes);
        
        CCSVBusSystem CSVBusSystem(read_stops, read_routes);

    EXPECT_EQ(CSVBusSystem.StopCount(), 3);
    EXPECT_EQ(CSVBusSystem.RouteCount(), 2);
}

