// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: L. Orsini, A. Petrucci					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
#include <fstream>
#include "ferolReceiver/FEROLReceiver.h"
#include "interface/shared/i2ogevb2g.h"
#include "i2o/Method.h"
#include "i2o/i2o.h"
#include "pt/frl/Method.h"

XDAQ_INSTANTIATOR_IMPL(ferolReceiver::FEROLReceiver)

ferolReceiver::FEROLReceiver::FEROLReceiver(xdaq::ApplicationStub* c)
	throw(xdaq::exception::Exception)
	: xdaq::Application(c), mutex_(toolbox::BSem::FULL)
{
  //I2O Super fragment
  i2o::bind(this,&ferolReceiver::FEROLReceiver::dataFragmentCallback,I2O_SUPER_FRAGMENT_READY,XDAQ_ORGANIZATION_ID);
  
  //I2O Data
  pt::frl::bind(this, &ferolReceiver::FEROLReceiver::rawDataAvailable);
}
		
void ferolReceiver::FEROLReceiver::rawDataAvailable (toolbox::mem::Reference* ref, int originator, tcpla::MemoryCache* cache)
{

  PI2O_DATA_READY_MESSAGE_FRAME frame = (PI2O_DATA_READY_MESSAGE_FRAME) ref->getDataLocation();

  LOG4CPLUS_INFO(this->getApplicationLogger(),"Saving Event: fedid: "<<frame->fedid<<"  triggNumber:"<<frame->triggerno); 

  unsigned char* Data = (unsigned char*) ref->getBuffer()->getAddress() + sizeof(I2O_DATA_READY_MESSAGE_FRAME);
  int DataSize = frame->totalLength;
  
  std::ofstream ofs;

  std::string ofileName = "/nfshome0/zmao/data2.txt";

  std::ifstream oFileExist(ofileName.c_str()); //Check if Output file exists
  if(oFileExist.good()){// If file exist, append
    oFileExist.close();
    ofs.open(ofileName.c_str(), std::ios::out | std::ios::app);
  }
  else{// If file doesn't exist, create new
    oFileExist.close();
    ofs.open(ofileName.c_str(), std::ofstream::out); 
  }
  
  ofs.write((char*)Data, DataSize);
  ofs.close();

  LOG4CPLUS_INFO(this->getApplicationLogger(),"Saving Complete");


  cache->grantFrame(ref);
}


void ferolReceiver::FEROLReceiver::dataFragmentCallback(toolbox::mem::Reference * ref)  throw (i2o::exception::Exception)
{
	// protect against multithreaded callback
	mutex_.take();
	
	PI2O_SUPER_FRAGMENT_READY_MESSAGE_FRAME frame = (PI2O_SUPER_FRAGMENT_READY_MESSAGE_FRAME) ref->getDataLocation();
	std::cout<<"fedid: "<<frame->fedid<<"    triggNumber:"<<frame->triggerno<<std::endl;
	//void * ferolDataPtr = (char*)(ref->getDataLocation()) + sizeof(I2O_SUPER_FRAGMENT_READY_MESSAGE_FRAME);

	LOG4CPLUS_DEBUG (getApplicationLogger(), "received message number ");
    
	ref->release();
	
	mutex_.give();

}
