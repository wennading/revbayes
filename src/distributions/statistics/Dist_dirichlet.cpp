/**
 * @file
 * This file contains the implementation of Dist_dirichlet, which is used to hold
 * parameters and functions related to a Dirichlet distribution.
 *
 * @brief Implementation of Dist_dirichlet
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2009-12-14 12:43:32 +0100 (Mån, 14 Dec 2009) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-08-27, version 1.0
 *
 * $Id: MemberObject.h 194 2009-12-14 11:43:32Z ronquist $
 */

#include "ArgumentRule.h"
#include "DAGNode.h"
#include "Dist_dirichlet.h"
#include "Move_msimplex.h"
#include "RealPos.h"
#include "RandomNumberGenerator.h"
#include "RbException.h"
#include "RbMath.h"
#include "RbNames.h"
#include "RbStatistics.h"
#include "Real.h"
#include "ReferenceRule.h"
#include "Simplex.h"
#include "VectorReal.h"
#include "VectorString.h"
#include "Workspace.h"

#include <cmath>
#include <sstream>
#include <vector>


/** Default constructor for parser use */
Dist_dirichlet::Dist_dirichlet(void) : Distribution(getMemberRules()) {

}

/** Constructor for internal use */
Dist_dirichlet::Dist_dirichlet(std::vector<double> a) : Distribution(getMemberRules()) {

    setValue("alpha", new VectorReal(a));
}

/**
 * This function calculates the cumulative probability for
 * a Dirichlet-distributed random variable.
 *
 * @brief Dirichlet cumulative probability
 *
 * @param q     Quantile
 * @return      Cumulative probability
 *
 */
double Dist_dirichlet::cdf(double q) {

	/* TO DO: We should implement the cumulative probability for the Dirichlet. The most recent
	   algorithms are discussed in:
	   
	   Gouda, A. A., and T. Szantai. 2010. On numerical calculation of probabilities according 
	   to Dirichlet distribution. Ann. Oper. Res. 177:185–200. 
       
       Also, note that implementing the CDF here will require some changes to the object
       hierarchy; The cdf function is declared as pure virtual in the base classes of this object,
       and the pure virtual base class definition only takes in a single double. To properly 
       implement the cdf of the Dirichlet, however, you need to pass in a vector (a simplex)
       of values. */
    return 0.0;
}

/** Clone this object */
Dist_dirichlet* Dist_dirichlet::clone(void) const {

    return new Dist_dirichlet(*this);
}

/** Get class vector showing type of object */
const VectorString& Dist_dirichlet::getClass(void) const {

    static VectorString rbClass = VectorString(Dist_dirichlet_name) + Distribution::getClass();
    return rbClass;
}

/** Get default move */
Move* Dist_dirichlet::getDefaultMove(StochasticNode* node) {

	// default move for a stochastic node having a Dirichlet distribution
    return new Move_msimplex(node, 300.0, 4, 1.0);
}

/** Get min value of distribution */
const Real* Dist_dirichlet::getMin(void) {

    return NULL;
}

/** Get member variable rules */
const MemberRules& Dist_dirichlet::getMemberRules(void) const {

    static MemberRules memberRules;
    static bool        rulesSet = false;

    if (!rulesSet) 
		{
        memberRules.push_back(new ReferenceRule("alpha", VectorReal_name));

        /* Inherit rng from Distribution, put it at back */
        const MemberRules& inheritedRules = Distribution::getMemberRules();
        memberRules.insert(memberRules.end(), inheritedRules.begin(), inheritedRules.end()); 

        rulesSet = true;
		}

    return memberRules;
}

/** Get random variable type */
const std::string& Dist_dirichlet::getVariableType(void) const {

    return Simplex_name;
}

/**
 * This function calculates the natural log of the likelihood
 * ratio for an Dirichlet-distributed random variable under
 * two different values of the distribution parameter.
 *
 * @brief Natural log of Dirichlet likelihood ratio
 *
 * @param value     Value of random variable
 * @return          Natural log of the likelihood ratio
 */
