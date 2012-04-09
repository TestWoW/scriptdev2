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
SDName: Instance The Violet Hold
SD%Complete: 60%
SDComment:
SDCategory: The Violet Hold
EndScriptData */

#include "precompiled.h"
#include "violet_hold.h"

/* The Violet Hold encounters:
0 Whole Event
1 Rift
2 Erekem
3 Moragg
4 Ichoron
5 Xevozz
6 Lavanthor
7 Zuramat
*/
//inline uint32 RandRiftBoss() { return ((rand()%2) ? NPC_GUARDIAN : NPC_KEEPER); }

instance_violet_hold::instance_violet_hold(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_violet_hold::Initialize()
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            m_auiEncounter[i] = NOT_STARTED;

        Clear();
    }

void instance_violet_hold::Clear()
{
    bIsInBoss = false;

    m_uiLastBossID = 0;
    m_uiRiftPortalCount = 0;
    m_uiPortalTime = 0;
    m_uiShieldPercent = 100;
}

void instance_violet_hold::InitWorldState(bool Enable = true)
{
    DoUpdateWorldState(WORLD_STATE_VH,Enable ? 1 : 0);
    DoUpdateWorldState(WORLD_STATE_VH_PRISON,100);
    DoUpdateWorldState(WORLD_STATE_VH_PORTALS,0);
}

void instance_violet_hold::OnPlayerEnter(Player* pPlayer)
{
    if(m_auiEncounter[0] != NOT_STARTED)
        pPlayer->SendUpdateWorldState(WORLD_STATE_VH,1);
}

bool instance_violet_hold::IsEncounterInProgress() const
{
    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS)
            return true;

    return false;
}

void instance_violet_hold::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_SINCLARI:
        case NPC_DOOR_SEAL:
        case NPC_EREKEM:
        case NPC_MORAGG:
        case NPC_ICHORON:
        case NPC_XEVOZZ:
        case NPC_LAVANTHOR:
        case NPC_ZURAMAT:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}

void instance_violet_hold::OnObjectCreate(GameObject* pGo)
{
    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_violet_hold::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_EVENT:
            if (uiData == IN_PROGRESS)
            {
                Clear();
                InitWorldState();
            }
            else if (uiData == FAIL || uiData == DONE)
            {
                DoUpdateWorldState(WORLD_STATE_VH, 0);
                DoUseDoorOrButton(GO_DOOR_SEAL);
                if (Creature* pSinclari = GetSingleCreatureFromStorage(NPC_SINCLARI))
                    pSinclari->ForcedDespawn(1000);
            }
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_EREKEM:
            m_auiEncounter[2] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_MORAGG:
            m_auiEncounter[3] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_ICHORON:
            m_auiEncounter[4] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_XEVOZZ:
            m_auiEncounter[5] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_LAVANTHOR:
            m_auiEncounter[6] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_ZURAMAT:
            m_auiEncounter[7] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_CYANIGOSA:
            m_auiEncounter[8] = uiData;
            if (uiData == IN_PROGRESS) bIsInBoss = true;
            break;
        case TYPE_PORTAL6:
            m_auiEncounter[9] = uiData;
            break;
        case TYPE_PORTAL12:
            m_auiEncounter[10] = uiData;
            break;
        case TYPE_RIFT:
            if (uiData == FAIL)
               DoUseDoorOrButton(GO_DOOR_SEAL);
            m_auiEncounter[1] = uiData;
            break;
        case TYPE_DOOR:
            if (uiData == SPECIAL)
            {
                m_uiShieldPercent = m_uiShieldPercent - 5;
                if(m_uiShieldPercent > 0)
                    DoUpdateWorldState(WORLD_STATE_VH_PRISON, m_uiShieldPercent);
                else
                {   DoUpdateWorldState(WORLD_STATE_VH, 0);
                    DoUseDoorOrButton(GO_DOOR_SEAL);
                    m_auiEncounter[0] = FAIL;
                }
            }
            break;
        case TYPE_DISRUPTIONS:
        m_uiDisruptions = uiData;
//            DoUpdateWorldState(WORLD_STATE_VH_PRISON, 100-m_uiDisruptions*5);
        break;
        case TYPE_LASTBOSS_ID:
        m_uiLastBossIDConst = uiData;
        break;
        case TYPE_ACHIEV_ZURAMAT:
        m_bCriteriaDanceWithVoidFailed = (uiData == FAIL);
        return;
        case TYPE_ACHIEV_ICHORON:
        m_bCriteriaDeshidratationFailed = (uiData == FAIL);
        return;
    }
    if (uiData == DONE)
    {
        bIsInBoss = false;
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            saveStream << m_auiEncounter[i] << " ";

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }

}

