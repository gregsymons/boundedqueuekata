#ifndef __bounded_queue_h_
#define __bounded_queue_h_

#include "QueueControl.h"

template <typename T>
class BoundedQueue {
public:
    BoundedQueue(QueueControl& producer) { producer.Resume(); };
};

#endif
