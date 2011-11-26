/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 MangosR2
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
SDName: Boss_Drakos
SD%Complete:
SDComment:
SDAuthor:
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

enum
{
    SAY_AGGRO                                     = -1578000,
    SAY_KILL_1                                    = -1578001,
    SAY_KILL_2                                    = -1578002,
    SAY_KILL_3                                    = -1578003,
    SAY_DEATH                                     = -1578004,
    SAY_PULL_1                                    = -1578005,
    SAY_PULL_2                                    = -1578006,
    SAY_PULL_3                                    = -1578007,
    SAY_PULL_4                                    = -1578008,
    SAY_STOMP_1                                   = -1578009,
    SAY_STOMP_2                                   = -1578010,
    SAY_STOMP_3                                   = -1578011,

    SAY_BELGAR                                    = -1578040,

    SPELL_MAGIC_PULL                              = 51336,
    SPELL_MAGIC_PULL_EFFECT                       = 50770,
    SPELL_THUNDERING_STOMP_N                      = 50774,
    SPELL_THUNDERING_STOMP_H                      = 59370,
    SPELL_UNSTABLE_SPHERE_PASSIVE                 = 50756,
    SPELL_UNSTABLE_SPHERE_PULSE                   = 50757,
    SPELL_UNSTABLE_SPHERE_TIMER                   = 50758,
    SPELL_UNSTABLE_SPHERE_EXPLODE                 = 50759,

    NPC_UNSTABLE_SPHERE                           = 28166
};

/****
* Boss_Drakos
****/

struct MANGOS_DLL_DECL drakos_eventAI : public ScriptedAI
{
    drakos_eventAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiStep;
    uint32 m_uiPhase_timer;

    bool m_bIsOutro;

