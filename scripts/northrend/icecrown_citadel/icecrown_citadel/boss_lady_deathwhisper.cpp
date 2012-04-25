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
SDName: boss_lady_deathwhisper
SD%Complete: 95%
SDComment:  Dominate Mind needs core support, uncomment code in script if it works.
            Adds vulnerable to stun, cultor's explosion at 10% health (by Carlos93)
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
        SPELL_BERSERK                           = 26662,
        SPELL_INSIGNIFICANCE                    = 71204,
        SPELL_DOMINATE_MIND                     = 71289,
        SPELL_MANA_BARRIER                      = 70842,
        SPELL_DEATH_AND_DECAY                   = 71001,
        SPELL_SHADOW_BOLT                       = 71254,
        SPELL_FROSTBOLT                         = 71420,
        SPELL_FROSTBOLT_VOLLEY                  = 72905,
        SPELL_BLIND                             = 43433,

        SPELL_FROST_FEVER                       = 71129,
        SPELL_SHROUD_OF_THE_OCCULT              = 70768,
        SPELL_DEATHCHILL_BOLT                   = 70594,
        SPELL_DEATHCHILL_BLAST                  = 70906,
        SPELL_CURSE_OF_TORPOR                   = 71237,
        SPELL_DARK_EMPOWERMENT                  = 70896,
        SPELL_DARK_MARTYRDOM                    = 70897,
        SPELL_ADHERENTS_DETERMINATION           = 71234,

        SPELL_SHADOW_CLEAVE                     = 70670,
        SPELL_NECROTIC_STRIKE                   = 70659,
        SPELL_VAMPIRIC_MIGHT                    = 70674,
        SPELL_DARK_TRANSFORMATION               = 70895,
        SPELL_FANATICS_DETERMINATION            = 71235,

        // Vengeful Shade
        NPC_VENGEFUL_SHADE                      = 38222,
        SPELL_VENGEFUL_BLAST_AURA               = 71494, // must proc on melee hit

        SPELL_ACHIEVEMENT_CREDIT                = 72827,
};

// talks
enum
{
    SAY_SPEECH_1                = -1631011,
    SAY_SPEECH_2                = -1631012,
    SAY_SPEECH_3                = -1631013,
    SAY_SPEECH_4                = -1631014,
    SAY_SPEECH_5                = -1631015,
    SAY_SPEECH_6                = -1631016,
    SAY_SPEECH_7                = -1631017,
    SAY_AGGRO                   = -1631018,
    SAY_PHASE_TWO               = -1631019,
    SAY_DARK_EMPOWERMENT        = -1631020,
    SAY_DARK_TRANSFORMATION     = -1631021,
    SAY_ANIMATE_DEAD            = -1631022,
    SAY_DOMINATE_MIND           = -1631023,
    SAY_BERSERK                 = -1631024,
    SAY_DEATH                   = -1631025,
    SAY_SLAY_1                  = -1631026,
    SAY_SLAY_2                  = -1631027,
};

static Locations SpawnLoc[]=
{
    {-623.055481f, 2211.326660f, 51.764259f},  // 0 Lady's stay point
    {-620.197449f, 2272.062256f, 50.848679f},  // 1 Right Door 1
    {-598.636353f, 2272.062256f, 50.848679f},  // 2 Right Door 2
    {-578.495728f, 2272.062256f, 50.848679f},  // 3 Right Door 3
    {-578.495728f, 2149.211182f, 50.848679f},  // 4 Left Door 1
    {-598.636353f, 2149.211182f, 50.848679f},  // 5 Left Door 2
    {-620.197449f, 2149.211182f, 50.848679f},  // 6 Left Door 3
    {-525.652466f, 2216.611328f, 62.823681f},  // 7 Upper marsh 1
    {-525.652466f, 2211.611328f, 62.823681f},  // 8 Upper marsh 2
    {-525.652466f, 2206.611328f, 62.823681f},  // 9 Upper marsh 3
};

