#ifndef __QUEUE_CONTROL_H_
#define __QUEUE_CONTROL_H_

class QueueControl {
public:
	virtual ~QueueControl() {}
    virtual void Resume() = 0;
    virtual void Pause() = 0;
};

#endif
