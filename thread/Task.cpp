#include "Task.h"
#include "Mutex.h"

using namespace thread;

Task::Task(): m_data(nullptr) {}

Task::Task(void* data): m_data(data) {}

Task::~Task() {}

void* Task::get_data() {
    Alock al(m_mutex);
    return m_data;
}

void Task::set_data(void* data) {
    Alock al(m_mutex);
    m_data = data;
}