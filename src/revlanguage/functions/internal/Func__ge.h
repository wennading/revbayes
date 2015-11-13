/**
 * @file
 * This file contains the declaration and implementation
 * of the templated Func_ge, which is used to to compare to values ( a >= b).
 *
 * @brief Declaration and implementation of Func__ge
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2012-06-12 10:25:58 +0200 (Tue, 12 Jun 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: Func_vector.h 1626 2012-06-12 08:25:58Z hoehna $
 */

#ifndef Func__ge_H
#define Func__ge_H

#include "RlBoolean.h"
#include "RlTypedFunction.h"

#include <string>

namespace RevLanguage {
    
    template <typename leftValType, typename rightValType>
    class Func__ge : public TypedFunction<RlBoolean> {
        
    public:
        Func__ge();
        
        // Basic utility functions
        Func__ge*                                               clone(void) const;                                          //!< Clone the object
        static const std::string&                               getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                  getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                             getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                         getTypeSpec(void) const;                                    //!< Get language type of the object
        bool                                                    isInternal(void) const { return true; }                     //!< Is this an internal function?

        // Regular functions
        RevBayesCore::TypedFunction<RevBayesCore::Boolean>*     createFunction(void) const;                                 //!< Create a function object
        const ArgumentRules&                                    getArgumentRules(void) const;                               //!< Get argument rules
        
    };
    
}


#include "ArgumentRule.h"
#include "GreaterEqualFunction.h"
#include "RbUtil.h"
#include "RlBoolean.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypeSpec.h"



template <typename leftValType, typename rightValType>
RevLanguage::Func__ge<leftValType,rightValType>::Func__ge() : TypedFunction<RlBoolean>() {
    
}

/* Clone object */
template <typename leftValType, typename rightValType>
RevLanguage::Func__ge<leftValType,rightValType>* RevLanguage::Func__ge<leftValType,rightValType>::clone( void ) const {
    
    return new Func__ge<leftValType,rightValType>( *this );
}


/** Execute function: We rely on getValue and overloaded push_back to provide functionality */
template <typename leftValType, typename rightValType>
RevBayesCore::TypedFunction<RevBayesCore::Boolean>* RevLanguage::Func__ge<leftValType,rightValType>::createFunction( void ) const
{
    
    const RevBayesCore::TypedDagNode<typename leftValType::valueType>* leftVal = static_cast<const leftValType &>( args[0].getVariable()->getRevObject() ).getDagNode();
    const RevBayesCore::TypedDagNode<typename rightValType::valueType>* rightVal = static_cast<const rightValType &>( args[1].getVariable()->getRevObject() ).getDagNode();
    
    RevBayesCore::GreaterEqualFunction<typename leftValType::valueType, typename rightValType::valueType> *func = new RevBayesCore::GreaterEqualFunction<typename leftValType::valueType, typename rightValType::valueType>( leftVal, rightVal );
    
    return func;
    
}


/** Get argument rules */
template <typename leftValType, typename rightValType>
const RevLanguage::ArgumentRules& RevLanguage::Func__ge<leftValType,rightValType>::getArgumentRules( void ) const
{
    
    static ArgumentRules argumentRules = ArgumentRules();
    static bool          rulesSet = false;
    
    if ( !rulesSet )
    {
        
        argumentRules.push_back( new ArgumentRule( "", leftValType::getClassTypeSpec() , "The left hand side variable.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        argumentRules.push_back( new ArgumentRule( "", rightValType::getClassTypeSpec(), "The right hand side variable.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        rulesSet = true;
    }
    
    return argumentRules;
}


/** Get Rev type of object */
template <typename leftValType, typename rightValType>
const std::string& RevLanguage::Func__ge<leftValType,rightValType>::getClassType(void)
{
    
    static std::string revType = "Func__ge<" + leftValType::getClassType() + "," + rightValType::getClassType() + ">";
    
	return revType; 
}


/** Get class type spec describing type of object */
template <typename leftValType, typename rightValType>
const RevLanguage::TypeSpec& RevLanguage::Func__ge<leftValType,rightValType>::getClassTypeSpec(void)
{
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( Function::getClassTypeSpec() ) );
    
	return revTypeSpec; 
}


/**
 * Get the primary Rev name for this function.
 */
template <typename leftValType, typename rightValType>
std::string RevLanguage::Func__ge<leftValType, rightValType>::getFunctionName( void ) const
{
    // create a name variable that is the same for all instance of this class
    std::string f_name = "ge";
    
    return f_name;
}


/** Get type spec */
template <typename leftValType, typename rightValType>
const RevLanguage::TypeSpec& RevLanguage::Func__ge<leftValType,rightValType>::getTypeSpec( void ) const
{
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}


#endif


