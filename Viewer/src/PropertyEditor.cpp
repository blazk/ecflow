//============================================================================
// Copyright 2015 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//
//============================================================================

#include "PropertyEditor.hpp"

#include <QDebug>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QToolButton>

#include "ChangeNotifyEditor.hpp"
#include "IconProvider.hpp"
#include "PropertyLine.hpp"
#include "VConfig.hpp"
#include "VProperty.hpp"

PropertyEditor::PropertyEditor(QWidget* parent) : QWidget(parent), 
    group_(0),
    currentGrid_(0)
{
    setupUi(this);

    headerWidget_->setProperty("editorHeader","1");
    scArea_->setProperty("editor","1");
    scAreaContents_->setProperty("editorArea","1");

    pixLabel_->clear();
}

PropertyEditor::~PropertyEditor()
{
}

void PropertyEditor::edit(VProperty * vGroup,QPixmap pix)
{
	 clear();

	 group_=vGroup;

	 QString txt=group_->param("desc");
	 headerLabel_->setText(txt);

	 pixLabel_->setPixmap(pix);

	 build();
}

void PropertyEditor::edit(VProperty * vGroup,QString serverName)
{
	 clear();

	 group_=vGroup;

	 headerWidget_->hide();

	 serverName_=serverName;

	 build();
}

void PropertyEditor::clear()
{
	lineItems_.clear();

	QLayoutItem* item;
	while((item=vBox_->takeAt(0))!= 0)
	{
		if(QWidget *w=item->widget())
		{
			vBox_->removeWidget(w);
		    delete w;
		}

		delete item;
	}
}


//Build the property tree from the the definitions
void PropertyEditor::build()
{
	if(!group_)
		return;

	//Loop over the children of the group
    Q_FOREACH(VProperty* vProp,group_->children())
    {
        addItem(vProp,vBox_);

    }

    addHelpers();
}

void PropertyEditor::addHelpers()
{
	QMap<std::string,PropertyLine*> lineMap;
	Q_FOREACH(PropertyLine* line,lineItems_)
	{
		lineMap[line->property()->path()]=line;
	}

	Q_FOREACH(PropertyLine* line,lineItems_)
	{
		QString h=line->property()->param("helpers");
		if(!h.isEmpty())
		{
			Q_FOREACH(QString s,h.split("/"))
			{
				if(PropertyLine* hl=lineMap.value(s.toStdString(),NULL))
				{
					line->addHelper(hl);
				}
			}
		}
	}
}


void PropertyEditor::addItem(VProperty* vProp,QVBoxLayout *layout)
{
    if(vProp->name() == "line")
    {
    	if (!currentGrid_)
        {
            currentGrid_=new QGridLayout();
            layout->addLayout(currentGrid_);
        }    
        addLine(vProp,currentGrid_);
    }     
       
    else if(vProp->name() == "group")
    {
		currentGrid_=0;
        addGroup(vProp,layout);
    }
    else if(vProp->name() == "grid")
    {
        currentGrid_=0;
        addGrid(vProp,layout);
    }
    else if(vProp->name() == "custom-notification")
    {
        currentGrid_=0;
        addNotification(vProp,layout);
    }
    else if(vProp->name() == "note")
    {
        if(currentGrid_)
        {
        	addNote(vProp,currentGrid_);
        }
        else
        {
        	addNote(vProp,layout);
        }
    }
    else if(vProp->name() == "tabs")
    {
        currentGrid_=0;
        addTabs(vProp,layout);
    }     

}

PropertyLine* PropertyEditor::addLine(VProperty *vProp,QGridLayout *gridLayout)
{
	PropertyLine* item = PropertyLineFactory::create(vProp->link(),true,this);

    if(item)
    {
    	item->init();
    	//item->reset(vProp->link()->value());

        int row=gridLayout->rowCount();

        QLabel* lw=item->label();
        QLabel* slw=item->suffixLabel();

        if(lw)
        {
        	gridLayout->addWidget(lw,row,0,Qt::AlignLeft);

            if(slw)
            {
            	QHBoxLayout* hb=new QHBoxLayout;
                hb->addWidget(item->item());
                hb->addWidget(slw);
                gridLayout->addLayout(hb,row,1,Qt::AlignLeft);
            }
            else
            {
                gridLayout->addWidget(item->item(),row,1,Qt::AlignLeft);
            }
        }
        else
        {
        	gridLayout->addWidget(item->item(),row,0,1,2,Qt::AlignLeft);
        }

        QWidget *bw=item->button();
        if(bw)
            gridLayout->addWidget(bw,row,2);


        QToolButton* defTb=item->defaultTb();
        if(defTb)
        {
           gridLayout->addWidget(defTb,row,3);
        }

        QToolButton* masterTb=item->masterTb();
        if(masterTb)
        {
           gridLayout->addWidget(masterTb,row,4);
        }

       connect(item,SIGNAL(changed()),
    		   this,SIGNAL(changed()));

       lineItems_ << item;
    }

    return item;
}    

