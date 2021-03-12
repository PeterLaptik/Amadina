#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "../processor/drawmanager.h"


enum InteractiveState
{
    SCR_NOTHING,
    SCR_DRAGGING,
    SCR_PICKING
};

class AbstractBuilder;

class Screen
{
    public:
        /// Default constructor
        Screen();

        virtual ~Screen();

        DrawManager* GetDrawManager(void);

        void CreateEntity(AbstractBuilder *builder);

        // Common interface for interaction with derived panel
        ///\brief The method should be called each time on derived panel resizing.
        /// Recalculates screen ratios
        ///\param width - new panel width
        ///\param height - new panel height
        virtual void ScreenResize(const int &width, const int &height);

        ///\brief The method should be called each time on mouse move over a screen
        ///\return true - if the screen has to be refreshed, otherwise - false
        virtual bool ScreenMouseMove(const int &coord_x, const int &coord_y,
                                     const bool &is_ctrl_pressed,
                                     const bool &is_lb_pressed);

        ///\brief The method should be called each time on mouse wheel event over a derived panel.
        /// Recalculates screen scale (zoom in / zoom out)
        ///\param direction - negative integer value on zoom in / positive integer value on zoom out
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheel(const int &direction, const int &coord_x, const int &coord_y);

        ///\brief The method should be called each time on mouse left button is clicked on a derived panel.
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseLBClicked(const int &coord_x,
                                          const int &coord_y,
                                          const bool &is_ctrl_pressed);

        ///\brief The method has been called on mouse left button released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y);

        ///\brief The method should be called on mouse wheel click released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelUp(const int &coord_x, const int &coord_y);

        ///\brief The method should be called on mouse wheel click down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelDown(const int &coord_x, const int &coord_y);

        ///\brief Refresh the screen: draw all entities and signs
        ///\param dc - device context (implementation of IAdapterDC)
        ///\see IAdapterDC
        virtual void RedrawAll(IAdapterDC &dc);

//        ///\brief Sets screen size in pixels.
//        /// Sets screen width and height in pixels
//        /// (unlike SetBorders which sets border in real scale units).
//        ///\param width - screen width in pixels
//        ///\param height - screen height in pixels
//        void ScreenSetSizeInPixels(const int &width, const int &height)
//        {
//            m_width = width;
//            m_height = height;
//        }

        ///\brief Sets current screen borders (in a real scale coordinates)
        ///\param left - left border value
        ///\param right - right border value
        ///\param top - top border value
        ///\param bottom - bottom border value
        void SetBorders(const double &left,
                        const double &right,
                        const double &top,
                        const double &bottom);

        ///\brief Returns current screen borders (in a real scale coordinates)
        ///\param left - pointer to the left border container
        ///\param right - pointer to the right border container
        ///\param top - pointer to the top border container
        ///\param bottom - pointer to the bottom border container
        void GetBorders(double *left,
                        double *right,
                        double *top,
                        double *bottom) const;

        ///\brief Resets screen interactive state (executing commend etc.)
        bool CancelCommand(void);

//        void ScreenSetSizeInPixels(const int &width, const int &height)
//        {
//            m_width = width;
//            m_height = height;
//        }

    protected:

    private:
        /// Calculates snap radius value in a real coordinates
        inline void CalculateBestSnapRadius();

        /// Recalculates coordinates values from a local values on a panel into a global values
        inline void TransformCoordinatesToGlobal(double &x, double &y);

        /// On point is picked event
        inline void PointPicked(double x, double y);

        DrawManager m_draw_manager;

        /// Values of a borders of the screen in a real coordinates scale
        struct Borders
        {
            double left;
            double right;
            double top;
            double bottom;
        } m_borders;

        /// Keeps current mouse coordinates.
        /// The mouse coordinates are to be refreshed each time on mouse move over a derived panel
        struct MouseCoordinates
        {
            double x;
            double y;
        } m_mouse_coord;

        // Size of a visible area of the drawing
        double m_width;
        double m_height;

        // Screen size
        // Means the size of a panel derived from the Screen-class
        int m_screen_width;
        int m_screen_height;

        // Snap radius value in a real coordinates
        double m_snap_radius;

        // Keeps interactive state of the screen
        InteractiveState m_screen_state;
        bool m_is_wheel_pressed;
        AbstractBuilder *m_shape_builder;
};

#endif // SCREEN_H_INCLUDED
