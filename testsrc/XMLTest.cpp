#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"
#include <memory>

CXMLReader CreateXMLReader(const std::string& input){
    auto datasource = std::make_shared<CStringDataSource>(input);
    return CXMLReader(datasource);
}

using DataSinkPointer = std::shared_ptr<CStringDataSink>;

CXMLWriter CreateXMLWriter (DataSinkPointer datsSink){
    return CXMLWriter(datsSink);
}

TEST(XMLReaderTest, simple){
    CXMLReader XMLReader = CreateXMLReader("<user name=\"Vincent\" city=\"Davis\"/>");
    SXMLEntity XMLEntity;
    
    ASSERT_TRUE(XMLReader.ReadEntity(XMLEntity));
    EXPECT_EQ(XMLEntity.DType, SXMLEntity::EType::CompleteElement);
    EXPECT_EQ(XMLEntity.DNameData, "user");
    EXPECT_EQ(XMLEntity.DAttributes.size(), 2);
    EXPECT_EQ(XMLEntity.AttributeValue("name"), "Vincent");
    EXPECT_EQ(XMLEntity.AttributeValue("city"), "Davis");
}

TEST(XMLWriterTest, simple) {
    auto outputStream = std::make_shared<CStringDataSink>();
    CXMLWriter XMLWriter = CreateXMLWriter(outputStream);
    
    XMLWriter.WriteEntity({SXMLEntity::EType::CompleteElement, "user", {{"name", "Vincent"}, {"city", "Davis"}}});
    
    EXPECT_EQ(outputStream->String(), "<user name=\"Vincent\" city=\"Davis\"/>");
}