void PropertyEditor::addGroup(VProperty* vProp,QVBoxLayout * layout)
{
   if(vProp->name() != "group")
      return;
   
        QGroupBox *groupBox = new QGroupBox(vProp->param("title"));
        groupBox->setObjectName("editorGroupBox");
        QGridLayout *grid=new QGridLayout();
        grid->setColumnStretch(1,1);
        //grid->setColumnStretch(2,1);
        //grid->setColumnStretch(3,1);

        groupBox->setLayout(grid);
        //gridLayout=grid;

        //add it to the main layout
        //nt row=grid_->rowCount();
        //grid_->addWidget(groupBox,row,0,2,4);
        layout->addWidget(groupBox);
        
        currentGrid_=grid;
        //Loop over the children of the group
        Q_FOREACH(VProperty* chProp,vProp->children())
        {
            //Add each item to the the editor
            addItem(chProp,layout);
        }
        currentGrid_=0;
}

void PropertyEditor::addGrid(VProperty* vProp,QVBoxLayout *layout)
{
    if(vProp->name() != "grid")
        return;
        
    QGroupBox *groupBox = new QGroupBox(vProp->param("title"));
    groupBox->setObjectName("editorGroupBox");
    QGridLayout* grid=new QGridLayout();
    groupBox->setLayout(grid);
        
        //add it to the main layout
        //int row=grid_->rowCount();
        //grid_->addLayout(grid,row,0,2,4);
    
    layout->addWidget(groupBox);
        
    //Add header
    for(int i=1; i < 10; i++)
    {    
         QString h=vProp->param("h" + QString::number(i));

         if(h.isEmpty())
         {
             grid->setColumnStretch(i+1,1);
             break;
         }
         
         h+="   ";
         QLabel* hLabel=new QLabel(h);
         grid->addWidget(hLabel,0,i,Qt::AlignHCenter);
    }    

     //Add rows
     Q_FOREACH(VProperty* chProp,vProp->children())
     {
         addGridRow(chProp,grid);
     }
}    


void PropertyEditor::addGridRow(VProperty* vProp,QGridLayout *grid)
{
    if(vProp->name() != "row")
    {
    	if(vProp->name() == "note")
    	{
    		 QLabel *empty=new QLabel(" ");
    		 grid->addWidget(empty,grid->rowCount(),0,1,-1,Qt::AlignVCenter);
    		 QLabel *label=new QLabel("&nbsp;&nbsp;&nbsp;<b>Note:</b> " + vProp->value().toString());
    		 grid->addWidget(label,grid->rowCount(),0,1,-1,Qt::AlignVCenter);
    	}
    	return;
    }

    int row=grid->rowCount();
    QString labelText=vProp->param("label");
    QLabel* label=new QLabel(labelText);
    grid->addWidget(label,row,0);

    int col=1;
    Q_FOREACH(VProperty* chProp,vProp->children())
    {
        if(chProp->name() == "line")
        {
            PropertyLine* item = PropertyLineFactory::create(chProp->link(),false,this);

            if(item)
            {
                item->init();
            	//item->reset(chProp->link()->value());

            //QLabel* lw=item->label();
            //QLabel* slw=item->suffixLabel();

                //gridLayout->addWidget(item->item(),row,col,Qt::AlignLeft);

            /*QWidget *bw=item->button();
            if(bw)
                gridLayout->addWidget(bw,row,2);*/


            QToolButton* defTb=item->defaultTb();
            QToolButton* masterTb=item->masterTb();
            if(defTb || masterTb)
            {
                QHBoxLayout *hb=new QHBoxLayout();
                hb->addWidget(item->item());
                if(defTb)
                	hb->addWidget(defTb);
                if(masterTb)
                	hb->addWidget(masterTb);

                hb->addSpacing(15);
                hb->addStretch(1);
                grid->addLayout(hb,row,col);
            }
            else
            {
                 grid->addWidget(item->item(),row,col,Qt::AlignLeft);
            }    

            connect(item,SIGNAL(changed()),
               		   this,SIGNAL(changed()));
                lineItems_ << item;
                col++;
            }
        }    
    }


}

