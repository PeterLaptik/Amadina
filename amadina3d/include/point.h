#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point
{
    public:
        Point(double x, double y, double z = 0.0)
            : m_x(x), m_y(y), m_z(z)
        { }

        Point(void)
            : m_x(0), m_y(0), m_z(0)
        { }

        virtual ~Point()
        { }

        void SetX(double x)
        {
            m_x = x;
        }

        void SetY(double y)
        {
            m_y = y;
        }

        void SetZ(double z)
        {
            m_z = z;
        }

        double GetX(void) const
        {
            return m_x;
        }

        double GetY(void) const
        {
            return m_y;
        }

        double GetZ(void) const
        {
            return m_z;
        }

    private:
        double m_x, m_y, m_z;
};

#endif // POINT_H_INCLUDED
