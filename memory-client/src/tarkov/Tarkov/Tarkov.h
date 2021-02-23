#pragma once
#include "Unity.h"
#include "TarkovPlayer.h"
#include "TarkovLootItem.h"
#include "TarkovExfilPoint.h"

#include <list>

#include "rapidjson/document.h"

const struct Offsets
{
    static const uint64_t GameObjectManager = 0x156B698;
} Offsets;

class TarkovGame : public UnityGame
{
protected:
    void GameMain();

public:
    TarkovGame(WinProcess *GameProcess, WinDll* Module, RelayAbstract *Relay)
        : UnityGame(GameProcess, Module, Relay)
    {
        GameMain();
    }

    int32_t GetPlayerCount();

    std::vector<TarkovPlayer> GetAllPlayers(rapidjson::Value &playerConfig);

    std::vector<TarkovLootItem> GetAllLoot(rapidjson::Value &lootConfig, rapidjson::Document &itemList);

    std::vector<TarkovExfilPoint> GetExfilArray();
};