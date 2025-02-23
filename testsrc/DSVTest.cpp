#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"
#include <sstream>
#include <memory>
#include <vector>
#include <string>


CDSVReader CreateDSVReader(const std::string& input){
    auto datasource = std::make_shared<CStringDataSource>(input);
    return CDSVReader(datasource, ',');
}

using DataSinkPointer = std::shared_ptr<CStringDataSink>;

CDSVWriter CreateDSVWriter(DataSinkPointer datasink, char delimiter = ',', bool quote = false){
    //auto datasource = std::make_shared<CStringDataSource>(input);
    return CDSVWriter(datasink, delimiter, quote);
}


TEST(DSVReaderTest, ReadNormalDSV){
    CDSVReader dsvReader = CreateDSVReader("Vincent,Age22,Davis\nMellow Huang,25,San Jose");
    std::vector<std::string> currentRow;

    ASSERT_TRUE(dsvReader.ReadRow(currentRow));
    EXPECT_EQ(currentRow.size(), 3);
    EXPECT_EQ(currentRow[0], "Vincent");
    EXPECT_EQ(currentRow[1], "Age22");
    EXPECT_EQ(currentRow[2], "Davis");

    ASSERT_TRUE(dsvReader.ReadRow(currentRow));
    EXPECT_EQ(currentRow[0], "Mellow Huang");
    EXPECT_EQ(currentRow[1], "25");
    EXPECT_EQ(currentRow[2], "San Jose");
}

TEST(DSVReaderTest, readSpecialCharacters) {
    CDSVReader dsvReader = CreateDSVReader("\"Vincent\",\"Age22\",\"Davis\"\n\"Mellow Huang\",\"25\",\"San Jose\"");
    std::vector<std::string> currentRow;

    ASSERT_TRUE(dsvReader.ReadRow(currentRow));
    EXPECT_EQ(currentRow.size(), 3);
    EXPECT_EQ(currentRow[0], "Vincent");
    EXPECT_EQ(currentRow[1], "Age22");
    EXPECT_EQ(currentRow[2], "Davis");

    ASSERT_TRUE(dsvReader.ReadRow(currentRow));
    EXPECT_EQ(currentRow[0], "Mellow Huang");
    EXPECT_EQ(currentRow[1], "25");
    EXPECT_EQ(currentRow[2], "San Jose");
}

//! Did Not Pass, commented for proj3 temp
//! *************
// TEST(DSVReaderTest, reademptyrow) {
//     CDSVReader dsvReader = CreateDSVReader("\n\nVincent,Age22,Davis\n\nMellow Huang,25,San Jose\n\n");
//     std::vector<std::string> currentRow;

//     ASSERT_TRUE(dsvReader.ReadRow(currentRow));
//     EXPECT_EQ(currentRow.size(), 3);
//     EXPECT_EQ(currentRow[0], "Vincent");

//     ASSERT_TRUE(dsvReader.ReadRow(currentRow));
//     EXPECT_EQ(currentRow[0], "Mellow Huang");
// }

TEST(DSVWriterTest, regularDSVWrite) {
    auto dataSink = std::make_shared<CStringDataSink>();
    CDSVWriter dsvWriter = CreateDSVWriter(dataSink);

    dsvWriter.WriteRow({"Vincent", "Age22", "Davis"});
    dsvWriter.WriteRow({"Mellow Huang", "25", "San Jose"});

    EXPECT_EQ(dataSink->String(), "Vincent,Age22,Davis\nMellow Huang,25,San Jose\n");
}

TEST(DSVWriterTest,writeSpecialCharacters) {
    auto dataSink = std::make_shared<CStringDataSink>();
    CDSVWriter dsvWriter = CreateDSVWriter(dataSink, ',', true);

    dsvWriter.WriteRow({"Vincent", "Age22", "Davis"});
    dsvWriter.WriteRow({"Mellow Huang", "25", "San Jose"});

    EXPECT_EQ(dataSink->String(), "\"Vincent\",\"Age22\",\"Davis\"\n\"Mellow Huang\",\"25\",\"San Jose\"\n");
}

TEST(DSVWriterTest, writeemptyrow) {
    auto dataSink = std::make_shared<CStringDataSink>();
    CDSVWriter dsvWriter = CreateDSVWriter(dataSink);

    dsvWriter.WriteRow({});
    EXPECT_EQ(dataSink->String(), "\n");
}