//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#ifndef VIEWER_SRC_PALETTE_HPP_
#define VIEWER_SRC_PALETTE_HPP_

#include <string>

class Palette
{
public:
	Palette();
	static void load(const std::string& parFile);
};


#endif /* VIEWER_SRC_PALETTE_HPP_ */