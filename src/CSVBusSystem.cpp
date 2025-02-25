#include "CSVBusSystem.h"
#include "BusSystem.h"
#include "DSVReader.h"
#include <memory>
#include <string>
#include <cstddef>

#include <vector>
#include <algorithm>

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
            if (index < route_stopid.size()){
                return route_stopid[index];
            }

            return CBusSystem::InvalidStopID;
            
        }


    };

    std::vector<ToSaveStop> all_stops;
    std::vector<ToSaveRoute> all_routes;
    
    
};


// namespace{
//     void ReadStops(CCSVBusSystem* new_CSVBusSystem, std::shared_ptr<CDSVReader> stopsrc){
//         while(!stopsrc -> End()){
//             std::vector<std::string> reading_row;

//             if(stopsrc-> ReadRow(reading_row)){
//                 if(reading_row.size() >=2){
//                     auto current_stop= std::make_shared<CCSVBusSystem::SImplementation::ToSaveStop>();


//                     current_stop->saved_stopid = reading_row[0];
//                     current_stop->saved_nodeid = reading_row[1];

//                     new_CSVBusSystem->DImplementation->all_stops.push_back(*current_stop);

//                 }
//             }
//         }
//     }


//     void ReadRoutes(CCSVBusSystem* new_CSVBusSystem, std::shared_ptr<CDSVReader> routesrc){
//         bool is_firstrow = true;

//         while (!routesrc->End()){
//             std::vector<std::string> reading_row;
            

//             if(is_firstrow){
//                 if(!isdigit(reading_row[0][0])){
//                     is_firstrow = false;

//                     continue;
//                 }


//             }

//             is_firstrow = false;

//             std::string current_route_name = reading_row[0];


//             bool sameroute_exist = false;

//             for(std::size_t i = 0; i < new_CSVBusSystem->DImplementation->all_routes.size(); i++){
//                 if (new_CSVBusSystem->DImplementation->all_routes[i].route_name == current_route_name){

//                     for (std::size_t j = 1; j < reading_row.size(); j++){
//                         std::vector <std::string>& stop_list = new_CSVBusSystem->DImplementation->all_routes[i].route_stopid;


//                         std::string new_stopid = reading_row[j];
//                         stop_list.push_back(new_stopid);
//                     }

//                     sameroute_exist = true;

//                     break;
//                 }
//             }


//             if(!sameroute_exist){
//                 CCSVBusSystem::SImplementation::ToSaveRoute create_newroute;

//                 create_newroute.route_name = current_route_name;

//                 for (std::size_t j = 1; j< reading_row.size();j++){
//                     create_newroute.route_stopid.push_back(reading_row[j]);

//                 }

//                 new_CSVBusSystem->DImplementation->all_routes.push_back(create_newroute);
//             }




//         }

//     }
// }

// CCSVBusSystem member functions 
// Constructor for the CSV Bus System 
CCSVBusSystem::CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc)
{

    // std::vector<ToSaveStop> all_stops;
    // std::vector<ToSaveRoute> all_routes;

    DImplementation = std::make_unique<SImplementation>();

    // ReadStops(this, stopsrc);
    // ReadRoutes(this, routesrc);


        while(!stopsrc -> End()){
            std::vector<std::string> reading_row;

            if(stopsrc-> ReadRow(reading_row)){
                if(reading_row.size() >=2){
                    auto current_stop= std::make_shared<CCSVBusSystem::SImplementation::ToSaveStop>();


                    // added after stoull ERROR
                    try{

                    current_stop->saved_stopid = std::stoull(reading_row[0]);
                    current_stop->saved_nodeid = std::stoull(reading_row[1]);

                    DImplementation->all_stops.push_back(*current_stop);
                    }
                    catch(...){
                        continue;
                    }

                }
            }
        }
    


        bool is_firstrow = true;

        while(!routesrc->End()){
            std::vector<std::string> reading_row;
            
            // added after stoull ERROR
            if(!routesrc->ReadRow(reading_row) || reading_row.empty()){
                continue;
            }

            if(is_firstrow){
                if(!isdigit(reading_row[0][0])){
                    is_firstrow = false;

                    continue;
                }
                
                is_firstrow = false;
            }

            //is_firstrow = false;

            // added after stoull ERROR
            if(reading_row.empty()){
                continue;
            }

            std::string current_route_name = reading_row[0];


            bool sameroute_exist = false;

            for(std::size_t i = 0; i < DImplementation->all_routes.size(); i++){
                if (DImplementation->all_routes[i].route_name == current_route_name){

                    for (std::size_t j = 1; j < reading_row.size(); j++){
                        //std::vector <std::string>& stop_list = DImplementation->all_routes[i].route_stopid;
                        std::vector <CBusSystem::TStopID>& stop_list = DImplementation->all_routes[i].route_stopid;

                        //std::string new_stopid = reading_row[j];

                        CBusSystem::TStopID new_stopid = std::stoull(reading_row[j]);
                        stop_list.push_back(new_stopid);
                    }

                    sameroute_exist = true;

                    break;
                }
            }


            if(!sameroute_exist){
                CCSVBusSystem::SImplementation::ToSaveRoute create_newroute;

                create_newroute.route_name = current_route_name;

                for (std::size_t j = 1; j< reading_row.size();j++){

                    CBusSystem::TStopID new_stopid = std::stoull(reading_row[j]);
                    create_newroute.route_stopid.push_back(new_stopid);

                }

                DImplementation->all_routes.push_back(create_newroute);
            }




        }

    


    // //read stops

    // while(!stopsrc -> End()){
    //     std::vector<std::string> reading_row;

    //     if(stopsrc-> ReadRow(reading_row)){
    //         if(reading_row.size() >=2){
    //             auto current_stop= std::make_shared<SImplementation::ToSaveStop>();


    //             current_stop->saved_stopid = row[0];
    //             current_stop->saved_nodeid = row[1];

    //             DImplementation->all_stops.push_back(stop);

    //         }
    //     }
    // }


    //read routes

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
        return std::make_shared<SImplementation::ToSaveStop>(DImplementation -> all_stops[index]);
    }
    return nullptr;
}


// Returns the SStop specified by the stop id, nullptr is returned if id is
// not in the stops
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    for (const auto& StopByID_all_stops  : DImplementation -> all_stops) {
        if (StopByID_all_stops.ID() == id) {
            return std::make_shared<SImplementation::ToSaveStop>(StopByID_all_stops);
        }
    }
    return nullptr;
}


//! Duplicated, same function

// Returns the SRoute specified by the index, nullptr is returned if index is
// greater than equal to RouteCount()

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    if (index < DImplementation -> all_routes.size()) {
        return std::make_shared<SImplementation::ToSaveRoute>(DImplementation -> all_routes[index]);
    }
    return nullptr;
}







// Returns the SRoute specified by the name, nullptr is returned if name is
// not in the routes

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept {
    for (const auto& RouteByName_all_routes : DImplementation -> all_routes) {
        // if (all_routes -> Name() == name) {
        //     return all_routes;
        // }

        if (RouteByName_all_routes.route_name == name) {
            return std::make_shared<SImplementation::ToSaveRoute>(RouteByName_all_routes);
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
