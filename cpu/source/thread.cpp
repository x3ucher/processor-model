#include "../include/thread.hpp"

StatCode Thread::getStat() const { 
    return stat_;
}

void Thread::setStat(StatCode stat) {
    stat_ = stat;
}