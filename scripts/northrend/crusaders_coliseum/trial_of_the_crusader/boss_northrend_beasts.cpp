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
SDName: boss_northrend_beasts
SDComment: Timers
SDAuthor: Walkum
EndScriptData */

// Worms: Paralytic Toxin requires core support.

#include "precompiled.h"
#include "trial_of_the_crusader.h"

enum Emotes
{
    EMOTE_SUMMON_SNOBOLD        = -1713601,
    EMOTE_ENRAGE                = -1713504,
    EMOTE_TRAMPLE               = -1713506,
    EMOTE_STAGGERED             = -1713507,
    EMOTE_CRASH                 = -1713508,
};
enum Equipment
{
    EQUIP_MAIN                  = 47505,
    EQUIP_DONE                  = EQUIP_NO_CHANGE,
};

enum Summons
{
    NPC_SNOBOLD_VASSAL          = 34800,
    NPC_SLIME_POOL              = 35176,
    NPC_FIRE_BOMB               = 34854,
};

enum BossSpells
{
    // Gormok
    SPELL_IMPALE                = 66331,
    SPELL_STAGGERING_STOMP      = 67648,
    SPELL_RISING_ANGER          = 66636,
    SPELL_SNOBOLLED             = 66406,
    SPELL_BATTER                = 66408,
    SPELL_FIRE_BOMB             = 66313,
    SPELL_FIRE_BOMB_DOT         = 66318,
    SPELL_HEAD_CRACK            = 66407,

    // Acidmaw & Dreadscale
    SPELL_SUBMERGE              = 53421,
    SPELL_EMERGE                = 65982,
    SPELL_ENRAGE                = 68335,
    SPELL_ACID_SPIT             = 66880,
    SPELL_PARALYTIC_SPRAY       = 66901,
    SPELL_PARALYTIC_TOXIN       = 66823,
    SPELL_ACID_SPEW             = 66819,
    SPELL_PARALYTIC_BITE        = 66824,
    SPELL_SWEEP                 = 66794,
    SPELL_FIRE_SPIT             = 66796,
    SPELL_MOLTEN_SPEW           = 66821,
    SPELL_BURNING_BITE          = 66879,
    SPELL_BURNING_SPRAY         = 66902,
    SPELL_BURNING_BILE          = 66869,
    SPELL_SLIME_POOL            = 66883,
    SPELL_SLIME_POOL_AURA       = 66882,
    SPELL_SLIME_POOL_VISUAL     = 63084,

    // Icehowl
    SPELL_FEROCIOUS_BUTT        = 66770,
    SPELL_MASSIVE_CRASH         = 66683,
    SPELL_WHIRL                 = 67345,
    SPELL_ARCTIC_BREATH         = 66689,
    SPELL_TRAMPLE               = 66734,
    SPELL_ADRENALINE            = 68667,
    SPELL_FROTHING_RAGE         = 66759,
    SPELL_STAGGERED_DAZE        = 66758,
};

struct MANGOS_DLL_DECL boss_gormokAI : public BSWScriptedAI
{
    boss_gormokAI(Creature* pCreature) : BSWScriptedAI(pCreature)
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

    uint8 SnoboldsCount;

    uint32 m_uiImpaleTimer;
    uint32 m_uiStaggeringStompTimer;
    uint32 m_uiSummonSnoboldTimer;

    void Reset() 
    {
        if (!m_pInstance) 
            return;

        SetEquipmentSlots(false, EQUIP_MAIN, -1, -1);
        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetInCombatWithZone();

        SnoboldsCount = m_bIs25Man? 5 : 4;

        m_uiImpaleTimer           = urand(15000, 30000);
        m_uiStaggeringStompTimer  = urand(20000, 25000);
        m_uiSummonSnoboldTimer    = urand(20000, 30000);
       
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, GORMOK_DONE);
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, FAIL);

        m_creature->ForcedDespawn();
    }

    void Aggro(Unit* pWho)
    {
        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, GORMOK_IN_PROGRESS);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiImpaleTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_IMPALE) == CAST_OK)
                m_uiImpaleTimer = 10000;
        }
        else
            m_uiImpaleTimer -= uiDiff;

        if (m_uiStaggeringStompTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_STAGGERING_STOMP) == CAST_OK)
                m_uiStaggeringStompTimer = 15000;
        }
        else
            m_uiStaggeringStompTimer -= uiDiff;

        if (m_uiSummonSnoboldTimer <= uiDiff && SnoboldsCount > 0)
        {
            float x, y, z;
            m_creature->GetPosition(x, y, z);
            m_creature->SummonCreature(NPC_SNOBOLD_VASSAL, x + urand(5.0f, 10.0f), y + urand(5.0f, 10.0f), z, 0, TEMPSUMMON_MANUAL_DESPAWN, 30000);
            DoScriptText(EMOTE_SUMMON_SNOBOLD, m_creature);
            --SnoboldsCount;
            m_uiSummonSnoboldTimer = 25000;
        }
        else
            m_uiSummonSnoboldTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_gormok(Creature* pCreature)
{
    return new boss_gormokAI(pCreature);
}