struct MANGOS_DLL_DECL boss_lady_deathwhisper_eventAI : public base_icc_bossAI
{
    boss_lady_deathwhisper_eventAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        m_uiStep = 0;
        m_uiEventTimer = 0;
        m_bIsEventStarted = false;
        m_bIsEventFinished = false;
    }

    uint32 m_uiStep;
    uint32 m_uiEventTimer;
    bool m_bIsEventStarted;
    bool m_bIsEventFinished;

    void Reset(){}

    void NextStep(uint32 uiTimer)
    {
        m_uiEventTimer = uiTimer;
        ++m_uiStep;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsEventStarted)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                m_bIsEventStarted = true;
                NextStep(0);
                return;
            }
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    // for the fight handler
    virtual void UpdateFightAI(const uint32 uiDiff){}

    void UpdateAI(const uint32 uiDiff)
    {
        UpdateFightAI(uiDiff);

        if (!m_bIsEventStarted || m_bIsEventFinished)
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            switch (m_uiStep)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    DoScriptText(SAY_SPEECH_1, m_creature);
                    NextStep(13000);
                    break;
                }
                case 2:
                {
                    DoScriptText(SAY_SPEECH_2, m_creature);
                    NextStep(11000);
                    break;
                }
                case 3:
                {
                    DoScriptText(SAY_SPEECH_3, m_creature);
                    NextStep(10000);
                    break;
                }
                case 4:
                {
                    DoScriptText(SAY_SPEECH_4, m_creature);
                    NextStep(9000);
                    break;
                }
                case 5:
                {
                    DoScriptText(SAY_SPEECH_5, m_creature);
                    NextStep(10000);
                    break;
                }
                case 6:
                {
                    DoScriptText(SAY_SPEECH_6, m_creature);
                    NextStep(10000);
                    break;
                }
                case 7:
                {
                    DoScriptText(SAY_SPEECH_7, m_creature);
                    NextStep(10000);
                    break;
                }
                case 8:
                {
                    m_bIsEventFinished = true;
                    break;
                }
                default:
                    break;
            }
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

struct MANGOS_DLL_DECL boss_lady_deathwhisperAI : public boss_lady_deathwhisper_eventAI
{
    boss_lady_deathwhisperAI(Creature* pCreature) : boss_lady_deathwhisper_eventAI(pCreature)
    {
        Reset();
    }

    bool m_bIsPhaseOne;
    uint32 m_uiManaBarrierCheckTimer;

    bool m_bIsLeftSideSummon;

    uint32 m_uiBerserkTimer;
    uint32 m_uiSummonWaveTimer;
    uint32 m_uiTouchOfInsignificanceTimer;
    uint32 m_uiShadowBoltTimer;
    uint32 m_uiDeathAndDecayTimer;
    uint32 m_uiFrostboltTimer;
    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiDominateMindTimer;
    uint32 m_uiVengefulShadeTimer;
    uint32 m_uiCheckTimer;
    uint32 m_uiMindControlCount;

    void Reset()
    {
        m_bIsPhaseOne                   = true;
        m_bIsLeftSideSummon             = true;
        m_uiManaBarrierCheckTimer       = 1000;
        m_uiBerserkTimer                = 10 * MINUTE * IN_MILLISECONDS;
        m_uiSummonWaveTimer             = 8000;
        m_uiTouchOfInsignificanceTimer  = urand(7000, 10000);
        m_uiShadowBoltTimer             = 5000;
        m_uiDeathAndDecayTimer          = 30000;
        m_uiFrostboltTimer              = urand(5000, 10000);
        m_uiFrostboltVolleyTimer        = 5000;
        m_uiDominateMindTimer           = urand(30000, 45000);
        m_uiVengefulShadeTimer          = 10000;
        m_uiCheckTimer                  = 1000;

        SetCombatMovement(false);

        m_uiMindControlCount = 0;

        if (m_bIs25Man)
        {
            if (m_bIsHeroic)
                m_uiMindControlCount = 3; // 3 targets on heroic 25man
            else
                m_uiMindControlCount = 1; // 1 target on normal 25man
        }
        else
        {
            if (m_bIsHeroic)
                m_uiMindControlCount = 1; // 1 target on heroic 10man
        }
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DEATHWHISPER, IN_PROGRESS);

        // make sure that the event will not continue in the fight
        m_bIsEventFinished = true;

