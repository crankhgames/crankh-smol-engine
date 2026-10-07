#include "Tilemap-Parser.h"
#include "Tilemap.h"

#include "Math/Math.h"

#include <fstream>
#include <print>
#include <vector>

using json = nlohmann::json;

namespace Core::Renderer{

    ECS::Entity loadTilemap(std::filesystem::path tilemapFile, ECS::Scene& scene){

        std::ifstream file {tilemapFile};

        json j = json::parse(file);

        std::println("Parse completed!");

        std::string tilemapTexture {j["tileset"].get<std::string>()};
        std::pair<int,int> size {j["size"].get<std::pair<int,int>>()};
        auto json_tiles {j["tiles"].get<std::vector<std::vector<std::pair<int,int>>>>()};

        std::vector<Tile> tiles {};
        for (auto json_tile : json_tiles){
            Tile tile {
                Math::Vec2Int{json_tile[0].first, json_tile[0].second},
                Math::Vec2Int{size.first, size.second},
                Math::Vec2Int{json_tile[1].first, json_tile[1].second},
            };

            tiles.push_back(tile);
        }

        ECS::Entity tilemapEntity {scene.createEntity()};
        using namespace ECS::Components;

        tilemapEntity.addComponent<TransformComponent>(Math::Vec2{-4.0, -2.0});
        tilemapEntity.addComponent<TilemapComponent>(tilemapTexture, tiles, 0.5, true);

        return tilemapEntity;

    }
    
}