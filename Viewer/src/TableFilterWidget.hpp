//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//============================================================================

#ifndef TABLEFILTERWIDGET_INC_
#define TABLEFILTERWIDGET_INC_

#include "ui_TableFilterWidget.h"

#include <QWidget>

class NodeFilterDef;

class TableFilterWidget : public QWidget, private Ui::TableFilterWidget
{
Q_OBJECT

public:
    explicit TableFilterWidget(QWidget *parent=0);
    ~TableFilterWidget() {};

    void build(NodeFilterDef*);

public Q_SLOTS:


private:
	NodeFilterDef* filterDef_;

};

#endif
