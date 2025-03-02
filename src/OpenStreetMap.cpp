#include "OpenStreetMap.h"
#include <expat.h>
#include <fstream>
#include <iostream>

// Constructor
COpenStreetMap::COpenStreetMap() : DImplementation(std::make_unique<SImplementation>()) {}

void ParseNodeAttributes(const char **attrs, TNodeID &id, TLocation &location) {
    for (int i = 0; attrs[i]; i += 2) {
        std::string key = attrs[i];
        std::string value = attrs[i + 1];

        if (key == "id") {
            id = std::stoll(value);
        } else if (key == "lat") {
            location.first = std::stod(value);
        } else if (key == "lon") {
            location.second = std::stod(value);
        }
    }
}

void StartElementHandler(void *userData, const char *name, const char **attrs) {
    auto *osm = static_cast<COpenStreetMap::SImplementation *>(userData);

    if (strcmp(name, "node") == 0) {
        TNodeID id = 0;
        TLocation location;
        std::map<std::string, std::string> attributes;

        ParseNodeAttributes(attrs, id, location);
        osm->DNodeMap[id] = std::make_shared<COpenStreetMap::SImplementation::new_SNode>(id, location, attributes);

    } else if (strcmp(name, "way") == 0) {
        osm->CurrentWayID = 0;
        osm->CurrentWayNodes.clear();
        osm->CurrentWayAttributes.clear();

        for (int i = 0; attrs[i]; i += 2) {
            if (std::string(attrs[i]) == "id") {
                osm->CurrentWayID = std::stoll(attrs[i + 1]);
            }
        }

    } else if (strcmp(name, "nd") == 0 && osm->CurrentWayID) {
        for (int i = 0; attrs[i]; i += 2) {
            if (std::string(attrs[i]) == "ref") {
                osm->CurrentWayNodes.push_back(std::stoll(attrs[i + 1]));
            }
        }

    } else if (strcmp(name, "tag") == 0) {
        std::string key, value;
        for (int i = 0; attrs[i]; i += 2) {
            if (std::string(attrs[i]) == "k") {
                key = attrs[i + 1];
            } else if (std::string(attrs[i]) == "v") {
                value = attrs[i + 1];
            }
        }
        if (osm->CurrentWayID) {
            osm->CurrentWayAttributes[key] = value;
        }
    }
}

void EndElementHandler(void *userData, const char *name) {
    auto *osm = static_cast<COpenStreetMap::SImplementation *>(userData);

    if (strcmp(name, "way") == 0 && osm->CurrentWayID) {
        osm->DWays.push_back(std::make_shared<COpenStreetMap::SImplementation::new_SWay>(
            osm->CurrentWayID, osm->CurrentWayNodes, osm->CurrentWayAttributes));

        osm->DWayMap[osm->CurrentWayID] = osm->DWays.back();
    }
}

bool COpenStreetMap::LoadMapFromXML(const std::string &filename) {
    XML_Parser parser = XML_ParserCreate(nullptr);
    if (!parser) {
        std::cerr << "Error: Failed to create XML parser." << std::endl;
        return false;
    }

    XML_SetUserData(parser, DImplementation.get());
    XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file '" << filename << "'." << std::endl;
        XML_ParserFree(parser);
        return false;
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        if (XML_Parse(parser, buffer, file.gcount(), file.eof()) == XML_STATUS_ERROR) {
            std::cerr << "Error: XML parsing failed in file '" << filename 
                      << "': " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
            XML_ParserFree(parser);
            return false;
        }
    }

    XML_ParserFree(parser);
    return true;
}
