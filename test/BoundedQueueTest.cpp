#include "BoundedQueue.h"

#include <gmock/gmock.h>

class MockQueueControl : public QueueControl {
public:
    MOCK_METHOD0(Resume, void());
    MOCK_METHOD0(Pause, void());
};


class BoundedQueueTest : public ::testing::Test {
public:
    MockQueueControl producer;
    MockQueueControl consumer;
    BoundedQueueTest() : producer(), consumer(), q(producer, consumer) { }

    BoundedQueue<int> q;
};

TEST_F(BoundedQueueTest, CreateResumesProducer) {
    EXPECT_CALL(producer, Resume());
    BoundedQueue<int> q(producer, consumer);
}

TEST_F(BoundedQueueTest, CreatePausesConsumer)
{
    EXPECT_CALL(consumer, Pause());
    BoundedQueue<int> q(producer, consumer);
}

TEST_F(BoundedQueueTest, EnqueueResumesConsumer)
{
    EXPECT_CALL(consumer, Resume());
    q.enqueue(5);
}