double Dist_dirichlet::lnLikelihoodRatio(const RbObject* value) {

	// get the value and the parameters of the Dirichlet
    std::vector<double> aNew = ((VectorReal*) (getVariable("alpha")->getValue      ()))->getValue();
    std::vector<double> aOld = ((VectorReal*) (getVariable("alpha")->getStoredValue()))->getValue();
    std::vector<double> x    = ((VectorReal*) value)->getValue();
	
	// check that the vectors are all the same size
	if ( aNew.size() != aOld.size() || aNew.size() != x.size() )
		throw (RbException("Inconsistent size of vectors when calculating Dirichlet likelihood ratio"));
	
	// calculate the likelihood ratio for the two values of the Dirichlet parameters
	int n = aNew.size();
	double alpha0New = 0.0, alpha0Old = 0.0;
	for (int i=0; i<n; i++)
		{
		alpha0New += aNew[i];
		alpha0Old += aOld[i];
		}
	double lnP = RbMath::lnGamma(alpha0New) - RbMath::lnGamma(alpha0Old);
	for (int i=0; i<n; i++)
		lnP += ( RbMath::lnGamma(aOld[i]) - RbMath::lnGamma(aNew[i]) ) + ( (aNew[i] - aOld[i]) * std::log(x[i]) );
	return lnP;	
}

/**
 * This function calculates the natural log of the probability
 * density for a Dirichlet-distributed random variable.
 *
 * @brief Natural log of Dirichlet probability density
 *
 * @param value Observed value
 * @return      Natural log of the probability density
 */
double Dist_dirichlet::lnPdf(const RbObject* value) {

	// get the value and the parameters of the Dirichlet
    std::vector<double> a = ((VectorReal*) getValue("alpha"))->getValue();
    std::vector<double> x = ((VectorReal*) value)->getValue();

	// check that the vectors are both the same size
	if ( a.size() != x.size() )
		throw (RbException("Inconsistent size of vectors when calculating Dirichlet log probability density"));

	return RbStatistics::Dirichlet::lnPdf( a, x );
}

/**
 * This function calculates the natural log of the probability
 * density ratio for two Dirichlet-distributed random variables.
 *
 * @brief Natural log of Dirichlet probability density ratio
 *
 * @param newX      Value in numerator
 * @param oldX      Value in denominator
 * @return          Natural log of the probability density ratio
 */
double Dist_dirichlet::lnPriorRatio(const RbObject* newVal, const RbObject* oldVal) {

	// get the values and the parameters of the Dirichlet
    std::vector<double> a    = ((VectorReal*) getValue("rate"))->getValue();
    std::vector<double> newX = ((VectorReal*) newVal)->getValue();
    std::vector<double> oldX = ((VectorReal*) oldVal)->getValue();

	// check that the vectors are all the same size
	if ( a.size() != newX.size() || a.size() != oldX.size() )
		throw (RbException("Inconsistent size of vectors when calculating Dirichlet prior ratio"));

	// calculate the log prior ratio
	int n = a.size();
	double lnP = 0.0;
	for (int i=0; i<n; i++)
		lnP += (a[i] - 1.0) * (std::log(newX[i]) - std::log(oldX[i]));
    return lnP;
}

/**
 * This function calculates the probability density
 * for a Dirichlet-distributed random variable.
 *
 * @brief Dirichlet probability density
 *
 * @param value Observed value
 * @return      Probability density
 */
double Dist_dirichlet::pdf(const RbObject* value) {

	// get the value and the parameters of the Dirichlet
    std::vector<double> a = ((VectorReal*) getValue("alpha"))->getValue();
    std::vector<double> x = ((Simplex*) value)->getValue();

	// check that the vectors are both the same size
	if ( a.size() != x.size() )
		throw (RbException("Inconsistent size of vectors when calculating Dirichlet log probability density"));

	return RbStatistics::Dirichlet::pdf( a, x );
}

/**
 * This function calculates the quantile for a
 * Dirichlet-distributed random variable.
 *
 * @brief Quantile of Dirichlet probability density
 *
 * @param p     Cumulative probability of quantile
 * @return      Quantile
 *
 */
double Dist_dirichlet::quantile(const double p) {

    /* TO DO: I don't know if this can be sensibly implemented. See notes
       (above) on the cdf function for a Dirichlet rv. */
	throw (RbException("Cannot calculate the quantiles of a Dirichlet"));
    return 0.0;
}

/**
 * This function generates an Dirichlet-distributed
 * random variable.
 *
 * @brief Random draw from Dirichlet distribution
 *
 * @return      Random draw from Dirichlet distribution
 */
RbObject* Dist_dirichlet::rv(void) {

    std::vector<double> a      = ((VectorReal*) getValue("alpha"))->getValue();
    RandomNumberGenerator* rng = GLOBAL_RNG;
	std::vector<double> r(a.size());

	r = RbStatistics::Dirichlet::rv(a, rng);
    return new Simplex( r );
}