struct MANGOS_DLL_DECL mob_snobold_vassalAI : public BSWScriptedAI
{
    mob_snobold_vassalAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Unit* pWho;

    uint32 m_uiBatterTimer;
    uint32 m_uiFireBombTimer;
    uint32 m_uiHeadCrackTimer;

    void Reset()
    {
        pWho = NULL;

        m_uiBatterTimer         = 10000;
        m_uiFireBombTimer       = urand(10000, 20000);
        m_uiHeadCrackTimer      = urand(10000, 30000);

        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(DAY);

        if (Creature* pBoss = m_pInstance->GetSingleCreatureFromStorage(NPC_GORMOK))
            pBoss->_AddAura(SPELL_RISING_ANGER);
    }

    void Aggro(Unit *who)
    {
        if (!m_pInstance) 
            return;

        pWho = who;

        m_creature->AddThreat(pWho, 10000.0f);
        pWho->_AddAura(SPELL_SNOBOLLED);
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* pKiller)
    {
        if (pWho && pWho->isAlive()) 
            pWho->RemoveAurasDueToSpell(SPELL_SNOBOLLED);

        m_creature->ForcedDespawn(5000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_NORTHREND_BEASTS) == FAIL)
            m_creature->ForcedDespawn();

        if (m_uiBatterTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_BATTER) == CAST_OK)
                m_uiBatterTimer = 15000;
        }
        else
            m_uiBatterTimer -= uiDiff;

        if (m_uiFireBombTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIRE_BOMB) == CAST_OK)
            {
                float x, y, z;
                m_creature->GetPosition(x, y, z);

                if (Creature* pFireBomb = m_creature->SummonCreature(NPC_FIRE_BOMB, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 60000))
                {
                    pFireBomb->CastSpell(pFireBomb, SPELL_FIRE_BOMB_DOT, false);
                }
            }
            m_uiFireBombTimer = urand(10000, 20000);
        }
        else
            m_uiFireBombTimer -= uiDiff;

        if (m_uiHeadCrackTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_HEAD_CRACK) == CAST_OK)
                m_uiHeadCrackTimer = urand(10000, 30000);
        }
        else
            m_uiHeadCrackTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_snobold_vassal(Creature* pCreature)
{
    return new mob_snobold_vassalAI(pCreature);
}

struct MANGOS_DLL_DECL mob_fire_bombAI : public BSWScriptedAI
{
    mob_fire_bombAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        m_creature->SetInCombatWithZone();
        SetCombatMovement(false);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_NORTHREND_BEASTS) == FAIL)
            m_creature->ForcedDespawn();
    }
};

CreatureAI* GetAI_mob_fire_bomb(Creature* pCreature)
{
    return new mob_fire_bombAI(pCreature);
}

