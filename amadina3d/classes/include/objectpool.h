#ifndef OBJECTPOOL_H_INCLUDED
#define OBJECTPOOL_H_INCLUDED

#include <AIS_Shape.hxx>

class ObjectPool
{
    public:
        ObjectPool();
        ~ObjectPool();
        void AppendShape(Handle(AIS_Shape) shape);

    private:
        std::vector<Handle(AIS_Shape)> m_shapes;

};

#endif // OBJECTPOOL_H_INCLUDED
