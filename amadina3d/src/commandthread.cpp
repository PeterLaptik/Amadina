#include "command_thread.h"
#include <thread>

using CommandThread = cad::modeller::command::CommandThread;

const char *ERR_MESSAGE = "Cannot receive input while waiting for another one";

CommandThread::CommandThread()
    : is_waiting_for_point(false),
    is_waiting_for_number(false)
{ }

CommandThread::~CommandThread()
{ }

Point CommandThread::InputPoint()
{
    if(IsBusy())
        throw std::exception(ERR_MESSAGE);

    is_waiting_for_point = true;
    while(is_waiting_for_point)
        std::this_thread::yield();

    return m_point;
}

double CommandThread::InputNumber()
{
    if(IsBusy())
        throw std::exception(ERR_MESSAGE);

    is_waiting_for_number = true;
    while(is_waiting_for_number)
        std::this_thread::yield();

    return m_number;
}

void CommandThread::SetPoint(const Point &point)
{
    if(!is_waiting_for_point)
        return;

    m_point = point;
    is_waiting_for_point = false;
}

void CommandThread::SetNumber(double number)
{
    if(!is_waiting_for_number)
        return;

    m_number = number;
    is_waiting_for_number = false;
}

bool CommandThread::IsBusy() const
{
    // TODO: mutex?
    return is_waiting_for_point || is_waiting_for_number;
}
