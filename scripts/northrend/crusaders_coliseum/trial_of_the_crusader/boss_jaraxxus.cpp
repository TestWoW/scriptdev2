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
SDName: boss_jaraxxus
SDComment: Timers
SDAuthor: Walkum
EndScriptData */

#include "precompiled.h"
#include "trial_of_the_crusader.h"

enum Yells
{
    SAY_AGGRO                          = -1713517,
    SAY_DEATH                          = -1713525,
    SAY_SLAY_1                         = -1713567,
    SAY_SLAY_2                         = -1713568,
    SAY_INFERNAL_VOLCANO               = -1713520,
    SAY_NETHER_PORTAL                  = -1713519,
    SAY_SUMMON_MISTRESS                = -1713521,
    SAY_SUMMON_INFERNAL                = -1713524,
    SAY_INCINERATE_FLESH               = -1713523,

    EMOTE_INCINERATE_FLESH             = -1713522,
};

enum Equipment
{
    EQUIP_MAIN                         = 47266,
    EQUIP_DONE                         = EQUIP_NO_CHANGE,
};

enum Summons
{
    NPC_LEGION_FLAME                   = 34784,
    NPC_INFERNAL_VOLCANO               = 34813,
    NPC_FEL_INFERNAL                   = 34815,
    NPC_NETHER_PORTAL                  = 34825,
    NPC_MISTRESS                       = 34826,
};

enum BossSpells
{
    SPELL_NETHER_POWER                 = 67108,
    SPELL_INFERNAL                     = 66258,
    SPELL_INFERNAL_ERUPTION            = 66255,
    SPELL_FEL_FIREBALL                 = 66532,
    SPELL_FEL_LIGHTING                 = 66528,
    SPELL_INCINERATE_FLESH             = 66237,
    SPELL_BURNING_INFERNO              = 66242,
    SPELL_NETHER_PORTAL                = 66264,
    SPELL_LEGION_FLAME                 = 66197,
    SPELL_LEGION_FLAME_AURA            = 66201,
    SPELL_SHIVAN_SLASH                 = 67098,
    SPELL_SPINNING_STRIKE              = 66283, // Need core support
    SPELL_MISTRESS_KISS                = 67906,
    SPELL_FEL_INFERNO                  = 67047,
    SPELL_FEL_STREAK                   = 66494,
    SPELL_WILFRED_PORTAL               = 68424,
};

/*######
## boss_jaraxxus
######*/

