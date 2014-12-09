/**
 * @file
 * This file contains the implementation of RlChromosomesState, which is
 * a RevBayes wrapper around a regular Chromosomes character.
 *
 * @brief Implementation of RlChromosomesState
 *
 * (c) Copyright 2014-
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: RlChromosomesState.cpp $
 */

#include "RlChromosomesState.h"
#include "ConstantNode.h"
#include "RbUtil.h"
#include "TypeSpec.h"
#include <sstream>

using namespace RevLanguage;

/** Default constructor */
ChromosomesState::ChromosomesState(void) : ModelObject<RevBayesCore::ChromosomesState>() {
    
}

/** Construct from bool */
ChromosomesState::ChromosomesState(const RevBayesCore::ChromosomesState &d) : ModelObject<RevBayesCore::ChromosomesState>( new RevBayesCore::ChromosomesState(d) ) {
    
}

ChromosomesState::ChromosomesState( RevBayesCore::TypedDagNode<RevBayesCore::ChromosomesState> *v ) : ModelObject<RevBayesCore::ChromosomesState>( v ) {
    
}


/** Clone object */
ChromosomesState* ChromosomesState::clone(void) const {
    
	return new ChromosomesState(*this);
}



/** Get Rev type of object */
const std::string& ChromosomesState::getClassType(void) {
    
    static std::string revType = "Chromosomes";
    
	return revType;
}

/** Get class type spec describing type of object */
const TypeSpec& ChromosomesState::getClassTypeSpec(void) {
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( RevObject::getClassTypeSpec() ) );
    
	return revTypeSpec;
}



/** Get type spec */
const TypeSpec& ChromosomesState::getTypeSpec( void ) const {
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}


