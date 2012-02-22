/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: instance_icecrown_citadel
SD%Complete: 90%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"
#include "World.h"

static Locations SpawnLoc[]=
{
    {-446.788971f, 2003.362915f, 191.233948f},  // 0 Horde ship enter
    {-428.140503f, 2421.336914f, 191.233078f},  // 1 Alliance ship enter
};

instance_icecrown_citadel::instance_icecrown_citadel(Map* pMap) : ScriptedInstance(pMap)
{
    Difficulty = pMap->GetDifficulty();
    Initialize();
}

void instance_icecrown_citadel::Initialize()
{
    for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
        m_auiEncounter[i] = NOT_STARTED;

    for (uint8 i = 0; i < MAX_SPECIAL_ACHIEV_CRITS; ++i)
        m_abAchievCriteria[i] = false;

    m_auiEncounter[TYPE_TELEPORT] = 0;

    switch (Difficulty)
    {
         case RAID_DIFFICULTY_10MAN_NORMAL:
                   m_uiGunshipArmoryH_ID = GO_GUNSHIP_ARMORY_H_10;
                   m_uiGunshipArmoryA_ID = GO_GUNSHIP_ARMORY_A_10;
                   m_uiValithriaCache = GO_DREAMWALKER_CACHE_10;
                   m_uiSaurfangCache = GO_SAURFANG_CACHE_10;
                   break;
         case RAID_DIFFICULTY_10MAN_HEROIC:
                   m_uiGunshipArmoryH_ID = GO_GUNSHIP_ARMORY_H_10H;
                   m_uiGunshipArmoryA_ID = GO_GUNSHIP_ARMORY_A_10H;
                   m_uiValithriaCache = GO_DREAMWALKER_CACHE_10_H;
                   m_uiSaurfangCache = GO_SAURFANG_CACHE_10_H;
                   break;
         case RAID_DIFFICULTY_25MAN_NORMAL:
                   m_uiGunshipArmoryH_ID = GO_GUNSHIP_ARMORY_H_25;
                   m_uiGunshipArmoryA_ID = GO_GUNSHIP_ARMORY_A_25;
                   m_uiValithriaCache = GO_DREAMWALKER_CACHE_25;
                   m_uiSaurfangCache = GO_SAURFANG_CACHE_25;
                   break;
         case RAID_DIFFICULTY_25MAN_HEROIC:
                   m_uiGunshipArmoryH_ID = GO_GUNSHIP_ARMORY_H_25H;
                   m_uiGunshipArmoryA_ID = GO_GUNSHIP_ARMORY_A_25H;
                   m_uiValithriaCache = GO_DREAMWALKER_CACHE_25_H;
                   m_uiSaurfangCache = GO_SAURFANG_CACHE_25_H;
                   break;
         default:
                   break;
    };
}

bool instance_icecrown_citadel::IsEncounterInProgress()
{
    for(uint8 i = 1; i < MAX_ENCOUNTERS-2 ; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS)
            return true;

    if (m_auiEncounter[TYPE_PUTRICIDE] == SPECIAL)
        return true;

    return false;
}

bool instance_icecrown_citadel::IsRaidWiped()
{
    Map::PlayerList const &players = instance->GetPlayers();

    for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
    {
        if (Player* pPlayer = i->getSource())
        {
            if (pPlayer->isAlive() &&
                (pPlayer->HasAura(642) || //Divine shield
                 pPlayer->HasAura(1022) || // Hand of protection
                 pPlayer->HasAura(45438) || // Ice block
                 pPlayer->HasAura(5384) || // Feign Death
                 pPlayer->HasAura(1784))) // Stealth
                continue;

            if (!pPlayer->IsInCombat())
                continue;

            if (pPlayer->isAlive())
                return false;
        }
    }
    return true;
}

void instance_icecrown_citadel::DoOpenDoor(ObjectGuid guid)
{
    if (guid.IsEmpty())
        return;

    GameObject* pGo = instance->GetGameObject(guid);

    if (pGo)
        pGo->SetGoState(GO_STATE_ACTIVE);
}

void instance_icecrown_citadel::DoCloseDoor(ObjectGuid guid)
{
    if (guid.IsEmpty())
        return;

    GameObject* pGo = instance->GetGameObject(guid);

    if (pGo)
        pGo->SetGoState(GO_STATE_READY);
}