struct MANGOS_DLL_DECL boss_acidmawAI : public BSWScriptedAI
{
    boss_acidmawAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (instance_trial_of_the_crusader*)pCreature->GetInstanceData();
        Reset();
    }

    instance_trial_of_the_crusader* m_pInstance;
    Unit* target;

    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;

    uint32 m_uiStaticTimer;
    uint32 m_uiMobileTimer;
    uint32 m_uiAcidSpewTimer;
    uint32 m_uiParalyticBiteTimer;
    uint32 m_uiAcidSpitTimer;
    uint32 m_uiParalyticSprayTimer;
    uint32 m_uiSweepTimer;
    uint32 m_uiSlimePoolTimer;

    uint32 m_uiCheckAchiev;
    uint32 m_uiAchievTimer;

    bool m_bIsParalyticToxin;
    bool m_bIsEnraged;

    void Reset()
    {
        m_uiEventStep                   = 1;
        m_uiNextEventTimer              = 0;

        m_uiStaticTimer                 = 55000;
        m_uiMobileTimer                 = 60000;
        m_uiAcidSpewTimer               = urand(10000, 20000);
        m_uiParalyticBiteTimer          = 15000;
        m_uiAcidSpitTimer               = 0;
        m_uiParalyticSprayTimer         = 15000;
        m_uiSweepTimer                  = 20000;
        m_uiSlimePoolTimer              = 10000;

        m_uiCheckAchiev                 = 0;
        m_uiAchievTimer                 = 0;

        m_bIsParalyticToxin             = false;
        m_bIsEnraged                    = false;

        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(7*DAY);
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance) 
            return;

        if (Creature* pDreadscale = m_pInstance->GetSingleCreatureFromStorage(NPC_DREADSCALE))
        {
            if (!pDreadscale->isAlive())
                m_pInstance->SetData(TYPE_NORTHREND_BEASTS, SNAKES_DONE);
            else
                m_pInstance->SetData(TYPE_NORTHREND_BEASTS, SNAKES_SPECIAL);
        }
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        if (m_pInstance->GetData(TYPE_BEASTS) == IN_PROGRESS && m_pInstance->GetData(TYPE_NORTHREND_BEASTS) != FAIL)
            m_pInstance->SetData(TYPE_NORTHREND_BEASTS, FAIL);

        m_creature->ForcedDespawn();
    }

    void SpellHitTarget(Unit *target, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_PARALYTIC_SPRAY)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
            {
                m_creature->CastSpell(target, SPELL_PARALYTIC_TOXIN, false);
            }
        }

        if (spell->Id == SPELL_PARALYTIC_TOXIN)
        {
            if (target->GetTypeId() == TYPEID_PLAYER && target->HasAura(SPELL_BURNING_BILE))
            {
                target->RemoveAurasDueToSpell(SPELL_PARALYTIC_TOXIN);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if ((!m_creature->SelectHostileTarget() || !m_creature->getVictim()))
            return;

            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep) 
                {
                    case 0: 
                         if (m_uiAcidSpewTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_ACID_SPEW) == CAST_OK)
                                 m_uiAcidSpewTimer = urand(15000, 30000);
                         }
                         else
                             m_uiAcidSpewTimer -= uiDiff;

                         if (m_uiParalyticBiteTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_PARALYTIC_BITE) == CAST_OK)
                                 m_uiParalyticBiteTimer = urand(15000, 30000);
                         }
                         else
                             m_uiParalyticBiteTimer -= uiDiff;

                         if (m_uiSlimePoolTimer <= uiDiff)
                         {
                             m_creature->CastSpell(m_creature->getVictim(), SPELL_SLIME_POOL, false);
                             m_uiSlimePoolTimer = 12000;
                         }
                         else
                             m_uiSlimePoolTimer -= uiDiff;

                         if (m_uiStaticTimer <= uiDiff)
                         {
                             m_uiEventStep = 1;
                             m_uiStaticTimer = 65000;
                         }
                         else
                             m_uiStaticTimer -= uiDiff;

                        break;
                    case 1: 
                        m_creature->CastSpell(m_creature, SPELL_SUBMERGE, false);
                        NextStep(3000);
                        break;
                    case 2: 
                        m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                        m_creature->CastSpell(m_creature, SPELL_EMERGE, false);
                        m_creature->SetSpeedRate(MOVE_RUN, 0.0f);
                        NextStep(2000);
                        break;
                    case 3:
                         if (m_uiAcidSpitTimer <= uiDiff)
                         {
                             if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                             {
                                 m_creature->CastSpell(pTarget, SPELL_ACID_SPIT, false);
                                 m_uiAcidSpitTimer = 1200;
                             }
                         }
                         else
                             m_uiAcidSpitTimer -= uiDiff;

                         if (m_uiParalyticSprayTimer <= uiDiff)
                         {
                             if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                             {
                                 m_creature->CastSpell(pTarget, SPELL_PARALYTIC_SPRAY, false);
                                 m_uiParalyticSprayTimer = 20000;
                             }
                         }
                         else
                             m_uiParalyticSprayTimer -= uiDiff;

                         if (m_uiSweepTimer <= uiDiff)
                         {
                             m_creature->CastSpell(m_creature->getVictim(), SPELL_SWEEP, false);
                             m_uiSweepTimer = 20000;
                         }
                         else
                             m_uiSweepTimer -= uiDiff;

                         if (m_uiMobileTimer <= uiDiff)
                         {
                             m_uiEventStep = 4;
                             m_uiMobileTimer = 65000;
                         }
                         else
                             m_uiMobileTimer -= uiDiff;

                        break;
                    case 4: 
                        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
                        DoResetThreat();
                        m_uiEventStep = 0;
                        break;
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;

        if (m_pInstance->GetData(TYPE_NORTHREND_BEASTS) == SNAKES_SPECIAL && !m_bIsEnraged)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
            m_creature->CastSpell(m_creature, SPELL_EMERGE, false);

            DoScriptText(EMOTE_ENRAGE, m_creature);
            m_creature->_AddAura(SPELL_ENRAGE);

            m_bIsEnraged = true;
            m_uiEventStep = 4;
        }

        /*if (m_uiCheckAchiev <= uiDiff)
        {
            if (Creature *pSister = m_pInstance->GetSingleCreatureFromStorage(NPC_DREADSCALE))
            {
                if (!pSister->isAlive())
                    ++m_uiAchievTimer;
            }
            m_uiCheckAchiev = 1000;
        }
        else
            m_uiCheckAchiev -= uiDiff;

        if (m_uiAchievTimer > 10000)
            m_pInstance->SetSpecialAchievementCriteria(TYPE_ACHIEV_JORMUNGAR, false);
        else
            m_uiAchievTimer -= uiDiff;*/

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_acidmaw(Creature* pCreature)
{
    return new boss_acidmawAI(pCreature);
}

