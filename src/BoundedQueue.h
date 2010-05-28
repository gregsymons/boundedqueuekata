#ifndef __bounded_queue_h_
#define __bounded_queue_h_

#include "QueueControl.h"

template <typename T>
class BoundedQueue {
public:
    BoundedQueue(QueueControl& producer, QueueControl& consumer) 
    { 
        producer.Resume(); 
        consumer.Pause();
    };
};

#endif
