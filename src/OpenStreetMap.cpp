// #include "OpenStreetMap.h"
// #include <memory>
// #include <string>
// #include <cstddef>

// // COpenStreetMap member functions 
// // Constructor for the Open Street Map 
// COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src)
// {
// }

// // Destructor for the Open Street Map 
// COpenStreetMap::~COpenStreetMap() {
// }

// // Returns the number of nodes in the map 
// std::size_t COpenStreetMap::NodeCount() const noexcept {
//     return 0;
// }

// // Returns the number of ways in the map 
// std::size_t COpenStreetMap::WayCount() const noexcept {
//     return 0;
// }

// // Returns the SNode associated with index, returns nullptr if index is larger than or equal to NodeCount() 
// std::shared_ptr<SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
//     return nullptr;
// }

// // Returns the SNode with the id of id, returns nullptr if doesn't exist 
// std::shared_ptr<SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
//     return nullptr;
// }

// // Returns the SWay associated with index, returns nullptr if index is larger than or equal to WayCount() 
// std::shared_ptr<SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
//     return nullptr;
// }

// // Returns the SWay with the id of id, returns nullptr if doesn't exist 
// std::shared_ptr<SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
//     return nullptr;
// }

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
