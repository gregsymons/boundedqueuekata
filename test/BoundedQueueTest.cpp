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

TEST_F(BoundedQueueTest, FirstInFirstOut)
{
    q.enqueue(1);
    q.enqueue(2);

    ASSERT_EQ(1, q.dequeue());
    ASSERT_EQ(2, q.dequeue());
}

TEST_F(BoundedQueueTest, EnqueueResumesConsumerOnFirstItemOnly)
{
    EXPECT_CALL(consumer, Resume()).Times(1);
    q.enqueue(5);
    q.enqueue(5);
}

TEST_F(BoundedQueueTest, DequeuePausesConsumerWhenQueueIsEmpty)
{
    q.enqueue(3);
    q.enqueue(6);
    EXPECT_CALL(consumer, Pause());
    q.dequeue();
    q.dequeue();
}