void instance_icecrown_citadel::DoOpenDoor(uint32 entry)
{
    EntryGuidMap::iterator find = m_mGoEntryGuidStore.find(entry);
    if (find != m_mGoEntryGuidStore.end())
    {
        ObjectGuid guid = find->second;
        DoOpenDoor(guid);
    }
}

void instance_icecrown_citadel::DoCloseDoor(uint32 entry)
{
    EntryGuidMap::iterator find = m_mGoEntryGuidStore.find(entry);
    if (find != m_mGoEntryGuidStore.end())
    {
        ObjectGuid guid = find->second;
        DoCloseDoor(guid);
    }
}

void instance_icecrown_citadel::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_LORD_MARROWGAR:
        case NPC_LADY_DEATHWHISPER:
        case NPC_DEATHBRINGER_SAURFANG:
        case NPC_FESTERGUT:
        case NPC_ROTFACE:
        case NPC_PROFESSOR_PUTRICIDE:
        case NPC_TALDARAM:
        case NPC_VALANAR:
        case NPC_KELESETH:
        case NPC_LANATHEL:
        case NPC_LANATHEL_INTRO:
        case NPC_HORDE_1:
        case NPC_HORDE_2:
        case NPC_HORDE_3:
        case NPC_HORDE_4:
        case NPC_HORDE_5:
        case NPC_ALLY_1:
        case NPC_ALLY_2:
        case NPC_ALLY_3:
        case NPC_ALLY_4:
        case NPC_ALLY_5:
        case NPC_SVALNA:
        case NPC_CROK:
        case NPC_VALITHRIA:
        case NPC_VALITHRIA_QUEST:
        case NPC_LICH_TRIGGER:
        case NPC_SINDRAGOSA:
        case NPC_LICH_KING:
        case NPC_TIRION:
        case NPC_RIMEFANG:
        case NPC_SPINESTALKER:
        case NPC_STINKY:
        case NPC_PRECIOUS:
        case NPC_COMBAT_TRIGGER:
        case NPC_FROSTMOURNE_TRIGGER:
        case NPC_FROSTMOURNE_HOLDER:
        case NPC_BLOOD_ORB_CONTROL:
             m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
             break;
    }
}

