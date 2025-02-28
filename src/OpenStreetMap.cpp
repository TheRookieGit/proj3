#include "OpenStreetMap.h"
#include <memory>
#include <string>
#include <vector>
#include <map>

struct COpenStreetMap::SImplementation {
    struct new_SNode : COpenStreetMap::SNode {
        TNodeID DID;
        TLocation DLocation;
        std::map<std::string, std::string> DAttributes; 
        std::vector<std::shared_ptr<SWay>> DWays;              
       
        // Constructor to initialize the node with an ID, location, and attributes
        new_SNode(TNodeID id, TLocation location, std::map<std::string, std::string> attributes)
            : DID(id), DLocation(location), DAttributes(std::move(attributes)) {}

        TNodeID ID() const noexcept override {
            return DID;
        }

        TLocation Location() const noexcept override {
            return DLocation;
        }

        std::size_t AttributeCount() const noexcept override {
            return DAttributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index >= DAttributes.size()) {
                return "";
            }
            auto it = DAttributes.begin();
            std::advance(it, index);
            return it->first;
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return DAttributes.find(key) != DAttributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = DAttributes.find(key);
            return (it != DAttributes.end()) ? it->second : "";
        }
    };

    struct new_SWay : COpenStreetMap::SWay {
        TWayID DID;
        std::vector<TNodeID> DNodeIDs;
        std::map<std::string, std::string> DAttributes;

        // Constructor to initialize the way with an ID, nodes, and attributes
        new_SWay(TWayID id, std::vector<TNodeID> nodes, std::map<std::string, std::string> attributes)
            : DID(id), DNodeIDs(std::move(nodes)), DAttributes(std::move(attributes)) {}

        TWayID ID() const noexcept override {
            return DID;
        }

        std::size_t NodeCount() const noexcept override {
            return DNodeIDs.size();
        }

        TNodeID GetNodeID(std::size_t index) const noexcept override {
            return (index < DNodeIDs.size()) ? DNodeIDs[index] : InvalidNodeID;
        }

        std::size_t AttributeCount() const noexcept override {
            return DAttributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index >= DAttributes.size()) {
                return "";
            }
            auto it = DAttributes.begin();
            std::advance(it, index);
            return it->first;
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return DAttributes.find(key) != DAttributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = DAttributes.find(key);
            return (it != DAttributes.end()) ? it->second : "";
        }
    };
};

// Returns the number of ways in the map 
std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->DWays.size();
}

// returns the SNode associated with index returns nullptr if index is out of range
std::shared_ptr<COpenStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    return (index < DImplementation->DNodeIDs.size()) ? DImplementation->DNodeIDs[index] : nullptr;
}

// returns the SNode with the given id returns nullptr if it doesn't exist 
std::shared_ptr<COpenStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
    auto it = DImplementation->DNodeMap.find(id);
    return (it != DImplementation->DNodeMap.end()) ? it->second : nullptr;
}

// returns the SWay associated with index returns nullptr if index is out of range
std::shared_ptr<COpenStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    return (index < DImplementation->DWays.size()) ? DImplementation->DWays[index] : nullptr;
}

// returns the SWay with the given id returns nullptr if it doesn't exist
std::shared_ptr<COpenStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
    auto it = DImplementation->DWayMap.find(id);
    return (it != DImplementation->DWayMap.end()) ? it->second : nullptr;
}


// // Street Map Node member functions 
// // Returns the id of the SNode 
// TNodeID SNodeImpl::ID() const noexcept {
//     return TNodeID();
// }

// // Returns the lat/lon location of the SNode 
// TLocation SNodeImpl::Location() const noexcept {
//     return TLocation();
// }

// // Returns the number of attributes attached to the SNode 
// std::size_t SNodeImpl::AttributeCount() const noexcept {
//     return 0;
// }

// // Returns the key of the attribute at index, returns empty string if index is greater than or equal to AttributeCount() 
// std::string SNodeImpl::GetAttributeKey(std::size_t index) const noexcept {
//     return "";
// }

// // Returns if the attribute is attached to the SNode 
// bool SNodeImpl::HasAttribute(const std::string &key) const noexcept {
//     return false;
// }

// // Returns the value of the attribute specified by key, returns empty string if key hasn't been attached to SNode 
// std::string SNodeImpl::GetAttribute(const std::string &key) const noexcept {
//     return "";
// }




// // Street Map Way 
// // Returns the id of the SWay 
// TWayID SWayImpl::ID() const noexcept {
//     return TWayID();
// }

// // Returns the number of nodes in the way 
// std::size_t SWayImpl::NodeCount() const noexcept {
//     return 0;
// }

// // Returns the node id of the node at index, returns InvalidNodeID if index is greater than or equal to NodeCount() 
// TNodeID SWayImpl::GetNodeID(std::size_t index) const noexcept {
//     return TNodeID();
// }

// // Returns the number of attributes attached to the SWay 
// std::size_t SWayImpl::AttributeCount() const noexcept {
//     return 0;
// }

// // Returns the key of the attribute at index, returns empty string if index is greater than or equal to AttributeCount() 
// std::string SWayImpl::GetAttributeKey(std::size_t index) const noexcept {
//     return "";
// }

// // Returns if the attribute is attached to the SWay 
// bool SWayImpl::HasAttribute(const std::string &key) const noexcept {
//     return false;
// }

// // Returns the value of the attribute specified by key, returns empty string if key hasn't been attached to SWay 
// std::string SWayImpl::GetAttribute(const std::string &key) const noexcept {
//     return "";
// }
