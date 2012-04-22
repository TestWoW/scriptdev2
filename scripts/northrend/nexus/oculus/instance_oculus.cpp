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
SDName: instance_oculus
SD%Complete: 70%
SDComment:
SDAuthor: originally from TC, reworked by MaxXx2021 Aka Mioka, corrected by /dev/rsa
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

/* The Occulus encounters:
0 - Drakos the Interrogator
1 - Varos Cloudstrider
2 - Mage-Lord Urom
3 - Ley-Guardian Eregos */

instance_oculus::instance_oculus(Map* pMap) : ScriptedInstance(pMap)
{
    m_bIsRegularMode = pMap->IsRegularDifficulty();
    Initialize();
}

<<<<<<< HEAD
void instance_oculus::Initialize()
{
    for (uint8 i = 0; i < MAX_ENCOUNTERS+1; ++i)
        m_auiEncounter[i] = NOT_STARTED;

    m_auiEncounter[TYPE_ROBOTS] = 10;
    m_auiEncounter[TYPE_UROM_PHASE] = 0;
    m_bRubyDrake = true;
    m_bEmeraldDrake = true;
    m_bAmberDrake = true;

    m_auiEregosCache = m_bIsRegularMode ? GO_EREGOS_CACHE_H : GO_EREGOS_CACHE;
}

void instance_oculus::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_DRAGON_CAGE_DOOR:
        case GO_EREGOS_CACHE:
        case GO_EREGOS_CACHE_H:
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
       default:
            return;
    }
}

void instance_oculus::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_VAROS:
            pCreature->SetActiveObjectState(true);
            break;
        case NPC_EREGOS:
            if (GetData(TYPE_UROM) == DONE)
                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            else
                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            break;
        case NPC_UROM:
            if (GetData(TYPE_VAROS) == DONE)
                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            else
                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            break;
        case NPC_DRAKOS:
        case NPC_BELGARISTRASZ:
        case NPC_VERDISA:
        case NPC_ETERNOS:
        case NPC_BALGAR_IMAGE:
        case NPC_RUBY_DRAGON:
        case NPC_EMERALD_DRAGON:
        case NPC_AMBER_DRAGON:
            break;
    }
    m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
}

void instance_oculus::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_DRAKOS:
        case TYPE_VAROS:
        case TYPE_UROM:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_EREGOS:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                if (GameObject* pChest = GetSingleGameObjectFromStorage(m_auiEregosCache))
                {
                    if (pChest && !pChest->isSpawned())
                        pChest->SetRespawnTime(1*DAY);
                }
                /*DoRespawnGameObject(m_bIsRegularMode ? GO_EREGOS_CACHE : GO_EREGOS_CACHE_H, HOUR);
                DoRespawnGameObject(GO_SPOTLIGHT, HOUR);*/
            }
            break;
        case TYPE_ROBOTS:
            m_auiEncounter[uiType] = m_auiEncounter[uiType] - uiData;
            if(m_auiEncounter[uiType] == 0)
=======
instance_oculus::instance_oculus(Map* pMap) : ScriptedInstance(pMap)
{
    m_bIsRegularMode = pMap->IsRegularDifficulty();
    Initialize();
};


void instance_oculus::Initialize()
{
    for (uint8 i = 0; i < MAX_ENCOUNTERS+1; ++i)
        m_auiEncounter[i] = NOT_STARTED;

    m_auiEncounter[TYPE_ROBOTS] = 10;
    m_auiEncounter[TYPE_UROM_PHASE] = 0;
    for (uint8 i = 0; i < ACHIEV_COUNT; ++i)
        m_bAchievCriteria[i] = false;
}

void instance_oculus::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_DRAGON_CAGE_DOOR_1:
            break;
        case GO_DRAGON_CAGE_DOOR_2:
            break;
        case GO_DRAGON_CAGE_DOOR_3:
            break;
        default:
            return;
    }

    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_oculus::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_VAROS:
            pCreature->SetActiveObjectState(true);
        case NPC_TRIGGER:
        case NPC_ETERNOS:
        case NPC_VERDISA:
        case NPC_BELGAR:
        case NPC_DRAKOS:
        case NPC_UROM:
        case NPC_EREGOS:
        case NPC_BALGAR_IMAGE:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}

bool instance_oculus::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{
    switch (uiCriteriaId)
    {
        case ACHIEV_CRITERIA_RUBY_VOID:
            return m_bAchievCriteria[ACHIEV_RUBY_VOID];
        case ACHIEV_CRITERIA_EMERALD_VOID:
            return m_bAchievCriteria[ACHIEV_EMERALD_VOID];
        case ACHIEV_CRITERIA_AMBER_VOID:
            return m_bAchievCriteria[ACHIEV_AMBER_VOID];
        default:
            return false;
    }
}

