/**
 * @file
 * This file contains the implementation of FileMonitor, used to save
 * information to file about the monitoring of a variable DAG node.
 *
 * @brief Implementation of FileMonitor
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-09-08, version 1.0
 *
 * $Id$
 */

#include "DagNodeContainer.h"
#include "Ellipsis.h"
#include "Integer.h"
#include "FileMonitor.h"
#include "RbException.h"
#include "RbUtil.h"
#include "ValueRule.h"
#include "VariableNode.h"
#include "VectorString.h"

#include <sstream>


// Definition of the static type spec member
const TypeSpec FileMonitor::typeSpec(FileMonitor_name);

/** Constructor */
FileMonitor::FileMonitor(void) : Monitor(getMemberRules() ) {
    
}

/** Copy Constructor */
FileMonitor::FileMonitor(const FileMonitor &x) : Monitor(x) {
    
    // shallow copy
    separator = x.separator;
    
}

FileMonitor::~FileMonitor() {
   
}


/** Clone the object */
FileMonitor* FileMonitor::clone(void) const {

    return new FileMonitor(*this);
}


/** Get class vector describing type of object */
const VectorString& FileMonitor::getClass() const {

    static VectorString rbClass = VectorString(FileMonitor_name) + ConstantMemberObject::getClass();
    return rbClass;
}

/** Return member rules */
const MemberRules& FileMonitor::getMemberRules( void ) const {
    
    static MemberRules memberRules = MemberRules();
    static bool        rulesSet = false;
    
    if (!rulesSet) 
    {
        memberRules.push_back( new ValueRule( "filename"  , TypeSpec(RbString_name)         ) );
        memberRules.push_back( new ValueRule( "printgen"  , TypeSpec(Integer_name),  new Integer(1)    ) );
        memberRules.push_back( new ValueRule( "separator" , TypeSpec(RbString_name), new RbString("\t") ) );
        memberRules.push_back( new ValueRule( "variable"  , TypeSpec(RbLanguageObject_name) ) );
        memberRules.push_back( new Ellipsis (               TypeSpec(RbLanguageObject_name) ) );
        rulesSet = true;
    }
    
    return memberRules;
}


/** Get the type spec of this class. We return a static class variable because all instances will be exactly from this type. */
const TypeSpec& FileMonitor::getTypeSpec(void) const {
    return typeSpec;
}


/** Monitor value unconditionally */
void FileMonitor::monitor(void) {

    for (std::vector<VariableNode*>::const_iterator it=nodes.begin(); it!=nodes.end(); it++) {
        // add a separator before every new element except the first element
        if ( it != nodes.begin() )
            outStream << separator;
        
        // print the value
        (*it)->printValue(outStream);
    }
    
    outStream << std::endl;
    
    
}


/** Monitor value at generation gen */
void FileMonitor::monitor(int gen) {

    // get the printing frequency
    int samplingFrequency = dynamic_cast<const Integer&>( getMemberValue("printgen") ).getValue();
    
    if (gen % samplingFrequency == 0) {
        // print the iteration number first
        outStream << gen;
        
        for (std::vector<VariableNode*>::const_iterator it=nodes.begin(); it!=nodes.end(); it++) {
            // add a separator before every new element
            outStream << separator;
            
            // print the value
            (*it)->printValue(outStream);
        }

	outStream << std::endl;
    }
}


/** open the file stream for printing */
void FileMonitor::openStream(void) {

    // get the filename
    std::string filename = dynamic_cast<const RbString&>( getMemberValue("filename") ).getValue();
    
    // open the stream to the file
    outStream.open(filename.c_str());
    
}

/** Print header for monitored values */
void FileMonitor::printHeader() {
  
    // print one column for the iteration number
    outStream << "Sample";
    
    for (std::vector<VariableNode*>::const_iterator it=nodes.begin(); it!=nodes.end(); it++) {
        // add a separator before every new element
        outStream << separator;
        
         VariableNode* theNode = *it;
        
        // print the header
        if (theNode->getName() != "")
            outStream << theNode->getName();
        else
            outStream << "Unnamed " << theNode->getType();
    }
    
    outStream << std::endl;
}


/** Print value for user */
void FileMonitor::printValue(std::ostream& o) const {
    
    // get the printing frequency
    int samplingFrequency = dynamic_cast<const Integer&>( getMemberValue("printgen") ).getValue();
    
    o << "Monitor: interval = " << samplingFrequency;
}


void FileMonitor::setMemberVariable(std::string const &name, Variable* var) {
    
    // catch setting of the variables 
    if (name == "variable" || name == "") {
        DAGNode* theNode = var->getDagNode();
        if (theNode->getValue().isType(DagNodeContainer_name)) {
            const DagNodeContainer& theContainer = static_cast<const DagNodeContainer&>( theNode->getValue() );
            for (size_t i = 0; i < theContainer.size(); i++) {
                theNode = static_cast<const VariableSlot&>( theContainer.getElement(i) ).getDagNode()->clone();
                if (theNode->isType(VariableNode_name)) {
                    nodes.push_back( static_cast<VariableNode*>( theNode ) );
//                } else {
//                    throw RbException("Cannot monitor a constant node!");
                }
            }
        }
        else {
            if (theNode->isType(VariableNode_name)) {
                nodes.push_back( static_cast<VariableNode*>( theNode ) );
//            } else {
//                throw RbException("Cannot monitor a constant node!");
            }
        }
    } 
    else if (name == "separator") {
        separator = static_cast<RbString&>( var->getValue() ).getValue();
        
        // call parent class to set member variable
        ConstantMemberObject::setMemberVariable( name, var );
    } 
    else {
        // call parent class to set member variable
        ConstantMemberObject::setMemberVariable( name, var );
    }
}