        DoScriptText(SAY_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_MANA_BARRIER, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DEATHWHISPER, FAIL);
    }

    void JustDied(Unit *pKiller)
    {
        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_DEATHWHISPER, DONE);

        if (CheckAchiev())
        {
            Map* pMap = m_creature->GetMap();
            Map::PlayerList const& lPlayers = pMap->GetPlayers();

            if (!lPlayers.isEmpty())
            {
                for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                {
                    if (Player* pPlayer = itr->getSource())
                        pPlayer->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_CREDIT, 0, 0);
                }
            }
        }

        DoScriptText(SAY_DEATH, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoScriptText(SAY_SLAY_1 - urand(0, 1),m_creature,pVictim);
    }

    void JustSummoned(Creature *pSummoned)
    {
        if (!m_pInstance || !pSummoned)
            return;

        pSummoned->SetInCombatWithZone();
    }

    bool CheckAchiev()
    {
        Unit *pAdherent = m_pInstance->GetSingleCreatureFromStorage(NPC_CULT_ADHERENT);
        Unit *pFanatic = m_pInstance->GetSingleCreatureFromStorage(NPC_CULT_FANATIC);
        Unit *pDeformed = m_pInstance->GetSingleCreatureFromStorage(NPC_DEFORMED_FANATIC);
        Unit *pBoneFanatic = m_pInstance->GetSingleCreatureFromStorage(NPC_REANIMATED_FANATIC);
        Unit *pBoneAdherent = m_pInstance->GetSingleCreatureFromStorage(NPC_REANIMATED_ADHERENT);

        if (pAdherent && pFanatic && pDeformed && pBoneFanatic && pBoneAdherent &&
            pAdherent->isAlive() && pFanatic->isAlive() && pDeformed->isAlive() &&
            pBoneFanatic->isAlive() && pBoneAdherent->isAlive())
            return true;
        else
            return false;
    }

    void DoSummonShade()
    {
        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
        {
            float x, y, z;
            pTarget->GetNearPoint(pTarget, x, y, z, pTarget->GetObjectBoundingRadius(), 10.0f, frand(-M_PI_F, M_PI_F));

            if (Creature *pShade = m_creature->SummonCreature(NPC_VENGEFUL_SHADE, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
            {
                pShade->SetSpeedRate(MOVE_RUN, 0.5f);
                pShade->AI()->AttackStart(pTarget);
                pShade->AddThreat(pTarget, 100000.0f);
                pShade->CastSpell(pShade, SPELL_VENGEFUL_BLAST_AURA, true);
                pShade->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }
    }

    void DoSummonWave()
    {
        // summoning on all sides
        if (m_bIs25Man)
        {
            // summon 1 fanatic and 2 adherents on right side
            m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);

            // summon 2 fanatics and 1 adherent on left side
            m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[5].x, SpawnLoc[5].y, SpawnLoc[5].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[6].x, SpawnLoc[6].y, SpawnLoc[6].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);

            // summon random on stairs
            m_creature->SummonCreature(roll_chance_i(50) ? NPC_REANIMATED_FANATIC : NPC_REANIMATED_ADHERENT, SpawnLoc[8].x, SpawnLoc[8].y, SpawnLoc[8].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
        }
        // summoning on 1 side alternatively
        else
        {
            // left side summoning
            if (m_bIsLeftSideSummon)
            {
                // summon 1 fanatic and 2 adherents
                m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
                m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
                m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            }
            else
            {
                // summon 2 fanatics and 1 adherent
                m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
                m_creature->SummonCreature(NPC_CULT_ADHERENT, SpawnLoc[5].x, SpawnLoc[5].y, SpawnLoc[5].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
                m_creature->SummonCreature(NPC_CULT_FANATIC, SpawnLoc[6].x, SpawnLoc[6].y, SpawnLoc[6].z, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 25000);
            }

            // change sides for next summoning
            m_bIsLeftSideSummon = !m_bIsLeftSideSummon;
        }
    }

    void UpdateFightAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBerserkTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiBerserkTimer = 10 * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        if (m_uiDeathAndDecayTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_DEATH_AND_DECAY) == CAST_OK)
                    m_uiDeathAndDecayTimer = 30000;
            }
        }
        else
            m_uiDeathAndDecayTimer -= uiDiff;

        if (m_uiMindControlCount)
        {
            if (m_uiDominateMindTimer <= uiDiff)
            {
                /* uncomment when spell implemented in core
                for (int i = 0; i < m_uiMindControlCount; ++i)
                {
                    if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, SPELL_DOMINATE_MIND, SELECT_FLAG_PLAYER))
                        DoCastSpellIfCan(pTarget, SPELL_DOMINATE_MIND, CAST_TRIGGERED);
                }*/

                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, SPELL_DOMINATE_MIND, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(pTarget, SPELL_BLIND, CAST_TRIGGERED); // Blind, temporally hack, remove when MC implemented

                DoScriptText(SAY_DOMINATE_MIND, m_creature);
                m_uiDominateMindTimer = 45000;
            }
            else
                m_uiDominateMindTimer -= uiDiff;
        }


         // PHASE ONE
        if (m_bIsPhaseOne)
        {
            if (m_uiManaBarrierCheckTimer <= uiDiff)
            {
                if (!m_creature->HasAura(SPELL_MANA_BARRIER))
                {
                    DoScriptText(SAY_PHASE_TWO, m_creature);
                    SetCombatMovement(true);
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_bIsPhaseOne = false;
                    return;
                }

                m_uiManaBarrierCheckTimer = 1000;
            }
            else
                m_uiManaBarrierCheckTimer -= uiDiff;

            if (m_uiSummonWaveTimer <= uiDiff)
            {
                DoSummonWave();
                m_uiSummonWaveTimer = 60000;
                DoScriptText(SAY_ANIMATE_DEAD, m_creature);
            }
            else
                m_uiSummonWaveTimer -= uiDiff;

            if (m_uiShadowBoltTimer <= uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_SHADOW_BOLT) == CAST_OK)
                        m_uiShadowBoltTimer = 8000;
                }
            }
            else
                m_uiShadowBoltTimer -= uiDiff;
        }
        else // PHASE TWO
        {
            if (m_bIsHeroic)
            {
                if (m_uiSummonWaveTimer <= uiDiff)
                {
                    DoSummonWave();
                    m_uiSummonWaveTimer = 60000;
                    DoScriptText(SAY_ANIMATE_DEAD, m_creature);
                }
                else
                    m_uiSummonWaveTimer -= uiDiff;
            }
            if (m_uiFrostboltVolleyTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                    m_uiFrostboltVolleyTimer = urand(15000, 20000);
            }
            else
                m_uiFrostboltVolleyTimer -= uiDiff;

            if (m_uiTouchOfInsignificanceTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_INSIGNIFICANCE) == CAST_OK)
                    m_uiTouchOfInsignificanceTimer = urand(7000, 10000);
            }
            else
                m_uiTouchOfInsignificanceTimer -= uiDiff;

            if (m_uiFrostboltTimer <= uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_FROSTBOLT) == CAST_OK)
                        m_uiFrostboltTimer = urand(5000, 10000);
                }
            }
            else
                m_uiFrostboltTimer -= uiDiff;

            if (m_uiVengefulShadeTimer <= uiDiff)
            {
                DoSummonShade();
                m_uiVengefulShadeTimer = 10000;
            }
            else
                m_uiVengefulShadeTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_lady_deathwhisper(Creature* pCreature)
{
    return new boss_lady_deathwhisperAI(pCreature);
}

