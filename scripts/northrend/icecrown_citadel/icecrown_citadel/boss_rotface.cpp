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
SDName: boss_rotface
SD%Complete: 99%
SDComment:
SDCategory: Icecrown Citadel
EndScriptData */

// Precious scripted by Walkum. Zombies repaired by Walkum. Decimate & Plague Stench repaired by Carlos93.

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    SPELL_BERSERK               = 47008,

    // Precious
    SPELL_PRECIOUS_DECIMATE     = 71123,
    SPELL_PRECIOUS_MORTALWOUND  = 71127,
    NPC_ZOMBIE                  = 38104,

    // Mutated Infection
    SPELL_MUTATED_INFECTION_1   = 70090, // periodic trigger auras
    SPELL_MUTATED_INFECTION_2   = 70003,
    SPELL_MUTATED_INFECTION_3   = 70004,
    SPELL_MUTATED_INFECTION_4   = 70005,
    SPELL_MUTATED_INFECTION_5   = 70006,

    // Slime Spray
    SPELL_SLIME_SPRAY_SUMMON    = 70882,
    SPELL_SLIME_SPRAY           = 69508,

    // Ooze Flood
    SPELL_OOZE_FLOOD_PERIODIC   = 70069, // periodically trigger ooze flood
    SPELL_OOZE_FLOOD_REMOVE     = 70079,
    SPELL_OOZE_FLOOD_VISUAL     = 69785,
    SPELL_OOZE_FLOOD_DAMAGE     = 69788,
    SPELL_OOZE_FLOOD_1          = 69783,

    // Little Ooze
    SPELL_STICKY_OOZE           = 69774,
    SPELL_STICKY_AURA           = 69776,
    SPELL_WEAK_RADIATING_OOZE   = 69750,
    SPELL_LITTLE_OOZE_COMBINE   = 69537, // periodic check
    SPELL_MERGE                 = 69889,

    // Big Ooze
    SPELL_UNSTABLE_OOZE         = 69558, // stacking buff
    SPELL_RADIATING_OOZE        = 69760,
    SPELL_BIG_OOZE_COMBINE      = 69552, // periodic check
    SPELL_BIG_OOZE_BUFF_COMB    = 69611, // periodic check
    SPELL_BIG_OOZE_EXPLOSION    = 69839, // area trigger
    SPELL_BIG_OOZE_EXPLOSION_1  = 69833, // damage

    // Vile Gas (heroic)
    SPELL_VILE_GAS_SUMMON       = 72288,
    SPELL_VILE_GAS_SUMMON_TRIG  = 72287,
    SPELL_VILE_GAS              = 71307,
    SPELL_VILE_GAS_TRIGGERED    = 72272,
};

static uint32 uiMutatedInfections[5] =
{
    SPELL_MUTATED_INFECTION_1,
    SPELL_MUTATED_INFECTION_2,
    SPELL_MUTATED_INFECTION_3,
    SPELL_MUTATED_INFECTION_4,
    SPELL_MUTATED_INFECTION_5
};

//talks
enum
{
    SAY_PRECIOUS_ZOMBIES        = -1631193,
    SAY_PRECIOUS_DIES           = -1631070,
    SAY_AGGRO                   = -1631071,
    SAY_SLIME_SPRAY             = -1631072,
    SAY_OOZE_EXPLODE            = -1631073,
    SAY_SLIME_FLOW_1            = -1631074,
    SAY_SLIME_FLOW_2            = -1631075,
    SAY_SLAY_1                  = -1631076,
    SAY_SLAY_2                  = -1631077,
    SAY_BERSERK                 = -1631078,
    SAY_DEATH                   = -1631079,
};

static Locations SpawnLoc[]=
{
    {4322.85f, 3164.17f, 389.40f, 3.76f},                       // festergut side
    {4311.91f, 3157.42f, 389.00f, 3.62f},                       // hacky (LoS problems?) festergut side
    {4391.38f, 3163.71f, 389.40f, 5.80f},                       // rotface side
    {4417.087891f, 3108.290283f, 360.46f, 5.8f},                // SouthWest
    {4419.419922f, 3164.149902f, 360.46f, 5.8f},                // NorthWest
    {4471.930176f, 3163.899902f, 360.46f, 5.8f},                // NorthEast
    {4472.549805f, 3110.770020f, 360.46f, 5.8f},                // SouthEast
};
// Rotface
struct MANGOS_DLL_DECL boss_rotfaceAI : public base_icc_bossAI
{
    boss_rotfaceAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiSlimeSprayTimer;
    uint32 m_uiMutatedInfectionTimer;
    uint32 m_uiInfectionsRate;
    uint32 m_uiVileGasTimer;
    uint32 m_uiSlimeFlowTimer;
    uint32 m_uiTurnTimer;

