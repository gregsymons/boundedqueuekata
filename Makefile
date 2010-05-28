SRC_DIR 		= src
TEST_DIR 		= test
BUILD_DIR 		= build
BIN_DIR 		= bin
GMOCK_DIR  		= 3rdparty/gmock
GTEST_DIR		= 3rdparty/gtest/
GTEST_SRC_DIR	= $(GTEST_DIR)/src
GTEST_INC_DIR	= $(GTEST_DIR)/include
GMOCK_SRC_DIR 	= $(GMOCK_DIR)/src
GMOCK_INC_DIR	= $(GMOCK_DIR)/include

VPATH=$(SRC_DIR):$(TEST_DIR):$(BUILD_DIR):$(GTEST_SRC_DIR):$(GMOCK_SRC_DIR)

SRCS  = $(wildcard $(SRC_DIR)/*.cpp)
HDRS  = $(wildcard $(SRC_DIR)/*.h)
TESTS = $(wildcard $(TEST_DIR)/*.cpp)
GMOCK_SRCS = $(GMOCK_SRC_DIR)/gmock-all.cc $(GMOCK_SRC_DIR)/gmock_main.cc
GTEST_SRCS = $(GTEST_SRC_DIR)/gtest-all.cc

ALL_SRCS = $(ALL_MY_SRCS) $(GMOCK_SRCS) $(GTEST_SRCS)
MY_OBJS	 = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cpp=.o)))
MY_TESTS = $(addprefix $(BUILD_DIR)/,$(notdir $(TESTS:.cpp=.o)))
GMOCK_OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(GMOCK_SRCS:.cc=.o)))
GTEST_OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(GTEST_SRCS:.cc=.o)))

ALL_OBJS = $(MY_OBJS) $(MY_TESTS) $(GMOCK_OBJS) $(GTEST_OBJS)

CXXFLAGS =-I$(SRC_DIR)				\
		  -I$(GMOCK_INC_DIR) 		\
		  -I$(GMOCK_DIR)	 		\
		  -I$(GTEST_DIR) 			\
		  -I$(GTEST_INC_DIR) 		\
		  -pthread 					\
		  -g 						\
		  -O2						\
		  -MD						\
		  -MP

all: BoundedQueueTest
	./bin/BoundedQueueTest

.PHONY: dirs $(BUILD_DIR) $(BIN_DIR)

dirs: $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	echo $(ALL_OBJS)
	[[ -x $(BUILD_DIR) ]] || mkdir $(BUILD_DIR)

$(BIN_DIR):
	echo $(ALL_OBJS)
	[[ -x $(BIN_DIR) ]] || mkdir $(BIN_DIR)

BoundedQueueTest: dirs $(ALL_OBJS)
	g++ -o $(BIN_DIR)/BoundedQueueTest $(ALL_OBJS) $(CXXFLAGS)

$(MY_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(MY_TESTS): $(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(GMOCK_OBJS): $(BUILD_DIR)/%.o: $(GMOCK_SRC_DIR)/%.cc
	g++ -o $@ -c $< $(CXXFLAGS)

$(GTEST_OBJS): $(BUILD_DIR)/%.o: $(GTEST_SRC_DIR)/%.cc
	g++ -o $@ -c $< $(CXXFLAGS)

clean: 
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
