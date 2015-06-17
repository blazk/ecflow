//============================================================================
// Copyright 2015 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#ifndef PROPERTYLINE_INC_
#define PROPERTYLINE_INC_

#include <string>

#include <QObject>
#include <QVariant>

class  QCheckBox;
class  QLabel;
class  QLineEdit;
class  QSpinBox;
class  QToolButton;
class  QWidget;

class PropertyLine;
class VProperty;

//-------------------------------------
// Factory
//------------------------------------

class PropertyLineFactory
{
public:
	PropertyLineFactory(const std::string&);
	virtual ~PropertyLineFactory();

	virtual PropertyLine* make(VProperty* p,QWidget* w) = 0;
	static PropertyLine* create(VProperty* p,QWidget* w);

private:
	PropertyLineFactory(const PropertyLineFactory&);
	PropertyLineFactory& operator=(const PropertyLineFactory&);

};

template<class T>
class PropertyLineMaker : public PropertyLineFactory
{
	PropertyLine* make(VProperty* p,QWidget* w) { return new T(p,w); }
public:
	PropertyLineMaker(const std::string& name) : PropertyLineFactory(name) {}
};


//-------------------------------------
// Abstract property line editor
//------------------------------------

class PropertyLine: public QObject
{
public:
	PropertyLine(VProperty*,bool addLabel,QWidget* parent=0);
	virtual ~PropertyLine() {}

	QLabel* label() {return label_;};
	virtual QWidget* item()=0;
	virtual QWidget* button()=0;

	virtual void reset(QVariant)=0;

protected:
	VProperty* prop_;
	QVariant val_;
	QLabel* label_;
};


//-------------------------------------
// String editor
//------------------------------------

class StringPropertyLine : public PropertyLine
{
public:
	StringPropertyLine(VProperty* vProp,QWidget * parent=0);
	QWidget* item();
	QWidget* button();
	void reset(QVariant);

private:
	QLineEdit* le_;
};

//-------------------------------------
// Colour editor
//------------------------------------

class ColourPropertyLine : public PropertyLine
{
Q_OBJECT

public:
	ColourPropertyLine(VProperty* vProp,QWidget * parent=0);
	QWidget* item();
	QWidget* button();
	void reset(QVariant);

private Q_SLOTS:
	void slotEdit(bool);

private:
	QToolButton* cb_;
};

//-------------------------------------
// Font editor
//------------------------------------

class FontPropertyLine : public PropertyLine
{
Q_OBJECT

public:
	FontPropertyLine(VProperty* vProp,QWidget * parent=0);
	QWidget* item();
	QWidget* button();
	void reset(QVariant);

private Q_SLOTS:
	void slotEdit(bool);

private:
	QLabel* lName_;
	QToolButton *tbEdit_;
};

//-------------------------------------
// Int editor
//------------------------------------

class IntPropertyLine : public PropertyLine
{
public:
	IntPropertyLine(VProperty* vProp,QWidget * parent=0);
	QWidget* item();
	QWidget* button();
	void reset(QVariant);

private:
	QSpinBox* spin_;
};

//-------------------------------------
// Boolean editor
//------------------------------------

class BoolPropertyLine : public PropertyLine
{
public:
	BoolPropertyLine(VProperty* vProp,QWidget * parent=0);
	QWidget* item();
	QWidget* button();
	void reset(QVariant);

private:
	QCheckBox* cb_;
};


#endif

