#include "CSVBusSystem.h"
#include "BusSystem.h"
#include "DSVReader.h"
#include <memory>
#include <string>
#include <cstddef>

struct CCSVBusSystem::SImplementation{

    struct ToSaveStop:CBusSystem::SStop{

        CBusSystem::TStopID saved_stopid;
        CStreetMap::TNodeID saved_nodeid;

        CBusSystem::TStopID ID() const noexcept override{
            return saved_stopid;
        }

        CStreetMap::TNodeID NodeID() const noexcept override{
            //return NodeID();
            return saved_nodeid;
        }


    };

    struct ToSaveRoute : CBusSystem::SRoute {


        std::string route_name;
        std::vector<CBusSystem::TStopID> route_stopid;

        std::string Name() const noexcept {
            return route_name;
        }

        // Returns the number of stops on the route 
        std::size_t StopCount() const noexcept {
            return route_stopid.size();
        }

        // Returns the stop id specified by the index, returns InvalidStopID if index is greater than or equal to StopCount() 
        TStopID GetStopID(std::size_t index) const noexcept {
            return route_stopid[index];
        }


    };

    std::vector<ToSaveStop> all_stops;
    std::vector<ToSaveRoute> all_routes;
    
};

// CCSVBusSystem member functions 
// Constructor for the CSV Bus System 
CCSVBusSystem::CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc)
{

    // std::vector<ToSaveStop> all_stops;
    // std::vector<ToSaveRoute> all_routes;

    DImplementation 


}

//Done with null
// Destructor for the CSV Bus System 
CCSVBusSystem::~CCSVBusSystem() = default;

//Done with null
// Returns the number of stops in the system 
std::size_t CCSVBusSystem::StopCount() const noexcept {
    return DImplementation -> all_stops.size();
}

//Done with null
// Returns the number of routes in the system 
std::size_t CCSVBusSystem::RouteCount() const noexcept {
    return DImplementation -> all_routes.size();
}


// Returns the SStop specified by the index, nullptr is returned if index is
// greater than equal to StopCount()
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    if (index < DImplementation -> all_stops.size()) {
        return DImplementation -> all_stops[index];
    }
    return nullptr;
}


// Returns the SStop specified by the stop id, nullptr is returned if id is
// not in the stops
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    for (const auto& stop : DImplementation -> all_stops) {
        if (all_stops -> ID() == id) {
            return all_stops;
        }
    }
    return nullptr;
}


//! Duplicated, same function

// Returns the SRoute specified by the index, nullptr is returned if index is
// greater than equal to RouteCount()

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    if (index < DImplementation -> all_routes.size()) {
        return DImplementation -> all_routes[index];
    }
    return nullptr;
}







// Returns the SRoute specified by the name, nullptr is returned if name is
// not in the routes

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept {
    for (const auto& route : DImplementation -> all_routes) {
        if (all_routes -> Name() == name) {
            return all_routes;
        }
    }
    return nullptr;
}






// // Bus System Stop member functions 
// // Returns the stop id of the stop 
// TStopID SStopImpl::ID() const noexcept {
//     return TStopID();
// }

// // Returns the node id of the bus stop 
// CStreetMap::TNodeID SStopImpl::NodeID() const noexcept {
//     return CStreetMap::TNodeID();
// }

// // Bus System Route member functions 
// // Returns the name of the route 
// std::string SRouteImpl::Name() const noexcept {
//     return "";
// }

// // Returns the number of stops on the route 
// std::size_t SRouteImpl::StopCount() const noexcept {
//     return 0;
// }

// // Returns the stop id specified by the index, returns InvalidStopID if index is greater than or equal to StopCount() 
// TStopID SRouteImpl::GetStopID(std::size_t index) const noexcept {
//     return TStopID();
// }
