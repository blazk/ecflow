//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================
#ifndef VIEWER_SRC_NODESEARCHWIDGET_HPP_
#define VIEWER_SRC_NODESEARCHWIDGET_HPP_

#include <QAbstractItemModel>
#include <QDialog>
#include <QWidget>

#include "ServerFilter.hpp"
#include "VInfo.hpp"

#include "ui_NodeSearchWidget.h"

class NodeQuery;
class NodeQueryEngine;
class NodeQueryResultModel;

class NodeSearchWidget : public QWidget, protected Ui::NodeSearchWidget
{
    Q_OBJECT

public:
    explicit NodeSearchWidget(QWidget *parent = 0);
    ~NodeSearchWidget();

    void setServerFilter(ServerFilter*);
    void setRootNode(VInfo_ptr);

public Q_SLOTS:
	void slotStop();

protected Q_SLOTS:
	void slotShowDefPanel(bool);
	void slotFind();
	void slotClose();
	void slotQueryStarted();
	void slotQueryFinished();
	void slotQueryEnabledChanged(bool queryEnabled);

Q_SIGNALS:
	void closeClicked();
	void selectionChanged(VInfo_ptr);

private:
	void adjustColumns();

	NodeQuery* query_;
	NodeQueryEngine* engine_;
	NodeQueryResultModel* model_;
	bool columnsAdjusted_;
};

#endif /* VIEWER_SRC_NODESEARCHWIDGET_HPP_ */