uint32 instance_violet_hold::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_EVENT:
            return m_auiEncounter[TYPE_EVENT];
        case TYPE_EREKEM:
            return m_auiEncounter[TYPE_EREKEM];
        case TYPE_MORAGG:
            return m_auiEncounter[TYPE_MORAGG];
        case TYPE_ICHORON:
            return m_auiEncounter[TYPE_ICHORON];
        case TYPE_XEVOZZ:
            return m_auiEncounter[TYPE_XEVOZZ];
        case TYPE_LAVANTHOR:
            return m_auiEncounter[TYPE_LAVANTHOR];
        case TYPE_ZURAMAT:
            return m_auiEncounter[TYPE_ZURAMAT];
        case TYPE_CYANIGOSA:
            return m_auiEncounter[TYPE_CYANIGOSA];
        case TYPE_PORTAL6:
            return m_auiEncounter[TYPE_PORTAL6];
        case TYPE_PORTAL12:
            return m_auiEncounter[TYPE_PORTAL12];
        case TYPE_RIFT:
            return m_uiRiftPortalCount;
        case TYPE_LASTBOSS_ID:
            return m_uiLastBossIDConst;
        case TYPE_LASTBOSS:
        {
            if (m_uiLastBossID == 0)
                m_uiLastBossID = urand(2, 7);
            else
            {
                m_uiLastBossID = urand(2, 7);
                if ( m_auiEncounter[TYPE_EREKEM] == DONE &&
                     m_auiEncounter[TYPE_MORAGG] == DONE &&
                     m_auiEncounter[TYPE_ICHORON] == DONE &&
                     m_auiEncounter[TYPE_XEVOZZ] == DONE &&
                     m_auiEncounter[TYPE_LAVANTHOR] == DONE &&
                     m_auiEncounter[TYPE_ZURAMAT] == DONE) return 0;
                while ( m_auiEncounter[m_uiLastBossID] == DONE
                        || m_auiEncounter[m_uiLastBossID] == IN_PROGRESS
                        || m_auiEncounter[m_uiLastBossID] == SPECIAL )
                    {
                        m_uiLastBossID = urand(2, 7);
                    }
            }
            return m_uiLastBossID;
        }
        case DATA_BOSSTIME:
            return bIsInBoss;
        case TYPE_DISRUPTIONS:
            return m_uiDisruptions;
    }
    return 0;
}

bool instance_violet_hold::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{
    switch (uiCriteriaId)
    {
        case ACHIEV_DEHYDRATATION:
            return !m_bCriteriaDeshidratationFailed;
        case ACHIEV_VOID_DANCE:
            return !m_bCriteriaDanceWithVoidFailed;
        case ACHIEV_DEFENSELESS:
            return !instance->IsRegularDifficulty() && m_uiShieldPercent >= 100;
        default:
            return false;
    }
}
void instance_violet_hold::Load(const char* strIn)
{
    if (!strIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(strIn);

    std::istringstream loadStream(strIn);

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        loadStream >> m_auiEncounter[i];

        if (m_auiEncounter[i] == IN_PROGRESS && i != 1)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_violet_hold(Map* pMap)
{
    return new instance_violet_hold(pMap);
}

void AddSC_instance_violet_hold()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_violet_hold";
    newscript->GetInstanceData = &GetInstanceData_instance_violet_hold;
    newscript->RegisterSelf();
}
