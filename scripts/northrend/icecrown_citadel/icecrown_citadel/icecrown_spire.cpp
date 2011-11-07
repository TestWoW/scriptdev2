/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: icecrown_spire
SD%Complete: 100%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel - mobs
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"
enum
{
        SPELL_FROST_BREATH                      = 70116,
        SPELL_BLIZZARD                          = 70362,
        SPELL_CLEAVE                            = 70361,

        SPELL_STOMP                             = 64652,
        SPELL_DEATH_PLAGUE                      = 72865,
//        SPELL_DEATH_PLAGUE                      = 72879,

};

struct MANGOS_DLL_DECL mob_spire_frostwyrmAI : public BSWScriptedAI
{
    mob_spire_frostwyrmAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
        Reset();
    }

    ScriptedInstance *pInstance;
    uint8 stage;

    void Reset()
    {
        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
        m_creature->SetRespawnDelay(DAY);

        stage = 0;
        resetTimers();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);

        timedCast(SPELL_CLEAVE, diff);
        timedCast(SPELL_BLIZZARD, diff);
        timedCast(SPELL_FROST_BREATH, diff);

        DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_mob_spire_frostwyrm(Creature* pCreature)
{
    return new mob_spire_frostwyrmAI(pCreature);
}

struct MANGOS_DLL_DECL mob_frost_giantAI : public BSWScriptedAI
{
    mob_frost_giantAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;

    void Aggro(Unit *who)
    {
        if(pInstance) pInstance->SetData(TYPE_FLIGHT_WAR, IN_PROGRESS);
    }

    void JustDied(Unit *killer)
    {
        if(!pInstance)
            return;
        if (killer->GetTypeId() == TYPEID_PLAYER || killer->GetCharmerOrOwnerOrSelf()->GetTypeId() == TYPEID_PLAYER )
              pInstance->SetData(TYPE_FLIGHT_WAR, DONE);
    }

    void JustReachedHome()
    {
        if (pInstance)
            pInstance->SetData(TYPE_FLIGHT_WAR, FAIL);
    }

    void Reset()
    {
        m_creature->SetRespawnDelay(7*DAY);
        resetTimers();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        timedCast(SPELL_STOMP, diff);
        timedCast(SPELL_DEATH_PLAGUE, diff);

        DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_mob_frost_giant(Creature* pCreature)
{
    return new mob_frost_giantAI(pCreature);
}

void AddSC_icecrown_spire()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mob_spire_frostwyrm";
    newscript->GetAI = &GetAI_mob_spire_frostwyrm;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_frost_giant";
    newscript->GetAI = &GetAI_mob_frost_giant;
    newscript->RegisterSelf();
}