struct MANGOS_DLL_DECL boss_dreadscaleAI : public BSWScriptedAI
{
    boss_dreadscaleAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (instance_trial_of_the_crusader*)pCreature->GetInstanceData();
        Reset();
    }

    instance_trial_of_the_crusader* m_pInstance;

    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;

    uint32 m_uiStaticTimer;
    uint32 m_uiMobileTimer;
    uint32 m_uiBurningBiteTimer;
    uint32 m_uiMoltenSpewTimer;
    uint32 m_uiFireSpitTimer;
    uint32 m_uiBurningSprayTimer;
    uint32 m_uiSweepTimer;
    uint32 m_uiSlimePoolTimer;

    uint32 m_uiCheckAchiev;
    uint32 m_uiAchievTimer;

    bool m_bIsEnraged;

    void Reset()
    {
        m_uiEventStep                   = 0;
        m_uiNextEventTimer              = 0;

        m_uiStaticTimer                 = 60000;
        m_uiMobileTimer                 = 60000;
        m_uiBurningBiteTimer            = urand(10000, 20000);
        m_uiMoltenSpewTimer             = urand(15000, 30000);
        m_uiFireSpitTimer               = 1000;
        m_uiBurningSprayTimer           = 15000;
        m_uiSweepTimer                  = 20000;
        m_uiSlimePoolTimer              = 10000;

        m_uiCheckAchiev                 = 0;
        m_uiAchievTimer                 = 0;

        m_bIsEnraged                    = false;

        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(7*DAY);
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance) 
            return;
            
        if (Creature *pSister = m_pInstance->GetSingleCreatureFromStorage(NPC_ACIDMAW))
            if (!pSister->isAlive())
                m_pInstance->SetData(TYPE_NORTHREND_BEASTS, SNAKES_DONE);
            else 
                m_pInstance->SetData(TYPE_NORTHREND_BEASTS, SNAKES_SPECIAL);
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        if (m_pInstance->GetData(TYPE_BEASTS) == IN_PROGRESS && m_pInstance->GetData(TYPE_NORTHREND_BEASTS) != FAIL)
            m_pInstance->SetData(TYPE_NORTHREND_BEASTS, FAIL);

        m_creature->ForcedDespawn();
    }

    void SpellHitTarget(Unit *target, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_BURNING_SPRAY)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
            {
                m_creature->CastSpell(target, SPELL_BURNING_BILE, false);
            }
        }

        if (spell->Id == SPELL_BURNING_BILE)
        {
            if (target->GetTypeId() == TYPEID_PLAYER)
            {
                target->RemoveAurasDueToSpell(SPELL_PARALYTIC_TOXIN);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if ((!m_creature->SelectHostileTarget() || !m_creature->getVictim()))
            return;

            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep) 
                {
                    case 0: 
                         if (m_uiBurningBiteTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_BURNING_BITE) == CAST_OK)
                                 m_uiBurningBiteTimer = urand(15000, 30000);
                         }
                         else
                             m_uiBurningBiteTimer -= uiDiff;

                         if (m_uiMoltenSpewTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MOLTEN_SPEW) == CAST_OK)
                                 m_uiMoltenSpewTimer = urand(15000, 30000);
                         }
                         else
                             m_uiMoltenSpewTimer -= uiDiff;

                         if (m_uiSlimePoolTimer <= uiDiff)
                         {
                             m_creature->CastSpell(m_creature->getVictim(), SPELL_SLIME_POOL, false);
                             m_uiSlimePoolTimer = 12000;
                         }
                         else
                             m_uiSlimePoolTimer -= uiDiff;

                         if (m_uiStaticTimer <= uiDiff)
                         {
                             m_uiEventStep = 1;
                             m_uiStaticTimer = 65000;
                         }
                         else
                             m_uiStaticTimer -= uiDiff;

                        break;
                    case 1: 
                        m_creature->CastSpell(m_creature, SPELL_SUBMERGE, false);
                        NextStep(3000);
                        break;
                    case 2: 
                        m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                        m_creature->CastSpell(m_creature, SPELL_EMERGE, false);
                        m_creature->SetSpeedRate(MOVE_RUN, 0.0f);
                        NextStep(2000);
                        break;
                    case 3:
                         if (m_uiFireSpitTimer <= uiDiff)
                         {
                             if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                             {
                                 m_creature->CastSpell(pTarget, SPELL_FIRE_SPIT, false);
                                 m_uiFireSpitTimer = 1200;
                             }
                         }
                         else
                             m_uiFireSpitTimer -= uiDiff;

                         if (m_uiBurningSprayTimer <= uiDiff)
                         {
                             if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                             {
                                 m_creature->CastSpell(pTarget, SPELL_BURNING_SPRAY, false);
                                 m_uiBurningSprayTimer = 20000;
                             }
                         }
                         else
                             m_uiBurningSprayTimer -= uiDiff;

                         if (m_uiSweepTimer <= uiDiff)
                         {
                             m_creature->CastSpell(m_creature->getVictim(), SPELL_SWEEP, false);
                             m_uiSweepTimer = 20000;
                         }
                         else
                             m_uiSweepTimer -= uiDiff;

                         if (m_uiMobileTimer <= uiDiff)
                         {
                             m_uiEventStep = 4;
                             m_uiMobileTimer = 65000;
                         }
                         else
                             m_uiMobileTimer -= uiDiff;

                        break;
                    case 4: 
                        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
                        DoResetThreat();
                        m_uiEventStep = 0;
                        break;
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;

        if (m_pInstance->GetData(TYPE_NORTHREND_BEASTS) == SNAKES_SPECIAL && !m_bIsEnraged)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
            m_creature->CastSpell(m_creature, SPELL_EMERGE, false);

            DoScriptText(EMOTE_ENRAGE, m_creature);
            m_creature->_AddAura(SPELL_ENRAGE);

            m_bIsEnraged = true;
            m_uiEventStep = 4;
        }

        /*if (m_uiCheckAchiev <= uiDiff)
        {
            if (Creature *pSister = m_pInstance->GetSingleCreatureFromStorage(NPC_ACIDMAW))
            {
                if (!pSister->isAlive())
                    ++m_uiAchievTimer;
            }
            m_uiCheckAchiev = 1000;
        }
        else
            m_uiCheckAchiev -= uiDiff;

        if (m_uiAchievTimer > 10000)
            m_pInstance->SetSpecialAchievementCriteria(TYPE_ACHIEV_JORMUNGAR, false);
        else
            m_uiAchievTimer -= uiDiff;*/

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_dreadscale(Creature* pCreature)
{
    return new boss_dreadscaleAI(pCreature);
}

