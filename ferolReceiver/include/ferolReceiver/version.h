#ifndef _ferolReceiver_version_hh_
#define _ferolReceiver_version_hh_

#include "config/PackageInfo.h"

#define FEROLRECEIVER_VERSION_MAJOR 1
#define FEROLRECEIVER_VERSION_MINOR 0
#define FEROLRECEIVER_VERSION_PATCH 0
#undef FEROLRECEIVER_PREVIOUS_VERSIONS  

#define FEROLRECEIVER_VERSION_CODE PACKAGE_VERSION_CODE(FEROLRECEIVER_VERSION_MAJOR, FEROLRECEIVER_VERSION_MINOR, FEROLRECEIVER_VERSION_PATCH)
#ifndef FEROLRECEIVER_PREVIOUS_VERSIONS
#define FEROLRECEIVER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(FEROLRECEIVER_VERSION_MAJOR, FEROLRECEIVER_VERSION_MINOR, FEROLRECEIVER_VERSION_PATCH)
#else
#define FEROLRECEIVER_FULL_VERSION_LIST FEROLRECEIVER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(FEROLRECEIVER_VERSION_MAJOR, FEROLRECEIVER_VERSION_MINOR, FEROLRECEIVER_VERSION_PATCH)
#endif


namespace ferolReceiver
{
  const std::string package  =  "ferolReceiver";
  const std::string versions = FEROLRECEIVER_FULL_VERSION_LIST;
  const std::string summary = "FEROL receiver package";
  const std::string description = "Receives data via NIC from a FEROL or MOL";
  const std::string authors = "Adam Scherlis";
  const std::string link = "http://xdaq.web.cern.ch";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

