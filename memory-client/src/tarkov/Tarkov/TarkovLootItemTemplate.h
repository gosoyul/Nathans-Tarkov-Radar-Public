#pragma once
#include "Base.h"
#include "Unity/UnityEngineString.h"

class TarkovLootItemTemplate : public MemoryObject
{
public:
    TarkovLootItemTemplate(WinProcess *GameProcess, uint64_t Address)
        : MemoryObject(GameProcess, Address)
    {
    }

    UnityEngineString GetName()
    {
        return UnityEngineString(GameProcess, GameProcess->Read<uint64_t>(Address + 0x10));
    }
    UnityEngineString GetId()
    {
        return UnityEngineString(GameProcess, GameProcess->Read<uint64_t>(Address + 0x50));
    }
    UnityEngineString Get_Name()
    {
        return UnityEngineString(GameProcess, GameProcess->Read<uint64_t>(Address + 0x58));
    }
    int32_t GetCreditsPrice()
    {
        return GameProcess->Read<int32_t>(Address + 0x88);
    }
};