    void Reset()
    {
        m_bIsOutro        = true;
        m_uiPhase_timer   = 3000;
        m_uiStep          = 1;

        if (Creature* pEternos = m_pInstance->GetSingleCreatureFromStorage(NPC_ETERNOS))
        {
            pEternos->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        if (Creature* pVerdisa = m_pInstance->GetSingleCreatureFromStorage(NPC_VERDISA))
        {
            pVerdisa->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        if (Creature* pBelgar = m_pInstance->GetSingleCreatureFromStorage(NPC_BELGAR))
        {
            pBelgar->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
    }

    void JumpToNextStep(uint32 uiTimer)
    {
        m_uiPhase_timer = uiTimer;
        m_uiStep++;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_bIsOutro)
        {
        if (m_uiPhase_timer <= uiDiff)
        {
            switch(m_uiStep)
            {
                case 1:
                    if (GameObject* pDoorOne = m_pInstance->GetSingleGameObjectFromStorage(GO_DRAGON_CAGE_DOOR_1))
                    {
                        pDoorOne->SetGoState(GO_STATE_ACTIVE);
                    }
                    if (GameObject* pDoorTwo = m_pInstance->GetSingleGameObjectFromStorage(GO_DRAGON_CAGE_DOOR_2))
                    {
                        pDoorTwo->SetGoState(GO_STATE_ACTIVE);
                    }
                    if (GameObject* pDoorThree = m_pInstance->GetSingleGameObjectFromStorage(GO_DRAGON_CAGE_DOOR_3))
                    {
                        pDoorThree->SetGoState(GO_STATE_ACTIVE);
                    }
                    JumpToNextStep(4000);
                    break;
                case 2:
                    if (Creature* pEternos = m_pInstance->GetSingleCreatureFromStorage(NPC_ETERNOS))
                    {
                        pEternos->GetMotionMaster()->MovePoint(0, 942.89f, 1059.64f, 359.96f);
                    }
                    if (Creature* pVerdisa = m_pInstance->GetSingleCreatureFromStorage(NPC_VERDISA))
                    {
                        pVerdisa->GetMotionMaster()->MovePoint(0, 949.44f, 1033.27f, 359.96f);
                    }
                    if (Creature* pBelgar = m_pInstance->GetSingleCreatureFromStorage(NPC_BELGAR))
                    {
                        pBelgar->GetMotionMaster()->MovePoint(0, 941.19f, 1043.98f, 359.96f);
                    }
                    JumpToNextStep(4000);
                    break;
                case 3:
                    if (Creature* pEternos = m_pInstance->GetSingleCreatureFromStorage(NPC_ETERNOS))
                    {
                        pEternos->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                    if (Creature* pVerdisa = m_pInstance->GetSingleCreatureFromStorage(NPC_VERDISA))
                    {
                        pVerdisa->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                    if (Creature* pBelgar = m_pInstance->GetSingleCreatureFromStorage(NPC_BELGAR))
                    {
                        pBelgar->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                    JumpToNextStep(1000);
                    break;
                case 4:
                    if (Creature* pBelgar = m_pInstance->GetSingleCreatureFromStorage(NPC_BELGAR))
                    {
                        DoScriptText(SAY_BELGAR, pBelgar);
                    }
                    JumpToNextStep(4000);
                    break;
                case 5:
                    break;
            }
        }
        else m_uiPhase_timer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_drakos_event(Creature* pCreature)
{
    return new drakos_eventAI(pCreature);
}

struct MANGOS_DLL_DECL boss_drakosAI : public ScriptedAI
{
    boss_drakosAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiMagicPullTimer ;
    uint32 m_uiStompTimer ;
    uint32 m_uiBombSummonTimer ;

    bool MagicPull80;
    bool MagicPull60;
    bool MagicPull40;
    bool MagicPull20;

    void Reset()
    {
        m_uiMagicPullTimer = urand(12000, 15000);
        m_uiStompTimer = urand(3000, 6000);
        m_uiBombSummonTimer = 7000;

        if (m_pInstance && m_creature->isAlive())
            m_pInstance->SetData(TYPE_DRAKOS, NOT_STARTED);

        MagicPull80 = false;
        MagicPull60 = false;
        MagicPull40 = false;
        MagicPull20 = false;
    }

    void Aggro(Unit* who)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_DRAKOS, IN_PROGRESS);
    }

    void JustDied(Unit* killer)
    {
        m_creature->SummonCreature(NPC_TRIGGER, 940.41f, 1043.79f, 359.96f, 0.21, TEMPSUMMON_MANUAL_DESPAWN, 30000);

        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_DRAKOS, DONE);
    }

    void KilledUnit(Unit *victim)
    {
        switch (urand(0, 2))
        {
            case 0: DoScriptText(SAY_KILL_1, m_creature); break;
            case 1: DoScriptText(SAY_KILL_2, m_creature); break;
            case 2: DoScriptText(SAY_KILL_3, m_creature); break;
        }
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_MAGIC_PULL)
            if (pTarget->GetTypeId() == TYPEID_PLAYER)
                DoCast(pTarget, SPELL_MAGIC_PULL_EFFECT, true);
    }

///-> magic pull bombing
    /*void MagicPullBombing
    {
        uint8 BombCount = 5;
            for(uint32 i = 0; i < BombCount; i++)
                DoSpawnCreature(NPC_UNSTABLE_SPHERE, 0, 0, 0, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
    }*/

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBombSummonTimer < uiDiff)
        {
            uint8 BombCount = urand(1, m_bIsRegularMode ? 4 : 6);
            for(uint32 i = 0; i < BombCount; i++)
                DoSpawnCreature(NPC_UNSTABLE_SPHERE, 0, 0, 0, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
            m_uiBombSummonTimer = urand(5000, 6000);
        }
        else
            m_uiBombSummonTimer -= uiDiff;

        if (m_uiStompTimer < uiDiff)
        {
            DoCast(m_creature, m_bIsRegularMode ? SPELL_THUNDERING_STOMP_N : SPELL_THUNDERING_STOMP_H);
            m_uiStompTimer = urand(11000, 18000);
            switch (urand(0, 2))
            {
               case 0: DoScriptText(SAY_STOMP_1, m_creature); break;
               case 1: DoScriptText(SAY_STOMP_2, m_creature); break;
               case 2: DoScriptText(SAY_STOMP_3, m_creature); break;
            }
        }
        else
            m_uiStompTimer -= uiDiff ;

        if (m_uiMagicPullTimer < uiDiff)
        {
            if (!MagicPull80 && m_creature->GetHealthPercent() < 80.0f) // 80% hp
            {
                DoScriptText(SAY_PULL_1, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_MAGIC_PULL);
///-> summons lots of spheres at once each pull need more data
                MagicPull80 = true;
                return;
            }
            if (!MagicPull60 && m_creature->GetHealthPercent() < 60.0f) // 60% hp
            {
                DoScriptText(SAY_PULL_2, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_MAGIC_PULL);
///-> summons lots of spheres at once each pull need more data
                MagicPull60 = true;
                return;
            }
            if (!MagicPull40 && m_creature->GetHealthPercent() < 40.0f) // 40% hp
            {
                DoScriptText(SAY_PULL_3, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_MAGIC_PULL);
///-> summons lots of spheres at once each pull need more data
                MagicPull40 = true;
                return;
            }
            if (!MagicPull20 && m_creature->GetHealthPercent() < 20.0f) // 20% hp
            {
                DoScriptText(SAY_PULL_4, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_MAGIC_PULL);
///-> summons lots of spheres at once each pull need more data
                MagicPull20 = true;
                return;
            }
        }
        else
            m_uiMagicPullTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_drakos(Creature* pCreature)
{
    return new boss_drakosAI (pCreature);
}

/*****
* npc_unstable_sphere
*****/

#define X               960
#define Y               1050
#define Z               360
#define PI              3.14

struct MANGOS_DLL_DECL npc_unstable_sphereAI : public ScriptedAI
{
    npc_unstable_sphereAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiPulseTimer;

    void MoveToPointInCircle(uint32 id)
    {
        float x, y, z, r, angle;
        angle = urand(0, 36000) / 100;
        r = urand(20, 320) / 10;
        (angle <= PI) ? y = Y + (sin(angle) * r) : y = Y - (sin(angle) * r);
        (angle >= (PI / 2) && angle <= (PI * 3 / 2)) ? x = X - (cos(angle) * r) : x = X + (cos(angle) * r);
        z = Z;
        m_creature->GetMotionMaster()->MovePoint(id, x, y, z);
    }

    void Reset()
    {
        m_creature->SetLevitate(true);
        MoveToPointInCircle(1);
        m_creature->setFaction(14);
        DoCast(m_creature, SPELL_UNSTABLE_SPHERE_PASSIVE, true);
        DoCast(m_creature, SPELL_UNSTABLE_SPHERE_TIMER, true);
        m_uiPulseTimer = 3000;
        m_creature->ForcedDespawn(19000);
    }

    void AttackStart(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_DRAKOS) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (m_uiPulseTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_UNSTABLE_SPHERE_PULSE, true);
            m_uiPulseTimer = 3000;
        }
        else
            m_uiPulseTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_unstable_sphere(Creature* pCreature)
{
    return new npc_unstable_sphereAI (pCreature);
}

void AddSC_boss_drakos()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_drakos";
    pNewScript->GetAI = &GetAI_boss_drakos;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_unstable_sphere";
    pNewScript->GetAI = &GetAI_npc_unstable_sphere;
    pNewScript->RegisterSelf();
}