struct MANGOS_DLL_DECL boss_jaraxxusAI : public BSWScriptedAI
{
    boss_jaraxxusAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (instance_trial_of_the_crusader*)pCreature->GetInstanceData();
        Reset();
    }

    instance_trial_of_the_crusader* m_pInstance;

    uint8 MistressCount;
    uint32 m_uiCheckAchiev;

    uint32 m_uiEventStep;

    uint32 m_uiNetherPowerTimer;
    uint32 m_uiFelFireballTimer;
    uint32 m_uiFelLightingTimer;
    uint32 m_uiIncinerateFleshTimer;
    uint32 m_uiLegionFlameTimer;
    uint32 m_uiInfernalEruptionTimer;
    uint32 m_uiNetherPortalTimer;


    void Reset() 
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_JARAXXUS, NOT_STARTED);

        MistressCount               = 0;
        m_uiCheckAchiev             = 0;

        m_uiEventStep               = 0;

        m_uiNetherPowerTimer        = 0;
        m_uiFelFireballTimer        = 15000;
        m_uiFelLightingTimer        = 12000;
        m_uiIncinerateFleshTimer    = 15000;
        m_uiLegionFlameTimer        = 20000;
        m_uiInfernalEruptionTimer   = 80000;
        m_uiNetherPortalTimer       = 20000;

        m_creature->SetRespawnDelay(DAY);
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_JARAXXUS, FAIL);
        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance) 
            return;

        DoScriptText(SAY_DEATH, m_creature);
        m_pInstance->SetData(TYPE_JARAXXUS, DONE);
        m_pInstance->SetData(TYPE_EVENT,1999);
        m_pInstance->SetData(TYPE_STAGE,0);
    }

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance) 
            return;

        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetInCombatWithZone();
        m_pInstance->SetData(TYPE_JARAXXUS, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)

        switch (urand(0,1))
        {
            case 0:
                DoScriptText(SAY_SLAY_1, m_creature);
                break;
            case 1:
                DoScriptText(SAY_SLAY_2, m_creature);
                break;
        };
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiNetherPowerTimer <= uiDiff)
        {
            m_creature->CastSpell(m_creature, SPELL_NETHER_POWER, false);
            m_uiNetherPowerTimer = 30000;
        }
        else
            m_uiNetherPowerTimer -= uiDiff;

        if (m_uiCheckAchiev <= uiDiff)
        {
            if (Creature* pMistress = m_pInstance->GetSingleCreatureFromStorage(NPC_MISTRESS)) 
            {
                if (!pMistress->isAlive())
                    --MistressCount;
            }

            if (MistressCount < 2)
                m_pInstance->SetSpecialAchievementCriteria(TYPE_ACHIEV_JARAXXUS, false);

            m_uiCheckAchiev = 5000;
        }
        else
            m_uiCheckAchiev -= uiDiff;

        if (m_uiFelFireballTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(pTarget, SPELL_FEL_FIREBALL, false);

            m_uiFelFireballTimer = 12000;
        }
        else
            m_uiFelFireballTimer -= uiDiff;

        if (m_uiFelLightingTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(pTarget, SPELL_FEL_LIGHTING, false);

            m_uiFelLightingTimer = 25000;
        }
        else
            m_uiFelLightingTimer -= uiDiff;

        if (m_uiIncinerateFleshTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoScriptText(SAY_INCINERATE_FLESH, m_creature);
                DoScriptText(EMOTE_INCINERATE_FLESH, m_creature, pTarget);
                m_creature->CastSpell(pTarget, SPELL_INCINERATE_FLESH, false);
            }
            m_uiIncinerateFleshTimer = 25000;
        }
        else
            m_uiIncinerateFleshTimer -= uiDiff;

        if (m_uiLegionFlameTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                m_creature->CastSpell(pTarget, SPELL_LEGION_FLAME, false);
                m_uiLegionFlameTimer = 30000;
            }
        }
        else
            m_uiLegionFlameTimer -= uiDiff;

        if (m_uiInfernalEruptionTimer <= uiDiff)
        {
            DoScriptText(SAY_INFERNAL_VOLCANO, m_creature);
            m_creature->CastSpell(m_creature, SPELL_INFERNAL, false);
            m_uiInfernalEruptionTimer = 80000;
        }
        else
            m_uiInfernalEruptionTimer -= uiDiff;

        if (m_uiNetherPortalTimer <= uiDiff)
        {
            DoScriptText(SAY_NETHER_PORTAL, m_creature);
                
            float x, y, z;
            m_creature->GetPosition(x, y, z);
            m_creature->SummonCreature(NPC_NETHER_PORTAL, x + urand(5.0f, 10.0f), y + urand(5.0f, 10.0f), z, 5, TEMPSUMMON_TIMED_DESPAWN, 10000);
            if (Creature* pMistress = m_pInstance->GetSingleCreatureFromStorage(NPC_NETHER_PORTAL)) 
            {
                pMistress->SetDisplayId(17612);
                pMistress->CastSpell(pMistress, SPELL_WILFRED_PORTAL, false);
                ++MistressCount;
            }
            m_uiNetherPortalTimer = 100000;
        }
        else
            m_uiNetherPortalTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jaraxxus(Creature* pCreature)
{
    return new boss_jaraxxusAI(pCreature);
}

struct MANGOS_DLL_DECL mob_legion_flameAI : public BSWScriptedAI
{
    mob_legion_flameAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        m_creature->_AddAura(SPELL_LEGION_FLAME_AURA);
        m_creature->ForcedDespawn(60000);
        m_creature->SetRespawnDelay(DAY);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER) 
            return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS) 
            m_creature->ForcedDespawn();
    }
};

CreatureAI* GetAI_mob_legion_flame(Creature* pCreature)
{
    return new mob_legion_flameAI(pCreature);
}

struct MANGOS_DLL_DECL mob_infernal_volcanoAI : public BSWScriptedAI
{
    mob_infernal_volcanoAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    uint32 m_InfernalCount;
    uint32 m_uiSummonInfernalTimer;