void PropertyEditor::addNotification(VProperty* vProp,QVBoxLayout* layout)
{
    if(vProp->name() != "custom-notification")
        return;

    ChangeNotifyEditor* ne=new ChangeNotifyEditor(this);

    bool useGroup=(vProp->param("group") == "true");

    if(useGroup)
    {
    	QString labelText=vProp->param("title");
    	QGroupBox *groupBox = new QGroupBox(labelText);
    	groupBox->setObjectName("editorGroupBox");
    	QVBoxLayout* vb=new QVBoxLayout();
    	groupBox->setLayout(vb);
    	vb->addWidget(ne);
    	layout->addWidget(groupBox);

    }
    else
    {
    	layout->addWidget(ne);
    }

    //Add rows
    Q_FOREACH(VProperty* chProp,vProp->children())
    {
    	if(chProp->name() == "row")
    	{
    		QString labelText=chProp->param("label");

    		QList<PropertyLine*> lineLst;

    		QWidget* w=new QWidget(this);
    		QVBoxLayout* vb=new QVBoxLayout(w);
    		vb->setContentsMargins(0,4,0,4);

            currentGrid_=0;
            
            int lineLstPos=lineItems_.count();
    		Q_FOREACH(VProperty* lineProp,chProp->children())
    	    {
    	        addItem(lineProp,vb);
    	    }
    	    for(int i=lineLstPos; i < lineItems_.count(); i++)
                lineLst << lineItems_[i];
    	    
    		ne->addRow(labelText,lineLst,w);
    	 }
     }
}

void PropertyEditor::addTabs(VProperty* vProp,QVBoxLayout *layout)
{
    if(vProp->name() != "tabs")
        return;
    
    QTabWidget *t=new QTabWidget(this);
    layout->addWidget(t);
   
    int col=1;
    Q_FOREACH(VProperty* chProp,vProp->children())
    {
        if(chProp->name() == "tab")
        {
            addTab(chProp,t);
        }    
    }
} 

void PropertyEditor::addTab(VProperty* vProp,QTabWidget* tab)
{
    if(vProp->name() != "tab")
        return;

    QWidget *w=new QWidget(this);
    QVBoxLayout* vb=new QVBoxLayout();
    w->setLayout(vb);
    
    tab->addTab(w,vProp->param("label"));
    
    Q_FOREACH(VProperty* chProp,vProp->children())
    {
        addItem(chProp,vb);
    }

    vb->addStretch(1);
}    

void PropertyEditor::addNote(VProperty* vProp,QVBoxLayout* layout)
{
    if(vProp->name() != "note")
        return;

    QString txt=vProp->value().toString();
    txt.replace("%SERVER%",(serverName_.isEmpty())?"?":"<b>" + serverName_ + "</b>");

    layout->addSpacing(5);
    QLabel *label=new QLabel("<b>Note:</b> " + txt);
    label->setWordWrap(true);
    layout->addWidget(label);
}

void PropertyEditor::addNote(VProperty* vProp,QGridLayout* layout)
{
    if(vProp->name() != "note")
        return;

    QString txt=vProp->value().toString();
    txt.replace("%SERVER%",(serverName_.isEmpty())?"?":"<b>" + serverName_ + "</b>");


    QLabel *empty=new QLabel(" ");
    layout->addWidget(empty,layout->rowCount(),0,1,-1,Qt::AlignVCenter);
   	QLabel *label=new QLabel("&nbsp;&nbsp;&nbsp;<b>Note:</b> " + txt);
    layout->addWidget(label,layout->rowCount(),0,1,-1,Qt::AlignVCenter);
}


bool PropertyEditor::applyChange()
{
    bool changed=false;
	//Loop over the top level properties (groups) in the browser
    Q_FOREACH(PropertyLine* item, lineItems_)
    {
        //Sync the changes to VConfig
    	if(item->applyChange())
    	{
    		changed=true;
    	}
    }

    return changed;
}

