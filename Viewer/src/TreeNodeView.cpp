//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//============================================================================

#include "TreeNodeView.hpp"

#include <QApplication>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>

#include "ActionHandler.hpp"
#include "Animation.hpp"
#include "ExpandState.hpp"
#include "NodeFilterModel.hpp"
#include "TreeNodeViewDelegate.hpp"
#include "VNode.hpp"

TreeNodeView::TreeNodeView(QWidget* parent) :
	QTreeView(parent)
{
	expandState_=new ExpandState();
	actionHandler_=new ActionHandler(this);

	//Set the model.
	setModel(model_);

	//Create delegate to the view
	TreeNodeViewDelegate *delegate=new TreeNodeViewDelegate(this);
	setItemDelegate(delegate);

	//setRootIsDecorated(false);
	setAllColumnsShowFocus(true);
	setUniformRowHeights(true);
	setMouseTracking(true);
	setSelectionMode(QAbstractItemView::ExtendedSelection);

	//!!!!We need to do it because:
	//The background colour between the views left border and the nodes cannot be
	//controlled by delegates or stylesheets. It always takes the QPalette::Highlight
	//colour from the palette. Here we set this to transparent so that Qt could leave
	//this area empty and we will fill it appropriately in our delegate.
	QPalette pal=palette();
	pal.setColor(QPalette::Highlight,Qt::transparent);
	setPalette(pal);

	//Hide header
	header()->hide();

	//Context menu
	setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
		                this, SLOT(slotContextMenu(const QPoint &)));

	//Selection
	connect(this,SIGNAL(clicked(const QModelIndex&)),
			this,SLOT(slotSelectItem(const QModelIndex)));

	connect(this,SIGNAL(doubleClicked(const QModelIndex&)),
			this,SLOT(slotDoubleClickItem(const QModelIndex)));

	expandAll();
}

TreeNodeView::~TreeNodeView()
{
	delete expandState_;
	delete actionHandler_;
}

void TreeNodeView::setModel(NodeFilterModel *model)
{
	model_= model;

	//Set the model.
	QTreeView::setModel(model_);
}


QWidget* TreeNodeView::realWidget()
{
	return this;
}

//Collects the selected list of indexes
QModelIndexList TreeNodeView::selectedList()
{
  	QModelIndexList lst;
  	Q_FOREACH(QModelIndex idx,selectedIndexes())
	  	if(idx.column() == 0)
		  	lst << idx;
	return lst;
}

void TreeNodeView::slotSelectItem(const QModelIndex&)
{
	QModelIndexList lst=selectedIndexes();
	if(lst.count() > 0)
	{
		VInfo_ptr info=model_->nodeInfo(lst.front());
		if(info)
		{
			Q_EMIT selectionChanged(info);
		}
	}
}
VInfo_ptr TreeNodeView::currentSelection()
{
	QModelIndexList lst=selectedIndexes();
	if(lst.count() > 0)
	{
		return model_->nodeInfo(lst.front());
	}
	return VInfo_ptr();
}

void TreeNodeView::currentSelection(VInfo_ptr info)
{
	QModelIndex idx=model_->infoToIndex(info);
	if(idx.isValid())
	{
			setCurrentIndex(idx);
			Q_EMIT selectionChanged(info);
	}
}

void TreeNodeView::slotSetCurrent(VInfo_ptr info)
{
	QModelIndex idx=model_->infoToIndex(info);
	if(idx.isValid())
	{
			setCurrentIndex(idx);
			Q_EMIT selectionChanged(info);
	}
}

void TreeNodeView::slotDoubleClickItem(const QModelIndex&)
{
}

void TreeNodeView::slotContextMenu(const QPoint &position)
{
	QModelIndexList lst=selectedList();
	//QModelIndex index=indexAt(position);
	QPoint scrollOffset(horizontalScrollBar()->value(),verticalScrollBar()->value());

	handleContextMenu(indexAt(position),lst,mapToGlobal(position),position+scrollOffset,this);
}


void TreeNodeView::handleContextMenu(QModelIndex indexClicked,QModelIndexList indexLst,QPoint globalPos,QPoint widgetPos,QWidget *widget)
{
  	//Node actions
  	if(indexClicked.isValid() && indexClicked.column() == 0)   //indexLst[0].isValid() && indexLst[0].column() == 0)
	{
	  	qDebug() << "context menu" << indexClicked;

  		std::vector<VInfo_ptr> nodeLst;
		for(int i=0; i < indexLst.count(); i++)
		{
			VInfo_ptr info=model_->nodeInfo(indexLst[i]);
			if(!info->isEmpty())
				nodeLst.push_back(info);
		}

		actionHandler_->contextMenu(nodeLst,globalPos);
	}

	//Desktop actions
	else
	{
	}
}

void TreeNodeView::slotViewCommand(std::vector<VInfo_ptr> nodeLst,QString cmd)
{

	if(nodeLst.size() == 0)
		return;

	/*if(cmd == "set_as_root")
	{
		qDebug() << "set as root";
		model_->setRootNode(nodeLst.at(0)->node());
		expandAll();
	}*/
}


void TreeNodeView::reload()
{
	//model_->reload();
	//expandAll();
}

void TreeNodeView::rerender()
{
	viewport()->update();
}

void TreeNodeView::slotRepaint(Animation* an)
{
	if(!an)
		return;

	Q_FOREACH(QModelIndex idx,an->targets())
	{
		update(idx);
	}
}


//====================================================
// Expand state management
//====================================================

//Save the expand state for the given node (it can be a server as well)
void TreeNodeView::slotSaveExpand(const VNode* node)
{
	expandState_->clear();

	QModelIndex idx=model_->nodeToIndex(node);
	if(isExpanded(idx))
	{
		expandState_->setRoot(node->strName());
		saveExpand(expandState_->root(),idx);
	}
}

void TreeNodeView::saveExpand(ExpandNode *parentExpand,const QModelIndex& idx)
{
	for(int i=0; i < model_->rowCount(idx); i++)
	{
		QModelIndex chIdx=model_->index(i, 0, idx);

		if(!isExpanded(chIdx))
	        continue;
		else
		{
			ExpandNode* expand=parentExpand->add(chIdx.data(Qt::DisplayRole).toString().toStdString());
			saveExpand(expand,chIdx);
		}
	}
}

//Save the expand state for the given node (it can be a server as well)
void TreeNodeView::slotRestoreExpand(const VNode* node)
{
	if(!expandState_->root())
		return;

	if(node->strName() != expandState_->root()->name_)
	{
		expandState_->clear();
		return;
	}

	restoreExpand(expandState_->root(),node);

	expandState_->clear();
}

void TreeNodeView::restoreExpand(ExpandNode *expand,const VNode* node)
{
	//Lookup the mnode in the model
	QModelIndex nodeIdx=model_->nodeToIndex(node);
	if(nodeIdx != QModelIndex())
	{
		setExpanded(nodeIdx,true);
	}
	else
	{
		return;
	}

	for(int i=0; i < expand->children_.size(); i++)
	{
		ExpandNode *chExpand=expand->children_.at(i);
		std::string name=chExpand->name_;

		if(VNode *chNode=node->findChild(name))
		{
			QModelIndex chIdx=model_->nodeToIndex(chNode);
			if(chIdx != QModelIndex())
			{
				//setExpanded(chIdx,true);
				restoreExpand(chExpand,chNode);
			}
		}
	}
}
