/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */


#ifndef __embObjDevPrivData_h__
#define __embObjDevPrivData_h__





namespace yarp {
    namespace dev {
        class embObjDevPrivData;
    }
}

class yarp::dev::embObjDevPrivData
{
public:
    eth::TheEthManager* ethManager;
    eth::AbstractEthResource* res;
    struct behFlags
    {
        bool opened;
        bool verbosewhenok;
    }behFlags;
    
    embObjDevPrivData();
    ~embObjDevPrivData();
    
    inline  eth::AbstractEthResource* getEthRes()
    {return res;}
    
    inline  eth::TheEthManager* getEthManager()
    {return ethManager;}
    
    inline bool isOpen() {return behFlags.opened;}
    inline bool isVerbose() {return behFlags.verbosewhenok;}
    
    std::string getBoardInfo(void) const; //This function need to be const
};

yarp::dev::embObjDevPrivData::embObjDevPrivData()
{
    ethManager = nullptr;
    res = nullptr;
    behFlags.opened = false;
    ConstString tmp = NetworkBase::getEnvironment("ETH_VERBOSEWHENOK");
    if (tmp != "")
    {
        behFlags.verbosewhenok = (bool)NetType::toInt(tmp);
    }
    else
    {
        behFlags.verbosewhenok = false;
    }
    
}
yarp::dev::embObjDevPrivData::~embObjDevPrivData()
{;}

std::string yarp::dev::embObjDevPrivData::getBoardInfo(void) const
{
    if(nullptr == res)
    {
        return " BOARD name_unknown (IP unknown) ";
    }
    else
    {
        return ("BOARD " + res->getProperties().boardnameString +  " (IP "  + res->getProperties().ipv4addrString + ") ");
    }
}

#endif //__embObjDevPrivData_h__