struct MANGOS_DLL_DECL mob_slime_poolAI : public BSWScriptedAI
{
    mob_slime_poolAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiIncreaseSizeTimer;

    float m_fSize;
    bool m_bIsCloudCasted;

    void Reset()
    {
        if (!m_pInstance) 
            return;

        m_uiIncreaseSizeTimer = 0;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetInCombatWithZone();
        m_creature->CastSpell(m_creature, SPELL_SLIME_POOL_AURA, false);

        SetCombatMovement(false);

        m_fSize = m_creature->GetFloatValue(OBJECT_FIELD_SCALE_X);
        m_bIsCloudCasted = false;
    }

    void AttackStart(Unit *who)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance->GetData(TYPE_NORTHREND_BEASTS) == SNAKES_DONE)
            m_creature->ForcedDespawn();

        if (!m_bIsCloudCasted) 
        {
            m_creature->CastSpell(m_creature, SPELL_SLIME_POOL_VISUAL, false);
            m_bIsCloudCasted = true;
        }

        if (m_uiIncreaseSizeTimer <= uiDiff)
        {
            m_fSize = m_fSize*1.035;
            m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, m_fSize);
            m_uiIncreaseSizeTimer = 500;
        }
        else
            m_uiIncreaseSizeTimer -= uiDiff;

        if (m_fSize >= 6.0f) 
            m_creature->ForcedDespawn();
    }

};

