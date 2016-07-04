#include "timerevent.h"

int fr::TimerEvent::id() const {
    return _id;
}

fr::TimerEvent::TimerEvent(int id)
    : _id(id) {
}