void instance_oculus::SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet)
{
    if (uiType < ACHIEV_COUNT)
        m_bAchievCriteria[uiType] = bIsMet;
}

void instance_oculus::SetData(uint32 type, uint32 data)
{
    switch(type)
    {
        case TYPE_DRAKOS:
            m_auiEncounter[type] = data;
            if (data == IN_PROGRESS)
                DoStartTimedAchievement(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, ACHIEV_START_EREGOS_ID);
            break;
        case TYPE_VAROS:
        case TYPE_UROM:
            m_auiEncounter[type] = data;
            break;
        case TYPE_EREGOS:
            m_auiEncounter[type] = data;
            if (data == DONE)
            {
                DoRespawnGameObject(m_bIsRegularMode ? GO_EREGOS_CACHE : GO_EREGOS_CACHE_H, HOUR);
                DoRespawnGameObject(GO_SPOTLIGHT, HOUR);
            }
            break;
        case TYPE_ROBOTS:
            m_auiEncounter[type] = m_auiEncounter[type] - data;
            if(m_auiEncounter[type] == 0)
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
            {
                if(Creature* pVaros = GetSingleCreatureFromStorage(NPC_VAROS))
                {
                    DoScriptText(SAY_VAROS_SPAWN, pVaros);
                    pVaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pVaros->InterruptNonMeleeSpells(false);
                    pVaros->RemoveAurasDueToSpell(50053);
                }
            }
<<<<<<< HEAD
            uiData = NOT_STARTED;
            break;
        case TYPE_UROM_PHASE:
            m_auiEncounter[uiType] = uiData;
            uiData = NOT_STARTED;
            break;
        case TYPE_RUBY_VOID:
            m_bRubyDrake = (uiData == FAIL);
            break;
        case TYPE_EMERALD_VOID:
            m_bEmeraldDrake = (uiData == FAIL);
            break;
        case TYPE_AMBER_VOID:
            m_bAmberDrake = (uiData == FAIL);
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

=======
            data = NOT_STARTED;
            break;
        case TYPE_UROM_PHASE:
            m_auiEncounter[type] = data;
            data = NOT_STARTED;
            break;
        default:
            return;
    }

    if (data == DONE)
    {
        OUT_SAVE_INST_DATA;
        std::ostringstream saveStream;
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
        for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            saveStream << m_auiEncounter[i] << " ";

        strSaveData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

<<<<<<< HEAD
uint32 instance_oculus::GetData(uint32 uiType)
{
    switch(uiType)
=======
uint32 instance_oculus::GetData(uint32 type)
{
    switch(type)
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
    {
        case TYPE_DRAKOS:
        case TYPE_VAROS:
        case TYPE_UROM:
        case TYPE_EREGOS:
        case TYPE_ROBOTS:
        case TYPE_UROM_PHASE:
<<<<<<< HEAD
            return m_auiEncounter[uiType];
=======
            return m_auiEncounter[type];
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
        default:
            return 0;
    }
    return 0;
}

<<<<<<< HEAD
bool instance_oculus::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1)
{
    switch(uiCriteriaId)
    {
        /*case ACHIEV_CRITERIA_RUBY_VOID:
            return !m_bRubyDrake;
        case ACHIEV_CRITERIA_EMERALD_VOID:
            return !m_bEmeraldDrake;
        case ACHIEV_CRITERIA_AMBER_VOID:
            return !m_bAmberDrake;*/
        default:
            return false;
    }
=======
const char* instance_oculus::Save()
{
    return strSaveData.c_str();
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
}

void instance_oculus::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }
<<<<<<< HEAD

    OUT_LOAD_INST_DATA(chrIn);

=======

    OUT_LOAD_INST_DATA(chrIn);
>>>>>>> 646140f9a30397c365fa502673f52897c3be977e
    std::istringstream loadStream(chrIn);

    for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
    {
        loadStream >> m_auiEncounter[i];

        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    m_auiEncounter[TYPE_ROBOTS] = 10;
    m_auiEncounter[TYPE_UROM_PHASE] = 0;

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_oculus(Map* pMap)
{
    return new instance_oculus(pMap);
}

void AddSC_instance_oculus()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_oculus";
    pNewScript->GetInstanceData = &GetInstanceData_instance_oculus;
    pNewScript->RegisterSelf();
}
