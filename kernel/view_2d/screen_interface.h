#ifndef SCREEN_INTERFACE_H_INCLUDED
#define SCREEN_INTERFACE_H_INCLUDED

#include "../graphics/colour.h"
#include "../api/exports.h"

class IAdapterDC;
class DrawManager;
class AbstractBuilder;

///\brief Common widget interface for interactive drawing.
/// A drafting panel can contain the screen interface implementation
/// or to be a derived class from the screen interface.
class DLL_EXPORT ScreenInterface
{
    public:
        ///\brief Refresh the screen: draw all entities and signs
        ///\param dc - device context (implementation of IAdapterDC)
        ///\see IAdapterDC
        virtual void RedrawAll(IAdapterDC &dc) = 0;


        ///\brief The method should be called on a derived panel resizing
        ///\param width - new panel width
        ///\param height - new panel height
        virtual void ScreenResize(const int &width, const int &height) = 0;


        ///\brief The method should be called on a mouse move over a screen
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\param is_ctrl_pressed - is control-button is pressed on a keyboard
        ///\param is_lb_pressed - is mouse left button pressed
        virtual void ScreenMouseMove(const int &coord_x, const int &coord_y,
                                     const bool &is_ctrl_pressed,
                                     const bool &is_lb_pressed) = 0;


        ///\brief The method should be called on mouse left button is clicked on a derived panel
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\param is_ctrl_pressed - is control-button is pressed on a keyboard
        virtual void ScreenMouseLeftButtonClicked(const int &coord_x,
                                                const int &coord_y,
                                                const bool &is_ctrl_pressed) = 0;


        ///\brief The method should be called on mouse left button released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse right button pressed down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseLeftButtonDown(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse right button is clicked on a derived panel
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\param is_ctrl_pressed - is control-button is pressed on a keyboard
        virtual void ScreenMouseRightButtonClicked(const int &coord_x,
                                                const int &coord_y,
                                                const bool &is_ctrl_pressed) = 0;


        ///\brief The method should be called on mouse right button released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseRightButtonUp(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse right button pressed down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseRightButtonDown(const int &coord_x, const int &coord_y) = 0;

        ///\brief The method receives information about pressed key.
        /// There is no need to process each key pressed,
        /// only necessary key codes can be processed depending
        /// on interaction logic.
        ///\param key - key ASCII code
        virtual void ScreenKeyPressed(char key) = 0;

        ///\brief The method should be called on mouse wheel event over a screen
        /// (mouse wheel rotation)
        ///\param direction - mouse wheel motion direction
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        virtual void ScreenMouseWheel(const int &direction,
                                      const int &coord_x,
                                      const int &coord_y) = 0;


        ///\brief The method should be called on mouse wheel click down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelDown(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse wheel click released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        virtual void ScreenMouseWheelUp(const int &coord_x, const int &coord_y) = 0;


        ///\brief Creates a new entity via builder.
        ///\param builder - entity builder instance
        virtual void CreateEntity(AbstractBuilder *builder) = 0;


        ///\brief Resets screen interactive state (executing command etc.)
        virtual void ScreenCancelCommand(void) = 0;


        ///\brief Returns pointer to a draw manager.
        /// Each instance of a screen has its own draw manager.
        ///\see DrawManager
        ///\return Pointer to a draw manager instance
        virtual DrawManager* GetDrawManager(void) = 0;


        ///\brief Sets current screen borders (in a real scale coordinates)
        ///\param left - left border value
        ///\param right - right border value
        ///\param top - top border value
        ///\param bottom - bottom border value
        virtual void SetBorders(const double &left,
                        const double &right,
                        const double &top,
                        const double &bottom) = 0;


        ///\brief Returns current screen borders (in a real scale coordinates)
        ///\param left - pointer to the left border container
        ///\param right - pointer to the right border container
        ///\param top - pointer to the top border container
        ///\param bottom - pointer to the bottom border container
        virtual void GetBorders(double *left,
                        double *right,
                        double *top,
                        double *bottom) const = 0;


        ///\brief Set screen background colour
        ///\param colour - colour value
        virtual void SetColour(const Colour &colour)
        {
            m_colour = colour;
        }


        ///\brief Returns colour of the screen
        ///\return colour value
        virtual Colour GetColour(void) const
        {
            return m_colour;
        }

    protected:
        // Screen background colour
        Colour m_colour;
};

#endif // SCREEN_INTERFACE_H_INCLUDED
