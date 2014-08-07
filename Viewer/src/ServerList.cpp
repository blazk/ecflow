//============================================================================
// Copyright 2014 ECMWF.
// This software is licensed under the terms of the Apache Licence version 2.0
// which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
// In applying this licence, ECMWF does not waive the privileges and immunities
// granted to it by virtue of its status as an intergovernmental organisation
// nor does it submit to any jurisdiction.
//============================================================================

#include "ServerList.hpp"

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "ServerItem.hpp"
#include "ViewConfig.hpp"
#include "DirectoryHandler.hpp"

ServerList* ServerList::instance_=0;

ServerList::ServerList()
{
	if(load() == false)
	{
		if(readRcFile() ==  false)
		{
			readSystemFile();
		}

		save();
	}
}

ServerList::~ServerList()
{
	save();
	for(std::vector<ServerItem*>::iterator it=items_.begin(); it != items_.end(); it++)
		delete *it;
}

ServerList* ServerList::Instance()
{
	if(!instance_)
		instance_=new ServerList();

	return instance_;
}


ServerItem* ServerList::item(int index)
{
	return (index >=0 && index < static_cast<int>(items_.size()))?items_.at(index):0;
}

ServerItem* ServerList::add(const std::string& name,const std::string& host,const std::string& port)
{
	ServerItem* item=new ServerItem(name,host,port);
	items_.push_back(item);
	return item;
}

ServerItem* ServerList::add(const std::string& name)
{
	//ServerItem_ptr res(new ServerItem(name));
	//		return res;

	ServerItem* item=new ServerItem(name);
	items_.push_back(item);
	return item;
}

void ServerList::add(ServerItem *item)
{
	items_.push_back(item->clone());
}

void ServerList::rescan()
{

}

void ServerList::update(const std::vector<ServerItem*>& items)
{
	for(std::vector<ServerItem*>::iterator it=items_.begin(); it != items_.end(); it++)
		delete *it;

	items_.clear();

	for(std::vector<ServerItem*>::const_iterator it=items.begin(); it != items.end(); it++)
		items_.push_back((*it)->clone());

	save();
}


bool ServerList::load()
{
	std::string path(DirectoryHandler::userConfigDir());
	path+="/servers.txt";

	std::ifstream in(path.c_str());
	if(!in.good())
		return false;

	std::string line;
	while(getline(in,line))
	{
		//We ignore comment lines
		std::string buf=boost::trim_left_copy(line);
		if(buf.size() > 1 && buf.at(0) == '#')
			continue;

		std::vector<std::string> sv;
		boost::split(sv,line,boost::is_any_of(","));

		if(sv.size() >= 3)
		{
						add(sv[0],sv[1],sv[2]);
		}
	}

	in.close();

	return true;
}

void ServerList::save()
{
	std::string path(DirectoryHandler::userConfigDir());
	path+="/servers.txt";

	std::ofstream out;
	out.open(path.c_str());
	if(!out.good())
		  	return;

	out << "#Name Host Port" << std::endl;

	for(std::vector<ServerItem*>::iterator it=items_.begin(); it != items_.end(); it++)
	{
		out << (*it)->name() << "," << (*it)->host() << "," <<  (*it)->port() << std::endl;
	}
	out.close();
}


bool ServerList::readRcFile()
{
	std::string path(DirectoryHandler::userRcDir());
	path+="/servers";

	std::ifstream in(path.c_str());

	if(in.good())
	{
		std::string line;
		while(getline(in,line))
		{
			std::string buf;
			std::stringstream ssdata(line);
			std::vector<std::string> vec;

			while(ssdata >> buf)
			{
				vec.push_back(buf);
			}

			if(vec.size() >= 3)
			{
					add(vec[0],vec[1],vec[2]);
			}
		}
	}
	else
		return false;

	in.close();

	return true;
}

bool ServerList::readSystemFile()
{
	return false;
}