void instance_icecrown_citadel::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_ICEWALL_1:
            if (m_auiEncounter[TYPE_MARROWGAR] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_ICEWALL_2:
            if (m_auiEncounter[TYPE_MARROWGAR] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_DEATHWHISPER_ELEVATOR:
        case GO_SAURFANG_DOOR:
            if (m_auiEncounter[TYPE_SAURFANG] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_ORANGE_PLAGUE:
            if (m_auiEncounter[TYPE_FESTERGUT] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_GREEN_PLAGUE:
            if (m_auiEncounter[TYPE_ROTFACE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SCIENTIST_DOOR_GREEN:
            if (m_auiEncounter[TYPE_ROTFACE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SCIENTIST_DOOR_ORANGE:
            if (m_auiEncounter[TYPE_FESTERGUT] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SCIENTIST_DOOR_COLLISION:
            if (m_auiEncounter[TYPE_FESTERGUT] == DONE && m_auiEncounter[TYPE_ROTFACE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SCIENTIST_DOOR:
            if (m_auiEncounter[TYPE_FESTERGUT] == DONE && m_auiEncounter[TYPE_ROTFACE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_CRIMSON_HALL_DOOR:
            if (m_auiEncounter[TYPE_BLOOD_COUNCIL] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_COUNCIL_DOOR_1:
            if (m_auiEncounter[TYPE_BLOOD_COUNCIL] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_COUNCIL_DOOR_2:
            if (m_auiEncounter[TYPE_BLOOD_COUNCIL] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_GREEN_DRAGON_DOOR_1:
            if (m_auiEncounter[TYPE_SVALNA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
        case GO_GREEN_DRAGON_DOOR_2:
            if (m_auiEncounter[TYPE_VALITHRIA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SINDRAGOSA_DOOR_1:
            if (m_auiEncounter[TYPE_VALITHRIA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SINDRAGOSA_DOOR_2:
            if (m_auiEncounter[TYPE_VALITHRIA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_SAURFANG_CACHE_10:
        case GO_SAURFANG_CACHE_25:
        case GO_SAURFANG_CACHE_10_H:
        case GO_SAURFANG_CACHE_25_H:
        case GO_GUNSHIP_ARMORY_A_10:
        case GO_GUNSHIP_ARMORY_A_25:
        case GO_GUNSHIP_ARMORY_A_10H:
        case GO_GUNSHIP_ARMORY_A_25H:
        case GO_GUNSHIP_ARMORY_H_10:
        case GO_GUNSHIP_ARMORY_H_25:
        case GO_GUNSHIP_ARMORY_H_10H:
        case GO_GUNSHIP_ARMORY_H_25H:
        case GO_DREAMWALKER_CACHE_10:
        case GO_DREAMWALKER_CACHE_25:
        case GO_DREAMWALKER_CACHE_10_H:
        case GO_DREAMWALKER_CACHE_25_H:
        case GO_ICESHARD_1:
        case GO_ICESHARD_2:
        case GO_ICESHARD_3:
        case GO_ICESHARD_4:
        case GO_FROSTY_WIND:
        case GO_FROSTY_EDGE:
        case GO_SNOW_EDGE:
        case GO_ARTHAS_PLATFORM:
        case GO_ARTHAS_PRECIPICE:
        case GO_GAS_RELEASE_VALVE:
        case GO_MARROWGAR_DOOR:
        case GO_BLOODPRINCE_DOOR:
        case GO_ICECROWN_GRATE:
        case GO_SINDRAGOSA_ENTRANCE:
        case GO_SINDRAGOSA_ICEWALL:
        case GO_VALITHRIA_DOOR_1:
        case GO_VALITHRIA_DOOR_2:
        case GO_VALITHRIA_DOOR_3:
        case GO_VALITHRIA_DOOR_4:
        case GO_FROSTWING_DOOR:
        case GO_BLOODWING_DOOR:
        case GO_ORATORY_DOOR:
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
    }
}

void instance_icecrown_citadel::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_TELEPORT:
            break;
        case TYPE_MARROWGAR:
            m_auiEncounter[TYPE_MARROWGAR] = uiData;

            if (uiData == DONE)
            {
                DoOpenDoor(GO_ICEWALL_1);
                DoOpenDoor(GO_ICEWALL_2);
                DoOpenDoor(GO_ORATORY_DOOR);
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_MARROWGAR_DOOR);
                SetSpecialAchievementCriteria(TYPE_BONED, true);
            }
            else
                DoOpenDoor(GO_MARROWGAR_DOOR);
            break;
         case TYPE_DEATHWHISPER:
            m_auiEncounter[TYPE_DEATHWHISPER] = uiData;

            if (uiData == DONE)
            {
                if (GameObject* pGO = GetSingleGameObjectFromStorage(GO_DEATHWHISPER_ELEVATOR))
                {
                      pGO->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                      pGO->SetGoState(GO_STATE_READY);
                }
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_ORATORY_DOOR);
                SetSpecialAchievementCriteria(TYPE_FULL_HOUSE, false);
            }
            else
                DoOpenDoor(GO_ORATORY_DOOR);
            break;
         case TYPE_FLIGHT_WAR:
            /*if (uiData == DONE && m_auiEncounter[TYPE_FLIGHT_WAR] != DONE) // add when implemented
            {
                if (GameObject* pChest = GetSingleGameObjectFromStorage(m_uiGunshipArmoryA_ID))
                {
                    if (pChest && !pChest->isSpawned())
                    {
                        pChest->SetRespawnTime(7*DAY);
                    }
                }
                if (GameObject* pChest = GetSingleGameObjectFromStorage(m_uiGunshipArmoryH_ID))
                {
                    if (pChest && !pChest->isSpawned())
                    {
                        pChest->SetRespawnTime(7*DAY);
                    }
                }
            }*/
            m_auiEncounter[TYPE_FLIGHT_WAR] = uiData;
            break;
         case TYPE_SAURFANG:
            m_auiEncounter[TYPE_SAURFANG] = uiData;

            if (uiData == DONE)
            {
                DoOpenDoor(GO_SAURFANG_DOOR);

                if (GameObject* pChest = GetSingleGameObjectFromStorage(m_uiSaurfangCache))
                {
                    if (pChest && !pChest->isSpawned())
                        pChest->SetRespawnTime(7*DAY);
                }
            }
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_IVE_MADE_AND_MESS, true);
            }
            break;
         case TYPE_FESTERGUT:
            m_auiEncounter[TYPE_FESTERGUT] = uiData;

            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_ROTFACE] == DONE)
                {
                    DoOpenDoor(GO_SCIENTIST_DOOR_COLLISION);
                }
                DoOpenDoor(GO_SCIENTIST_DOOR_ORANGE);
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_ORANGE_PLAGUE);
                SetSpecialAchievementCriteria(TYPE_FLU_SHORT_SHORTAGE, true);
            }
            else
                DoOpenDoor(GO_ORANGE_PLAGUE);
            break;
         case TYPE_ROTFACE:
            m_auiEncounter[TYPE_ROTFACE] = uiData;

            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_FESTERGUT] == DONE)
                {
                    DoOpenDoor(GO_SCIENTIST_DOOR_COLLISION);
                }
                DoOpenDoor(GO_SCIENTIST_DOOR_GREEN);
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_GREEN_PLAGUE);
                SetSpecialAchievementCriteria(TYPE_DANCES_WITH_OOZES, true);
            }
            else
                DoOpenDoor(GO_GREEN_PLAGUE);
            break;
         case TYPE_PUTRICIDE:
            m_auiEncounter[TYPE_PUTRICIDE] = uiData;

            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_SINDRAGOSA] == DONE &&
                    m_auiEncounter[TYPE_LANATHEL] == DONE)
                {
                    m_auiEncounter[TYPE_KINGS_OF_ICC] = DONE;
                }
            }
            if (uiData == IN_PROGRESS || uiData == SPECIAL)
            {
                DoCloseDoor(GO_SCIENTIST_DOOR);
                SetSpecialAchievementCriteria(TYPE_NAUSEA_HEATBURN_INDIGESTION, true);
            }
            else
                DoOpenDoor(GO_SCIENTIST_DOOR);
            break;
         case TYPE_BLOOD_COUNCIL:
            m_auiEncounter[TYPE_BLOOD_COUNCIL] = uiData;

            if (uiData == DONE)
            {
                DoOpenDoor(GO_COUNCIL_DOOR_1);
                DoOpenDoor(GO_COUNCIL_DOOR_2);
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_CRIMSON_HALL_DOOR);
                SetSpecialAchievementCriteria(TYPE_ORB_WHISPERER, true);
            }
            else
                DoOpenDoor(GO_CRIMSON_HALL_DOOR);
            break;
         case TYPE_LANATHEL:
            m_auiEncounter[TYPE_LANATHEL] = uiData;

            if (uiData == DONE)
            {
                DoOpenDoor(GO_ICECROWN_GRATE);

                if (m_auiEncounter[TYPE_PUTRICIDE] == DONE &&
                    m_auiEncounter[TYPE_SINDRAGOSA] == DONE)
                {
                    m_auiEncounter[TYPE_KINGS_OF_ICC] = DONE;
                }
            }
            if (uiData == IN_PROGRESS)
                DoCloseDoor(GO_BLOODPRINCE_DOOR);
            else
                DoOpenDoor(GO_BLOODPRINCE_DOOR);
            break;
         case TYPE_VALITHRIA:
            m_auiEncounter[TYPE_VALITHRIA] = uiData;

            if (uiData == DONE)
            {
                DoOpenDoor(GO_GREEN_DRAGON_DOOR_2);

                DoOpenDoor(GO_SINDRAGOSA_DOOR_1);
                DoOpenDoor(GO_SINDRAGOSA_DOOR_2);

                if (GameObject* pChest = GetSingleGameObjectFromStorage( m_uiValithriaCache))
                {
                    if (pChest && !pChest->isSpawned())
                        pChest->SetRespawnTime(7*DAY);
                }
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_GREEN_DRAGON_DOOR_1);
                DoOpenDoor(GO_VALITHRIA_DOOR_1);
                DoOpenDoor(GO_VALITHRIA_DOOR_2);

                if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL ||
                    instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                {
                    DoOpenDoor(GO_VALITHRIA_DOOR_3);
                    DoOpenDoor(GO_VALITHRIA_DOOR_4);
                }
                SetSpecialAchievementCriteria(TYPE_PORTAL_JOCKEY, false); // should be true when implemented
            }
            else
            {
                DoOpenDoor(GO_GREEN_DRAGON_DOOR_1);
                DoCloseDoor(GO_VALITHRIA_DOOR_1);
                DoCloseDoor(GO_VALITHRIA_DOOR_2);

                if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL ||
                    instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                {
                    DoCloseDoor(GO_VALITHRIA_DOOR_3);
                    DoCloseDoor(GO_VALITHRIA_DOOR_4);
                }
            }
            break;
         case TYPE_SINDRAGOSA:
            m_auiEncounter[TYPE_SINDRAGOSA] = uiData;

            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_PUTRICIDE] == DONE &&
                    m_auiEncounter[TYPE_LANATHEL] == DONE)
                {
                    m_auiEncounter[TYPE_KINGS_OF_ICC] = DONE;
                }
            }
            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_SINDRAGOSA_ICEWALL);
                SetSpecialAchievementCriteria(TYPE_ALL_YOU_CAN_EAT, true);
            }
            else
                DoOpenDoor(GO_SINDRAGOSA_ICEWALL);

            break;
         case TYPE_LICH_KING:
            m_auiEncounter[TYPE_LICH_KING] = uiData;
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_NECK_DEEP_IN_VILE, true);
                SetSpecialAchievementCriteria(TYPE_BEEN_WAITING_A_LONG_TIME, false);
            }
            break;
         case TYPE_FROSTMOURNE_ROOM:
             m_auiEncounter[TYPE_FROSTMOURNE_ROOM] = uiData;
             break;
         case TYPE_ICECROWN_QUESTS:
             m_auiEncounter[TYPE_ICECROWN_QUESTS] = uiData;
             break;
         case TYPE_STINKY:
             m_auiEncounter[TYPE_STINKY] = uiData;
             break;
         case TYPE_PRECIOUS:
             m_auiEncounter[TYPE_PRECIOUS] = uiData;
             break;
         case TYPE_SVALNA:
             m_auiEncounter[TYPE_SVALNA] = uiData;
             if (uiData == DONE)
                 DoOpenDoor(GO_GREEN_DRAGON_DOOR_1);
             break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            saveStream << m_auiEncounter[i] << " ";

        strSaveData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

