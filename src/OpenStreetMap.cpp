#include "OpenStreetMap.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

struct COpenStreetMap::SImplementation {
    struct new_SNode : COpenStreetMap::SNode {
        TNodeID NodeID;
        TLocation NodeLocation;
        std::map<std::string, std::string> Attributes;

        new_SNode(TNodeID id, TLocation location, std::map<std::string, std::string> attributes)
            : NodeID(id), NodeLocation(location), Attributes(std::move(attributes)) {}

        TNodeID ID() const noexcept override {
            return NodeID;
        }

        TLocation Location() const noexcept override {
            return NodeLocation;
        }

        std::size_t AttributeCount() const noexcept override {
            return Attributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index >= Attributes.size()) return "";
            auto it = Attributes.begin();
            std::advance(it, index);
            return it->first;
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return Attributes.find(key) != Attributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = Attributes.find(key);
            return it != Attributes.end() ? it->second : "";
        }
    };

    struct new_SWay : COpenStreetMap::SWay {
        TWayID WayID;
        std::vector<TNodeID> NodeIDs;
        std::map<std::string, std::string> Attributes;

        new_SWay(TWayID id, std::vector<TNodeID> nodes, std::map<std::string, std::string> attributes)
            : WayID(id), NodeIDs(std::move(nodes)), Attributes(std::move(attributes)) {}

        TWayID ID() const noexcept override {
            return WayID;
        }

        std::size_t NodeCount() const noexcept override {
            return NodeIDs.size();
        }

        TNodeID GetNodeID(std::size_t index) const noexcept override {
            if (index >= NodeIDs.size()) return InvalidNodeID;
            return NodeIDs[index];
        }

        std::size_t AttributeCount() const noexcept override {
            return Attributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index >= Attributes.size()) return "";
            auto it = Attributes.begin();
            std::advance(it, index);
            return it->first;
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return Attributes.find(key) != Attributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = Attributes.find(key);
            return it != Attributes.end() ? it->second : "";
        }
    };

    std::map<TNodeID, std::shared_ptr<new_SNode>> DNodeMap;
    std::vector<std::shared_ptr<new_SWay>> DWays;
    std::map<TWayID, std::shared_ptr<new_SWay>> DWayMap;
};

COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) : DImplementation(std::make_unique<SImplementation>()) {
    SXMLEntity entity;
    while (src->ReadEntity(entity)) {
        if (entity.DType == SXMLEntity::EType::StartElement) {
            if (entity.DNameData == "node") {
                TNodeID nodeID = std::stoll(entity.DAttributes["id"]);
                TLocation location = {std::stod(entity.DAttributes["lat"]), std::stod(entity.DAttributes["lon"])};
                std::map<std::string, std::string> attributes;
                while (src->ReadEntity(entity) && entity.DType != SXMLEntity::EType::EndElement) {
                    if (entity.DNameData == "tag") {
                        attributes[entity.DAttributes["k"]] = entity.DAttributes["v"];
                    }
                }
                DImplementation->DNodeMap[nodeID] = std::make_shared<new_SNode>(nodeID, location, attributes);
            } else if (entity.DNameData == "way") {
                TWayID wayID = std::stoll(entity.DAttributes["id"]);
                std::vector<TNodeID> nodes;
                std::map<std::string, std::string> attributes;
                while (src->ReadEntity(entity) && entity.DType != SXMLEntity::EType::EndElement) {
                    if (entity.DNameData == "nd") {
                        nodes.push_back(std::stoll(entity.DAttributes["ref"]));
                    } else if (entity.DNameData == "tag") {
                        attributes[entity.DAttributes["k"]] = entity.DAttributes["v"];
                    }
                }
                DImplementation->DWayMap[wayID] = std::make_shared<new_SWay>(wayID, nodes, attributes);
                DImplementation->DWays.push_back(DImplementation->DWayMap[wayID]);
            }
        }
    }
}

COpenStreetMap::~COpenStreetMap() = default;

std::size_t COpenStreetMap::NodeCount() const noexcept {
    return DImplementation->DNodeMap.size();
}

std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->DWays.size();
}

std::shared_ptr<COpenStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    if (index >= DImplementation->DNodeMap.size()) return nullptr;
    auto it = DImplementation->DNodeMap.begin();
    std::advance(it, index);
    return it->second;
}

std::shared_ptr<COpenStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
    auto it = DImplementation->DNodeMap.find(id);
    return it != DImplementation->DNodeMap.end() ? it->second : nullptr;
}

std::shared_ptr<COpenStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    if (index >= DImplementation->DWays.size()) return nullptr;
    return DImplementation->DWays[index];
}

std::shared_ptr<COpenStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
    auto it = DImplementation->DWayMap.find(id);
    return it != DImplementation->DWayMap.end() ? it->second : nullptr;
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
