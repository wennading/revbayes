/**
 * @file
 * This file contains the implementation of CharacterContinuous, which is
 * the base class for the continuous character data type in RevBayes.
 *
 * @brief Implementation of CharacterContinuous
 *
 * (c) Copyright 2009-
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 *
 * $Id$
 */

#include "RbUtil.h"
#include "CharacterContinuous.h"
#include "VectorString.h"
#include <cmath>
#include <sstream>


// Definition of the static type spec member
const TypeSpec CharacterContinuous::typeSpec(CharacterContinuous_name);

/** Default constructor */
CharacterContinuous::CharacterContinuous(void) : Character() {

    mean     = 0.0;
    variance = 0.0;
}


/** Copy constructor */
CharacterContinuous::CharacterContinuous(const CharacterContinuous& s) : Character() {

    mean     = s.mean;
    variance = s.variance;
}


/** Constructor that sets the mean value */
CharacterContinuous::CharacterContinuous(const double x) : Character() {

    mean     = x;
    variance = 0.0;
}


/** Constructor that sets the mean and variance */
CharacterContinuous::CharacterContinuous(const double x, const double v) : Character() {

    mean     = x;
    variance = v;
}


/** Equals comparison */
bool CharacterContinuous::operator==(const Character& x) const {

    const CharacterContinuous* derivedX = static_cast<const CharacterContinuous*>(&x);

    if ( fabs(mean - derivedX->mean) < 0.000000001 && fabs(variance - derivedX->variance) < 0.000000001 )
        return true;
    return false;
}


/** Not equals comparison */
bool CharacterContinuous::operator!=(const Character& x) const {

    return !operator==(x);
}


/** Clone object */
CharacterContinuous* CharacterContinuous::clone(void) const {

	return new CharacterContinuous( *this );
}


/** Get class vector describing type of object */
const VectorString& CharacterContinuous::getClass(void) const {

    static VectorString rbClass = VectorString( CharacterContinuous_name ) + Character::getClass();
    return rbClass;
}


/** Get the type spec of this class. We return a static class variable because all instances will be exactly from this type. */
const TypeSpec& CharacterContinuous::getTypeSpec(void) const {
    return typeSpec;
}


/** Print information for the user */
void CharacterContinuous::printValue(std::ostream &o) const {

    if ( fabs(variance - 0.0) < 0.00000001 )
        o << mean;
    else
        o << mean << " (" << variance << ")";
}


