/**
 * @file
 * This file contains the declaration of Func_history, which is
 * used to provide the user with information on history.
 *
 * @brief Declaration of Func_history
 *
 * @author Fredrik Ronquist
 * @license GPL version 3
 */

#ifndef Func_history_H
#define Func_history_H

#include "RlFunction.h"

namespace RevLanguage {
    
    class Func_history : public Function {
        
    public:
        Func_history( void );
        
        // Basic utility functions
        Func_history*                           clone(void) const;                                                          //!< Clone object
        static const std::string&               getClassType(void);                                                         //!< Get Rev type
        static const TypeSpec&                  getClassTypeSpec(void);                                                     //!< Get class type spec
        const TypeSpec&                         getTypeSpec(void) const;                                                    //!< Get language type of the object
        
        // Func_history functions
        const ArgumentRules&                    getArgumentRules(void) const;                                               //!< Get argument rules
        const TypeSpec&                         getReturnType(void) const;                                                  //!< Get type of return val
        bool                                    throws(void) const { return false; }                                         //!< Function may throw exceptions
        
        RevPtr<Variable>                        execute(void);                                                              //!< Execute function
        
    };
    
}

#endif