    void Reset()
    {
        m_uiSlimeSprayTimer = urand(17000, 23000);
        m_uiVileGasTimer = 20000;
        //m_uiMutatedInfectionTimer = 50000;
        //m_uiInfectionsRate = 1;
        m_uiSlimeFlowTimer = 20000;
        m_uiTurnTimer = 0;
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ROTFACE, IN_PROGRESS);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
            {
                pProfessor->NearTeleportTo(SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, SpawnLoc[2].o);
                pProfessor->SetInCombatWithZone();
            }
        }

        DoScriptText(SAY_AGGRO, m_creature);

        DoCastSpellIfCan(m_creature, SPELL_MUTATED_INFECTION_1, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_OOZE_FLOOD_PERIODIC, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ROTFACE, FAIL);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                pProfessor->AI()->EnterEvadeMode();
        }

        DoCastSpellIfCan(m_creature, SPELL_OOZE_FLOOD_REMOVE, CAST_TRIGGERED);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_SLAY_1 - urand(0,1), m_creature, pVictim);
    }

    void JustDied(Unit *pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ROTFACE, DONE);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                pProfessor->AI()->EnterEvadeMode();
        }

        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTurnTimer > uiDiff)
        {
            Unit *pFocus = m_pInstance->GetSingleCreatureFromStorage(NPC_OOZE_SPRAY_STALKER);
            if (pFocus)
                m_creature->SetFacingToObject(pFocus);
            else if (!pFocus)
                m_creature->InterruptNonMeleeSpells(true);

            m_uiTurnTimer -= uiDiff;
            return;
        }

        // Slime Spray
        if (m_uiSlimeSprayTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SLIME_SPRAY_SUMMON, CAST_TRIGGERED) == CAST_OK)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_SLIME_SPRAY) == CAST_OK)
                {
                    DoScriptText(SAY_SLIME_SPRAY, m_creature);
                    m_uiSlimeSprayTimer = 20000;
                    m_uiTurnTimer = 8000;
                    return;
                }
            }
        }
        else
            m_uiSlimeSprayTimer -= uiDiff;

        // Mutated Infection - faster with time
        // implemented this instead of phases
        /*if (m_uiInfectionsRate < 5)
        {
            if (m_uiMutatedInfectionTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, uiMutatedInfections[m_uiInfectionsRate], CAST_TRIGGERED) == CAST_OK)
                {
                    m_uiMutatedInfectionTimer = 50000;
                    ++m_uiInfectionsRate;
                }
            }
            else
                m_uiMutatedInfectionTimer -= uiDiff;
        }*/

        // Vile Gas
        if (m_bIsHeroic)
        {
            if (m_uiVileGasTimer <= uiDiff)
            {
                if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                {
                    if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                    {
                        if (DoCastSpellIfCan(pTarget, SPELL_VILE_GAS_SUMMON_TRIG, CAST_TRIGGERED) == CAST_OK)
                        {
                            pProfessor->CastSpell(pProfessor, SPELL_VILE_GAS, true);
                            m_uiVileGasTimer = 20000;
                        }
                    }
                }
            }
            else
                m_uiVileGasTimer -= uiDiff;
        }

        // Slime Flow
        if (m_uiSlimeFlowTimer <= uiDiff)
        {
            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                DoScriptText(SAY_SLIME_FLOW_1 - urand(0, 1), pProfessor);

            m_uiSlimeFlowTimer = 20000;
        }
        else
            m_uiSlimeFlowTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_rotface(Creature* pCreature)
{
    return new boss_rotfaceAI(pCreature);
}

// all passive dummy NPCs
struct MANGOS_DLL_DECL  mob_rotface_ooze_dummyAI : public ScriptedAI
{
    mob_rotface_ooze_dummyAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        m_creature->SetVisibility(VISIBILITY_ON);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        Reset();
    }
    void Reset(){}
    void AttackStart(Unit *pWho){}
    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        uiDamage = 0;
    }
    void UpdateAI(const uint32 uiDiff){}
};

CreatureAI* GetAI_mob_rotface_ooze_dummy(Creature* pCreature)
{
    return new mob_rotface_ooze_dummyAI(pCreature);
}

struct MANGOS_DLL_DECL mob_little_oozeAI : public ScriptedAI
{
    mob_little_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiStickyOozeTimer;

    void Reset()
    {
        m_uiStickyOozeTimer = 5000;
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
    }

    void Aggro(Unit *pWho)
    {
        m_creature->SetSpeedRate(MOVE_RUN, 0.75f);
        DoCastSpellIfCan(m_creature, SPELL_WEAK_RADIATING_OOZE, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_LITTLE_OOZE_COMBINE, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (m_uiStickyOozeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_STICKY_OOZE) == CAST_OK)
                m_uiStickyOozeTimer = 20000;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_little_ooze(Creature* pCreature)
{
    return new mob_little_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_big_oozeAI : public ScriptedAI
{
    mob_big_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_icecrown_citadel*)pCreature->GetInstanceData();
        Reset();
    }

    instance_icecrown_citadel *m_pInstance;
    uint32 m_uiStickyOozeTimer;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiStickyOozeTimer = 5000;
        m_uiCheckTimer = 1000;
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
    }