    void Reset()
    {
        m_InfernalCount               = 3;
        m_uiSummonInfernalTimer       = 4000;

        m_creature->SetInCombatWithZone();
        m_creature->SetSpeedRate(MOVE_RUN, 0.0f);

        if (!m_bIsHeroic)
             m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void JustDied(Unit* Killer)
    {
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (m_uiSummonInfernalTimer <= uiDiff)
        {
            if (m_InfernalCount > 0)
            {
                --m_InfernalCount;

                if (Creature* pBoss = m_pInstance->GetSingleCreatureFromStorage(NPC_JARAXXUS)) 
                    DoScriptText(SAY_SUMMON_INFERNAL, pBoss);

                if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    m_creature->CastSpell(pTarget, SPELL_INFERNAL_ERUPTION, false);
            }
            m_uiSummonInfernalTimer = 5000;
        }
        else
            m_uiSummonInfernalTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_infernal_volcano(Creature* pCreature)
{
    return new mob_infernal_volcanoAI(pCreature);
}

struct MANGOS_DLL_DECL mob_fel_infernalAI : public BSWScriptedAI
{
    mob_fel_infernalAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiFelInfernoTimer;
    uint32 m_uiFelStreakTimer;

    void Reset()
    {
        m_uiFelInfernoTimer      = 10000,
        m_uiFelStreakTimer       = 20000,

        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(DAY);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER) 
            return;
    }

    void JustDied(Unit* Killer)
    {
        m_creature->ForcedDespawn(5000);
    }

    void Aggro(Unit *who)
    {
        if (!m_pInstance) 
            return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFelInfernoTimer <= uiDiff)
        {
            if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(pTarget, SPELL_FEL_INFERNO, false);

            m_uiFelInfernoTimer = 25000;
        }
        else
            m_uiFelInfernoTimer -= uiDiff;

        if (m_uiFelStreakTimer <= uiDiff)
        {
            if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(pTarget, SPELL_FEL_STREAK, false);

            m_uiFelStreakTimer = 25000;
        }
        else
            m_uiFelStreakTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_fel_infernal(Creature* pCreature)
{
    return new mob_fel_infernalAI(pCreature);
}

struct MANGOS_DLL_DECL mob_nether_portalAI : public BSWScriptedAI
{
    mob_nether_portalAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiSummonMistressTimer;

    void Reset()
    {
        m_uiSummonMistressTimer = 8000;

        m_creature->SetInCombatWithZone();
        m_creature->SetSpeedRate(MOVE_RUN, 0.0f);
        m_creature->SetRespawnDelay(DAY);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (m_uiSummonMistressTimer <= uiDiff)
        {
            if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(pTarget, SPELL_NETHER_PORTAL, false);

            if (Creature* pBoss = m_pInstance->GetSingleCreatureFromStorage(NPC_JARAXXUS)) 
                DoScriptText(SAY_SUMMON_MISTRESS, pBoss);

            m_uiSummonMistressTimer = 5000;
        }
        else
            m_uiSummonMistressTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_nether_portal(Creature* pCreature)
{
    return new mob_nether_portalAI(pCreature);
}

struct MANGOS_DLL_DECL mob_mistress_of_painAI : public BSWScriptedAI
{
    mob_mistress_of_painAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    uint32 m_uiShivanSlashTimer;
    uint32 m_uiSpinningStrikeTimer;
    uint32 m_uiMistressKissTimer;

    void Reset()
    {
        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(DAY);

        m_uiShivanSlashTimer       = 10000;
        m_uiSpinningStrikeTimer    = 5000;
        m_uiMistressKissTimer      = 15000;
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER) 
            return;
    }

    void JustDied(Unit* Killer)
    {
        m_creature->ForcedDespawn(5000);
    }

    void Aggro(Unit *who)
    {
        if (!m_pInstance) 
            return;
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance) 
            return;

        if (m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS) 
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiShivanSlashTimer <= uiDiff)
        {
            m_creature->CastSpell(m_creature->getVictim(), SPELL_SHIVAN_SLASH, false);
            m_uiShivanSlashTimer = 10000;
        }
        else
            m_uiShivanSlashTimer -= uiDiff;

        if (m_uiSpinningStrikeTimer <= uiDiff)
        {
            m_creature->CastSpell(m_creature->getVictim(), SPELL_SPINNING_STRIKE, false);
            m_uiSpinningStrikeTimer = 10000;
        }
        else
            m_uiSpinningStrikeTimer -= uiDiff;

        if (m_bIsHeroic)
        {
            if (m_uiMistressKissTimer <= uiDiff)
            {
                m_creature->CastSpell(m_creature->getVictim(), SPELL_MISTRESS_KISS, false);
                m_uiMistressKissTimer = 10000;
            }
            else
                m_uiMistressKissTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_mistress_of_pain(Creature* pCreature)
{
    return new mob_mistress_of_painAI(pCreature);
}

void AddSC_boss_jaraxxus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_jaraxxus";
    pNewScript->GetAI = &GetAI_boss_jaraxxus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_legion_flame";
    pNewScript->GetAI = &GetAI_mob_legion_flame;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_infernal_volcano";
    pNewScript->GetAI = &GetAI_mob_infernal_volcano;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_fel_infernal";
    pNewScript->GetAI = &GetAI_mob_fel_infernal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nether_portal";
    pNewScript->GetAI = &GetAI_mob_nether_portal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_mistress_of_pain";
    pNewScript->GetAI = &GetAI_mob_mistress_of_pain;
    pNewScript->RegisterSelf();
}
