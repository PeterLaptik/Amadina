#ifndef LEXER_FUNCTIONS_H_INCLUDED
#define LEXER_FUNCTIONS_H_INCLUDED

namespace cad
{
    namespace command
    {
        // Any function available in a lexer must have the following signature
        typedef double (*lexer_function_t)(double);

        // Initializes available lexer functions and constants
        void lexer_functions_init(void);

        // Sets degrees / radians mode
        // is_degree -- true for degrees mode / false for radians mode
        void lexer_set_use_degree_units(bool is_degree);

        // Following functions are to be called for transforming any angle values:
        // - deg_to_rad -- for incoming angle values if they will be used in math.h-functions
        // - rad_to_deg -- for returning angle values derived from math.h-functions
        // If degree mode is turned off, then the both functions do nothing (return received value).
        // Otherwise incoming values will be converted from degrees to radians for using in math.h-functions,
        // out-coming values will be converted from radians to degrees.
        //
        // Use this calls for trigonometric functions, and other functions computing angles
        //
        // Converts angle from degrees to radians if it is necessary
        double deg_to_rad(double x);
        // Converts angle from radians to degrees if it is necessary
        double rad_to_deg(double x);
    }
}

#endif // LEXER_FUNCTIONS_H_INCLUDED
