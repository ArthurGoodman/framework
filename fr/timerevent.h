#pragma once

namespace fr {

class TimerEvent {
    friend class Window;

    int _id;

public:
    int id() const;

private:
    TimerEvent(int id);
};
}
