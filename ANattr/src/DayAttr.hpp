#ifndef DAYATTR_HPP_
#define DAYATTR_HPP_
//============================================================================
// Name        :
// Author      : Avi
// Revision    : $Revision: #27 $ 
//
// Copyright 2009-2017 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0 
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
// In applying this licence, ECMWF does not waive the privileges and immunities 
// granted to it by virtue of its status as an intergovernmental organisation 
// nor does it submit to any jurisdiction. 
//
// Description : Note: calendarChanged() once a day is free, it stays free
//               It relies on parent cron/repeat to re-queue
//============================================================================

#include <ostream>
#include <vector>
#include <string>
#include "Serialization.hpp"
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace ecf { class Calendar;} // forward declare class that is in a name space

// Use default copy constructor, assignment operator, destructor
class DayAttr {
public:
	enum Day_t { SUNDAY=0, MONDAY=1, TUESDAY=2, WEDNESDAY=3, THURSDAY=4, FRIDAY=5, SATURDAY=6 };
   DayAttr() : day_(DayAttr::SUNDAY), free_(false),state_change_no_(0) {}
   explicit DayAttr(Day_t day) : day_(day), free_(false),state_change_no_(0) {}
   explicit DayAttr(const std::string& str) : day_(DayAttr::getDay(str)), free_(false),state_change_no_(0) {}
   explicit DayAttr(const boost::gregorian::date& date)
	: day_(static_cast<DayAttr::Day_t>(date.day_of_week().as_number())), free_(false),state_change_no_(0) {}

	std::ostream& print(std::ostream&) const;
	bool operator==(const DayAttr& rhs) const;
   bool operator<(const DayAttr& rhs) const { return day_ < rhs.day_; }
	bool structureEquals(const DayAttr& rhs) const;

	void setFree();   // ensures that isFree() always returns true
	void clearFree(); // resets the free flag
	bool isSetFree() const { return free_; }
	void calendarChanged( const ecf::Calendar& c ) ; // can set attribute free
	bool isFree(const ecf::Calendar&) const;
	bool checkForRequeue( const ecf::Calendar&) const;
	bool validForHybrid(const ecf::Calendar&) const;
 	bool why(const ecf::Calendar&, std::string& theReasonWhy) const;

	// The state_change_no is never reset. Must be incremented if it can affect equality
 	unsigned int state_change_no() const { return state_change_no_; }

        std::string name() const { return toString(); } /* ABO */
	std::string toString() const;
	std::string dump() const;

	// return the days, if input is not valid will throw a runtime_error
	static DayAttr create(const std::string& dayStr);
	static DayAttr::Day_t getDay(const std::string&);

	static std::vector<std::string> allDays();

	// access
	DayAttr::Day_t day() const { return day_;}

private:
   bool is_free(const ecf::Calendar&) const; // ignores free_

private:
   DayAttr::Day_t day_;
   bool           free_;         // persisted for use by why() on client side
   unsigned int  state_change_no_;  // *not* persisted, only used on server side

   friend class cereal::access;
   template<class Archive>
   void serialize(Archive & ar, std::uint32_t const version )
   {
      ar( CEREAL_NVP(day_),
          CEREAL_NVP(free_)
      );
   }
};
#endif
