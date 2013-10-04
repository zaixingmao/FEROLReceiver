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

#ifndef _FEROLReceiver_h_
#define _FEROLReceiver_h_

#include "toolbox/mem/Reference.h"
#include "toolbox/BSem.h"
#include "xdaq/Application.h"
#include "xdata/Event.h"
#include "xdata/String.h"
#include "xdata/Integer.h"
#include "xdata/ActionListener.h"
#include "i2o/Method.h"
#include "tcpla/MemoryCache.h"
#include <fstream>

namespace ferolReceiver {
class FEROLReceiver: public xdaq::Application, xdata::ActionListener
{	
	public:
		XDAQ_INSTANTIATOR();

		FEROLReceiver(xdaq::ApplicationStub* c) throw(xdaq::exception::Exception);
		
		// Interface function invoked for the I2O token message
		// that is received from the FEROL
        // I2O Super fragment
        void dataFragmentCallback(toolbox::mem::Reference * ref)  throw  (i2o::exception::Exception);
	    // I2O Data
        void rawDataAvailable (toolbox::mem::Reference* ref, int originator, tcpla::MemoryCache* cache);
        //Pick up parameters from xml file
        void actionPerformed(xdata::Event& e); 

	protected:
	
		toolbox::BSem mutex_;
        std::ofstream ofs;
        xdata::String OutputFileName_;
        xdata::UnsignedInteger PreScale_;
};
}
#endif