// adds AI
struct MANGOS_DLL_DECL mob_cult_fanaticAI : public ScriptedAI
{
    mob_cult_fanaticAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiCleaveTimer;
    uint32 m_uiNecroticStrikeTimer;
    uint32 m_uiTransformationTimer;
    uint32 m_uiVampiricMightTimer;
    bool m_bEmpowered;

    void Reset()
    {
        m_uiCleaveTimer = urand(4000, 8000);
        m_uiNecroticStrikeTimer = urand(5000, 10000);
        m_uiTransformationTimer = urand(20000, 60000);
        m_uiVampiricMightTimer = urand(20000, 60000);
        m_bEmpowered = false;
    }

    void JustReachedHome()
    {
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiCleaveTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_CLEAVE) == CAST_OK)
                m_uiCleaveTimer = urand(4000, 8000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        if (m_uiNecroticStrikeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_NECROTIC_STRIKE) == CAST_OK)
                m_uiNecroticStrikeTimer = urand(5000, 10000);
        }
        else
            m_uiNecroticStrikeTimer -= uiDiff;

        if (m_bEmpowered)
        {
            if (m_uiVampiricMightTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_VAMPIRIC_MIGHT) == CAST_OK)
                    m_uiVampiricMightTimer = urand(20000, 40000);
            }
            else
                m_uiVampiricMightTimer -= uiDiff;
        }

        if (m_uiTransformationTimer <= uiDiff && m_creature->GetEntry() == NPC_CULT_FANATIC && !m_bEmpowered)
        {
            if (Unit *pLady = m_pInstance->GetSingleCreatureFromStorage(NPC_LADY_DEATHWHISPER))
            {
                if (roll_chance_i(33))
                {
                    pLady->CastSpell(m_creature, SPELL_DARK_TRANSFORMATION, false);
                    m_creature->UpdateEntry(NPC_DEFORMED_FANATIC);
                    m_creature->SetSpeedRate(MOVE_WALK, 0.5f);
                    m_creature->SetSpeedRate(MOVE_RUN, 0.5f);
                }
                else if (roll_chance_i(50))
                {
                    pLady->CastSpell(m_creature, SPELL_DARK_EMPOWERMENT, false);
                    m_bEmpowered = true;
                }
                else
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_DARK_MARTYRDOM) == CAST_OK)
                    {
                        DoCastSpellIfCan(m_creature, SPELL_FANATICS_DETERMINATION, CAST_TRIGGERED);
                        m_creature->UpdateEntry(NPC_REANIMATED_FANATIC);
                    }
                }
            }
        }
        else
            m_uiTransformationTimer -= uiDiff;

        if (m_creature->GetEntry() == NPC_REANIMATED_FANATIC && !m_creature->HasAura(SPELL_FANATICS_DETERMINATION))
            DoCastSpellIfCan(m_creature, SPELL_FANATICS_DETERMINATION, CAST_TRIGGERED);


        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_cult_fanatic(Creature* pCreature)
{
    return new mob_cult_fanaticAI(pCreature);
}

