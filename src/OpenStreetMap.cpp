#include "OpenStreetMap.h"
#include <utility>
#include <iostream>

struct COpenStreetMap::SImplementation{
    struct SNodeImpl : COpenStreetMap::SNode {
        TNodeID NodeID;
        TLocation NodeLocation;
        std::map<std::string, std::string> Attributes;
        
        SNodeImpl(TNodeID id, TLocation location, std::map<std::string, std::string> attributes)
            : NodeID(id), NodeLocation(location), Attributes(std::move(attributes)) {}

        TNodeID ID() const noexcept override {
            return NodeID;
        }

        TLocation Location() const noexcept override {
            return NodeLocation;
        }

        std::size_t AttributeCount() const noexcept override {
            return DAttributes.size();
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

    struct SWayImpl : COpenStreetMap::SWay {
        TWayID WayID;
        std::vector<TNodeID> NodeIDs;
        std::map<std::string, std::string> Attributes;

        SWayImpl(TWayID id, std::vector<TNodeID> nodes, std::map<std::string, std::string> attributes)
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
    
    std::map<TNodeID, std::shared_ptr<SNodeImpl>> DNodeMap;
    std::vector<std::shared_ptr<SWayImpl>> DWays;
    std::map<TWayID, std::shared_ptr<SWayImpl>> DWayMap;
};

COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src)
    : DImplementation(std::make_unique<SImplementation>()) {
    std::cout << "OpenStreetMap initialized." << std::endl;
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
