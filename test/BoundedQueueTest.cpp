#include "BoundedQueue.h"

#include <gmock/gmock.h>

class MockQueueControl : public QueueControl {
public:
    MOCK_METHOD0(Resume, void());
};

/*
class BoundedQueueTest : public ::testing::Test {
public:

};
*/

TEST(BoundedQueueTest, CreateResumesProducer) {
    MockQueueControl producer;
    EXPECT_CALL(producer, Resume());
    BoundedQueue<int> q(producer);
}
