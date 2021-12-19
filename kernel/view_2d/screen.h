#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "screen_interface.h"
#include "../context/context.h"
#include "../processor/drawmanager.h"

/// Screen interactive state value
enum InteractiveState
{
    SCR_NOTHING,    // nothing
    SCR_PICKING,    // panel is waiting for point pick
    SCR_SELECTING   // panel is waiting for entities pick
};


// Builder should be received for interactive entity creating
class AbstractBuilder;

//
class EntityBuilder;


///\brief Common interactive screen interface implementation.
/// A widget for drawing can contain the screen interface implementation
/// or to be a derived class from the screen interface.
/// Any events (like mouse move, mouse click etc.) are to be received by the screen.
class DLL_EXPORT Screen: public ScreenInterface
{
    public:
        /// Default constructor
        Screen();

        /// Destructor
        virtual ~Screen();

        ///\brief The method should be called each time on derived panel resizing.
        /// Recalculates screen ratios
        ///\param width - new panel width
        ///\param height - new panel height
        virtual void ScreenResize(const int &width, const int &height);

        ///\brief The method should be called each time on mouse move over a screen
        virtual void ScreenMouseMove(const int &coord_x, const int &coord_y,
                                     const bool &is_ctrl_pressed,
                                     const bool &is_lb_pressed);

        ///\brief The method should be called each time on mouse wheel event over a derived panel.
        /// Recalculates screen scale (zoom in / zoom out)
        ///\param direction - negative integer value on zoom in / positive integer value on zoom out
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheel(const int &direction, const int &coord_x, const int &coord_y);

        ///\brief The method should be called each time on mouse left button is clicked on a derived panel.
        virtual void ScreenMouseLeftButtonClicked(const int &coord_x,
                                                const int &coord_y,
                                                const bool &is_ctrl_pressed);

        ///\brief The method has been called on mouse left button released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y);

        ///\brief Empty implementation
        virtual void ScreenMouseLeftButtonDown(const int &coord_x, const int &coord_y)
        {
            // unreferenced parameters:
            coord_x, coord_y;
        }

        ///\brief Empty implementation
        virtual void ScreenMouseRightButtonClicked(const int &coord_x,
                                                const int &coord_y,
                                                const bool &is_ctrl_pressed)
        {
            // unreferenced parameters:
            coord_x, coord_y, is_ctrl_pressed;
        }

        ///\brief Empty implementation
        virtual void ScreenMouseRightButtonUp(const int &coord_x, const int &coord_y)
        {
            // unreferenced parameters:
            coord_x, coord_y;
        }

        ///\brief Empty implementation
        virtual void ScreenMouseRightButtonDown(const int &coord_x, const int &coord_y)
        {
            // unreferenced parameters:
            coord_x, coord_y;
        }

        ///\brief The method should be called on mouse wheel click released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelUp(const int &coord_x, const int &coord_y);

        ///\brief The method should be called on mouse wheel click down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelDown(const int &coord_x, const int &coord_y);

        ///\brief The method receives information about pressed key.
        /// There is no need to process each key pressed,
        /// only necessary key codes can be processed depending
        /// on interaction logic.
        ///\param key - key ASCII code
        virtual void ScreenKeyPressed(char key);

        ///\brief Refresh the screen: draw all entities and signs
        ///\param dc - device context (implementation of IAdapterDC)
        ///\see IAdapterDC
        virtual void RedrawAll(IAdapterDC &dc);

        ///\brief Sets current screen borders (in a real scale coordinates)
        ///\param left - left border value
        ///\param right - right border value
        ///\param top - top border value
        ///\param bottom - bottom border value
        virtual void SetBorders(const double &left,
                        const double &right,
                        const double &top,
                        const double &bottom);

        ///\brief Returns current screen borders (in a real scale coordinates)
        ///\param left - pointer to the left border container
        ///\param right - pointer to the right border container
        ///\param top - pointer to the top border container
        ///\param bottom - pointer to the bottom border container
        virtual void GetBorders(double *left,
                        double *right,
                        double *top,
                        double *bottom) const;

        ///\brief Resets screen interactive state (executing commend etc.)
        virtual void ScreenCancelCommand(void);

        ///\brief Refresh screen
        /// Implementation depends on GUI-library used for the screen panel
        virtual void RefreshScreen(void) = 0;

        ///\brief Returns pointer to a draw manager.
        /// Each instance of a screen has its own draw manager.
        ///\see DrawManager
        ///\return Pointer to a draw manager instance
        virtual DrawManager* GetDrawManager(void);

        ///\brief Creates a new entity via builder.
        /// The process of creation is interactive
        /// and consists of an atomic steps (like pick point, pick entity etc).
        /// Creating process can be canceled by CancelCommand method.
        /// The builder instance is handled by the screen after receiving
        /// and is not to be deleted outside.
        ///\param builder - entity builder instance
        virtual void CreateEntity(AbstractBuilder *builder);

        virtual void AppendEntity(Entity *entity);

//        virtual void AppendEntities(std::vector<Entity*> entities);

        virtual void DeleteEntity(Entity *entity);

//        virtual void DeleteEntities(std::vector<Entity*> entities);

        void SetState(InteractiveState state);

        InteractiveState GetState(void);

        Context* GetContext(void)
        {
            return &m_context;
        }

        void SetEntityBuilder(EntityBuilder *receiver)
        {
            m_receiver = receiver;
        }

    protected:

    private:
        /// Calculates snap radius value in a real coordinates
        inline void CalculateBestSnapRadius(void);

        /// Recalculates coordinates values from a local values on a panel into a global values
        inline void TransformCoordinatesToGlobal(double &x, double &y);

        /// On point is picked event
        inline void PointPicked(double x, double y);


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


        Context m_context;

        EntityBuilder *m_receiver;
        // Draw manager instance
        // All entities, geometric and painting routines are implemented in the DrawManager
        DrawManager m_draw_manager;

        // Size of a visible area of the drawing
        // The size is being kept in pixels
        // and has to be refreshed each time on derived panel changes its size
        double m_width;
        double m_height;

        // Snap radius value in a real coordinates
        double m_snap_radius;

        // Keeps interactive state of the screen
        // For example: point picking, entity picking, doing nothing etc.
        // Should be volatile, because can be changed from other thread
        volatile InteractiveState m_screen_state;

        // Keeps mouse wheel state: pressed or not
        // Needed for screen dragging by pressed mouse wheel
        bool m_is_wheel_pressed;

        // Builder for entity
        // Exists during entity creation process only,
        // at a free state points to null-pointer
        AbstractBuilder *m_shape_builder;
};

#endif // SCREEN_H_INCLUDED
