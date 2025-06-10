#ifndef BASE_COMMAND_H_INCLUDED
#define BASE_COMMAND_H_INCLUDED

#include "sheet_context.h"
#include "command_arguments.h"
#include "point.h"
#include "direction.h"
#include <string>
#include <vector>

namespace cad::model
{
    class AbstractShape;
}

namespace cad::app
{
    class SheetContext;
}

namespace cad::command::interpreter
{
    class CommandToken;
}

namespace cad::command {

    using cad::model::AbstractShape;
    using cad::model::flat::Point;
    using cad::model::geom::Direction;
    using cad::app::SheetContext;
    using cad::command::interpreter::CommandToken;
    using cad::command::interpreter::CommandArguments;

    class BaseCommand
    {
        public:
            BaseCommand() = default;

            virtual bool Execute(SheetContext *ctx, CommandArguments &args) = 0;

            //virtual void ObjectsCreated(std::vector<AbstractShape *> &container) = 0;

            //virtual void ObjectsToRemove(std::vector<AbstractShape*> &container) = 0;

            virtual BaseCommand* Clone() = 0;

            const std::string& GetMessage()
            {
                return m_err_msg;
            }

        protected:
            std::string m_err_msg = "";

            bool CheckArgSize(const CommandArguments &args, size_t min)
            {
                if (args.GetSize() < min)
                {
                    m_err_msg = "Too few arguments. At least ";
                    m_err_msg += std::to_string(min);
                    m_err_msg += " expected.";
                    return false;
                }
                return true;
            }

            Point GetPointFromList(CommandToken tk)
            {
                Point point;

                bool is_list = tk.IsList();
                size_t list_zize = tk.GetListSize();

                if (!is_list || list_zize < 2)
                    return point; // Uninitialized point. Use IsSet to check.

                point.SetX(tk.GetListValue(0));
                point.SetY(tk.GetListValue(1));
                point.SetZ(list_zize > 2 ? tk.GetListValue(2) : 0.0);
                return point;
            }

            Direction GetDirectionFromList(CommandToken tk)
            {
                Direction dir;

                bool is_list = tk.IsList();
                size_t list_zize = tk.GetListSize();

                if (!is_list || list_zize < 3)
                    return Direction{}; // Default direction.


                dir.SetX(tk.GetListValue(0));
                dir.SetY(tk.GetListValue(1));
                dir.SetZ(list_zize > 2 ? tk.GetListValue(2) : 0.0);
                return dir;
            }
    };
}

#endif // !BASE_COMMAND_H_INCLUDED

