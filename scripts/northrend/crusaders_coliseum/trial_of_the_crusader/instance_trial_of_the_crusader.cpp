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
SDName: instance_trial_of_the_crusader
SD%Complete: 80%
SDComment: by /dev/rsa
SDCategory: Trial of the Crusader
EndScriptData */

#include "precompiled.h"
#include "trial_of_the_crusader.h"

    instance_trial_of_the_crusader::instance_trial_of_the_crusader(Map* pMap) : BSWScriptedInstance(pMap)
    {
        Difficulty = pMap->GetDifficulty();
        Initialize();
    }

    void instance_trial_of_the_crusader::Initialize()
    {
        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            m_auiEncounter[i] = NOT_STARTED;

        for (uint8 i = 0; i < MAX_SPECIAL_ACHIEV_CRITS; ++i)
            m_bAchievCriteria[i] = false;

        m_auiEncounter[0] = 0;
        m_auiEncounter[7] = 50;
        m_auiEncounter[8] = 0;

        m_auiNorthrendBeasts = NOT_STARTED;
        m_auiEventTimer = 1000;
        m_auiCrusadersCount = 6;
        needsave = false;
    }

    bool instance_trial_of_the_crusader::IsEncounterInProgress() const
    {
        for(uint8 i = 1; i < MAX_ENCOUNTERS-2 ; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;

        return false;
    }

    void instance_trial_of_the_crusader::OnPlayerEnter(Player *m_player)
    {
        if (Difficulty == RAID_DIFFICULTY_10MAN_HEROIC || Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
        {
            m_player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW, 1);
            m_player->SendUpdateWorldState(UPDATE_STATE_UI_COUNT, GetData(TYPE_COUNTER));
        }
    }

    bool instance_trial_of_the_crusader::IsRaidWiped()
    {
        Map::PlayerList const &players = instance->GetPlayers();

        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
        {
            if(Player* pPlayer = i->getSource())
            {
                if (pPlayer->isAlive())
                    return false;
            }
        }
        return true;
    }

    void instance_trial_of_the_crusader::OnCreatureCreate(Creature* pCreature)
    {
        if (!pCreature)
            return;
        m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
    }

    void instance_trial_of_the_crusader::OnObjectCreate(GameObject *pGo)
    {
        if (!pGo)
            return;
        m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
    }

    bool instance_trial_of_the_crusader::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
    {
        switch (uiCriteriaId)
        {
            case CRITERIA_ACHIEV_GORMOK_10:
            case CRITERIA_ACHIEV_GORMOK_25:
                 return m_bAchievCriteria[TYPE_ACHIEV_GORMOK];
            case CRITERIA_ACHIEV_JORMUNGAR_10:
            case CRITERIA_ACHIEV_JORMUNGAR_25:
                 return m_bAchievCriteria[TYPE_ACHIEV_JORMUNGAR];
            case CRITERIA_ACHIEV_JARAXXUS_10:
            case CRITERIA_ACHIEV_JARAXXUS_25:
                 return m_bAchievCriteria[TYPE_ACHIEV_JARAXXUS];
            case CRITERIA_ACHIEV_CHAMPIONS_10:
            case CRITERIA_ACHIEV_CHAMPIONS_25:
                 return m_bAchievCriteria[TYPE_ACHIEV_CHAMPIONS];
            case CRITERIA_ACHIEV_CHAMPIONS_KILL_10:
            case CRITERIA_ACHIEV_CHAMPIONS_KILL_25:
            case CRITERIA_ACHIEV_CHAMPIONS_KILL_10H:
            case CRITERIA_ACHIEV_CHAMPIONS_KILL_25H:
                 return m_bAchievCriteria[TYPE_ACHIEV_CHAMPIONS_KILL];
            case CRITERIA_ACHIEV_VALKYRS_10:
            case CRITERIA_ACHIEV_VALKYRS_25:
                 return m_bAchievCriteria[TYPE_ACHIEV_VALKYRS];
            default:
                 return false;
        }
    }

    void instance_trial_of_the_crusader::SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet)
    {
        if (uiType < MAX_SPECIAL_ACHIEV_CRITS)
            m_bAchievCriteria[uiType] = bIsMet;
    }

    void instance_trial_of_the_crusader::SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
        case TYPE_STAGE:
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_BEASTS:
            m_auiEncounter[1] = uiData;
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_GORMOK, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_JORMUNGAR, true);
            }
            break;
        case TYPE_JARAXXUS:
            m_auiEncounter[2] = uiData;
            if (uiData == IN_PROGRESS)
                SetSpecialAchievementCriteria(TYPE_ACHIEV_JARAXXUS, true);
            break;
        case TYPE_CRUSADERS:
            if (uiData == FAIL && (m_auiEncounter[3] == FAIL || m_auiEncounter[3] == NOT_STARTED))
                m_auiEncounter[3] = NOT_STARTED;
            else
                m_auiEncounter[3] = uiData;
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_CHAMPIONS, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_CHAMPIONS_KILL, true);
            }
            if (uiData == DONE)
            {
                uint32 uiCacheEntry = GO_CRUSADERS_CACHE_10;

                switch (instance->GetDifficulty())
                {
                case RAID_DIFFICULTY_10MAN_HEROIC:
                    uiCacheEntry = GO_CRUSADERS_CACHE_10_H;
                    break;
                case RAID_DIFFICULTY_25MAN_NORMAL:
                    uiCacheEntry = GO_CRUSADERS_CACHE_25;
                    break;
                case RAID_DIFFICULTY_25MAN_HEROIC:
                    uiCacheEntry = GO_CRUSADERS_CACHE_25_H;
                    break;
                }
                if (GameObject* pChest = GetSingleGameObjectFromStorage(uiCacheEntry))
                    if (!pChest->isSpawned())
                        pChest->SetRespawnTime(7*DAY);
            };
            break;
        case TYPE_CRUSADERS_COUNT:
            if (uiData == 0)
                --m_auiCrusadersCount;
            else
                m_auiCrusadersCount = uiData;
            break;
        case TYPE_VALKIRIES:
            if (m_auiEncounter[4] == SPECIAL && uiData == SPECIAL)
                uiData = DONE;
            m_auiEncounter[4] = uiData;
            if (uiData == IN_PROGRESS)
                SetSpecialAchievementCriteria(TYPE_ACHIEV_VALKYRS, true);
            break;
        case TYPE_LICH_KING:
            m_auiEncounter[5] = uiData;
            break;
        case TYPE_ANUBARAK:
            m_auiEncounter[6] = uiData;

            if (uiData == IN_PROGRESS)
            {
                DoCloseDoor(GO_WEB_DOOR);
            }
            else
                DoOpenDoor(GO_WEB_DOOR);

            if (uiData == DONE)
            {
                if (Difficulty == RAID_DIFFICULTY_10MAN_HEROIC)
                {
                    if (m_auiEncounter[7] >= 25)
                        m_uiTributeChest1 = GO_TRIBUTE_CHEST_10H_25;
                    if (m_auiEncounter[7] >= 45)
                        m_uiTributeChest2 = GO_TRIBUTE_CHEST_10H_45;
                    if (m_auiEncounter[7] >= 49)
                        m_uiTributeChest3 = GO_TRIBUTE_CHEST_10H_50;
                    m_uiTributeChest4 = GO_TRIBUTE_CHEST_10H_99;
                }
                if (Difficulty == RAID_DIFFICULTY_25MAN_HEROIC)
                {
                    if (m_auiEncounter[7] >= 25)
                        m_uiTributeChest1 = GO_TRIBUTE_CHEST_25H_25;
                    if (m_auiEncounter[7] >= 45)
                        m_uiTributeChest2 = GO_TRIBUTE_CHEST_25H_45;
                    if (m_auiEncounter[7] >= 49)
                        m_uiTributeChest3 = GO_TRIBUTE_CHEST_25H_50;
                    m_uiTributeChest4 = GO_TRIBUTE_CHEST_25H_99;
                }
                // Attention! It is (may be) not off-like, but  spawning all Tribute Chests is real
                // reward for clearing TOC instance
                if (m_uiTributeChest1)
                  if (GameObject* pChest1 = GetSingleGameObjectFromStorage(m_uiTributeChest1))
                    if (pChest1 && !pChest1->isSpawned())
                        pChest1->SetRespawnTime(7*DAY);

                if (m_uiTributeChest2)
                  if (GameObject* pChest2 = GetSingleGameObjectFromStorage(m_uiTributeChest2))
                    if (pChest2 && !pChest2->isSpawned())
                        pChest2->SetRespawnTime(7*DAY);

                if (m_uiTributeChest3)
                  if (GameObject* pChest3 = GetSingleGameObjectFromStorage(m_uiTributeChest3))
                    if (pChest3 && !pChest3->isSpawned())
                        pChest3->SetRespawnTime(7*DAY);

                if (m_uiTributeChest4)
                  if (GameObject* pChest4 = GetSingleGameObjectFromStorage(m_uiTributeChest4))
                    if (pChest4 && !pChest4->isSpawned())
                        pChest4->SetRespawnTime(7*DAY);
            };
            break;
        case TYPE_COUNTER:
            m_auiEncounter[7] = uiData;
            uiData = DONE;
            break;
        case TYPE_EVENT:
            m_auiEncounter[8] = uiData;
            uiData = NOT_STARTED;
            break;
        case TYPE_EVENT_TIMER:
            m_auiEventTimer = uiData;
            uiData = NOT_STARTED;
            break;
        case TYPE_NORTHREND_BEASTS:
            m_auiNorthrendBeasts = uiData;
            break;
        case DATA_HEALTH_FJOLA:
            m_uiDataDamageFjola = uiData; uiData = NOT_STARTED;
            break;
        case DATA_HEALTH_EYDIS:
            m_uiDataDamageEydis = uiData; uiData = NOT_STARTED;
            break;
        case DATA_CASTING_VALKYRS:
            m_uiValkyrsCasting = uiData; uiData = NOT_STARTED;
            break;
        }

        if (IsEncounterInProgress()) 
        {
            DoCloseDoor(GO_WEST_PORTCULLIS);
            DoCloseDoor(GO_NORTH_PORTCULLIS);
            DoCloseDoor(GO_SOUTH_PORTCULLIS);

            if (Creature* pBarrent = GetSingleCreatureFromStorage(NPC_BARRENT)) 
                pBarrent->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        else
        {
            DoOpenDoor(GO_WEST_PORTCULLIS);
            DoCloseDoor(GO_NORTH_PORTCULLIS);
            DoCloseDoor(GO_SOUTH_PORTCULLIS);

            if (Creature* pBarrent = GetSingleCreatureFromStorage(NPC_BARRENT)) 
                pBarrent->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        };

        if (uiData == FAIL && uiType != TYPE_STAGE && uiType != TYPE_EVENT && uiType != TYPE_COUNTER && uiType != TYPE_EVENT_TIMER)
        {
            if (IsRaidWiped())
            {
                --m_auiEncounter[7];
                needsave = true;
            }
            uiData = NOT_STARTED;
        }

        if ((uiData == DONE && uiType != TYPE_STAGE && uiType != TYPE_EVENT && uiType != TYPE_EVENT_TIMER) || needsave == true)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;

            for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                saveStream << m_auiEncounter[i] << " ";

            m_strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
            needsave = false;
        }
    }

    uint32 instance_trial_of_the_crusader::GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_STAGE:     return m_auiEncounter[0];
            case TYPE_BEASTS:    return m_auiEncounter[1];
            case TYPE_JARAXXUS:  return m_auiEncounter[2];
            case TYPE_CRUSADERS: return m_auiEncounter[3];
            case TYPE_VALKIRIES: return m_auiEncounter[4];
            case TYPE_LICH_KING: return m_auiEncounter[5];
            case TYPE_ANUBARAK:  return m_auiEncounter[6];
            case TYPE_COUNTER:   return m_auiEncounter[7];
            case TYPE_EVENT:     return m_auiEncounter[8];
            case TYPE_DIFFICULTY:   return Difficulty;
            case TYPE_NORTHREND_BEASTS:    return m_auiNorthrendBeasts;
            case TYPE_EVENT_TIMER:  return m_auiEventTimer;
            case TYPE_CRUSADERS_COUNT:  return m_auiCrusadersCount;
            case TYPE_EVENT_NPC: switch (m_auiEncounter[8]) 
                                 {
                                 case 110:
                                 case 115:
                                 case 116:
                                 case 140:
                                 case 150:
                                 case 200:
                                 case 205:
                                 case 210:
                                 case 300:
                                 case 305:
                                 case 310:
                                 case 400:
                                 case 666:
                                 case 1010:
                                 case 1180:
                                 case 1999:
                                 case 2000:
                                 case 2030:
                                 case 3000:
                                 case 3001:
                                 case 3060:
                                 case 3061:
                                 case 3090:
                                 case 3091:
                                 case 3100:
                                 case 3110:
                                 case 4000:
                                 case 4010:
                                 case 4015:
                                 case 4040:
                                 case 4050:
                                 case 5000:
                                 case 5005:
                                 case 5020:
                                 case 6000:
                                 case 6005:
                                 case 6010:
                                 m_auiEventNPCId = NPC_TIRION;
                                 break;

                                 case 5010:
                                 case 5030:
                                 case 5040:
                                 case 5050:
                                 case 5060:
                                 case 5070:
                                 case 5080:
                                 m_auiEventNPCId = NPC_LICH_KING_1;
                                 break;

                                 case 130:
                                 case 2020:
                                 case 3080:
                                 case 3051:
                                 case 3071:
                                 case 4020:
                                 m_auiEventNPCId = NPC_RINN;
                                 break;

                                 case 120:
                                 case 2010:
                                 case 3050:
                                 case 3070:
                                 case 3081:
                                 case 4030:
                                 m_auiEventNPCId = NPC_GARROSH;
                                 break;

                                 case 1110:
                                 case 1120:
                                 case 1130:
                                 case 1132:
                                 case 1134:
                                 case 1135:
                                 case 1140:
                                 case 1142:
                                 case 1144:
                                 case 1145:
                                 case 1150:
                                 case 1160:
                                 case 1170:
                                 m_auiEventNPCId = NPC_FIZZLEBANG;
                                 break;

                                 default:
                                 m_auiEventNPCId = NPC_TIRION;
                                 break;

                                 };
                                 return m_auiEventNPCId;

        case DATA_HEALTH_FJOLA: return m_uiDataDamageFjola;
        case DATA_HEALTH_EYDIS: return m_uiDataDamageEydis;
        case DATA_CASTING_VALKYRS: return m_uiValkyrsCasting;
        }
        return 0;
    }

    void instance_trial_of_the_crusader::Load(const char* strIn)
    {
        if (!strIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(strIn);

        std::istringstream loadStream(strIn);

        for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
        {
            loadStream >> m_auiEncounter[i];

            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }
        m_auiEncounter[TYPE_EVENT] = 0;
        m_auiEncounter[TYPE_STAGE] = 0;

        OUT_LOAD_INST_DATA_COMPLETE;

    }


InstanceData* GetInstanceData_instance_trial_of_the_crusader(Map* pMap)
{
    return new instance_trial_of_the_crusader(pMap);
}

void AddSC_instance_trial_of_the_crusader()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_trial_of_the_crusader";
    pNewScript->GetInstanceData = &GetInstanceData_instance_trial_of_the_crusader;
    pNewScript->RegisterSelf();
}
