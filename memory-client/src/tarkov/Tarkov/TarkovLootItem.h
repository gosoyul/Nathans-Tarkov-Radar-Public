#pragma once
#include "Base.h"
#include "TarkovLootItemTemplate.h"

#include "rapidjson/document.h"

class TarkovLootItem : public CachedMemoryObject
{
    // Set to true ifyou only want to display valuable items
    // bool isOnlyValuable = true;
    // Set to true ifyou want to include corpses in valuable items
    // bool isCorpseValuable = true;
    // Change the item name to the name of itemList.json instead of the object name
    bool isChangeItemName = true;

public:
    // Changed to string to define the same type as 'ID' of TarkovPlayer class 
    std::string ID;

    std::string LootName;
    Vector3 LootLocation;
    bool isCorpse;
    bool isShown = false;
    bool isValuable = false;

    TarkovLootItem()
        : CachedMemoryObject()
    {
    }

    TarkovLootItem(WinProcess *GameProcess, uint64_t Address, rapidjson::Value &lootConfig, rapidjson::Document &itemList)
        : CachedMemoryObject(GameProcess, Address)
    {
        uint64_t m_lItemProfile = GameProcess->Read<uint64_t>(Address + 0x10);
        uint64_t m_lGameObject = GameProcess->Read<uint64_t>(m_lItemProfile + 0x30);
        
        // Get gameObject's name. This isn't item name.
        std::string gameObjectName = GetGameObjectName(m_lGameObject);

        // Check the contents in case of a lootable container
        // Finding item in lootable container is not normally coming out except hidden stash(scontainer_*)
        if(IsLootableObject(gameObjectName)) {
            if(!lootConfig["container"].GetBool())
                return;

            uint64_t m_lInteractive = GameProcess->Read<uint64_t>(m_lItemProfile + 0x28);

            uint64_t m_lItemOwner = GameProcess->Read<uint64_t>(m_lInteractive + 0x108);
            uint64_t m_lItem = GameProcess->Read<uint64_t>(m_lItemOwner + 0x90);

            uint64_t m_lGrids = GameProcess->Read<uint64_t>(m_lItem + 0x68);
            int32_t m_lGridsSize = GameProcess->Read<int32_t>(m_lGrids + 0x18);

            if(m_lGridsSize > 0) {
                uint64_t m_lGridObject = GameProcess->Read<uint64_t>(m_lGrids + 0x20);
                uint64_t m_lGridDict = GameProcess->Read<uint64_t>(m_lGridObject + 0x40);

                uint64_t m_lDict = GameProcess->Read<uint64_t>(m_lGridDict + 0x10);
                int32_t m_lDictSize = GameProcess->Read<int32_t>(m_lDict + 0x40);
                
                uint64_t m_lEntries = GameProcess->Read<uint64_t>(m_lDict + 0x18);
                
                bool isThisItemShown = true;
                for(int entriesIndex = 0; entriesIndex < m_lDictSize; entriesIndex++)
                {
                    std::string tmpLootName(LootName);

                    uint64_t m_lItemInContainer = GameProcess->Read<uint64_t>(m_lEntries + 0x28 + 0x18 * entriesIndex);
                    TarkovLootItemTemplate itemTemplateInContainer = TarkovLootItemTemplate(GameProcess, GameProcess->Read<uint64_t>(m_lItemInContainer + 0x38));

                    LootName = itemTemplateInContainer.Get_Name().GetString();
                    isValuable = IsHighValue(itemList);
                    
                    if(!lootConfig["onlyValuable"].GetBool() || (isShown && isThisItemShown) || isValuable) {
                        // Since the container does not have an item name, LootName is given as gameObjectName.
                        LootName = gameObjectName + "(" + LootName + ")";
                        LootLocation = GetLootLocation(m_lGameObject);
                        ID = LootName + "+" + std::to_string((int) LootLocation.x) + ":" + std::to_string((int) LootLocation.y) + ":" + std::to_string((int) LootLocation.z);

                        isThisItemShown = false;

                        if(isValuable)
                            break;
                    } else {
                        LootName = tmpLootName;
                    }
                }
            }

        } else {
            isCorpse = IsCorpse(gameObjectName);
            LootName = isCorpse ? gameObjectName : GetTarkovLootItemTemplate().Get_Name().GetString();

            // Filtering at the source level for performance when you only want to see valuable things
            isValuable = IsHighValue(itemList);

            if(isCorpse && lootConfig["corpse"].GetBool()) {
                isShown = true;

                if(lootConfig["corpseValuable"].GetBool())
                    isValuable = true;
            }

            if(!lootConfig["onlyValuable"].GetBool() || isShown) {
                isShown = true;
                LootLocation = GetLootLocation(m_lGameObject);

                ID = LootName + "+" + std::to_string((int) LootLocation.x) + ":" + std::to_string((int) LootLocation.y) + ":" + std::to_string((int) LootLocation.z);
            }
        }

        bCached = true;
    }
    
