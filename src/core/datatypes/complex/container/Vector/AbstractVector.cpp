/**
 * @file
 * This file contains the declaration of AbstractVector, a complex type
 * that acts as a base class for all AbstractVectors.
 *
 * @brief Declaration of AbstractVector
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-12-04, version 1.0
 * @extends Container
 *
 * $Id$
 */

#include "AbstractVector.h"
#include "Container.h"
#include "RbException.h"
#include "RbUtil.h"
#include "TypeSpec.h"
#include "Vector.h"
#include "VectorString.h"
#include <algorithm>

/** Set type of elements */
AbstractVector::AbstractVector(const TypeSpec& elemType) : Container(elemType) {
    
}


/** Set type of elements */
AbstractVector::AbstractVector(const TypeSpec& elemType, const MemberRules& memberRules) : Container(elemType,memberRules) {
    
}


/** Copy Constructor */
AbstractVector::AbstractVector(const AbstractVector &v) : Container(v) {
    
}


/** Destructor. Free the memory of the elements. */
AbstractVector::~AbstractVector(void) {
    
}

/** Assignment operator; make sure we get independent elements */
AbstractVector& AbstractVector::operator=( const AbstractVector& x ) {
    
    if ( this != &x ) {
        
        if (elementType != x.elementType) {
            throw RbException("Cannot assign a vector to another vector of different type.");
        }
    }
    
    return ( *this );
}


RbObject* AbstractVector::convertTo(const TypeSpec &type) const {
    
    if (type.getBaseType() == Vector_name) {
        Vector* newVector = new Vector(*type.getElementType());
        for (size_t i = 0; i < size(); i++) {
            newVector->push_back(getElement(i).clone());
        }
        return newVector;
    }
    
    return Container::convertTo(type);
}


/** Get class AbstractVector describing type of object */
const VectorString& AbstractVector::getClass(void) const { 
    
    static VectorString rbClass = VectorString(AbstractVector_name) + Container::getClass();
	return rbClass;
}


/** Print value for user */
void AbstractVector::printValue( std::ostream& o ) const {
    
    o << "[ ";
    for ( size_t i = 0; i<size(); i++) {
        if ( i != 0 )
            o << ", ";
        (dynamic_cast<const RbLanguageObject&>( getElement(i) )).printValue(o);
    }
    o <<  " ]";
    
}


void AbstractVector::setElement(const size_t index, RbObject* x) {
    RbLanguageObject *elem = dynamic_cast<RbLanguageObject*>( x );
    if (elem != NULL)
        setElement(index, elem );
}




