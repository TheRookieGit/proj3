#include <gtest/gtest.h>
#include "StringUtils.h"

using namespace StringUtils;

TEST(StringUtilsTest, SliceTest){
  EXPECT_EQ(Slice("vincent", 1, 3), "in");
  EXPECT_EQ(Slice("vincent wang", -5, -1), " wan");
  EXPECT_EQ(Slice("vincent wang", -50, 50), "vincent wang");
  EXPECT_EQ(Slice("", -5, -1), "");
  EXPECT_EQ(Slice("", 1, 3), ""); 
  EXPECT_EQ(Slice("Vincent Wang", -12, 6), "Vincen");
  EXPECT_EQ(Slice("vincent", 3, 3), "");
}

TEST(StringUtilsTest, Capitalize){
  EXPECT_EQ(Capitalize("vincent"), "Vincent");
  EXPECT_EQ(Capitalize("VINCENT"), "Vincent");
  EXPECT_EQ(Capitalize("vINcenT"), "Vincent");
  EXPECT_EQ(Capitalize("vincent_wang"), "Vincent_wang");
  EXPECT_EQ(Capitalize("vincent2wang"), "Vincent2wang");
  EXPECT_EQ(Capitalize(""), "");
  EXPECT_EQ(Capitalize("V"), "V");
  EXPECT_EQ(Capitalize("v"), "V");
}

TEST(StringUtilsTest, Upper){
  EXPECT_EQ(Upper("vincent"), "VINCENT");
  EXPECT_EQ(Upper("vincent wang"), "VINCENT WANG");
  EXPECT_EQ(Upper("Vincent Wang"), "VINCENT WANG");
  EXPECT_EQ(Upper("034"), "034");
  EXPECT_EQ(Upper(""), "");
  EXPECT_EQ(Upper("vince2002ent"), "VINCE2002ENT");
  EXPECT_EQ(Upper("vincent_wang"), "VINCENT_WANG");
  EXPECT_EQ(Upper("Vincent2Wang"), "VINCENT2WANG");
  EXPECT_EQ(Upper("vincent.wang"), "VINCENT.WANG");
}

TEST(StringUtilsTest, Lower){
  EXPECT_EQ(Lower("VINCENT"), "vincent");
  EXPECT_EQ(Lower("VINCENT WANG"), "vincent wang");
  EXPECT_EQ(Lower("Vincent Wang"), "vincent wang");
  EXPECT_EQ(Lower("034"), "034");
  EXPECT_EQ(Lower(""), "");
  EXPECT_EQ(Lower("VINCE2002ENT"), "vince2002ent");
}

TEST(StringUtilsTest, LStrip){
  EXPECT_EQ(LStrip("  vincent"), "vincent");
  EXPECT_EQ(LStrip("  vincent wang  "), "vincent wang  ");
  EXPECT_EQ(LStrip("\t\tVincent\tWang\t"), "Vincent\tWang\t");
}

TEST(StringUtilsTest, RStrip){
  EXPECT_EQ(RStrip("vincent "), "vincent");
  EXPECT_EQ(RStrip("  vincent wang  "), "  vincent wang");
  EXPECT_EQ(RStrip("\tVincent\tWang\t\t"), "\tVincent\tWang");
}

TEST(StringUtilsTest, Strip){
  EXPECT_EQ(Strip("vincent "), "vincent");
  EXPECT_EQ(Strip("  vincent wang  "), "vincent wang");
  EXPECT_EQ(Strip(" vincent"), "vincent");
  EXPECT_EQ(Strip("  vincent wang"), "vincent wang");
  EXPECT_EQ(Strip(""), "");
  EXPECT_EQ(Strip("\t\tVincent\tWang\t\t"), "Vincent\tWang");
  EXPECT_EQ(Strip("   Vincent-Wang   "), "Vincent-Wang");
}

TEST(StringUtilsTest, Center){
  EXPECT_EQ(Center("vincent", 9, ' '), " vincent ");
  EXPECT_EQ(Center("vincent", 8, '-'), "vincent-");
  EXPECT_EQ(Center("vincent", 10, '-'), "-vincent--");
  EXPECT_EQ(Center("vincent", 1, '-'), "vincent");
  EXPECT_EQ(Center("Vincent-Wang", 16, '.'), "..Vincent-Wang..");
}

