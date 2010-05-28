#ifndef __bounded_queue_h_
#define __bounded_queue_h_

#include <queue>
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
        q.push(item);
        if (q.size() == 1) 
        {
            consumer.Resume();
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
    std::queue<T> q;
};

#endif
