//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#include "NodeQueryResultModel.hpp"

#include "ModelColumn.hpp"
#include "NodeQueryResult.hpp"
#include "ServerHandler.hpp"
#include "VNode.hpp"

#include <QDebug>

NodeQueryResultModel::NodeQueryResultModel(QObject *parent) :
          QAbstractItemModel(parent),
          columns_(0)
{
	columns_=ModelColumn::def("query_columns");

	assert(columns_);

	data_=new NodeQueryResult(this);

	connect(data_,SIGNAL(beginAppendRow()),
			this,SLOT(slotBeginAppendRow()));

	connect(data_,SIGNAL(endAppendRow()),
			this,SLOT(slotEndAppendRow()));

	connect(data_,SIGNAL(beginAppendRows(int)),
			this,SLOT(slotBeginAppendRows(int)));

	connect(data_,SIGNAL(endAppendRows(int)),
			this,SLOT(slotEndAppendRows(int)));

	connect(data_,SIGNAL(beginRemoveRow(int)),
			this,SLOT(slotBeginRemoveRow(int)));

	connect(data_,SIGNAL(endRemoveRow(int)),
			this,SLOT(slotEndRemoveRow(int)));

	connect(data_,SIGNAL(beginRemoveRows(int,int)),
			this,SLOT(slotBeginRemoveRows(int,int)));

	connect(data_,SIGNAL(endRemoveRows(int,int)),
			this,SLOT(slotEndRemoveRows(int,int)));

	connect(data_,SIGNAL(beginReset()),
			this,SLOT(slotBeginReset()));

	connect(data_,SIGNAL(endReset()),
			this,SLOT(slotEndReset()));

	connect(data_,SIGNAL(stateChanged(const VNode*,int,int)),
			this,SLOT(slotStateChanged(const VNode*,int,int)));

}

NodeQueryResultModel::~NodeQueryResultModel()
{
}


void NodeQueryResultModel::clearData()
{
	data_->clear();
}

bool NodeQueryResultModel::hasData() const
{
	return data_->size() > 0;
}

int NodeQueryResultModel::columnCount( const QModelIndex& /*parent */) const
{
   	 return columns_->count();
}

int NodeQueryResultModel::rowCount( const QModelIndex& parent) const
{
	if(!hasData())
		return 0;

	//Parent is the root:
	if(!parent.isValid())
	{
		return data_->size();
	}

	return 0;
}

Qt::ItemFlags NodeQueryResultModel::flags ( const QModelIndex & index) const
{
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant NodeQueryResultModel::data( const QModelIndex& index, int role ) const
{
	if(!index.isValid() || !hasData() ||
	   (role != Qt::DisplayRole && role != Qt::BackgroundRole && role != Qt::TextAlignmentRole))
    {
		return QVariant();
	}

	int row=index.row();
	if(row < 0 || row >= data_->size())
		return QVariant();

	QString id=columns_->id(index.column());

	NodeQueryResultItem* d=data_->itemAt(row);

	if(role == Qt::DisplayRole)
	{
		if(id == "path")
			return d->pathStr();
		else if(id == "server")
			return d->serverStr();
		else if(id == "type")
			return d->typeStr();
		else if(id == "status")
			return d->stateStr();
		return QVariant();
	}
	else if(role == Qt::BackgroundRole)
	{
		if(id == "status")
			return d->stateColour();

		return QVariant();
	}
	else if(role == Qt::TextAlignmentRole)
	{
		if(id == "status" || id == "type")
			return Qt::AlignCenter;

		return QVariant();
	}

	return QVariant();
}

QVariant NodeQueryResultModel::headerData( const int section, const Qt::Orientation orient , const int role ) const
{
	if ( orient != Qt::Horizontal)
      		  return QAbstractItemModel::headerData( section, orient, role );

	QString id=columns_->id(section);

	if(role == Qt::DisplayRole)
		return columns_->label(section);
	else if(role == Qt::UserRole)
		return columns_->id(section);
	else if(role == Qt::ToolTipRole)
		return columns_->tooltip(section);
	else if(role == Qt::TextAlignmentRole)
	{
		if(id == "status" || id == "type")
			return Qt::AlignCenter;
	}

	return QVariant();
}

QModelIndex NodeQueryResultModel::index( int row, int column, const QModelIndex & parent ) const
{
	if(!hasData() || row < 0 || column < 0)
	{
		return QModelIndex();
	}

	//When parent is the root this index refers to a node or server
	if(!parent.isValid())
	{
		return createIndex(row,column);
	}

	return QModelIndex();

}

QModelIndex NodeQueryResultModel::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

VInfo_ptr NodeQueryResultModel::nodeInfo(const QModelIndex& index)
{
	//For invalid index no info is created.
	if(!index.isValid())
	{
		VInfo_ptr res;
		return res;
	}

	if(index.row() >=0 && index.row() <= data_->size())
	{
		NodeQueryResultItem* d=data_->itemAt(index.row());

		if(ServerHandler *s=d->server_)
		{
			if(d->node_)
			{
				if(d->node_->isServer())
				{
					return VInfoServer::create(s);
				}
				else
				{
					return VInfoNode::create(d->node_);
				}
			}
		}
	}

    VInfo_ptr res;
	return res;
}

QModelIndex NodeQueryResultModel::infoToIndex(VInfo_ptr info)
{
	/*if(info && info.get())
	{
		if(info->isServer())
		{
			if(ServerHandler *s=info->server())
			{
				return serverToIndex(s);
			}
		}
		else if(VNode* n=info->node())
		{
				return nodeToIndex(n);
		}
	}*/

	return QModelIndex();
}

void  NodeQueryResultModel::slotBeginAppendRow()
{
	int num=data_->size();
	Q_EMIT beginInsertRows(QModelIndex(),num,num);


	Q_EMIT endInsertRows();
}

void  NodeQueryResultModel::slotEndAppendRow()
{
	Q_EMIT endInsertRows();
}

void  NodeQueryResultModel::slotBeginAppendRows(int n)
{
	if(n <= 0)
		return;

	int num=data_->size();
	Q_EMIT beginInsertRows(QModelIndex(),num,num+n-1);
}

void  NodeQueryResultModel::slotEndAppendRows(int n)
{
	if(n <= 0)
		return;
	Q_EMIT endInsertRows();
}

void NodeQueryResultModel::slotBeginRemoveRow(int row)
{
	beginRemoveRows(QModelIndex(),row,row);
}

void NodeQueryResultModel::slotEndRemoveRow(int row)
{
	endRemoveRows();
}

void NodeQueryResultModel::slotBeginRemoveRows(int rowStart,int rowEnd)
{
	beginRemoveRows(QModelIndex(),rowStart,rowEnd);
}

void NodeQueryResultModel::slotEndRemoveRows(int,int)
{
	endRemoveRows();
}

void NodeQueryResultModel::slotBeginReset()
{
	beginResetModel();
}

void NodeQueryResultModel::slotEndReset()
{
	endResetModel();
}

void NodeQueryResultModel::slotStateChanged(const VNode*,int pos,int cnt)
{
	int col=columns_->indexOf("status");

	if(col != -1)
	{
		QModelIndex fromIdx=index(pos,col);
		QModelIndex toIdx=index(pos+cnt-1,col);

		Q_EMIT dataChanged(fromIdx,toIdx);
	}
}