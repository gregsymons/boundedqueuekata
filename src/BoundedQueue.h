#ifndef __bounded_queue_h_
#define __bounded_queue_h_

#include "QueueControl.h"

template <typename T>
class BoundedQueue {
public:
    BoundedQueue(QueueControl& producer, QueueControl& consumer) : consumer(consumer)
    { 
        producer.Resume(); 
        consumer.Pause();
    };
    
    void enqueue(const T& item) 
    { 
        consumer.Resume();
    };

private:
    QueueControl& consumer;
};

#endif
