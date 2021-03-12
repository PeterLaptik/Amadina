#ifndef SCREEN_INTERFACE_H_INCLUDED
#define SCREEN_INTERFACE_H_INCLUDED

///\brief Common widget interface for interactive drawing.
/// A drafting panel can contain the screen interface implementation
/// or to be a derived class from the screen interface.
class ScreenInterface
{
    public:
        ///\brief The method should be called on a derived panel resizing
        ///\param width - new panel width
        ///\param height - new panel height
        virtual void ScreenResize(const int &width, const int &height) = 0;


        ///\brief The method should be called on a mouse move over a screen
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\param is_ctrl_pressed - is control-button is pressed on a keyboard
        ///\param is_lb_pressed - is mouse left button pressed
        ///\return true - if the screen has to be refreshed, otherwise - false
        virtual bool ScreenMouseMove(const int &coord_x, const int &coord_y,
                                     const bool &is_ctrl_pressed,
                                     const bool &is_lb_pressed) = 0;


        ///\brief The method should be called on mouse left button is clicked on a derived panel
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\param is_ctrl_pressed - is control-button is pressed on a keyboard
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseLeftButtonClicked(const int &coord_x,
                                                const int &coord_y,
                                                const bool &is_ctrl_pressed) = 0;


        ///\brief The method should be called on mouse left button released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse wheel event over a screen
        /// (mouse wheel rotation)
        ///\param direction - mouse wheel motion direction
        ///\param coord_x - x-coordinate of a mouse position
        ///\param coord_y - y-coordinate of a mouse position
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseWheel(const int &direction,
                                      const int &coord_x,
                                      const int &coord_y) = 0;


        ///\brief The method should be called on mouse wheel click down
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseWheelDown(const int &coord_x, const int &coord_y) = 0;


        ///\brief The method should be called on mouse wheel click released
        ///\param coord_x - x-coordinate of a mouse pointer
        ///\param coord_y - y-coordinate of a mouse pointer
        ///\return true is the screen has to be refreshed / repainted
        virtual bool ScreenMouseWheelUp(const int &coord_x, const int &coord_y) = 0;


        ///\brief Resets screen interactive state (executing commend etc.)
        ///\return true is the screen has to be refreshed / repainted
        virtual bool CancelCommand(void) = 0;
};

#endif // SCREEN_INTERFACE_H_INCLUDED
