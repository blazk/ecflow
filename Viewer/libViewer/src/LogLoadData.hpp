//============================================================================
// Copyright 2009-2018 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#ifndef LOGLOADDATA_HPP
#define LOGLOADDATA_HPP

#include <map>
#include <string>
#include <vector>

#include <QAbstractItemModel>
#include <QGraphicsItem>
#include <QMap>
#include <QStringList>
#include <QWidget>

#include <QtCharts>
using namespace QtCharts;

class LogLoadData;
class LogLoadDataItem;

//Data for one type of request
class LogRequestItem
{
public:
    enum Type {ChildLabelType,ChildInitType,UserNewsType,UserSyncType,NoType};

    LogRequestItem() {}
    LogRequestItem(Type type,const std::string& name,const std::string& pattern) :
        type_(type), name_(name), pattern_(pattern) {}

    Type type_;
    std::string name_;
    std::string pattern_; //used to identify the request in the log file
    std::vector<int> req_;
    size_t sumTotal_; //sum of all the child and user requests
    size_t maxTotal_; //the maximum value of child+user requests
    int rank_;
    float percentage_;
    size_t counter_;
};


//Helper structure for data collection
struct LogReqCounter
{
   LogReqCounter(const std::string& name);

   void clear();
   void add(bool childCmd,const std::string& line);

   std::string name_; //used for suites
   size_t   childReq_;
   size_t   userReq_;
   std::vector<LogRequestItem> childSubReq_;
   std::vector<LogRequestItem> userSubReq_;
};

//Data structure containing load/request statistics for
//an individual suite or for all the suites
class LogLoadDataItem
{
public:
    LogLoadDataItem(const std::string& name);
    LogLoadDataItem();

    void clear();
    void init(size_t num);

    size_t size() const {return childReq_.size();}
    float percentage() const {return percentage_;}
    void setPercentage(float v) {percentage_=v;}
    size_t sumTotal() const {return sumTotal_;}
    size_t maxTotal() const {return maxTotal_;}
    int rank() const {return rank_;}
    void setRank(int v) {rank_=v;}
    const std::vector<int>& childReq() const {return childReq_;}
    const std::vector<int>& userReq() const {return userReq_;}
    const std::string& name() const {return name_;}
    void valuesAt(size_t idx,size_t& total,size_t& child,size_t& user) const;

    const std::vector<LogRequestItem>& childSubReq() const {return childSubReq_;}
    const std::vector<LogRequestItem>& userSubReq() const {return userSubReq_;}

    void add(const LogReqCounter&);
    static void buildSubReq(std::vector<LogRequestItem>& childSubReq,
                       std::vector<LogRequestItem>& useSubReq);

#if 0
    void add(size_t childVal,size_t userVal)
    {
        childReq_.push_back(static_cast<int>(childVal));
        userReq_.push_back(static_cast<int>(userVal));

        size_t tot=childVal + userVal;
        sumTotal_+=tot;
        if(maxTotal_ < tot)
            maxTotal_ = tot;
    }
#endif

protected:
    void buildSubReq();

    std::vector<int> childReq_; //per seconds
    std::vector<int> userReq_;  //per seconds

    std::vector<LogRequestItem> childSubReq_;
    std::vector<LogRequestItem> userSubReq_;


    size_t sumTotal_; //sum of all the child and user requests
    size_t maxTotal_; //the maximum value of child+user requests
    int rank_; //the rank of this item within other items with regards to sumTotal_
    float percentage_; //0-100, the percentage of sumTotal_ with respect to the
                       //sum of sumTotal_ of all the items

    std::string name_; //the name of the item (only makes sense for suites)
};


//The top level class for load/request statistics
class LogLoadData
{
public:
    enum TimeRes {SecondResolution, MinuteResolution};

    LogLoadData() : timeRes_(SecondResolution)  {}

    void clear();
    const LogLoadDataItem& dataItem() const {return total_;}
    QStringList suiteNames() const {return suites_;}
    const std::vector<LogLoadDataItem>& suites() const {return suiteData_;}
    const LogLoadDataItem& total() const {return total_;}
    TimeRes timeRes() const {return timeRes_;}
    void setTimeRes(TimeRes);
    void loadLogFile(const std::string& logFile);

    void getChildReq(QLineSeries& series);
    void getUserReq(QLineSeries& series);
    void getTotalReq(QLineSeries& series,int& maxVal);

    void getSuiteChildReq(size_t,QLineSeries& series);
    void getSuiteUserReq(size_t,QLineSeries& series);
    void getSuiteTotalReq(size_t,QLineSeries& series);

    void getSuiteChildSubReq(size_t,size_t,QLineSeries& series);
    void getSuiteUserSubReq(size_t,size_t,QLineSeries& series);

    const std::vector<qint64>& time() const {return time_;}
    qint64 period() const;
    bool indexOfTime(qint64 t,size_t&,size_t,qint64) const;

private:
    void getSeries(QLineSeries& series,const std::vector<int>& vals);
    void getSeries(QLineSeries& series,const std::vector<int>& vals1,
                   const std::vector<int>& vals2,int& maxVal);
    void add(std::vector<std::string> time_stamp,const LogReqCounter& total,
             const std::vector<LogReqCounter>& suite_vec);

    void processSuites();

    bool extract_suite_path(const std::string& line,bool child_cmd,std::vector<LogReqCounter>& suite_vec,
                            size_t& column_index);

    TimeRes timeRes_;
    std::vector<qint64> time_; //times stored as msecs since the epoch
    LogLoadDataItem total_; //generic data item for all the suites
    std::vector<LogLoadDataItem> suiteData_; //suite-related data items
    QStringList suites_;
};

#endif // LOGLOADDATA_HPP