    bool IsLootableObject(std::string gameObjectName)
    {

        // List of checking container
        std::vector<std::string> lootableObjectList = {
            "cap",
            "Ammo_crate_Cap",
            "Grenade_box_Door",
            "Medical_Door",
            "POS_Money",
            "POS_Money1",
            "Toolbox_Door",
            "card_file_box_Anim",
            "cover_110",
            "cover_140",
            "cover_64",
            "lootable",
            "scontainer_Blue_Barrel_Base_Cap",
            "scontainer_wood_CAP",
            "suitcase_plastic_lootable_open",
            "weapon_box_cover"
        };

        for(auto const &lootableObjectName: lootableObjectList) {
            // if(gameObjectName.find(lootableObjectName) != std::string::npos)
            if(gameObjectName == lootableObjectName)
                return true;
        }

        return false;
    }

    bool operator==(const TarkovLootItem &other)
    {
        return other.ID == ID;
    }

    bool IsHighValue(rapidjson::Document &itemList)
    {
        // List of shown items
        std::map<std::string, bool> shownItemMap;

        bool isValuable = false;

        for (auto& shownItem : itemList.GetArray()) {
            if(shownItem["use"].GetBool() && LootName.find(shownItem["_name"].GetString()) != std::string::npos) {
                isShown = true;
                isValuable = shownItem["valuable"].IsBool() ? shownItem["valuable"].GetBool() : false;

                if(isChangeItemName)
                    LootName = shownItem["name"].GetString();

                break;
            }
        }

        return isValuable;
    }

private:
    bool IsAlphabet(char c)
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '(' || c == ')' || c == '_';
    }

    TarkovLootItemTemplate GetTarkovLootItemTemplate()
    {
        uint64_t m_lItemProfile = GameProcess->Read<uint64_t>(Address + 0x10);
        uint64_t m_lInteractive = GameProcess->Read<uint64_t>(m_lItemProfile + 0x28);
        uint64_t m_lItem = GameProcess->Read<uint64_t>(m_lInteractive + 0x50);

        return TarkovLootItemTemplate(GameProcess, GameProcess->Read<uint64_t>(m_lItem + 0x38));
    }
    
    std::string GetGameObjectName(uint64_t m_lGameObject)
    {
        std::string result;
        uint64_t m_lItemName = GameProcess->Read<uint64_t>(m_lGameObject + 0x60);

        // char buff[300];
        // GameProcess->Read(m_lItemName, &buff[0], sizeof(buff));

        // std::string Name(buff);
        // Name.erase(std::find(Name.begin(), Name.end(), '\0'), Name.end());

        for (int i = 0; i <= 150; i++)
        {
            char CurrentChar = GameProcess->Read<char>(m_lItemName + i);

            if(CurrentChar == '\0')
                break;

            if(IsAlphabet(CurrentChar))
                result.push_back(CurrentChar);
        }

        return result;
    }

    Vector3 GetLootLocation(uint64_t m_lGameObject)
    {
        uint64_t m_lItemLocalization = GameProcess->Read<uint64_t>(m_lGameObject + 0x30);
        uint64_t m_lItemCoordinates = GameProcess->Read<uint64_t>(m_lItemLocalization + 0x8);
        uint64_t m_lItemLocationContainer = GameProcess->Read<uint64_t>(m_lItemCoordinates + 0x38);
        Vector3 m_lItemPosition = GameProcess->Read<Vector3>(m_lItemLocationContainer + 0xB0);

        return m_lItemPosition;
    }

    bool IsCorpse(std::string gameObjectName)
    {
        bool IsPlayerCorpse = gameObjectName.find("Observed_PlayerSuperior") != std::string::npos;
        bool IsCorpse = gameObjectName.find("LootCorpse_PlayerSuperior") != std::string::npos;
        bool IsScavCorpse = gameObjectName.find("Bot") != std::string::npos;

        return IsPlayerCorpse || IsCorpse || IsScavCorpse;
    }
};
