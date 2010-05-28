#ifndef __bounded_queue_h_
#define __bounded_queue_h_

#include <queue>
#include "QueueControl.h"

template <typename T>
class BoundedQueue {
public:
    BoundedQueue(QueueControl& producer, QueueControl& consumer, size_t bound = 100) : consumer(consumer), producer(producer), bound(bound)
    { 
        producer.Resume(); 
        consumer.Pause();
    };
    
    void enqueue(const T& item) 
    { 
        q.push(item);
        if (q.size() == 1) 
        {
            consumer.Resume();
        }
        
        if (q.size() > bound) 
        {
            producer.Pause();
        }
    };

    const T& dequeue() 
    { 
       const T& item = q.front();
       q.pop();
       
       if (q.size() == 0) 
       {
           consumer.Pause();
       }

       return item;
    } 

private:
    QueueControl& consumer;
    QueueControl& producer;
    size_t bound;
    std::queue<T> q;
};

#endif
