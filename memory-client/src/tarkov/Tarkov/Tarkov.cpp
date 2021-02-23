#include "Tarkov.h"
#include "TarkovPlayer.h"
#include "TarkovLootItem.h"
#include "TarkovExfilPoint.h"

#include "relayabstract.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

void TarkovGame::GameMain()
{
    while (true)
    {
        if (GameProcess == nullptr || Module == nullptr)
            break;

        sleep(1);
        GOM = GameObjectManager(GameProcess, GameProcess->Read<uint64_t>(Address + Offsets.GameObjectManager));
        LocalGameWorld = FindLocalGameWorld();

        auto gameReady = [this]() {
            bool GOMValid = (GOM.GetAddress() != 0x0);
            bool LGWValid = (LocalGameWorld != 0x0);
            bool HasPlayers = (GetPlayerCount() > 0);

            return GOMValid && LGWValid && HasPlayers;
        };

        RelayManager->UpdateGameReady(gameReady());

        rapidjson::Document itemList;
        rapidjson::Document config;
        // Read the list of items to be displayed
        if(gameReady()) {
            std::ifstream configStream("./config.json");
            if(configStream.is_open()) {
                rapidjson::IStreamWrapper configStreamWrapper(configStream);
                
                config.ParseStream(configStreamWrapper);
                configStream.close();
            } else {
                throw std::runtime_error("!! Unable to open config.json !!");
            }

            std::ifstream itemListStream("./itemList.json");
            if(itemListStream.is_open()) {
                rapidjson::IStreamWrapper itemListStreamWrapper(itemListStream);
                
                itemList.ParseStream(itemListStreamWrapper);
                itemListStream.close();
            } else {
                throw std::runtime_error("!! Unable to open itemList.json !!");
            }
        }

        int i = 0;
        while (gameReady())
        {
            usleep(100000);
            ++i;
            // Player Handling
            if(config["player"]["on"].IsBool() && config["player"]["on"].GetBool()) {
                std::vector<TarkovPlayer> AllPlayers = GetAllPlayers(config["player"]);
                // Update existing player
                for (const TarkovPlayer& Player : AllPlayers)
                {
                    //Player.DebugDump();
                    RelayManager->UpdatePlayer(Player, i);
                }
                
                RelayManager->DeleteOldPlayers(i);
            }

            // Loot Handling
            if(config["loot"]["on"].IsBool() && config["loot"]["on"].GetBool()) {
                std::vector<TarkovLootItem> AllLoot = GetAllLoot(config["loot"], itemList);

                for (const TarkovLootItem& Loot : AllLoot)
                {
                    RelayManager->UpdateLoot(Loot, i);
                }
                RelayManager->DeleteOldLoot(i);
            }
            
            // Exfil Handling
            if(config["exfil"]["on"].IsBool() && config["exfil"]["on"].GetBool()) {
                std::vector<TarkovExfilPoint> AllExfils = GetExfilArray();

                for (const TarkovExfilPoint& Exfil : AllExfils)
                {
                    RelayManager->UpdateExfil(Exfil, i);
                }
            }
        }
    }
}

int32_t TarkovGame::GetPlayerCount()
{
    uint64_t m_pPlayerList = GameProcess->Read<uint64_t>(LocalGameWorld + 0x80);

    return GameProcess->Read<int32_t>(m_pPlayerList + 0x18);
}

std::vector<TarkovPlayer> TarkovGame::GetAllPlayers(rapidjson::Value &playerConfig)
{
    std::vector<TarkovPlayer> PlayerList;

    uint64_t m_pPlayerList = GameProcess->Read<uint64_t>(LocalGameWorld + 0x80);

    int32_t m_pPlayerListSize = GameProcess->Read<int32_t>(m_pPlayerList + 0x18);
    std::vector<uint64_t> PlayerListPtr(m_pPlayerListSize, 0x0);

    uint64_t m_pPlayerListObject = GameProcess->Read<uint64_t>(m_pPlayerList + 0x10);

    GameProcess->Read(m_pPlayerListObject + 0x20, PlayerListPtr.data(), m_pPlayerListSize * sizeof(uint64_t));

    for (const uint64_t& PlayerPtr : PlayerListPtr)
    {
        PlayerList.push_back(TarkovPlayer(GameProcess, PlayerPtr, playerConfig));
    }

    /*
    for (int i = 0; i < m_pPlayerListSize; i++)
    {
        TarkovPlayer m_pPlayer = TarkovPlayer(GameProcess, GameProcess->Read<uint64_t>(m_pPlayerListObject + 0x20 + (i * 0x8)));
        PlayerList.push_back(m_pPlayer);
    }
    */

    return PlayerList;
}

std::vector<TarkovLootItem> TarkovGame::GetAllLoot(rapidjson::Value &lootConfig, rapidjson::Document &itemList)
{
    std::vector<TarkovLootItem> LootList;

    uint64_t m_lLootList = GameProcess->Read<uint64_t>(LocalGameWorld + 0x60);

    int32_t m_lLootListSize = GameProcess->Read<int32_t>(m_lLootList + 0x18);
    std::vector<uint64_t> LootListPtr(m_lLootListSize, 0x0);

    uint64_t m_lLootListObject = GameProcess->Read<uint64_t>(m_lLootList + 0x10);

    GameProcess->Read(m_lLootListObject + 0x20, LootListPtr.data(), m_lLootListSize * sizeof(uint64_t));
    for (const uint64_t& LootPtr : LootListPtr)
    {
        TarkovLootItem tarkovLootItem = TarkovLootItem(GameProcess, LootPtr, lootConfig, itemList);
        
        if(tarkovLootItem.isShown)
            LootList.push_back(tarkovLootItem);
    }

    // for (int i = 0; i < m_lLootListSize; i++)
    // {
    //     TarkovLootItem m_lItem = TarkovLootItem(GameProcess, GameProcess->Read<uint64_t>(m_lLootListObject + 0x20 + (i * 0x8)));
    //     Vector3 coord = m_lItem.LootLocation;
    //     if (coord.x == 0 && coord.y == 0 && coord.z == 0)
    //         continue;

    //     if(m_lItem.isShown)
    //         LootList.push_back(m_lItem);
    // }

    return LootList;
}

std::vector<TarkovExfilPoint> TarkovGame::GetExfilArray()
{
    std::vector<TarkovExfilPoint> ExfilList;

    uint64_t m_eExfilController = GameProcess->Read<uint64_t>(GameProcess->Read<uint64_t>(LocalGameWorld + 0x18) + 0x20);

    int64_t m_eExfilListSize = GameProcess->Read<int64_t>(m_eExfilController + 0x18);
    std::vector<uint64_t> ExfilListPtr(m_eExfilListSize, 0x0);

    //uint64_t m_eExfilController = GameProcess->Read<uint64_t>(GameProcess->Read<uint64_t>(LocalGameWorld + 0x18) + 0x28); //scav

    GameProcess->Read(m_eExfilController + 0x20, ExfilListPtr.data(), m_eExfilListSize * sizeof(uint64_t));

    for (const uint64_t& ExfilPtr : ExfilListPtr)
    {
        ExfilList.push_back(TarkovExfilPoint(GameProcess, ExfilPtr));
    }

    /*
    for (int i = 0; i < m_eExfilListSize; i++)
    {
        TarkovExfilPoint m_eExfilPoint = TarkovExfilPoint(GameProcess, GameProcess->Read<uint64_t>(m_eExfilController + 0x20 + (i * 0x8)));
        ExfilList.push_back(m_eExfilPoint);
    }
    */

    return ExfilList;
}
