#pragma once
#include "Base.h"

class TarkovLootItem : public CachedMemoryObject
{
public:
    std::string ID;

    std::string LootName;
    Vector3 LootLocation;
    bool isCorpse;
    bool isHighValue;

    TarkovLootItem()
        : CachedMemoryObject()
    {
    }

    TarkovLootItem(WinProcess *GameProcess, uint64_t Address)
        : CachedMemoryObject(GameProcess, Address)
    {
        LootName = GetLootName();
        isHighValue = IsHighValue();

        // 퍼포먼스 및 비싼것만 먹기 위해 추가
        if(isHighValue) {
            LootLocation = GetLootLocation();
            isCorpse = IsCorpse();
            //snprintf(ID, sizeof(ID), "%s+%i:%i:%i.", LootName.c_str(), (int)LootLocation.x, (int)LootLocation.y, (int)LootLocation.z);
            ID = LootName + "+" + std::to_string((int) LootLocation.x) + ":" + std::to_string((int) LootLocation.y) + ":" + std::to_string((int) LootLocation.z);
        }

        bCached = true;
    }

    bool operator==(const TarkovLootItem &other)
    {
        return other.ID == ID;
    }

    bool IsHighValue()
    {
       bool result = LootName.find("virtexprocessor") != std::string::npos || LootName.find("transilluminator") != std::string::npos || LootName.find("intelligence") != std::string::npos || LootName.find("tetriz") != std::string::npos || LootName.find("rfidreader") != std::string::npos || LootName.find("defibrillator") != std::string::npos || LootName.find("bitcoin") != std::string::npos || LootName.find("chicken") != std::string::npos || LootName.find("lion") != std::string::npos || LootName.find("prokill") != std::string::npos || LootName.find("rolex") != std::string::npos || LootName.find("video_card") != std::string::npos || LootName.find("item_keycard_lab_yellow") != std::string::npos || LootName.find("item_keycard_lab_violet") != std::string::npos || LootName.find("item_keycard_lab_red") != std::string::npos || LootName.find("item_keycard_lab_green") != std::string::npos || LootName.find("item_keycard_lab_blue") != std::string::npos || LootName.find("item_keycard_lab_black") != std::string::npos || LootName.find("flashstorage") != std::string::npos || LootName.find("paracord") != std::string::npos || LootName.find("woodclock") != std::string::npos || LootName.find("wirelesstranmitter") != std::string::npos || LootName.find("diagset") != std::string::npos;
       /* bool IsLedX = LootName.find("_transilluminator") != std::string::npos;
        bool IsCardA = LootName.find("key_") != std::string::npos;
        bool IsLab = LootName.find("lab") != std::string::npos;
        bool IsIntel = LootName.find("info_intelligence") != std::string::npos;
        bool IsGPU = LootName.find("video_card") != std::string::npos;*/
        //bool IsElec = LootName.find("electr_") != std::string::npos;
        //bool IsCorpseA = IsCorpse();

        //return IsLedX || IsCardA || IsLab || IsIntel || IsGPU;
        return result;
    }

private:
    uint64_t GetBasicInfo()
    {
        uint64_t m_lItemProfile = GameProcess->Read<uint64_t>(Address + 0x10);

        uint64_t m_lItemBasicInfo = GameProcess->Read<uint64_t>(m_lItemProfile + 0x30);
        return m_lItemBasicInfo;
    }

    bool IsAlphabet(char c)
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '(' || c == ')' || c == '_';
    }

    std::string GetLootName()
    {
        uint64_t m_lItemBasicInfo = GetBasicInfo();

        //std::string result;
        uint64_t m_lItemName = GameProcess->Read<uint64_t>(m_lItemBasicInfo + 0x60);

        char buff[100];
        GameProcess->Read(m_lItemName, &buff[0], sizeof(buff));

        std::string Name(buff);
        Name.erase(std::find(Name.begin(), Name.end(), '\0'), Name.end());

        /*
        for (int i = 0; i <= 100; i++)
        {
            char CurrentChar = GameProcess->Read<char>(m_lItemName + i);

            if (CurrentChar == '\0')
                break;

            if (IsAlphabet(CurrentChar))
                result.push_back(CurrentChar);
        }
        */

        return Name;
    }

    Vector3 GetLootLocation()
    {
        uint64_t m_lItemBasicInfo = GetBasicInfo();

        uint64_t m_lItemLocalization = GameProcess->Read<uint64_t>(m_lItemBasicInfo + 0x30);
        uint64_t m_lItemCoordinates = GameProcess->Read<uint64_t>(m_lItemLocalization + 0x8);
        uint64_t m_lItemLocationContainer = GameProcess->Read<uint64_t>(m_lItemCoordinates + 0x38);
        Vector3 m_lItemPosition = GameProcess->Read<Vector3>(m_lItemLocationContainer + 0xB0);

        return m_lItemPosition;
    }

    bool IsCorpse()
    {
        bool IsPlayerCorpse = GetLootName().find("Observed_PlayerSuperior") != std::string::npos;
        bool IsCorpse = GetLootName().find("LootCorpse_PlayerSuperior") != std::string::npos;
        bool IsScavCorpse = GetLootName().find("Bot") != std::string::npos;

        return IsPlayerCorpse || IsCorpse || IsScavCorpse;
    }
};