    void Aggro(Unit *pWho)
    {
        m_creature->SetSpeedRate(MOVE_RUN, 0.5f);
        DoCastSpellIfCan(m_creature, SPELL_RADIATING_OOZE, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_BIG_OOZE_COMBINE, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_BIG_OOZE_BUFF_COMB, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        // Unstable Ooze
        if (m_uiCheckTimer <= uiDiff)
        {
            if (SpellAuraHolderPtr holder= m_creature->GetSpellAuraHolder(SPELL_UNSTABLE_OOZE))
            {
                if (holder->GetStackAmount() >= 5)
                {
                    if (m_pInstance)
                    {
                        if (Creature *pRotface = m_pInstance->GetSingleCreatureFromStorage(NPC_ROTFACE))
                        {
                            m_pInstance->SetSpecialAchievementCriteria(TYPE_DANCES_WITH_OOZES, false);
                            DoScriptText(SAY_OOZE_EXPLODE, pRotface);
                            m_uiCheckTimer = 10000;
                            return;
                        }
                    }
                }
            }
            m_uiCheckTimer = 1000;
        }
        else
            m_uiCheckTimer -= uiDiff;

        // Sticky Ooze
        if (m_uiStickyOozeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_STICKY_OOZE) == CAST_OK)
                m_uiStickyOozeTimer = 20000;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_big_ooze(Creature* pCreature)
{
    return new mob_big_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_sticky_oozeAI : public ScriptedAI
{
    mob_sticky_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        pCreature->CastSpell(pCreature, SPELL_STICKY_AURA, true);
        Reset();
    }

    void Reset(){}
    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        uiDamage = 0;
    }
    void UpdateAI(const uint32 uiDiff){}
};

CreatureAI* GetAI_mob_sticky_ooze(Creature* pCreature)
{
    return new mob_sticky_oozeAI(pCreature);
}


// Precious
struct MANGOS_DLL_DECL mob_preciousAI : public ScriptedAI
{
    mob_preciousAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiDecimateTimer;
    uint32 m_uiMortalwoundTimer;
    uint32 m_uiZombiesTimer;
    uint32 m_uiNumZombies;

    void Reset()
    {
        m_uiDecimateTimer = urand(10000, 12000);
        m_uiMortalwoundTimer = urand(2000, 5000);
        m_uiZombiesTimer = urand (20000, 22000);
        m_uiNumZombies = 10;

        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
        m_creature->SetSpeedRate(MOVE_WALK, 1.0f);
    }

    void JustDied(Unit *killer)
    {
        if (m_pInstance)
            if (Creature* pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_ROTFACE))
                DoScriptText(SAY_PRECIOUS_DIES,pTemp,killer);
    }

    void JustSummoned(Unit *pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_ZOMBIE)
            pSummoned->setFaction(m_creature->getFaction());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Decimate
        if (m_uiDecimateTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_PRECIOUS_DECIMATE) == CAST_OK)
                m_uiDecimateTimer = 32000;
        }
        else
            m_uiDecimateTimer -= uiDiff;

        // Mortal wound
        if (m_uiMortalwoundTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_PRECIOUS_MORTALWOUND) == CAST_OK)
                m_uiMortalwoundTimer = 10000;
        }
        else
            m_uiMortalwoundTimer -= uiDiff;

        // Zombies
        if (m_uiZombiesTimer <= uiDiff)
        {
            DoScriptText(SAY_PRECIOUS_ZOMBIES, m_creature);
            float x, y, z;
            for (uint32 i = 0; i < m_uiNumZombies; i++)
            {
                m_creature->GetNearPoint(m_creature, x, y, z, m_creature->GetObjectBoundingRadius(), 10.0f, frand(-M_PI_F, M_PI_F));
                if (Creature *pZombie = m_creature->SummonCreature(NPC_ZOMBIE, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                {
                    pZombie->SetSpeedRate(MOVE_RUN, 0.5f);
                }
            }
            m_uiZombiesTimer = 30000;
        }
        else
            m_uiZombiesTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_precious(Creature *pCreature)
{
    return new mob_preciousAI(pCreature);
}

void AddSC_boss_rotface()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_rotface";
    pNewScript->GetAI = &GetAI_boss_rotface;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_rotface_ooze_dummy";
    pNewScript->GetAI = &GetAI_mob_rotface_ooze_dummy;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_little_ooze";
    pNewScript->GetAI = &GetAI_mob_little_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_big_ooze";
    pNewScript->GetAI = &GetAI_mob_big_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_sticky_ooze";
    pNewScript->GetAI = &GetAI_mob_sticky_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_precious";
    pNewScript->GetAI = &GetAI_mob_precious;
    pNewScript->RegisterSelf();
}

