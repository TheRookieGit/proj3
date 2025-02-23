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

std::shared_ptr<CXMLReader> CreateXMLReader_proj3(const std::string& input){
    auto datasource = std::make_shared<CStringDataSource>(input);
    return std::make_shared<CXMLReader>(datasource);
}


TEST(OpenStreetMapTest, Node_andWay_Counts){
    auto datasource = std::make_shared<CStringDataSource>("davis.osm");

    auto read_xmldata = std::make_shared<CXMLReader>(datasource);

    //CXMLReader CreateXMLReader_proj3(datasource);

    COpenStreetMap OpenStreetMap(read_xmldata);

    EXPECT_EQ(OpenStreetMap.NodeCount(), 10259);
    EXPECT_EQ(OpenStreetMap.WayCount(), 1644);
}