#ifndef BASE_COMMAND_H_INCLUDED
#define BASE_COMMAND_H_INCLUDED

#include "point.h"
#include <string>
#include <atomic>
#include <mutex>

namespace cad::command
{
    using cad::modeller::shapes2D::Point;

    class InteractiveDataReceiver
    {
        public:
            virtual void SetPoint(const Point &pt) = 0;
            virtual void SetText(const std::string &str) = 0;
            virtual void SetNumber(double number) = 0;
    };

    class BaseCommand: public InteractiveDataReceiver
    {
        // Execution states: waiting type, last input type
        enum InputType
        {
            empty = 0,
            tp_string = 2,
            tp_number = 4,
            tp_point = 8
        };

        public:
            BaseCommand() = default;
            virtual ~BaseCommand() = default;

            void Start();

            void Cancel();

            bool IsWaitingFor(InputType type);

            void SetPoint(const Point &pt) final;

            void SetText(const std::string &str) final;

            void SetNumber(double number) final;

        protected:
            // Called inside Start(): has to be overriden for all commands
            virtual void Execute();

            double GetNumber();
            Point GetPoint();
            std::string GetString();
            int GetStringOrNumber();

        private:
            std::mutex mt;
            std::atomic<bool> m_is_waiting = false;
            std::atomic<bool> m_is_canceled = false;

            // Incoming data
            std::string m_string;
            double m_number;
            Point m_point;

            int m_last_input = empty;
            int m_waiting_for = empty;
    };
}

#endif // !BASE_COMMAND_H_INCLUDED