CreatureAI* GetAI_mob_slime_pool(Creature* pCreature)
{
    return new mob_slime_poolAI(pCreature);
}

struct MANGOS_DLL_DECL boss_icehowlAI : public BSWScriptedAI
{
    boss_icehowlAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((instance_trial_of_the_crusader*)pCreature->GetInstanceData());
        Reset();
    }

    instance_trial_of_the_crusader* m_pInstance;

    uint8 SnoboldsCount;

    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;

    uint32 m_uiFerociousButtTimer;
    uint32 m_uiArcticBreathTimer;
    uint32 m_uiWhirlTimer;
    uint32 m_uiMassiveCrashTimer;
    uint32 m_uiTrampleTimer;

    uint32 m_uiCheckAchiev;

    bool m_bMovementStarted;
    bool m_bIsTrampleCasted;

    float fPosX, fPosY, fPosZ;
    Unit* pTarget;

    void Reset() 
    {
        if (!m_pInstance) 
            return;

        SnoboldsCount                  = 2;

        m_uiEventStep                  = 0;
        m_uiNextEventTimer             = 0;

        m_uiFerociousButtTimer         = 15000;
        m_uiArcticBreathTimer          = 25000;
        m_uiWhirlTimer                 = 20000;
        m_uiMassiveCrashTimer          = 30000;
        m_uiTrampleTimer               = 4000;

        m_uiCheckAchiev                = 0;

        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetSpeedRate(MOVE_RUN, 3.0f);
        m_bMovementStarted = false;
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, ICEHOWL_DONE);
    }

    void JumpTo(uint32 id)
    {
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveJump(SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z, 20.0f, 8.0f);
        m_bMovementStarted = true;
    }

    void JustReachedHome()
    {
        if (!m_pInstance) 
            return;

        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, FAIL);
        
        m_creature->ForcedDespawn();
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_pInstance->SetData(TYPE_NORTHREND_BEASTS, ICEHOWL_IN_PROGRESS);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

            if (m_uiCheckAchiev <= uiDiff)
            {
                if (Creature* pSnobold = m_pInstance->GetSingleCreatureFromStorage(NPC_SNOBOLD_VASSAL))
                {
                    if (!pSnobold->isAlive())
                        --SnoboldsCount;
                }
                m_uiCheckAchiev = 1000;

                if (SnoboldsCount < 2)
                    m_pInstance->SetSpecialAchievementCriteria(TYPE_ACHIEV_GORMOK, false);
            }
            else
                m_uiCheckAchiev -= uiDiff;

            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep) 
                {
                    case 0: 
                    {
                         m_creature->SetSpeedRate(MOVE_RUN, 3.0f);

                         if (m_uiFerociousButtTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FEROCIOUS_BUTT) == CAST_OK)
                                 m_uiFerociousButtTimer = urand(15000, 30000);
                         }
                         else
                             m_uiFerociousButtTimer -= uiDiff;

                         if (m_uiArcticBreathTimer <= uiDiff)
                         {
                             if (pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1)) 
                                 m_creature->CastSpell(pTarget, SPELL_ARCTIC_BREATH, false);

                             m_uiArcticBreathTimer = urand(25000, 40000);
                         }
                         else
                             m_uiArcticBreathTimer -= uiDiff;

                         if (m_uiWhirlTimer <= uiDiff)
                         {
                             if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_WHIRL) == CAST_OK)
                                 m_uiWhirlTimer = urand(20000, 30000);
                         }
                         else
                             m_uiWhirlTimer -= uiDiff;
        
                         if (m_uiMassiveCrashTimer <= uiDiff)
                         {
                             m_uiEventStep = 1;
                             m_uiMassiveCrashTimer = 40000;
                         }
                         else
                             m_uiMassiveCrashTimer -= uiDiff;
        
                        DoMeleeAttackIfReady();
        
                        break;
                    }
                    case 1: 
                    {
                        m_creature->AttackStop();
                        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        m_creature->SetSpeedRate(MOVE_RUN, 0.0f);
                        SetCombatMovement(false);
                        JumpTo(1);
                        NextStep(2500);
                        break;
                    }
                    case 2: 
                    {
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        m_creature->CastSpell(m_creature, SPELL_MASSIVE_CRASH, false);
                        SetCombatMovement(true);        

                        if (pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0)) 
                        {
                            m_bIsTrampleCasted = false;      
                            resetTimer(SPELL_TRAMPLE);
                            DoScriptText(EMOTE_TRAMPLE, m_creature, pTarget);
                            SetCombatMovement(false);
                            m_creature->GetMotionMaster()->MoveIdle();
                        }
                        NextStep(3000);
                        break;
                    }
                    case 3:
                        pTarget->GetPosition(fPosX, fPosY, fPosZ);
                        m_creature->SetFacingToObject(pTarget);
                        NextStep(2000);
                    case 4: 
                    {                
                        m_creature->SetSpeedRate(MOVE_RUN, 6.0f);
        
                        if (m_uiTrampleTimer <= uiDiff)
                        {
                            if (pTarget && pTarget->isAlive() && (pTarget->IsWithinDistInMap(m_creature, 250.0f))) 
                            {
                                m_creature->GetMotionMaster()->MovePoint(1, fPosX, fPosY, fPosZ);
                                DoScriptText(EMOTE_CRASH, m_creature);
                                NextStep(1200);
                            }
                            else        
                            {
                                m_uiEventStep = 6;
                            }
                            m_uiTrampleTimer = 4000;
                        }
                        else
                            m_uiTrampleTimer -= uiDiff;
        
                        break;        
                    }
                    case 5: 
                    {
                        Map* pMap = m_creature->GetMap();
                        Map::PlayerList const &lPlayers = pMap->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                        {
                            Unit* pPlayer = itr->getSource();
                            if (!pPlayer) 
                                continue;

                            if (pTarget->isAlive() && m_creature->IsWithinDistInMap(pTarget, 15.0f)) 
                            {
                                m_creature->CastSpell(pTarget, SPELL_TRAMPLE, true);
                                m_creature->CastSpell(m_creature, SPELL_FROTHING_RAGE, false);
                            }
                            else 
                            {
                                m_creature->CastSpell(pTarget, SPELL_TRAMPLE, true);
                                m_creature->CastSpell(m_creature, SPELL_STAGGERED_DAZE, false);
                                DoScriptText(EMOTE_STAGGERED, m_creature);
                            }
                        }
                        NextStep();                     
                        break;
                    }
                    case 6: 
                    {
                        m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        SetCombatMovement(true);
                        m_uiEventStep = 0;
                        break;
                    }
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_icehowl(Creature* pCreature)
{
    return new boss_icehowlAI(pCreature);
}

void AddSC_northrend_beasts()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_gormok";
    pNewScript->GetAI = &GetAI_boss_gormok;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_acidmaw";
    pNewScript->GetAI = &GetAI_boss_acidmaw;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_dreadscale";
    pNewScript->GetAI = &GetAI_boss_dreadscale;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_icehowl";
    pNewScript->GetAI = &GetAI_boss_icehowl;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_snobold_vassal";
    pNewScript->GetAI = &GetAI_mob_snobold_vassal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_fire_bomb";
    pNewScript->GetAI = &GetAI_mob_fire_bomb;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_slime_pool";
    pNewScript->GetAI = &GetAI_mob_slime_pool;
    pNewScript->RegisterSelf();
}
