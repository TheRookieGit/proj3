CXX=g++
CXXFLAGS = -std=c++17 -Wall -I$(include_folder) -I$(src_folder)
LDFLAGS = -lgtest -lgtest_main -pthread -lexpat #added after XML


include_folder = include
src_folder = src
test_folder = testsrc

obj_folder = obj
bin_folder = bin
#??

#includes = $(wildcard $(include_folder)/*.h)
srcs = $(wildcard $(src_folder)/*.cpp)
testsrc = $(wildcard $(test_folder)/*.cpp)
# ● Must compile string utils file and string utils tests using C++17
objs = $(patsubst $(src_folder)/%.cpp, $(obj_folder)/%.o, $(srcs))
testobjs = $(patsubst $(test_folder)/%.cpp, $(obj_folder)/%.o, $(testsrc))

execute_target = $(bin_folder)/teststrutils

test_targets = $(bin_folder)/teststrdatasource $(bin_folder)/teststrdatasink $(bin_folder)/testdsv $(bin_folder)/testxml
all_object = $(objs) $(testobjs)
# ● Must link string utils and string utils tests object files to make teststrutils
# executable

default: test

$(execute_target): $(objs) $(testobjs)
	@mkdir -p $(bin_folder)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(bin_folder)/teststrdatasource: $(obj_folder)/StringDataSource.o $(obj_folder)/StringDataSourceTest.o
	@mkdir -p $(bin_folder)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(bin_folder)/teststrdatasink: $(obj_folder)/StringDataSink.o $(obj_folder)/StringDataSinkTest.o
	@mkdir -p $(bin_folder)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(bin_folder)/testdsv: $(obj_folder)/DSVReader.o $(obj_folder)/DSVWriter.o $(obj_folder)/DSVTest.o
	@mkdir -p $(bin_folder)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(bin_folder)/testxml: $(obj_folder)/XMLReader.o $(obj_folder)/XMLWriter.o $(obj_folder)/XMLTest.o
	@mkdir -p $(bin_folder)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


$(obj_folder)/%.o: $(src_folder)/%.cpp
	@mkdir -p $(obj_folder)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(obj_folder)/%.o: $(test_folder)/%.cpp
	@mkdir -p $(obj_folder)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# default: test
# ● Must execute the teststrutils executable
test: $(execute_target)
			./$(execute_target) --gtest_break_on_failure=0
			./$(bin_folder)/teststrdatasource --gtest_break_on_failure=0
			./$(bin_folder)/teststrdatasink --gtest_break_on_failure=0
			./$(bin_folder)/testdsv --gtest_break_on_failure=0
			./$(bin_folder)/testxml --gtest_break_on_failure=0

# ● Must provide a clean that will remove the obj and bin directories
clean:
	rm -rf $(obj_folder) $(bin_folder)

.PHONY: all test clean
