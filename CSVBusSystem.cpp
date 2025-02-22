#include "CSVBusSystem.h"
#include <memory>
#include <string>
#include <cstddef>

// CCSVBusSystem member functions 
// Constructor for the CSV Bus System 
CCSVBusSystem::CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc)
{
}

// Destructor for the CSV Bus System 
CCSVBusSystem::~CCSVBusSystem() {
}

// Returns the number of stops in the system 
std::size_t CCSVBusSystem::StopCount() const noexcept {
    return 0;
}

// Returns the number of routes in the system 
std::size_t CCSVBusSystem::RouteCount() const noexcept {
    return 0;
}

// Returns the SStop specified by the index, nullptr is returned if index is greater than equal to StopCount() 
std::shared_ptr<SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    return nullptr;
}

// Returns the SStop specified by the stop id, nullptr is returned if id is not in the stops 
std::shared_ptr<SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    return nullptr;
}

// Returns the SRoute specified by the index, nullptr is returned if index is greater than equal to RouteCount() 
std::shared_ptr<SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    return nullptr;
}

// Returns the SRoute specified by the name, nullptr is returned if name is not in the routes 
std::shared_ptr<SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept {
    return nullptr;
}

// Bus System Stop member functions 
// Returns the stop id of the stop 
TStopID SStopImpl::ID() const noexcept {
    return TStopID();
}

// Returns the node id of the bus stop 
CStreetMap::TNodeID SStopImpl::NodeID() const noexcept {
    return CStreetMap::TNodeID();
}

// Bus System Route member functions 
// Returns the name of the route 
std::string SRouteImpl::Name() const noexcept {
    return "";
}

// Returns the number of stops on the route 
std::size_t SRouteImpl::StopCount() const noexcept {
    return 0;
}

// Returns the stop id specified by the index, returns InvalidStopID if index is greater than or equal to StopCount() 
TStopID SRouteImpl::GetStopID(std::size_t index) const noexcept {
    return TStopID();
}
