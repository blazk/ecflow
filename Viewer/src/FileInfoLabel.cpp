//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#include "FileInfoLabel.hpp"

#include "VFileInfo.hpp"
#include "VReply.hpp"

FileInfoLabel::FileInfoLabel(QWidget* parent) : QLabel(parent)
{
	setObjectName(QString::fromUtf8("fileInfoLabel"));

    //Set size policy
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    //setMinimumSize(QSize(0, 60));
    //setMaximumSize(QSize(16777215, 45));

	setMargin(8);
	setAlignment(Qt::AlignLeft);

	//Other settings
    setAutoFillBackground(true);

    setFrameShape(QFrame::StyledPanel);
    setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

}

void FileInfoLabel::update(VReply* reply)
{
	if(!reply)
		clear();

	QString fileName=QString::fromStdString(reply->fileName());

	QColor col(Qt::black);
	QColor colText("#000010");
	QColor colSize(0,0,255);

	QString s;

	//Name
	s="<b><font color=" + col.name() + ">File: </font></b>";
	s+="<font color=" +colText.name() + ">" + fileName + "</font>";

	VFileInfo f(fileName);

	if(reply->fileReadMode() == VReply::LocalReadMode && f.exists())
	{
		s+="<br>";

		s+="<b><font color=" + col.name() + "> Size: </font></b>";
		s+="<font color=" + colSize.name() + ">" + f.formatSize() + "</font>";

		s+="<b><font color=" + col.name() + "> Permissions: </font></b>";
		s+="<font color=" + colText.name() + ">" + f.formatPermissions() + "</font>";

		s+="<b><font color=" + col.name() + "> Owner: </font></b>";
		s+="<font color=" + colText.name() + ">" + f.owner() + "</font>";

		s+="<b><font color=" + col.name() + "> Group: </font></b>";
		s+="<font color=" + colText.name() + ">" + f.group() + "</font>";

		s+="<b><font color=" + col.name() + "> Modified: </font></b>";
		s+="<font color=" + colText.name() + ">" + f.formatModDate() + "</font>";
	}

	if(reply->fileReadMode() != VReply::NoReadMode)
	{
		s+="<br>";
		s+="<b><font color=" + col.name() + "> Access method: </font></b>";
	}

	if(reply->fileReadMode() == VReply::LocalReadMode)
	{
		s+="<font color=" + colText.name() + "> read from disk</font>";

	}
	else if(reply->fileReadMode() == VReply::ServerReadMode)
	{
		int rowLimit=10000;
		s+="<font color=" + colText.name() + "> through server (first " + QString::number(rowLimit) + "lines)</font>";
	}
	else if(reply->fileReadMode() == VReply::LogServerReadMode)
	{
		s+="<font color=" + colText.name() + "> through log server</font>";
	}

	setText(s);
}

