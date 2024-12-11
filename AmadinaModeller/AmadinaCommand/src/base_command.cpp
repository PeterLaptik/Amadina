#include "base_command.h"
#include <thread>

using cad::modeller::shapes2D::Point;


class InterruptedException : std::exception {};


void cad::command::BaseCommand::Start()
{
    m_is_canceled.store(false);
    try
    {
        Execute();
    }
    catch (const InterruptedException &e)
    {
        // Interrupted
    }
}

void cad::command::BaseCommand::Cancel()
{
    m_is_canceled = true;
    m_waiting_for = false;
}

bool cad::command::BaseCommand::IsWaitingFor(InputType type)
{
    return m_waiting_for & type;
}

void cad::command::BaseCommand::Execute()
{
    // Template method: should be defined in sub-classes
}

double cad::command::BaseCommand::GetNumber()
{
    std::lock_guard<std::mutex> guard(mt);

    m_waiting_for = tp_number;
    m_is_waiting.store(true);
    while (m_is_waiting.load() && !m_is_canceled.load())
        std::this_thread::yield();

    if (m_is_canceled)
        throw InterruptedException();

    return m_number;
}

Point cad::command::BaseCommand::GetPoint()
{
    std::lock_guard<std::mutex> guard(mt);

    m_waiting_for = tp_point;
    m_is_waiting.store(true);
    while (m_is_waiting.load() && !m_is_canceled.load())
        std::this_thread::yield();

    if (m_is_canceled)
        throw InterruptedException();

    return m_point;
}

std::string cad::command::BaseCommand::GetString()
{
    std::lock_guard<std::mutex> guard(mt);

    m_waiting_for = tp_string;
    m_is_waiting.store(true);
    while (m_is_waiting.load() && !m_is_canceled.load())
        std::this_thread::yield();

    if (m_is_canceled)
        throw InterruptedException();

    return m_string;
}

int cad::command::BaseCommand::GetStringOrNumber()
{
    std::lock_guard<std::mutex> guard(mt);

    m_waiting_for = tp_number | tp_string;
    m_is_waiting.store(true);
    while (m_is_waiting.load() && !m_is_canceled.load())
        std::this_thread::yield();

    if (m_is_canceled)
        throw InterruptedException();

    return m_last_input;
}

void cad::command::BaseCommand::SetPoint(const Point & pt)
{
    if (m_waiting_for & tp_point)
        return;

    m_point = pt;
    m_last_input = tp_point;
    m_waiting_for = empty;
    m_is_waiting.store(false);
}

void cad::command::BaseCommand::SetText(const std::string &str)
{
    if (m_waiting_for & tp_string)
        return;

    m_string = str;
    m_last_input = tp_string;
    m_waiting_for = empty;
    m_is_waiting.store(false);
}

void cad::command::BaseCommand::SetNumber(double number)
{
    if (m_waiting_for & tp_number)
        return;

    m_number = number;
    m_last_input = tp_number;
    m_waiting_for = empty;
    m_is_waiting.store(false);
}