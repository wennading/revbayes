/**
 * @file
 * This file contains the declaration of the deterministic variable class for Vectors.
 * This class is derived from the deterministic node and each instance will represent a deterministic variable
 * computing the Vector of its parameters.
 *
 * @brief Declaration of the deterministic variable for Vectors.
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2012-07-06, version 1.0
 * @interface TypedDagNode
 *
 * $Id$
 */



#ifndef LessEqualFunction_H
#define LessEqualFunction_H

#include "RbBoolean.h"
#include "TypedFunction.h"

#include <vector>

namespace RevBayesCore {
    
    template <class leftValueType, class rightValueType>
    class LessEqualFunction : public TypedFunction<Boolean> {
        
    public:
        LessEqualFunction(const TypedDagNode<leftValueType> * l, const TypedDagNode<rightValueType> *r);
        virtual                                            ~LessEqualFunction(void);                                                       //!< Virtual destructor
        
        // public member functions
        LessEqualFunction*                                  clone(void) const;                                                          //!< Create an independent clone
        void                                                update(void);
        
    protected:
        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);            //!< Implementation of swaping parameters
        
    private:
        
        // members
        const TypedDagNode<leftValueType>*                  left;
        const TypedDagNode<rightValueType>*                 right;
        
    };
    
}

template <class leftValueType, class rightValueType>
RevBayesCore::LessEqualFunction<leftValueType,rightValueType>::LessEqualFunction(const TypedDagNode<leftValueType> *l, const TypedDagNode<rightValueType> *r) : TypedFunction<Boolean>( new Boolean(false) ),
    left( l ),
    right( r )
{
    // add the parameters as parents
    this->addParameter( left );
    this->addParameter( right );
    
    update();
}


template <class leftValueType, class rightValueType>
RevBayesCore::LessEqualFunction<leftValueType,rightValueType>::~LessEqualFunction( void )
{
    // We don't delete the parameters, because they might be used somewhere else too. The model needs to do that!
}



template <class leftValueType, class rightValueType>
RevBayesCore::LessEqualFunction<leftValueType,rightValueType>* RevBayesCore::LessEqualFunction<leftValueType,rightValueType>::clone( void ) const
{
    return new LessEqualFunction<leftValueType,rightValueType>( *this );
}


template <class leftValueType, class rightValueType>
void RevBayesCore::LessEqualFunction<leftValueType,rightValueType>::update( void )
{
    
    *this->value = (left->getValue() <= right->getValue());
    
}



template <class leftValueType, class rightValueType>
void RevBayesCore::LessEqualFunction<leftValueType,rightValueType>::swapParameterInternal(const DagNode *oldP, const DagNode *newP)
{
    
    if ( oldP == left )
    {
        left = static_cast<const TypedDagNode<leftValueType>* >( newP );
    }
    if ( oldP == right )
    {
        right = static_cast<const TypedDagNode<rightValueType>* >( newP );
    }
    
}

#endif
