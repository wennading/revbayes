/**
 * @file
 * This file contains the declaration of Func_sort, which
 * is used to return a sorted vector from an input vector.
 *
 * @brief Declaration of Func_sort
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id$
 */

#ifndef Func_sort_H
#define Func_sort_H

#include "RbFunction.h"

#include <map>
#include <string>
#include <vector>

class DAGNode;
class VectorString;

const std::string Func_sort_name = "Sort function";

template <typename valType>
class Func_sort :  public RbFunction {
	
public:
	// Basic utility functions
	Func_sort*                  clone(void) const;                                  //!< Clone the object
	const VectorString&         getClass(void) const;                               //!< Get class vector
    const TypeSpec&             getTypeSpec(void) const;                            //!< Get language type of the object
	
	// Regular functions
    const ArgumentRules&        getArgumentRules(void) const;                       //!< Get argument rules
	const TypeSpec&             getReturnType(void) const;                          //!< Get type of return value

protected:
    RbLanguageObject*           executeFunction(void);                              //!< Execute operation

private:
    static const TypeSpec       typeSpec;	
};

#endif

#include "Ellipsis.h"
#include "RbUtil.h"
#include "TypeSpec.h"
#include "ValueRule.h"


// Definition of the static type spec member
template <typename valType>
const TypeSpec Func_sort<valType>::typeSpec("Func_sort", new TypeSpec(valType().getType()));


/** Clone object */
template <typename valType>
Func_sort<valType>* Func_sort<valType>::clone( void ) const {
    
    return new Func_sort( *this );
}


/** Execute function: We rely on operator overloading to provide the necessary functionality */
template <typename valType> 
RbLanguageObject* Func_sort<valType>::executeFunction( void ) {
    
    valType* val = static_cast<valType*>( (*args)[0].getValue().clone() );    
    if(val->size() == 0) 
        return val;
    val->sort();
    
    return val;
}


/** Get argument rules */
template <typename valType>
const ArgumentRules& Func_sort<valType>::getArgumentRules( void ) const {
    
    static ArgumentRules argumentRules = ArgumentRules();
    static bool          rulesSet = false;
    
    if ( !rulesSet ) 
    {
        argumentRules.push_back( new ValueRule( "", valType() .getTypeSpec() ) );
        rulesSet = true;
    }
    
    return argumentRules;
}


/** Get class vector describing type of object */
template <typename valType>
const VectorString& Func_sort<valType>::getClass( void ) const {
    
    static std::string  rbName  = "Func_sort<" + valType().getType() + ">"; 
    static VectorString rbClass = VectorString( rbName ) + RbFunction::getClass();
    
    return rbClass;
}


/** Get return type */
template <typename valType> 
const TypeSpec& Func_sort<valType>::getReturnType( void ) const {
	
    static TypeSpec retType = valType().getTypeSpec();
    return retType;
}


/** Get return type */
template <typename valType>
const TypeSpec& Func_sort<valType>::getTypeSpec( void ) const {
    
    return typeSpec;
}


