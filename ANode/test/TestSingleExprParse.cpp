#define BOOST_TEST_MODULE TestSingle
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// Name        :
// Author      : Avi
// Revision    : $Revision: #10 $
//
// Copyright 2009-2016 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
#include "ExprParser.hpp"
#include "ExprAst.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;


// DEBUG AID: to see the expression tree, invert the expected evaluation
//            so that test fail's

BOOST_AUTO_TEST_SUITE( NodeTestSuite )

BOOST_AUTO_TEST_CASE( test_single_expression )
{
    std::cout <<  "ANode:: ...test_single_expression\n";

	// The map key = trigger expression,
    // value.first  = type of expected root abstract syntax tree
    // value.second = result of expected evaluation
	map<string,std::pair<string,bool> > exprMap;

   exprMap["../family1/a:myEvent"] = std::make_pair(AstOr::stype(),true);
   //exprMap["checkdata:done or checkdata == complete"] = std::make_pair(AstOr::stype(),false);

 	std::pair<string, std::pair<string,bool> > p;
	BOOST_FOREACH(p, exprMap ) {

  		ExprParser theExprParser(p.first);
		std::string errorMsg;
		bool ok = theExprParser.doParse(errorMsg);
		BOOST_REQUIRE_MESSAGE(ok,errorMsg);

		string expectedRootType       = p.second.first;
		bool expectedEvaluationResult = p.second.second;

      std::stringstream ss;

		Ast* top = theExprParser.getAst();
		BOOST_REQUIRE_MESSAGE( top ,"No abstract syntax tree");
		BOOST_REQUIRE_MESSAGE( top->left() ,"No root created");
		BOOST_REQUIRE_MESSAGE( top->left()->isRoot() ,"First child of top should be a root");
		BOOST_REQUIRE_MESSAGE( top->left()->type() == expectedRootType,"expected root type " << expectedRootType << " but found " << top->left()->type());
      top->print_flat(ss);
		BOOST_REQUIRE_MESSAGE( expectedEvaluationResult == top->evaluate(),"evaluation not as expected for:\n" << p.first << "\n" << ss.str() << "\n" << *top);
	}
}

BOOST_AUTO_TEST_SUITE_END()

