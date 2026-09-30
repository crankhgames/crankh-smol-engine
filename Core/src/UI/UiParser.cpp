#include "UiParser.h"

#include "Text.h"
#include "Button.h"
#include "Image.h"
#include "UiContainer.h"

#include <fstream>
#include <optional>
#include <print>
#include <unordered_map>
#include <bits/stdc++.h>

namespace Core::UI::UiParser {

    std::unique_ptr<UiElement> createUiElementFromTag(std::string_view tag) {
        std::string_view tagContent {tag.substr(1, tag.size() - 2)};

        std::vector<std::string> tokens {};

        std::string currentProperty {};
        bool onTagProperty {false};

        for (auto it {tagContent.begin()}; it != tagContent.end(); ++it){
            //std::println("Char: {}", *it);
            if (*it == ' ' && !onTagProperty){
                tokens.push_back(currentProperty);
                currentProperty = "";
                continue;
            }
            else if (*it == '"' && !onTagProperty){
                onTagProperty = true;
            }
            else if (*it == '"' && onTagProperty){
                onTagProperty = false;
            }

            currentProperty += *it;
        }
        tokens.push_back(currentProperty);

        std::string tagName {tokens[0]};
        std::unordered_map<std::string, std::string> properties {};

        for (auto tokenIt {tokens.begin() + 1}; tokenIt != tokens.end(); ++tokenIt){

            std::size_t equalSignIndex {(*tokenIt).find_first_of('=')};
            std::string propertyName {(*tokenIt).substr(0, equalSignIndex)};
            std::string propertyValue {(*tokenIt).substr(equalSignIndex+1)};

            properties.insert({propertyName, propertyValue});
        }

        std::string id {""};
        if (properties.find("id") != properties.end()){
            id = properties["id"];
        }


        if (tagName == "text"){
            std::string font {"assets/fonts/Roboto-Medium.ttf"};
            std::string content {""};
            int pointSize {15};
            SDL_Color color {0, 0, 0, 255};

            if (properties.find("content") != properties.end()){
                content = properties["content"].substr(1, properties["content"].size()-2);
            }
            if (properties.find("font") != properties.end()){
                font = properties["font"].substr(1, properties["font"].size()-2);
            }
            if (properties.find("size") != properties.end()){
                pointSize = std::stoi(properties["size"]);
            }
            if (properties.find("color") != properties.end()){

                std::string_view red {properties["color"].subview(0, 2)};
                std::string_view green {properties["color"].subview(3, 2)};
                std::string_view blue {properties["color"].subview(5, 2)};
                std::string_view alpha {properties["color"].subview(7, 2)};

                color = SDL_Color{
                    static_cast<Uint8>(std::stoi(std::string{red}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{green}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{blue}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{alpha}, 0, 16)),
                };
            }


            //std::println("Returning text uiElement...");
            return std::make_unique<Text>(content, pointSize, font.c_str(), color, id);
        }
        else if (tagName == "button"){
            //std::println("Creating button...");
            int scaleX {100};
            int scaleY {75};
            SDL_Color backgroundColor {255, 255, 255, 255};

            if (properties.find("scaleX") != properties.end()){
                scaleX = std::stoi(properties["scaleX"]);
            }
            if (properties.find("scaleY") != properties.end()){
                scaleY = std::stoi(properties["scaleY"]);
            }
            if (properties.find("bgColor") != properties.end()){

                std::string_view red {properties["bgColor"].subview(0, 2)};
                std::string_view green {properties["bgColor"].subview(3, 2)};
                std::string_view blue {properties["bgColor"].subview(5, 2)};
                std::string_view alpha {properties["bgColor"].subview(7, 2)};

                backgroundColor = SDL_Color{
                    static_cast<Uint8>(std::stoi(std::string{red}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{green}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{blue}, 0, 16)),
                    static_cast<Uint8>(std::stoi(std::string{alpha}, 0, 16)),
                };
            }

            return std::make_unique<Button>(Math::Vec2Int{scaleX, scaleY}, backgroundColor, 
                []{
                    std::println("Button pressed...");
                }, id
            );
        }
        else if (tagName == "container"){
            bool isVertical {true};
            int gapSize {0};
            bool isDraggable {false};

            if (properties.find("gap") != properties.end()){
                gapSize = std::stoi(properties["gap"]);
            }
            if (properties.find("vertical") != properties.end()){
                isVertical = properties["vertical"] == "true";
            }
            if (properties.find("draggable") != properties.end()){
                isDraggable = properties["draggable"] == "true";
            }

            return std::make_unique<UiContainer>(isVertical, gapSize, isDraggable, id);
        }
        else if (tagName == "image"){
            std::string textureFilename {"assets/sprites/horse-image.jpg"};
            std::optional<int> scaleX{std::nullopt};
            std::optional<int> scaleY{std::nullopt};
            double scale {1.0};

            if (properties.find("scaleX") != properties.end()) {
                scaleX = std::stoi(properties["scaleX"]);
            }
            if (properties.find("scaleY") != properties.end()) {
                scaleY = std::stoi(properties["scaleY"]);
            }
            if (properties.find("scale") != properties.end()) {
                scale = std::stod(properties["scale"]);
            }
            if (properties.find("content") != properties.end()){
                textureFilename = properties["content"].substr(1, properties["content"].size()-2);
            }

            if (scaleX || scaleY){
                return std::make_unique<Image>(Math::Vec2Int{scaleX.value_or(500), scaleY.value_or(500)}, textureFilename);
            }
            else{
                return std::make_unique<Image>(scale, textureFilename, id);
            }

        }

        return std::make_unique<UiElement>();
    }

    std::pair<std::unique_ptr<UiElement>, std::vector<std::string>::iterator> createUiTreeRecursively(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end){
        std::unique_ptr<UiElement> rootElement {createUiElementFromTag(*start)};
        std::println("Tag {}", *start);


        auto it {start+1};
        while (it != end){
            if (it->starts_with("</")){
                ++it;
                break;
            }
            else{
                auto element {createUiTreeRecursively(it, end)};
                rootElement->add(std::move(element.first));
                it = element.second;
            }
        }

        return {std::move(rootElement), it};
    }

    std::unique_ptr<UiElement> createUiTree(std::filesystem::path uiConfigurations){
        std::vector<std::string> tags {loadUiConfigurationFile(uiConfigurations)};

        return createUiTreeRecursively(tags.begin(), tags.end()).first;
    }

    std::vector<std::string> loadUiConfigurationFile(std::filesystem::path uiConfigurations){
        
        std::ifstream file {uiConfigurations};

        std::vector<std::string> tags {};

        bool nameTag {false};

        if (file.is_open()){

            std::string currentNameTag {};

            while (!file.eof()){

                char currentCharacter {static_cast<char>(file.get())};

                switch (currentCharacter){
                case '<':
                    nameTag = true;
                    break;
                case '>':
                    nameTag = false;
                    tags.push_back(currentNameTag + '>');
                    currentNameTag = "";
                    break;
                }

                if (nameTag){
                    currentNameTag.push_back(currentCharacter);
                }
            }
        }
        else{
            std::println("ERROR loading file...");
        }

        return std::move(tags);
    }
}