uint32 instance_icecrown_citadel::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_TELEPORT:
        case TYPE_MARROWGAR:
        case TYPE_DEATHWHISPER:
        case TYPE_FLIGHT_WAR:
        case TYPE_SAURFANG:
        case TYPE_FESTERGUT:
        case TYPE_ROTFACE:
        case TYPE_PUTRICIDE:
        case TYPE_BLOOD_COUNCIL:
        case TYPE_LANATHEL:
        case TYPE_VALITHRIA:
        case TYPE_SINDRAGOSA:
        case TYPE_KINGS_OF_ICC:
        case TYPE_LICH_KING:
        case TYPE_FROSTMOURNE_ROOM:
        case TYPE_ICECROWN_QUESTS:
        case TYPE_SVALNA:
        case TYPE_STINKY:
        case TYPE_PRECIOUS:
            return m_auiEncounter[uiType];
    }
    return 0;
}

void instance_icecrown_citadel::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);

    for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
    {
        loadStream >> m_auiEncounter[i];

        if (m_auiEncounter[i] == IN_PROGRESS && i >= 1)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

bool instance_icecrown_citadel::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{
    switch (uiCriteriaId)
    {
    case CRITERIA_BONED_10N:
    case CRITERIA_BONED_25N:
    case CRITERIA_BONED_10H:
    case CRITERIA_BONED_25H:
        return m_abAchievCriteria[TYPE_BONED];
    case CRITERIA_FULL_HOUSE_10N:
    case CRITERIA_FULL_HOUSE_25N:
    case CRITERIA_FULL_HOUSE_10H:
    case CRITERIA_FULL_HOUSE_25H:
        return m_abAchievCriteria[TYPE_FULL_HOUSE];
    case CRITERIA_IVE_MADE_AND_MESS_10N:
    case CRITERIA_IVE_MADE_AND_MESS_10H:
    case CRITERIA_IVE_MADE_AND_MESS_25N:
    case CRITERIA_IVE_MADE_AND_MESS_25H:
        return m_abAchievCriteria[TYPE_IVE_MADE_AND_MESS];
    case CRITERIA_DANCES_WITH_OOZES_10N:
    case CRITERIA_DANCES_WITH_OOZES_25N:
    case CRITERIA_DANCES_WITH_OOZES_10H:
    case CRITERIA_DANCES_WITH_OOZES_25H:
        return m_abAchievCriteria[TYPE_DANCES_WITH_OOZES];
    case CRITERIA_FLU_SHORT_SHORTAGE_10N:
    case CRITERIA_FLU_SHORT_SHORTAGE_25N:
    case CRITERIA_FLU_SHORT_SHORTAGE_10H:
    case CRITERIA_FLU_SHORT_SHORTAGE_25H:
        return m_abAchievCriteria[TYPE_FLU_SHORT_SHORTAGE];
    case CRITERIA_NAUSEA_10N:
    case CRITERIA_NAUSEA_25N:
    case CRITERIA_NAUSEA_10H:
    case CRITERIA_NAUSEA_25H:
        return m_abAchievCriteria[TYPE_NAUSEA_HEATBURN_INDIGESTION];
    case CRITERIA_ORB_WHISPERER_10N:
    case CRITERIA_ORB_WHISPERER_25N:
    case CRITERIA_ORB_WHISPERER_10H:
    case CRITERIA_ORB_WHISPERER_25H:
        return m_abAchievCriteria[TYPE_ORB_WHISPERER];
    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10N:
        if (!pSource->HasAura(70867) && (Difficulty == RAID_DIFFICULTY_10MAN_NORMAL || Difficulty == RAID_DIFFICULTY_10MAN_HEROIC))
            return true;
        else
            return false;
        break;
    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25N:
        if (!pSource->HasAura(70867) && (Difficulty == RAID_DIFFICULTY_25MAN_NORMAL || Difficulty == RAID_DIFFICULTY_25MAN_HEROIC))
            return true;
        else
            return false;
        break;
    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10V:
        if (pSource->HasAura(70867) && (Difficulty == RAID_DIFFICULTY_10MAN_NORMAL || Difficulty == RAID_DIFFICULTY_10MAN_HEROIC))
            return true;
        else
            return false;
        break;
    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25V:
        if (pSource->HasAura(70867) && (Difficulty == RAID_DIFFICULTY_25MAN_NORMAL || Difficulty == RAID_DIFFICULTY_25MAN_HEROIC))
            return true;
        else
            return false;
        break;
    case CRITERIA_PORTAL_JOCKEY_10N:
    case CRITERIA_PORTAL_JOCKEY_25N:
    case CRITERIA_PORTAL_JOCKEY_10H:
    case CRITERIA_PORTAL_JOCKEY_25H:
        return m_abAchievCriteria[TYPE_PORTAL_JOCKEY];
    case CRITERIA_ALL_YOU_CAN_EAT_10N:
    case CRITERIA_ALL_YOU_CAN_EAT_25N:
    case CRITERIA_ALL_YOU_CAN_EAT_10H:
    case CRITERIA_ALL_YOU_CAN_EAT_25H:
        return m_abAchievCriteria[TYPE_ALL_YOU_CAN_EAT];
    case CRITERIA_BEEN_WAITING_10N:
    case CRITERIA_BEEN_WAITING_10H:
    case CRITERIA_BEEN_WAITING_25N:
    case CRITERIA_BEEN_WAITING_25H:
        return m_abAchievCriteria[TYPE_BEEN_WAITING_A_LONG_TIME];
    case CRITERIA_NECK_DEEP_IN_VILE_10N:
    case CRITERIA_NECK_DEEP_IN_VILE_10H:
    case CRITERIA_NECK_DEEP_IN_VILE_25N:
    case CRITERIA_NECK_DEEP_IN_VILE_25H:
        return m_abAchievCriteria[TYPE_NECK_DEEP_IN_VILE];
    default:
         return false;
    }
}

void instance_icecrown_citadel::SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet)
{
    if (uiType < MAX_SPECIAL_ACHIEV_CRITS)
        m_abAchievCriteria[uiType] = bIsMet;
}

InstanceData* GetInstanceData_instance_icecrown_citadel(Map* pMap)
{
    return new instance_icecrown_citadel(pMap);
}


void AddSC_instance_icecrown_citadel()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_icecrown_citadel";
    pNewScript->GetInstanceData = &GetInstanceData_instance_icecrown_citadel;
    pNewScript->RegisterSelf();
}

