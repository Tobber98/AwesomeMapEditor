//////////////////////////////////////////////////////////////////////////////////
//
//
//                     d88b         888b           d888  888888888888
//                    d8888b        8888b         d8888  888
//                   d88''88b       888'8b       d8'888  888
//                  d88'  '88b      888 '8b     d8' 888  8888888
//                 d88Y8888Y88b     888  '8b   d8'  888  888
//                d88""""""""88b    888   '8b d8'   888  888
//               d88'        '88b   888    '888'    888  888
//              d88'          '88b  888     '8'     888  888888888888
//
//
// AwesomeMapEditor: A map editor for GBA Pokémon games.
// Copyright (C) 2016 Diegoisawesome, Pokedude
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Include files
//
///////////////////////////////////////////////////////////
#include <AME/System/Configuration.hpp>
#include <AME/System/ErrorStack.hpp>
#include <yaml-cpp/yaml.h>
#include <QApplication>
#include <QFile>


namespace ame
{
    ///////////////////////////////////////////////////////////
    // Static variable definition
    //
    ///////////////////////////////////////////////////////////
    UInt32 Configuration::PokemonCount;
    UInt32 Configuration::PokemonNames;
    UInt32 Configuration::PokemonIcons;
    UInt32 Configuration::PokemonUsage;
    UInt32 Configuration::PokemonPals;
    UInt32 Configuration::WildPokemon;
    UInt32 Configuration::ItemHeader;
    UInt32 Configuration::Overworlds;
    UInt32 Configuration::OverworldPals;
    UInt32 Configuration::OverworldCount;
    UInt32 Configuration::FlyingLocs;
    UInt32 Configuration::StartBank;
    UInt32 Configuration::StartMap;
    UInt32 Configuration::StartX;
    UInt32 Configuration::StartY;
    UInt32 Configuration::MapBanks;
    UInt32 Configuration::MapLayouts;
    UInt32 Configuration::MapNames;
    UInt32 Configuration::MapNameCount;
    UInt32 Configuration::MapNameTotal;
    UInt32 Configuration::SpriteNormalSet;
    UInt32 Configuration::SpriteSmallSet;
    UInt32 Configuration::SpriteLargeSet;
    UInt32 Configuration::WorldMapCount;
    QList<UInt32> Configuration::WorldMapGFX;
    QList<UInt32> Configuration::WorldMapTileMap;
    QList<UInt32> Configuration::WorldMapPal;
    UInt32 Configuration::FreespaceStart;


    ///////////////////////////////////////////////////////////
    // Function type:  I/O
    // Contributors:   Pokedude
    // Last edit by:   Pokedude
    // Date of edit:   6/16/2016
    //
    ///////////////////////////////////////////////////////////
    bool Configuration::parse(const qboy::Rom &rom)
    {
        // Builds the path to the YAML file for this ROM
        const QString appFolder = QApplication::applicationDirPath();
        const QString subFolder = "/config/";
        const QString fileName = rom.info().code();
        const QString fileExt = ".yaml";
        QString filePath = appFolder + subFolder + fileName + fileExt;


        // Loads the YAML file
        YAML::Node topNode = YAML::LoadFile(filePath.toStdString());
        if (topNode.IsNull())
            AME_THROW2(CFG_ERROR_FILE);

        // Tries to parse all the properties
        YAML::Node configNode = topNode["Config"];
        PokemonCount    = configNode["PokemonCount"].as<UInt32>();
        PokemonNames    = configNode["PokemonNames"].as<UInt32>();
        PokemonIcons    = configNode["PokemonIcons"].as<UInt32>();
        PokemonUsage    = configNode["PokemonUsage"].as<UInt32>();
        PokemonPals     = configNode["PokemonPals"].as<UInt32>();
        WildPokemon     = configNode["WildPokemon"].as<UInt32>();
        ItemHeader      = configNode["ItemHeader"].as<UInt32>();
        Overworlds      = configNode["Overworlds"].as<UInt32>();
        OverworldPals   = configNode["OverworldPals"].as<UInt32>();
        OverworldCount  = configNode["OverworldCount"].as<UInt32>();
        FlyingLocs      = configNode["FlyingLocs"].as<UInt32>();
        StartBank       = configNode["StartBank"].as<UInt32>();
        StartMap        = configNode["StartMap"].as<UInt32>();
        StartX          = configNode["StartX"].as<UInt32>();
        StartY          = configNode["StartY"].as<UInt32>();
        MapBanks        = configNode["MapBanks"].as<UInt32>();
        MapLayouts      = configNode["MapLayouts"].as<UInt32>();
        MapNames        = configNode["MapNames"].as<UInt32>();
        MapNameCount    = configNode["MapNameCount"].as<UInt32>();
        MapNameTotal    = configNode["MapNameTotal"].as<UInt32>();
        SpriteNormalSet = configNode["SpriteNormalSet"].as<UInt32>();
        SpriteSmallSet  = configNode["SpriteSmallSet"].as<UInt32>();
        SpriteLargeSet  = configNode["SpriteLargeSet"].as<UInt32>();
        WorldMapCount   = configNode["WorldMapCount"].as<UInt32>();
        FreespaceStart  = configNode["FreespaceStart"].as<UInt32>();

        // Tries to parse all collections
        for (unsigned i = 0; i < WorldMapCount; i++)
        {
            WorldMapGFX.push_back(configNode["WorldMapGFX"][i].as<UInt32>());
            WorldMapTileMap.push_back(configNode["WorldMapTileMap"][i].as<UInt32>());
            WorldMapPal.push_back(configNode["WorldMapPal"][i].as<UInt32>());
        }

        // Tries to read all header offsets (or values) from the given pointer offsets
        FETCH(PokemonCount, rom.readHWord());
        FETCH(PokemonNames, rom.readPointer());
        FETCH(PokemonIcons, rom.readPointer());
        FETCH(PokemonUsage, rom.readPointer());
        FETCH(PokemonPals, rom.readPointer());
        FETCH(WildPokemon, rom.readPointer());
        FETCH(ItemHeader, rom.readPointer());
        FETCH(Overworlds, rom.readPointer());
        FETCH(OverworldPals, rom.readPointer());
        FETCH(OverworldCount, rom.readByte());
        FETCH(FlyingLocs, rom.readPointer());
        FETCH(StartBank, rom.readByte());
        FETCH(StartMap, rom.readByte());
        FETCH(StartX, rom.readByte());
        FETCH(StartY, rom.readByte());
        FETCH(MapBanks, rom.readPointer());
        FETCH(MapNames, rom.readPointer());
        FETCH(MapNameCount, rom.readByte());
        FETCH(MapNameTotal, rom.readByte());

        // Parsing successful
        return true;
    }
}
