//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#ifndef VNODE_HPP_
#define VNODE_HPP_

#include <vector>

#include <QColor>
#include <QStringList>

#include "Aspect.hpp"

class Node;
class ServerHandler;
class VAttribute;
class VNodeRoot;

//Describes the major changes during an update
class VNodeChange
{
public:
	VNodeChange() : cachedAttrNum_(-1), attrNum_(-1), cachedNodeNum_(-1),
					nodeNum_(-1), nodeAddedAt_(-1) {}
	int cachedAttrNum_;
	int attrNum_;
	int cachedNodeNum_;
	int nodeNum_;
	int nodeAddedAt_;
};


class VNode
{
friend class VNodeRoot;

public:
	VNode(VNode* parent,Node*);
	virtual ~VNode() {};

    Node *node() {return node_;}
    bool isTopLevel() const;

    void beginUpdateAttrNum();
    void endUpdateAttrNum();
    short cachedAttrNum() const;
    short attrNum() const;

    QStringList getAttributeData(int,VAttribute**);

    VNode* parent() const {return parent_;}
    int numOfChildren() const { return static_cast<int>(children_.size());}
    VNode* childAt(int index) const;
    int indexOfChild(const VNode* vn) const;
    int indexOfChild(Node* n) const;

    std::string genVariable(const std::string& key) const;

    virtual std::string absNodePath() const;
    QString name() const;
    QString stateName();
    QString defaultStateName();
    bool isSuspended() const;
    QColor  stateColour() const;

protected:
    void replaceChildren(const std::vector<VNode*>& newCh);
    void addChild(VNode*);

    Node* node_;
    VNode* parent_;
    std::vector<VNode*> children_;
    mutable short attrNum_;
    mutable short cachedAttrNum_;
};

class VNodeRoot : public VNode
{
public:
	VNodeRoot(ServerHandler*);
	~VNodeRoot();

	std::string absNodePath() const;
	int totalNum() const {return totalNum_;}
	VNode* find(const Node* nc) const;
	void beginUpdate(VNode* node,const std::vector<ecf::Aspect::Type>& aspect,VNodeChange&);
	void endUpdate(VNode* node,const std::vector<ecf::Aspect::Type>& aspect);

protected:
    void scan(VNode*);
    void deleteNode(VNode* node);

    int totalNum_;
};


#endif