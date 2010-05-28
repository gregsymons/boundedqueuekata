#include "BoundedQueue.h"

#include <gmock/gmock.h>

class MockQueueControl : public QueueControl {
public:
    MOCK_METHOD0(Resume, void());
    MOCK_METHOD0(Pause, void());
};

/*
class BoundedQueueTest : public ::testing::Test {
public:

};
*/

TEST(BoundedQueueTest, CreateResumesProducer) {
    MockQueueControl producer, consumer;
    EXPECT_CALL(producer, Resume());
    BoundedQueue<int> q(producer, consumer);
}

TEST(BoundedQueueTest, CreatePausesConsumer)
{
    MockQueueControl producer, consumer;
    EXPECT_CALL(consumer, Pause());
    BoundedQueue<int> q(producer, consumer);
}

TEST(BoundedQueueTest, EnqueueResumesConsumer)
{
    MockQueueControl producer, consumer;
    BoundedQueue<int> q(producer, consumer);
    EXPECT_CALL(consumer, Resume());
    q.enqueue(5);
}