struct MANGOS_DLL_DECL mob_cult_adherentAI : public ScriptedAI
{
    mob_cult_adherentAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiTransformationTimer;
    uint32 m_uiFrostFeverTimer;
    uint32 m_uiShroudTimer;
    uint32 m_uiDeathchillTimer;
    uint32 m_uiCurseOfTorporTimer;
    bool m_bEmpowered;

    void Reset()
    {
        m_uiTransformationTimer = urand(20000, 60000);
        m_uiCurseOfTorporTimer  = urand(5000, 10000);
        m_uiDeathchillTimer     = urand(3000, 5000);
        m_uiFrostFeverTimer     = urand(5000, 10000);
        m_uiShroudTimer         = urand(15000, 30000);
        m_bEmpowered = false;
    }

    void JustReachedHome()
    {
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFrostFeverTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_FROST_FEVER) == CAST_OK)
                    m_uiFrostFeverTimer = urand(5000, 10000);
            }
        }
        else
            m_uiFrostFeverTimer -= uiDiff;

        if (m_uiDeathchillTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, m_creature->HasAura(SPELL_SHROUD_OF_THE_OCCULT) ? SPELL_DEATHCHILL_BLAST : SPELL_DEATHCHILL_BOLT) == CAST_OK)
                    m_uiDeathchillTimer = urand(3000, 5000);
            }
        }
        else
            m_uiDeathchillTimer -= uiDiff;

        if (m_uiCurseOfTorporTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_CURSE_OF_TORPOR) == CAST_OK)
                    m_uiCurseOfTorporTimer = urand(5000, 15000);
            }
        }
        else
            m_uiCurseOfTorporTimer -= uiDiff;

        if (m_bEmpowered)
        {
            if (m_uiShroudTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_SHROUD_OF_THE_OCCULT) == CAST_OK)
                    m_uiShroudTimer = urand(30000, 40000);
            }
            else
                m_uiShroudTimer -= uiDiff;
        }

        if (m_uiTransformationTimer <= uiDiff && m_creature->GetEntry() == NPC_CULT_ADHERENT && !m_bEmpowered)
        {
            if (roll_chance_i(50))
            {
                if (Unit *pLady = m_pInstance->GetSingleCreatureFromStorage(NPC_LADY_DEATHWHISPER))
                {
                    pLady->CastSpell(m_creature, SPELL_DARK_EMPOWERMENT, false);
                    m_bEmpowered = true;
                }
            }
            else
            {
                if (DoCastSpellIfCan(m_creature, SPELL_DARK_MARTYRDOM) == CAST_OK)
                {
                    DoCastSpellIfCan(m_creature, SPELL_ADHERENTS_DETERMINATION, CAST_TRIGGERED);
                    m_creature->UpdateEntry(NPC_REANIMATED_ADHERENT);
                }
            }
        }
        else
            m_uiTransformationTimer -= uiDiff;

        if (m_creature->GetEntry() == NPC_REANIMATED_ADHERENT && !m_creature->HasAura(SPELL_ADHERENTS_DETERMINATION))
            DoCastSpellIfCan(m_creature, SPELL_ADHERENTS_DETERMINATION, CAST_TRIGGERED);

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_cult_adherent(Creature* pCreature)
{
    return new mob_cult_adherentAI(pCreature);
}

void AddSC_boss_lady_deathwhisper()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_lady_deathwhisper";
    pNewScript->GetAI = &GetAI_boss_lady_deathwhisper;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_cult_adherent";
    pNewScript->GetAI = &GetAI_mob_cult_adherent;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_cult_fanatic";
    pNewScript->GetAI = &GetAI_mob_cult_fanatic;
    pNewScript->RegisterSelf();

}