TEST(StringUtilsTest, LJust){
  EXPECT_EQ(LJust("vincent", 10, ' '), "vincent   ");
  EXPECT_EQ(LJust("vi", 4, '-'), "vi--");
  EXPECT_EQ(LJust("vi", 2, '-'), "vi");
}

TEST(StringUtilsTest, RJust){
  EXPECT_EQ(RJust("vincent", 10, ' '), "   vincent");
  EXPECT_EQ(RJust("vinc", 8, '-'), "----vinc");
  EXPECT_EQ(RJust("vinc", 2, '-'), "vinc");
}

TEST(StringUtilsTest, Replace){
  EXPECT_EQ(Replace("vincent", "n", "w"), "viwcewt");
  EXPECT_EQ(Replace("vincent", "n", "v"), "vivcevt");
  EXPECT_EQ(Replace("vincent", "n", ""), "vicet");
  EXPECT_EQ(Replace("vincent", "", "wang"), "vincent");
  EXPECT_EQ(Replace("", "n", "w"), "");
  EXPECT_EQ(Replace("Wang and Vincent", " and ", ", "), "Wang, Vincent");
}


TEST(StringUtilsTest, Split){ //std::vector<std::string>
  EXPECT_EQ(Split("vincnet", "i"), (std::vector<std::string>{"v", "ncnet"}));
  EXPECT_EQ(Split("vincent wang", " "), (std::vector<std::string>{"vincent", "wang"}));
  EXPECT_EQ(Split("vincent,wang", ","), (std::vector<std::string>{"vincent", "wang"}));
  EXPECT_EQ(Split("vincent", "n"), (std::vector<std::string>{"vi", "ce", "t"}));
  EXPECT_EQ(Split("vinnt", "n"), (std::vector<std::string>{"vi", "", "t"}));
  EXPECT_EQ(Split("", ","), (std::vector<std::string>{""}));
  EXPECT_EQ(Split("Wang,Vincent,Wang", ","), (std::vector<std::string>{"Wang", "Vincent", "Wang"}));
  EXPECT_EQ(Split("Vincent.Wang.Vincent", "."), (std::vector<std::string>{"Vincent", "Wang", "Vincent"}));
  EXPECT_EQ(Split("vincent,wang", ""), (std::vector<std::string>{"vincent,wang"}));
  EXPECT_EQ(Split("", ""), (std::vector<std::string>{""}));


}


TEST(StringUtilsTest, Join){ //std::vector<std::string>
  EXPECT_EQ(Join("-", std::vector<std::string>{"v", "i", "n", "c", "e"}), "v-i-n-c-e");
  EXPECT_EQ(Join("", std::vector<std::string>{"vinc", "ent"}), "vincent");
  EXPECT_EQ(Join("-", std::vector<std::string>{}), "");
  EXPECT_EQ(Join(" and ", std::vector<std::string>{"Vincent", "Wang"}), "Vincent and Wang");
}


TEST(StringUtilsTest, ExpandTabs){
  // EXPECT_EQ(ExpandTabs("\tvincent", 3), "   vincent");
  // EXPECT_EQ(ExpandTabs("vincent\twang", 3), "vincent  wang");
  // EXPECT_EQ(ExpandTabs("Vincent\tWang", 0), "VincentWang");
  // EXPECT_EQ(ExpandTabs("\t", 0), "");
  // EXPECT_EQ(ExpandTabs("\t12341241", 3), "   12341241");
  
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(EditDistance("vincent", "wang", false), 6);
    EXPECT_EQ(EditDistance("wang", "vincent", false), 6); 
    //EXPECT_EQ(EditDistance("Vincent", "WANG", false), 6); 
    EXPECT_EQ(EditDistance("Vincent", "WANG", false), 7); 
    EXPECT_EQ(EditDistance("", "vincent", false), 7); 
    EXPECT_EQ(EditDistance("wang", "", false), 4);  
    EXPECT_EQ(EditDistance("vincent", "vin", false), 4);  
    EXPECT_EQ(EditDistance("vin", "vincent", false), 4);  
    EXPECT_EQ(EditDistance("vincent", "wangent", false), 3);
    EXPECT_EQ(EditDistance("vincent", "xxxxxxx", false), 7);
    EXPECT_EQ(EditDistance("wang", "yyyy", false), 4);  
}