#ifndef CLIPBOARD_H_INCLUDED
#define CLIPBOARD_H_INCLUDED

#include "../entities/point.h"
#include <vector>

class Context;
class Entity;

///\brief Clipboard implementation.
/// Keeps set of objects to clone for 'paste'-routines
class ClipBoard
{
    public:
        ClipBoard(Context *context);
        ClipBoard() = delete;
        virtual ~ClipBoard();

        void AddObjects(const std::vector<Entity*> &objects);
        void SetBasePoint(const Point &p);
        const std::vector<Entity*>& GetObjects(void) const;
        Point GetBasePoint(void) const;

    private:
        inline void Clear(void);

        Context *m_context;
        Point m_base_point;
        std::vector<Entity*> m_objects;
};

#endif // CLIPBOARD_H_INCLUDED
