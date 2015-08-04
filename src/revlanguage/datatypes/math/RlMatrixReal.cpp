#include "ConstantNode.h"
#include "Integer.h"
#include "MatrixReal.h"
#include "Natural.h"
#include "ModelVector.h"
#include "Real.h"
#include "Probability.h"
#include "RlMatrixReal.h"
#include "RlMemberFunction.h"
#include "RbUtil.h"
#include "RlString.h"
#include "TypeSpec.h"

#include <iomanip>
#include <sstream>

using namespace RevLanguage;

/* Default constructor */
MatrixReal::MatrixReal(void) : ModelObject<RevBayesCore::MatrixReal>( new RevBayesCore::MatrixReal(1,1,0) )
{
    
    // initialize the member methods
    initializeMethods();
}

MatrixReal::MatrixReal(const RevBayesCore::MatrixReal& from) : ModelObject<RevBayesCore::MatrixReal>( from.clone() )
{
    
    // initialize the member methods
    initializeMethods();
}

MatrixReal::MatrixReal(RevBayesCore::MatrixReal* m) : ModelObject<RevBayesCore::MatrixReal>( m )
{
    
    // initialize the member methods
    initializeMethods();
}

MatrixReal::MatrixReal( RevBayesCore::TypedDagNode<RevBayesCore::MatrixReal> * mat ) : ModelObject<RevBayesCore::MatrixReal>( mat )
{
    
    // initialize the member methods
    initializeMethods();
}


/** Clone object */
MatrixReal* MatrixReal::clone(void) const
{
    
	return new MatrixReal(*this);
}


/* Map calls to member methods */
RevPtr<RevVariable> MatrixReal::executeMethod(std::string const &name, const std::vector<Argument> &args, bool &found)
{
    
    if (name == "min")
    {
        
        found = true;
        
        double m = this->dagNode->getValue().getMin();
        return new RevVariable( new Real( m ) );
    }
    else if (name == "max")
    {
        found = true;
        
        double m = this->dagNode->getValue().getMax();
        return new RevVariable( new Real( m ) );
    }
    else if (name == "column")
    {
        found = true;
        
        const Natural& index = static_cast<const Natural&>( args[0].getVariable()->getRevObject() );
        int i = index.getValue();
        
        RevBayesCore::RbVector<double> m = this->dagNode->getValue().getColumn( i );
        return new RevVariable( new ModelVector<Real>( m ) );
    }
    
    return ModelObject<RevBayesCore::MatrixReal>::executeMethod( name, args, found );
}


/** Get Rev type of object */
const std::string& MatrixReal::getClassType(void)
{
    
    static std::string revType = "MatrixReal";
    
	return revType;
}


/** Get class type spec describing type of object */
const TypeSpec& MatrixReal::getClassTypeSpec(void)
{
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( RevObject::getClassTypeSpec() ) );
    
	return revTypeSpec;
}


///** Return member rules (no members) */
//const MemberRules& MatrixReal::getParameterRules(void) const
//{
//    
//    static MemberRules memberRules;
//    static bool rulesSet = false;
//    
//    if ( !rulesSet )
//    {
//        
//        memberRules.push_back( new ArgumentRule("x", RevObject::getClassTypeSpec(), ArgumentRule::BY_CONSTANT_REFERENCE ) );
//        memberRules.push_back( new Ellipsis( RevObject::getClassTypeSpec() ) );
//        
//        rulesSet = true;
//    }
//    
//    return memberRules;
//}


/** Get type spec */
const TypeSpec& MatrixReal::getTypeSpec( void ) const
{
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}


void MatrixReal::initializeMethods( void )
{
    // Add method for call "x[]" as a function
    ArgumentRules* squareBracketArgRules = new ArgumentRules();
    squareBracketArgRules->push_back( new ArgumentRule( "index" , Natural::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
    methods.addFunction("[]", new MemberFunction<MatrixReal,ModelVector<Real> >(this, squareBracketArgRules ) );
    
    // add method for call "min" as a function
    ArgumentRules* minArgRules = new ArgumentRules();
    methods.addFunction("min",  new MemberProcedure( Real::getClassTypeSpec(), minArgRules) );
    
    // add method for call "max" as a function
    ArgumentRules* maxArgRules = new ArgumentRules();
    methods.addFunction("max",  new MemberProcedure( Real::getClassTypeSpec(), maxArgRules) );
    
    // add method for call "column" as a function
    ArgumentRules* columnArgRules = new ArgumentRules();
    columnArgRules->push_back( new ArgumentRule( "index" , Natural::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
    methods.addFunction("column", new MemberProcedure( ModelVector<Real>::getClassTypeSpec(), columnArgRules ) );
    
}


/** Print value for user */
void MatrixReal::printValue(std::ostream &o) const
{
    
    long previousPrecision = o.precision();
    std::ios_base::fmtflags previousFlags = o.flags();
    
    std::fixed( o );
    o.precision( 3 );

    dagNode->printValue( o );
    
    o.setf( previousFlags );
    o.precision( previousPrecision );
}


