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
SDName: boss_the_lich_king
SD%Complete: 85%
SDComment: by carlos93 tnx Walkum
SDCategory: Icecrown Citadel
EndScriptData */

// TODO:
// Implement Frostmourne phase
// Implement the Necrotic plague buff

#include "precompiled.h"
#include "icecrown_citadel.h"
#include "Vehicle.h"

enum BossSpells
{
    //////////////// LICH KING ////////////////
    // Phase 1
    SPELL_INFEST                        = 70541,
    SPELL_NECROTIC_PLAGUE               = 70337,
    SPELL_SUMMON_SHAMBLING_HORROR       = 70372,
    SPELL_SUMMON_DRUDGE_GHOULS          = 70358,
    SPELL_SUMMON_SHADOW_TRAP            = 73539, // Heroic only

    // Phase 2
    SPELL_SOUL_REAPER                   = 69409,
    SPELL_SUMMON_DEFILE                 = 72762,
    SPELL_SUMMON_VALKYR_10              = 69037,
    SPELL_SUMMON_VALKYR_25              = 74361,

    // Phase 3
    SPELL_HARVEST_SOUL                  = 68980,
    SPELL_HARVEST_SOULS                 = 74296,
    SPELL_SUMMON_VILE_SPIRITS           = 70498,

    // Intro / Outro visuals
    SPELL_STAND_UP                      = 73220,
    SPELL_ICE_LOCK                      = 71614,
    SPELL_RAISE_DEAD                    = 71769,
    SPELL_BROKEN_FROSTMOURNE            = 72398,
    SPELL_BOOM_VISUAL                   = 72726,  
    SPELL_LIGHTS_BLESSING               = 71797,
    SPELL_FROSTMOURNE_TRIGGER           = 72405,
    SPELL_SUMMON_BROKEN_FROSTMOURNE     = 72406,
    SPELL_SUMMON_BROKEN_FROSTMOURNE_2   = 73017,
    SPELL_FURY_OF_FROSTMOURNE           = 72350,
    SPELL_BERSERK                       = 47008,
    SPELL_SUMMON_TERENAS                = 72420,
    SPELL_SOUL_BARRAGE                  = 72305,

    // Transition phase
    SPELL_REMORSELESS_WINTER            = 68981,
    SPELL_PAIN_AND_SUFFERING            = 72133,
    SPELL_SUMMON_ICE_SPHERE             = 69104,
    SPELL_SUMMON_RAGING_SPIRIT          = 69200,
    SPELL_QUAKE                         = 72262,

    // Defile
    SPELL_DEFILE                        = 72743,
    SPELL_DEFILE_GROW                   = 72756,

    // Raging spirit
    SPELL_SOUL_SHRIEK                   = 69242,
    SPELL_CLONE                         = 69198,

    // Ice sphere
    SPELL_ICE_PULSE                     = 69091,
    SPELL_ICE_BURST                     = 69108,
    SPELL_ICE_SPHERE_VISUAL             = 69090,

    // Shadow Trap
    SPELL_SHADOW_TRAP                   = 73529,
    SPELL_SHADOW_TRAP_VISUAL            = 73525,

    // Shambling horror
    SPELL_SHOCKWAVE                     = 72149,
    SPELL_HORROR_ENRAGE                 = 72143,
    SPELL_HORROR_FRENZY                 = 28747,

    // Vile spirits
    SPELL_VILE_SPIRITS                  = 70497,
    SPELL_SPIRITS_BURST                 = 70503,

    // Valkyr
    SPELL_WINGS_OF_THE_DAMNED           = 74352,
    SPELL_VALKYR_CHARGE                 = 74399,
    SPELL_VALKYR_CARRY                  = 74445,
    SPELL_VALKYR_EJECT                  = 68576,
    SPELL_LIFE_SIPHON                   = 73783,

    // Terenas Menethil Final
    SPELL_MASS_RESURRECT                = 72429,

    // Spirit Warden
    SPELL_SOULRIP                       = 69397,
    SPELL_DESTROY_SOUL                  = 74086,
    SPELL_DARK_HUNGER                   = 69383,

    // Terenas Menethil Inside Frostmourne
    SPELL_LIGHTS_FAVOR                  = 69382,
    SPELL_RESTORE_SOUL                  = 72592,
    SPELL_RESTORE_SOUL_HERO             = 73650,

    // Npcs
    NPC_VALKYR                          = 36609,
    NPC_ICE_SPHERE                      = 36633,
    NPC_SHADOW_TRAP                     = 39137,
    NPC_DEFILER                         = 38757,
    NPC_RAGING_SPIRIT                   = 36701,
    NPC_VILE_SPIRIT                     = 37799,
    NPC_STRANGULATE_VEHICLE             = 36598,
    NPC_WICKED_SPIRIT                   = 39190,

};

// talks
enum
{
    SAY_INTRO_1                 = -1631158,
    SAY_INTRO_2                 = -1631159,
    SAY_INTRO_3                 = -1631160,
    SAY_INTRO_4                 = -1631161,
    SAY_INTRO_5                 = -1631162,
    SAY_AGGRO                   = -1631163,
    SAY_REMORSELESS_WINTER      = -1631164,
    SAY_SHATTER_ARENA           = -1631165,
    SAY_SUMMON_VALKYR           = -1631166,
    SAY_DEFILE                  = -1631596,
    SAY_HARVEST_SOUL            = -1631167,
    SAY_FM_TERENAS_AID_1        = -1631168,
    SAY_FM_TERENAS_AID_2        = -1631169,
    SAY_FM_TERENAS_AID_3        = -1631170,
    SAY_FM_PLAYER_ESCAPE        = -1631171,
    SAY_FM_PLAYER_DEATH         = -1631172,
    SAY_SPECIAL_1               = -1631173,
    SAY_SPECIAL_2               = -1631174,
    SAY_LAST_PHASE              = -1631175,
    SAY_SLAY_1                  = -1631176,
    SAY_SLAY_2                  = -1631177,
    SAY_ENRAGE                  = -1631178,
    SAY_OUTRO_1                 = -1631179,
    SAY_OUTRO_2                 = -1631180,
    SAY_OUTRO_3                 = -1631181,
    SAY_OUTRO_4                 = -1631182,
    SAY_OUTRO_5                 = -1631183,
    SAY_OUTRO_6                 = -1631184,
    SAY_OUTRO_7                 = -1631185,
    SAY_OUTRO_8                 = -1631186,
    SAY_OUTRO_9                 = -1631187,
    SAY_OUTRO_10                = -1631188,
    SAY_OUTRO_11                = -1631189,
    SAY_OUTRO_12                = -1631190,
    SAY_OUTRO_13                = -1631191,
    SAY_OUTRO_14                = -1631192,
};

enum Common
{
     FINAL_ARTHAS_MOVIE         = 16,
};

enum Points
{
    POINT_CENTER                = 10,
    POINT_WEST                  = 11,
    POINT_EAST                  = 12,
};

enum Equipment
{
    EQUIP_MAIN_LK           = 36942,
    EQUIP_MAIN_TIRION       = 13262,
    EQUIP_OFFHAND        = EQUIP_NO_CHANGE,
    EQUIP_RANGED         = EQUIP_NO_CHANGE,
    EQUIP_DONE           = EQUIP_NO_CHANGE,
};

static Locations SpawnLoc[]=
{
    {459.93689f, -2124.638184f, 1040.860107f},    // 0 Lich King Intro
    {503.15652f, -2124.516602f, 1040.860107f},    // 1 Lich king move end
    {491.27118f, -2124.638184f, 1040.860107f},    // 2 Tirion 1
    {481.69797f, -2124.638184f, 1040.860107f},    // 3 Tirion 2
    {498.00448f, -2201.573486f, 1046.093872f},    // 4 Valkyrs?
    {517.48291f, -2124.905762f, 1040.861328f},    // 5 Tirion?
    {502.66f, -2124.43f, 1040.859985f},           // 6 Lich king final (blizzlike), o=3.1146
    {520.311f, -2124.709961f, 1040.859985f},      // 7 Frostmourne
    {517.378f, -2124.905762f, 1040.861328f},      // 8 Tirion see Lich
    {502.66f, -2124.43f, 1040.859985f},           // 9 Tirion jumps
    {503.97330f, -2123.921800f, 1057.4666000f},   // 10 Valkyr Center (heroic)
    {503.37330f, -2213.671800f, 1043.6766000f},   // 11 Valkyr West
    {502.66666f, -2041.245483f, 1043.7098000f},   // 12 Valkyr East
};

struct MANGOS_DLL_DECL boss_the_lich_king_icc_eventAI : public ScriptedAI
{
    boss_the_lich_king_icc_eventAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;

        m_bMovementStarted = false;
        m_bIsIntroStarted = false;
        m_bIsIntroFinished = false;
        m_bIsOutroStarted = false;

        m_guidTirion.Clear();
        m_guidMenethil.Clear();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;

    ObjectGuid m_guidTirion;
    ObjectGuid m_guidMenethil;

    bool m_bIs25Man;
    bool m_bIsHeroic;
    bool m_bMovementStarted;
    bool m_bIsIntroStarted;
    bool m_bIsIntroFinished;
    bool m_bIsOutroStarted;

    uint32 m_uiNextEventTimer;
    uint32 m_uiEventStep;

    void Reset()
    {
        if (!m_pInstance)
            return;

        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;

        m_bMovementStarted = false;
        m_bIsIntroStarted = false;
        m_bIsIntroFinished = false;
        m_bIsOutroStarted = false;

        m_guidTirion.Clear();
        m_guidMenethil.Clear();
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !m_bMovementStarted)
            return;

        if (id)
        {
            m_bMovementStarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id, Unit *pTarget)
    {
        pTarget->GetMotionMaster()->Clear();
        pTarget->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        m_bMovementStarted = true;
    }

    virtual void UpdateFightAI(const uint32 uiDiff) {}

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS && !m_bIsIntroStarted)
        {
            m_bIsIntroStarted = true;
            m_bIsIntroFinished = false;
            NextStep();
        }

        if (m_creature->GetHealthPercent() <= 10.0f && !m_bIsOutroStarted)
        {
            m_bIsOutroStarted = true;
            NextStep();
        }

        if (m_bIsIntroStarted && !m_bIsIntroFinished)
        {
            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep)
                {
                case 0:
                    break;
                case 1:
                    m_creature->CastSpell(m_creature, SPELL_STAND_UP, true);
                    NextStep(2000);
                    break;
                case 2:
                    if (Creature* pTemp = m_creature->GetClosestCreatureWithEntry(m_creature, NPC_TIRION, 200.0f))
                    {
                        m_guidTirion = pTemp->GetObjectGuid();
                        pTemp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        pTemp->SetWalk(true);
                        StartMovement(2, pTemp);
                        NextStep(3000);
                    }
                    m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                    break;
                case 3:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        m_creature->HandleEmote(EMOTE_STATE_TALK);
                        pTemp->HandleEmote(EMOTE_STATE_READY2H);
                        DoScriptText(SAY_INTRO_1, m_creature);
                        StartMovement(0, m_creature);
                        NextStep(13500);
                    }
                    break;
                case 4:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        m_creature->HandleEmote(EMOTE_STATE_NONE);
                        DoScriptText(SAY_INTRO_2, pTemp);
                        NextStep(9000);
                    }
                    break;
                case 5:
                    DoScriptText(SAY_INTRO_3, m_creature);
                    NextStep(8000);
                    break;
                case 6:
                    m_creature->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                    NextStep(3000);
                    break;
                case 7:
                    m_creature->HandleEmote(EMOTE_ONESHOT_POINT);
                    NextStep(12000);
                    break;
                case 8:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        pTemp->HandleEmote(EMOTE_ONESHOT_POINT);
                        DoScriptText(SAY_INTRO_4, pTemp);
                        NextStep(4000);
                        break;
                    }
                case 9:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        pTemp->SetWalk(false);
                        StartMovement(3, pTemp);
                        NextStep(500);
                        break;
                    }
                case 10:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        m_creature->CastSpell(pTemp, SPELL_ICE_LOCK, true);
                        NextStep(1500);
                    }
                    break;
                case 11:
                    m_creature->HandleEmote(EMOTE_STATE_TALK);
                    DoScriptText(SAY_INTRO_5, m_creature);
                    NextStep(18000);
                    break;
                case 12:
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(true);
                    m_bIsIntroFinished = true;
                    m_creature->SetInCombatWithZone();
                    m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                    m_creature->SetSpeedRate(MOVE_WALK, 1.17f);
                    NextStep();
                    break;
                case 13:
                    break;
                default:
                    break;
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;
        }

        if (m_bIsOutroStarted)
        {
            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep)
                {
                case 14:
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    m_creature->CastSpell(m_creature, SPELL_FURY_OF_FROSTMOURNE, false);
                    m_creature->AttackStop();
                    SetCombatMovement(false);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    m_creature->SetOrientation(0.0f);
                    DoScriptText(SAY_OUTRO_1, m_creature);
                    NextStep(28000);
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        m_creature->SetInCombatWith(pTemp);
                        pTemp->AddThreat(m_creature, 1000.0f);
                    }
                    m_creature->SetInCombatWithZone();
                    break;
                case 15:
                    DoScriptText(SAY_OUTRO_2, m_creature);
                    NextStep(9000);
                    break;
                case 16:
                    DoScriptText(SAY_OUTRO_3, m_creature);
                    NextStep(23000);
                    break;
                case 17:
                    StartMovement(6, m_creature);
                    NextStep(5000);
                    break;
                case 18:
                    DoScriptText(SAY_OUTRO_4, m_creature);
                    m_creature->CastSpell(m_creature, SPELL_RAISE_DEAD, false);
                    NextStep(28000);
                    break;
                case 19:
                    DoScriptText(SAY_OUTRO_5, m_creature);
                    NextStep(8000);
                    break;
                case 20:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        DoScriptText(SAY_OUTRO_6, pTemp);
                        NextStep(9000);
                    }
                    break;
                case 21:
                    NextStep(3000);
                    break;
                case 22:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        pTemp->CastSpell(pTemp, SPELL_LIGHTS_BLESSING, true);
                        NextStep(7000);
                    }
                    break;
                case 23:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        pTemp->SetWalk(false);
                        pTemp->RemoveAurasDueToSpell(SPELL_ICE_LOCK);
                        pTemp->SetFacingToObject(m_creature);
                        NextStep(1000);
                    }
                    break;
                case 24:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        StartMovement(2, pTemp);
                        pTemp->HandleEmote(EMOTE_STATE_READY2H);
                        NextStep(500);
                    }
                    break;
                case 25:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                      pTemp->GetMotionMaster()->MoveJump(SpawnLoc[5].x, SpawnLoc[5].y, SpawnLoc[5].z, 20.0f, 8.0f);
                      NextStep(500);
                    }
                    break;
                case 26:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        m_creature->RemoveAurasDueToSpell(SPELL_RAISE_DEAD);
                        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED);
                        pTemp->CastSpell(m_creature, SPELL_BOOM_VISUAL, true);
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_BROKEN_FROSTMOURNE_2, true);
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_BROKEN_FROSTMOURNE, false);
                        DoScriptText(SAY_OUTRO_7, m_creature);
                        pTemp->HandleEmote(EMOTE_ONESHOT_SPECIALATTACK1H);
                        pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        NextStep(3000);
                    }
                    break;
                case 27:
                    NextStep();
                    break;
                case 28:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        pTemp->SetFacingToObject(m_creature);
                        DoScriptText(SAY_OUTRO_8, pTemp);
                        NextStep(0);
                    }
                    break;
                case 29:
                    float x, y, z;
                    if (Unit *pFrostmourne = m_creature->SummonCreature(NPC_FROSTMOURNE_HOLDER, SpawnLoc[6].x - 1, SpawnLoc[6].y, SpawnLoc[6].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 5000))
                    {
                        if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                        {
                            pFrostmourne->CastSpell(pFrostmourne, SPELL_BROKEN_FROSTMOURNE, true);
                            pFrostmourne->CastSpell(pFrostmourne, SPELL_FROSTMOURNE_TRIGGER, true);
                            m_creature->RemoveAurasDueToSpell(SPELL_SUMMON_BROKEN_FROSTMOURNE);
                            m_creature->RemoveAllAuras();
                            m_creature->GetPosition(x, y, z);
                            m_creature->GetMotionMaster()->MovePoint(0, x, y, z + 2.0f);
                            m_creature->CastSpell(m_creature, SPELL_SOUL_BARRAGE, true);
                            pTemp->CastSpell(pFrostmourne, SPELL_SUMMON_TERENAS, false);
                        }
                    }
                    NextStep(8000);
                    break;
                case 30:
                    if (Creature* pMenethil = m_creature->GetClosestCreatureWithEntry(m_creature, NPC_MENETHIL, 200.0f))
                    {
                        m_guidMenethil = pMenethil->GetObjectGuid();
                        DoScriptText(SAY_OUTRO_9, pMenethil);
                    }
                    NextStep(12000);
                    break;
                case 31:
                    if (Creature *pMenethil = m_creature->GetMap()->GetCreature(m_guidMenethil))
                    {
                        DoScriptText(SAY_OUTRO_10, pMenethil);
                        pMenethil->CastSpell(pMenethil, SPELL_MASS_RESURRECT, false);
                    }
                    NextStep(6000);
                    break;
                case 32:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        if (Creature *pMenethil = m_creature->GetMap()->GetCreature(m_guidMenethil))
                        {
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pTemp->SetInCombatWith(m_creature);
                            m_creature->SetInCombatWith(m_creature);
                            pTemp->AI()->AttackStart(m_creature);
                            pMenethil->AI()->AttackStart(m_creature);
                            pTemp->GetMotionMaster()->MoveChase(m_creature);
                        }
                    }
                    NextStep(6000);
                    break;
                case 33:
                    DoScriptText(SAY_OUTRO_12, m_creature);
                    SetCombatMovement(false);
                    NextStep(12000);
                    break;
                case 34:
                    DoScriptText(SAY_OUTRO_13, m_creature);
                    NextStep(12000);
                    break;
                case 35:
                    if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidTirion))
                    {
                        if (m_creature->GetHealthPercent() <= 5.0f)
                        {
                            DoScriptText(SAY_OUTRO_11, pTemp);
                            NextStep();
                        }
                    }
                    break;
                case 36:
                    break;
                default:
                    break;
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;
        }

        UpdateFightAI(uiDiff);
    }
};

struct MANGOS_DLL_DECL boss_the_lich_king_iccAI : public boss_the_lich_king_icc_eventAI
{
    boss_the_lich_king_iccAI(Creature* pCreature) : boss_the_lich_king_icc_eventAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        oldflag = 0;
        m_bIsFinalPhase = false;
        m_bIsEnrage = false;
        m_bInFrostmourne = false;
        mobsGUIDList.clear();
        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;
        m_uiNecroticPlagueTimer = 30000;
        m_uiInfestTimer = 20000;
        m_uiShadowTrapTimer = urand(30000, 35000);
        m_uiDrudgeGhoulsTimer = 10000;
        m_uiShamblingHorrorTimer = 20000;
        m_uiRagingSpiritTimer = 17000;
        m_uiIceSphereTimer = 2000;
        m_uiPainAndSufferingTimer = 2000;
        m_uiDefileTimer = 30000;
        m_uiValkyrTimer = 45000;
        m_uiSoulReaperTimer = 30000;
        m_uiVileSpiritsTimer = 30000;
        m_uiHarvestSoulTimer = 10000;
        m_uiEnrageTimer = 15 * MINUTE * IN_MILLISECONDS;
    }

    ScriptedInstance* m_pInstance;

    Creature* pTirion;
    Creature* pFrostmourne;
    std::list<ObjectGuid> mobsGUIDList;

    bool m_bIsFinalPhase;
    bool m_bIsEnrage;
    bool m_bInFrostmourne;
    bool m_bIs25Man;
    bool m_bIsHeroic;

    Difficulty m_uiMapDifficulty;

    uint32 oldflag;

    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;
    uint32 m_uiVileSpiritsTimer;
    uint32 m_uiInfestTimer;
    uint32 m_uiDrudgeGhoulsTimer;
    uint32 m_uiShamblingHorrorTimer;
    uint32 m_uiNecroticPlagueTimer;
    uint32 m_uiShadowTrapTimer;
    uint32 m_uiRagingSpiritTimer;
    uint32 m_uiIceSphereTimer;
    uint32 m_uiPainAndSufferingTimer;
    uint32 m_uiDefileTimer;
    uint32 m_uiValkyrTimer;
    uint32 m_uiSoulReaperTimer;
    uint32 m_uiHarvestSoulTimer;
    uint32 m_uiEnrageTimer;

    void ResetFight()
    {
        if(!m_pInstance)
            return;

        mobsGUIDList.clear();
        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;
        m_uiNecroticPlagueTimer = 30000;
        m_uiInfestTimer = 20000;
        m_uiShadowTrapTimer = urand(30000, 35000);
        m_uiDrudgeGhoulsTimer = 10000;
        m_uiShamblingHorrorTimer = 20000;
        m_uiRagingSpiritTimer = 17000;
        m_uiIceSphereTimer = 2000;
        m_uiPainAndSufferingTimer = 1500;
        m_uiDefileTimer = 30000;
        m_uiValkyrTimer = 45000;
        m_uiSoulReaperTimer = 30000;
        m_uiVileSpiritsTimer = 30000;
        m_uiHarvestSoulTimer = 10000;
        m_uiEnrageTimer = 15 * MINUTE * IN_MILLISECONDS;

        m_creature->SetOrientation(0.0f);
        m_pInstance->SetData(TYPE_LICH_KING, NOT_STARTED);

        if (GameObject* pGoBolvarChained = GetClosestGameObjectWithEntry(m_creature, 202437, 100.0f))
               pGoBolvarChained->Delete();

        m_creature->SummonGameobject(202437, 425.089f, -2123.31f, 1058.68f, 0, 0);

        if (GameObject* pGoFrostyWind = GetClosestGameObjectWithEntry(m_creature, 202188, 100.0f))
               pGoFrostyWind->Delete();

        m_creature->SummonGameobject(202188, 503.62f, -2124.66f, 1036.61f, 0, 0);

        if (oldflag)
            if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PLATFORM))
            {
               pGoFloor->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
               pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,oldflag);
            }

        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_1, 100.0f))
            pGoSnowEdge->SetGoState(GO_STATE_READY);

        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_2, 100.0f))
            pGoSnowEdge->SetGoState(GO_STATE_READY);

        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_3, 100.0f))
            pGoSnowEdge->SetGoState(GO_STATE_READY);

        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_4, 100.0f))
            pGoSnowEdge->SetGoState(GO_STATE_READY);

        if (Creature *pTirion = m_pInstance->GetSingleCreatureFromStorage(NPC_TIRION))
            pTirion->AI()->EnterEvadeMode();
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !m_bMovementStarted)
            return;

        if (id)
        {
            m_bMovementStarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id)
    {
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        m_bMovementStarted = true;
    }

    void EnterEvadeMode()
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS && (m_bIsFinalPhase || m_bInFrostmourne))
            return;

        DespawnMobs();
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);
        m_creature->LoadCreatureAddon();
        m_bIsFinalPhase = false;
        m_bInFrostmourne = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_pInstance->SetData(TYPE_LICH_KING, FAIL);
        if (m_creature->isAlive())
            m_creature->GetMotionMaster()->MoveTargetedHome();

        m_creature->SetLootRecipient(NULL);

        ResetFight();
    }

    void KilledUnit(Unit* pVictim)
    {
        if (m_bIsFinalPhase)
            return;

        DoScriptText(SAY_SLAY_1 - urand(0, 1), m_creature, pVictim);
    }

    void JustReachedHome()
    {
        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_LICH_KING, FAIL);
        m_bIsFinalPhase = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if (Creature *pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_TIRION))
            pTemp->AI()->EnterEvadeMode();
    }

    void JustSummoned(Creature* pSummoned)
    {
        if(!m_pInstance || !pSummoned)
            return;

        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))  // Should be 1, 0 its for debug
        {
           pSummoned->SetInCombatWith(pTarget);
           pSummoned->AddThreat(pTarget, 100.0f);
        }

        mobsGUIDList.push_back(pSummoned->GetObjectGuid());
    }

    void DespawnMobs()
    {
        if (mobsGUIDList.empty())
            return;

        for(std::list<ObjectGuid>::iterator itr = mobsGUIDList.begin(); itr != mobsGUIDList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                {
                    pTemp->DeleteThreatList();
                    pTemp->CombatStop(true);
                    pTemp->DealDamage(pTemp, pTemp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }
        }
        mobsGUIDList.clear();
    }


    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        DoScriptText(SAY_AGGRO, m_creature);
        m_pInstance->SetData(TYPE_LICH_KING, IN_PROGRESS);
        DoPlaySoundToSet(m_creature, 17458);
    }

    void JustDied(Unit *killer)
    {
        if(!m_pInstance)
            return;

        float x, y, z;
        m_creature->GetPosition(x, y, z);
        m_creature->GetMotionMaster()->MovePoint(0, x, y, z - 2.0f);

        DoScriptText(SAY_OUTRO_14, m_creature);
        m_pInstance->SetData(TYPE_LICH_KING, DONE);

        DespawnMobs();

    }

    void UpdateFightAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_pInstance)
            return;

        if (!m_creature->SelectHostileTarget() && !m_bIsFinalPhase && !m_bInFrostmourne)
        {
            m_pInstance->SetData(TYPE_LICH_KING, FAIL);
            EnterEvadeMode();
            return;
        }

        if (m_uiEnrageTimer < uiDiff && !m_bIsEnrage && !m_bIsFinalPhase)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                m_uiEnrageTimer = 15*MINUTE*IN_MILLISECONDS;
                m_bIsEnrage = true;
            }
        }
        else m_uiEnrageTimer -= uiDiff;

        if (m_uiNextEventTimer <= uiDiff)
        {
            switch (m_uiEventStep)
            {
            case 0: // Phase 1

                    // Infest
                    if (m_uiInfestTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_INFEST) == CAST_OK)
                            m_uiInfestTimer = 30000;
                    }
                    else m_uiInfestTimer -= uiDiff;

                    // Drudge Ghouls
                    if (m_uiDrudgeGhoulsTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_DRUDGE_GHOULS) == CAST_OK)
                            m_uiDrudgeGhoulsTimer = urand (20000, 22000);
                    }
                    else m_uiDrudgeGhoulsTimer -= uiDiff;

                    // Shambling Horror
                    if (m_uiShamblingHorrorTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_SHAMBLING_HORROR) == CAST_OK)
                            m_uiShamblingHorrorTimer = 60000;
                    }
                    else m_uiShamblingHorrorTimer -= uiDiff;

                    // Necrotic Plague                 
                    if (m_uiNecroticPlagueTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget,SPELL_NECROTIC_PLAGUE) == CAST_OK)
                                m_uiNecroticPlagueTimer = urand(30000, 35000);
                        }
                    }
                    else m_uiNecroticPlagueTimer -= uiDiff;

                    // Shadow Trap (only hero)
                    if (m_bIsHeroic)
                    {
                        if (m_uiShadowTrapTimer < uiDiff)
                        {
                            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                            {
                                if (DoCastSpellIfCan(pTarget,SPELL_SUMMON_SHADOW_TRAP) == CAST_OK)
                                    m_uiShadowTrapTimer = urand(30000, 35000);
                            }
                        }
                        else m_uiShadowTrapTimer -= uiDiff;
                    }

                    if (m_creature->GetHealthPercent() < 70.0f)
                    {
                        NextStep();
                    }

                    DoMeleeAttackIfReady();
                    break;

            case 1: // Go in transition phase
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    DoPlaySoundToSet(m_creature, 17459);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(false);
                    StartMovement(1);
                    NextStep();
                    break;
            case 2:
                    if (m_bMovementStarted)
                        return;

                    m_creature->CastSpell(m_creature, SPELL_REMORSELESS_WINTER, false);

                    DoScriptText(SAY_REMORSELESS_WINTER, m_creature);
                    NextStep(3000);
                    break;
            case 3:
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_1, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_2, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_3, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_ICESHARD_4, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    NextStep();
                    break;
            case 4:
                    // Raging Spirit
                    if (m_uiRagingSpiritTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_SUMMON_RAGING_SPIRIT) == CAST_OK)
                                m_uiRagingSpiritTimer = 17000;
                        }
                    }
                    else m_uiRagingSpiritTimer -= uiDiff;

                    // Ice Sphere
                    if (m_uiIceSphereTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_ICE_SPHERE) == CAST_OK)
                            m_uiIceSphereTimer = 6000;
                    }
                    else m_uiIceSphereTimer -= uiDiff;

                    // Pain And Suffering
                    if (m_uiPainAndSufferingTimer < uiDiff)
                    {
                            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_PAIN_AND_SUFFERING) == CAST_OK)
                                m_uiPainAndSufferingTimer = 1500;
                        }
                    }
                    else m_uiPainAndSufferingTimer -= uiDiff;

                    if (!m_creature->HasAuraOfDifficulty(SPELL_REMORSELESS_WINTER))
                    {
                        DoScriptText(SAY_SHATTER_ARENA, m_creature);
                        m_creature->CastSpell(m_creature, SPELL_QUAKE, false);
                        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_SNOW_EDGE, 100.0f))
                            pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);
                        NextStep(8000);
                    }
                    break;

            case 5: // Platform destruct
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PLATFORM))
                    {
                         pGoFloor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
                         oldflag = pGoFloor->GetUInt32Value(GAMEOBJECT_BYTES_1);
                         pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,8449);
                    }

                    if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PRECIPICE))
                    {
                         pGoFloor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
                         oldflag = pGoFloor->GetUInt32Value(GAMEOBJECT_BYTES_1);
                         pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,8449);
                    }

                    m_pInstance->DoUseDoorOrButton(GO_ARTHAS_PRECIPICE);

                    if (GameObject* pGoFrostyWind = GetClosestGameObjectWithEntry(m_creature, 202188, 100.0f))
                         pGoFrostyWind->Delete();

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_SNOW_EDGE, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(true);
                    NextStep();
                    break;

            case 6: // Phase 2

                    // Defile
                    if (m_uiDefileTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_SUMMON_DEFILE) == CAST_OK)
                            {
                                DoScriptText(SAY_DEFILE, m_creature);
                                m_uiDefileTimer = 30000;
                            }
                        }
                    }
                    else m_uiDefileTimer -= uiDiff;

                    // Soul Reaper
                    if (m_uiSoulReaperTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SOUL_REAPER) == CAST_OK)
                            m_uiSoulReaperTimer = 30000;
                    }
                    else m_uiSoulReaperTimer -= uiDiff;

                    // Valkyr
                    if (m_uiValkyrTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, m_bIs25Man ? SPELL_SUMMON_VALKYR_25 : SPELL_SUMMON_VALKYR_10) == CAST_OK)
                        {
                            m_uiValkyrTimer = 45000;
                            DoScriptText(SAY_SUMMON_VALKYR,m_creature);
                        }
                    }
                    else m_uiValkyrTimer -= uiDiff;

                    // Infest          
                    if (m_uiInfestTimer < uiDiff)
                    {
                            if (DoCastSpellIfCan(m_creature, SPELL_INFEST) == CAST_OK)
                                m_uiInfestTimer = 30000;
                    }
                    else m_uiInfestTimer -= uiDiff;

                    if (m_creature->GetHealthPercent() < 40.0f)
                    {
                        NextStep();
                    }

                    DoMeleeAttackIfReady();
                    break;
            case 7:           // Go in transition phase
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    DoPlaySoundToSet(m_creature, 17459);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(false);
                    StartMovement(1);
                    NextStep();
                    break;
            case 8:
                    if (m_bMovementStarted)
                        return;

                    m_creature->CastSpell(m_creature, SPELL_REMORSELESS_WINTER, false);

                    DoScriptText(SAY_REMORSELESS_WINTER, m_creature);
                    NextStep(2500);
                    break;
            case 9:         // Platform restore
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PLATFORM))
                    {
                        pGoFloor->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
                        pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,oldflag);
                    }
                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_SNOW_EDGE, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_READY);

                    m_pInstance->DoUseDoorOrButton(GO_ARTHAS_PRECIPICE);

                    NextStep();
                    break;
            case 10:
                    // Raging Spirit
                    if (m_uiRagingSpiritTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_SUMMON_RAGING_SPIRIT) == CAST_OK)
                                m_uiRagingSpiritTimer = 17000;
                        }
                    }
                    else m_uiRagingSpiritTimer -= uiDiff;

                    // Ice Sphere
                    if (m_uiIceSphereTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_ICE_SPHERE) == CAST_OK)
                            m_uiIceSphereTimer = 6000;
                    }
                    else m_uiIceSphereTimer -= uiDiff;

                    // Pain And Suffering
                    if (m_uiPainAndSufferingTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_PAIN_AND_SUFFERING) == CAST_OK)
                                m_uiPainAndSufferingTimer = 1500;
                        }
                    }
                    else m_uiPainAndSufferingTimer -= uiDiff;

                    if (!m_creature->HasAuraOfDifficulty(SPELL_REMORSELESS_WINTER))
                    {
                        DoScriptText(SAY_SHATTER_ARENA, m_creature);
                        m_creature->CastSpell(m_creature, SPELL_QUAKE, false);
                        if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_SNOW_EDGE, 100.0f))
                            pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                        m_creature->SummonGameobject(GO_FROSTY_WIND, 503.62f, -2124.66f, 1036.61f, 0, 0);
                        NextStep(0);
                    }
                    break;
            case 11:           // Platform destruct
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;

                    if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PLATFORM))
                    {
                         pGoFloor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
                         oldflag = pGoFloor->GetUInt32Value(GAMEOBJECT_BYTES_1);
                         pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,8449);
                    }

                    if (GameObject* pGoFloor = m_pInstance->GetSingleGameObjectFromStorage(GO_ARTHAS_PRECIPICE))
                    {
                         pGoFloor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED | GO_FLAG_NODESPAWN);
                         oldflag = pGoFloor->GetUInt32Value(GAMEOBJECT_BYTES_1);
                         pGoFloor->SetUInt32Value(GAMEOBJECT_BYTES_1,8449);
                    }

                    m_pInstance->DoUseDoorOrButton(GO_ARTHAS_PRECIPICE);

                    if (GameObject *pGoFrostyWind = GetClosestGameObjectWithEntry(m_creature, GO_FROSTY_WIND, 100.0f))
                        pGoFrostyWind->Delete();

                    if (GameObject *pGoSnowEdge = GetClosestGameObjectWithEntry(m_creature, GO_SNOW_EDGE, 100.0f))
                        pGoSnowEdge->SetGoState(GO_STATE_ACTIVE);

                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(true);
                    NextStep();
                    break;
            case 12:           // Phase 3

                    // Defile
                    if (m_uiDefileTimer < uiDiff)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_SUMMON_DEFILE) == CAST_OK)
                            {
                                DoScriptText(SAY_DEFILE, m_creature);
                                m_uiDefileTimer = 30000;
                            }
                        }
                    }
                    else m_uiDefileTimer -= uiDiff;

                    // Soul Reaper
                    if (m_uiSoulReaperTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SOUL_REAPER) == CAST_OK)
                            m_uiSoulReaperTimer = 30000;
                    }
                    else m_uiSoulReaperTimer -= uiDiff;

                    // Harvest Soul
                    if (m_uiHarvestSoulTimer < uiDiff)
                    {
                        if (m_bIsHeroic)
                        {
                            if (DoCastSpellIfCan(m_creature, SPELL_HARVEST_SOULS) == CAST_OK)
                            {
                                m_bInFrostmourne = true;
                                m_uiHarvestSoulTimer = 70000;
                                DoScriptText(SAY_HARVEST_SOUL,m_creature);
                            }
                        }
                        if (!m_bIsHeroic)
                        {
                            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                            {
                                if (DoCastSpellIfCan(pTarget, SPELL_HARVEST_SOUL) == CAST_OK)
                                {
                                    m_bInFrostmourne = true;
                                    m_uiHarvestSoulTimer = 70000;
                                    DoScriptText(SAY_HARVEST_SOUL,m_creature);
                                }
                            }
                        }
                    }
                    else m_uiHarvestSoulTimer -= uiDiff;         

                    /*// Vile Spirits
                    if (m_uiVileSpiritsTimer < uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_VILE_SPIRITS) == CAST_OK)
                            m_uiVileSpiritsTimer = 30000;
                    }
                    else
                        m_uiVileSpiritsTimer -= uiDiff;*/

                    if (m_creature->SelectHostileTarget() || m_creature->getVictim())
                        m_bInFrostmourne = false;

                    DoMeleeAttackIfReady();

                    if (m_creature->GetHealthPercent() < 10.0f)
                    {
                        m_bIsFinalPhase = true;
                        m_bInFrostmourne = false;
                        NextStep();
                    }
                    break;
            case 13:           // Ending Phase start
                    break;
            }
        }
        else
            m_uiNextEventTimer -= uiDiff;
    }
};


CreatureAI* GetAI_boss_the_lich_king_icc(Creature* pCreature)
{
    return new boss_the_lich_king_iccAI(pCreature);
};

struct MANGOS_DLL_DECL boss_tirion_iccAI : public ScriptedAI
{
    boss_tirion_iccAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 nextEvent;
    uint32 nextPoint;
    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;
    bool m_bMovementStarted;
    bool m_bTirionStarted;
    ObjectGuid m_guidLichKing;

    void EnterEvadeMode()
    {
        if (!m_pInstance)
            return;
        if (m_pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS)
            return;
    }

    void Reset()
    {
        if(!m_pInstance)
            return;
        m_bMovementStarted = false;
        m_bTirionStarted = false;
        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;
        m_creature->RemoveAurasDueToSpell(SPELL_ICE_LOCK);
        m_creature->SetOrientation(M_PI_F);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE,EMOTE_STATE_NONE);
        SetCombatMovement(false);
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !m_bMovementStarted)
            return;

        if (id)
        {
            m_bMovementStarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id)
    {
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        m_bMovementStarted = true;
    }

    void doSendCinematic()
    {
        Map::PlayerList const &pList = m_creature->GetMap()->GetPlayers();
        if (pList.isEmpty()) return;
        for (Map::PlayerList::const_iterator i = pList.begin(); i != pList.end(); ++i)
             if (Player* pPlayer = i->getSource())
                 if (pPlayer && pPlayer->isAlive() && pPlayer->IsInMap(m_creature))
                     pPlayer->SendMovieStart(FINAL_ARTHAS_MOVIE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_LICH_KING) == FAIL && m_creature->HasAura(SPELL_ICE_LOCK))
        {
            m_creature->RemoveAurasDueToSpell(SPELL_ICE_LOCK);
            m_creature->GetMotionMaster()->MoveTargetedHome();
            Reset();
        }

        if (m_pInstance->GetData(TYPE_LICH_KING) == DONE && !m_bTirionStarted)
        {
            m_bTirionStarted = true;
            NextStep();
        }

        if (m_uiNextEventTimer <= uiDiff && m_bTirionStarted)
        {
            switch (m_uiEventStep)
            {
            case 0:
                break;
            case 1:
                if (Unit* pTemp = m_creature->GetClosestCreatureWithEntry(m_creature, NPC_LICH_KING, 200.0f))
                {
                    m_guidLichKing = pTemp->GetObjectGuid();
                    m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                    pTemp->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                }
                NextStep(5000);
                break;
            case 2:
                if (GameObject* pGoBolvarUnchained = GetClosestGameObjectWithEntry(m_creature, 202437, 100.0f))
                    pGoBolvarUnchained->Delete();

                m_creature->SummonGameobject(202438, 425.089f, -2123.31f, 1058.68f, 0, 0);
                m_creature->SummonGameobject(202436, 426.56f, -2123.86f, 1064.89f, -3.12412f, 0);
                doSendCinematic();
                NextStep(230000);
                break;
            case 3:
                if (Creature* pMenethil = m_creature->GetClosestCreatureWithEntry(m_creature, NPC_MENETHIL, 200.0f))
                {
                    if (pMenethil->isAlive())
                        pMenethil->ForcedDespawn();
                }

                if (Creature *pTemp = m_creature->GetMap()->GetCreature(m_guidLichKing))
                {
                    pTemp->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                }
                NextStep(20000);
                EnterEvadeMode();
                break;
            case 4:
                break;
            default:
                break;
            }
        }
        else
            m_uiNextEventTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_boss_tirion_icc(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* m_pInstance;
    m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (m_pInstance->GetData(TYPE_LICH_KING) != NOT_STARTED &&
        m_pInstance->GetData(TYPE_LICH_KING) != FAIL )
    {
        pPlayer->PlayerTalkClass->SendGossipMenu(721002, pCreature->GetObjectGuid());
        return true;
    };

    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3631608, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    pPlayer->PlayerTalkClass->SendGossipMenu(721001, pCreature->GetObjectGuid());
    return true;
};

bool GossipSelect_boss_tirion_icc(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance* m_pInstance;
    m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    if (!m_pInstance) return false;

    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        m_pInstance->SetData(TYPE_LICH_KING, IN_PROGRESS);
        return true;
    } else return false;
};

CreatureAI* GetAI_boss_tirion_icc(Creature* pCreature)
{
    return new boss_tirion_iccAI(pCreature);
};

struct MANGOS_DLL_DECL  mob_ice_sphere_iccAI : public ScriptedAI
{
    mob_ice_sphere_iccAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiVisualTimer;
    Difficulty m_uiMapDifficulty;
    bool m_bIs25Man;
    bool m_bIsHeroic;
    bool m_bSkin;

    void Reset()
    {
        m_creature->SetWalk(true);
        m_creature->SetSpeedRate(MOVE_WALK, 1.0f);
        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
        m_uiVisualTimer = 2400;
        m_bSkin = false;
        SetCombatMovement(false);
        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
    }

    void Aggro(Unit *pWho)
    {
        if (!pWho)
            return;

        m_creature->CastSpell(pWho, SPELL_ICE_PULSE, true);
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_LICH_KING) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (m_uiVisualTimer < uiDiff && !m_bSkin)
        {
            m_creature->CastSpell(m_creature, SPELL_ICE_SPHERE_VISUAL, false);
            m_creature->SetVisibility(VISIBILITY_ON);
            m_bSkin = true;
        }
        else m_uiVisualTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (Creature *pLich = GetClosestCreatureWithEntry(m_creature, NPC_LICH_KING, 100.0f))
            {
                if (Unit *pTarget = pLich->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                {
                   m_creature->SetInCombatWith(pTarget);
                   m_creature->AddThreat(pTarget, 1000.0f);
                }
            }
        }

        if (m_bSkin)
        {
            SetCombatMovement(true);

            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), 2.0f))
                m_creature->CastSpell(m_creature, SPELL_ICE_BURST, false);

            m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        }
    }
};

CreatureAI* GetAI_mob_ice_sphere_icc(Creature* pCreature)
{
    return new mob_ice_sphere_iccAI(pCreature);
};

struct MANGOS_DLL_DECL mob_defiler_iccAI : public BSWScriptedAI
{
    mob_defiler_iccAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIs25Man;
    bool m_bIsHeroic;
    uint32 m_uiLifeTimer;
    float m_Size0;
    float m_Size;

    void Reset()
    {
        SetCombatMovement(false);
        m_uiLifeTimer = 30000;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, SPELL_DEFILE, true);
        m_Size0 = m_creature->GetObjectScale();
        m_Size = m_Size0;
    }

    void AttackStart(Unit *pWho)
    {

    }

    bool DoSearchPlayers(float range)
    {
        if(GetPlayerAtMinimumRange(m_Size * range))
            return true;
        else
            return false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_pInstance && m_pInstance->GetData(TYPE_LICH_KING) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (m_uiLifeTimer < uiDiff)
        {
            m_creature->ForcedDespawn();
        }
        else m_uiLifeTimer -= uiDiff;

        if (DoSearchPlayers(3.0f) && m_Size <= m_Size0 * 6.0f)
        {
            m_Size = m_Size*1.01;
            m_creature->SetObjectScale(m_Size);
        }
    }

};

CreatureAI* GetAI_mob_defiler_icc(Creature* pCreature)
{
    return new mob_defiler_iccAI(pCreature);
}

struct MANGOS_DLL_DECL mob_strangulate_vehicleAI : public ScriptedAI
{
    mob_strangulate_vehicleAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        SetCombatMovement(false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void AttackStart(Unit *pWho)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
       m_creature->ForcedDespawn();
    }

};

CreatureAI* GetAI_mob_strangulate_vehicle(Creature* pCreature)
{
    return new mob_strangulate_vehicleAI(pCreature);
}

struct MANGOS_DLL_DECL mob_vile_spiritAI : public ScriptedAI
{
    mob_vile_spiritAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_icecrown_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_icecrown_spire *m_pInstance;

    uint32 m_uiStartTimer;

    void Reset()
    {
       SetCombatMovement(false);
       m_creature->SetWalk(true);
       m_uiStartTimer = 15000;
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_LICH_KING) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStartTimer < uiDiff)
        {
           SetCombatMovement(true);
           m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
           m_pInstance->SetSpecialAchievementCriteria(TYPE_NECK_DEEP_IN_VILE, false);
        }
        else m_uiStartTimer -= uiDiff;

        if (m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
        {
           m_creature->CastSpell(m_creature->getVictim(), SPELL_SPIRITS_BURST, true);
           m_creature->ForcedDespawn(100);
        }

        if (m_creature->getVictim()->GetTypeId() != TYPEID_PLAYER)
            return;
    }
};

CreatureAI* GetAI_mob_vile_spirit(Creature* pCreature)
{
    return new mob_vile_spiritAI(pCreature);
}

struct MANGOS_DLL_DECL mob_raging_spiritAI : public ScriptedAI
{
    mob_raging_spiritAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiSoulShriekTimer = 10000;
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiSoulShriekTimer;

    void Reset()
    {
        m_uiSoulShriekTimer = 10000;
    }

    void Aggro(Unit *pWho)
    {
        if (!pWho)
            return;

        pWho->CastSpell(m_creature, SPELL_CLONE, false);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_LICH_KING) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSoulShriekTimer < uiDiff)
        {
            if(DoCastSpellIfCan(m_creature->getVictim(), SPELL_SOUL_SHRIEK))
                m_uiSoulShriekTimer = 10000;
        }
        else m_uiSoulShriekTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_raging_spirit(Creature* pCreature)
{
    return new mob_raging_spiritAI(pCreature);
}

struct MANGOS_DLL_DECL mob_valkyrAI : public ScriptedAI
{
    mob_valkyrAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;
    bool m_bIsCarry;
    bool m_bIsInCenter;
    bool m_bInMovement;
    uint32 m_uiLifeSiphonTimer;

    void Reset()
    {
        m_bIsCarry = false;
        m_bIsInCenter = false;
        m_bInMovement = false;
        m_uiLifeSiphonTimer = 10000;
        SetCombatMovement(true);
        m_creature->SetLevitate(false);
        m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);
    }

    void MovementInform(uint32 uiMovementType, uint32 uiData)
    {
        if (uiMovementType != POINT_MOTION_TYPE)
            return;

        if (uiData == POINT_WEST || uiData == POINT_EAST)
        {
            if (m_bIsCarry)
            {
                //DoCastSpellIfCan(m_creature, SPELL_VALKYR_EJECT);
                if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
                    pVehKit->RemoveAllPassengers();
                m_bIsCarry = false;
                m_bInMovement = false;
            }
        }
        else if (uiData == POINT_CENTER)
        {
            m_bIsInCenter = true;
            m_bInMovement = false;
        }
    }

    void MoveToClosestPoint()
    {
        float WestDistance, EastDistance;
        m_creature->GetMotionMaster()->Clear();
        m_bInMovement = true;

        WestDistance = m_creature->GetDistance2d(SpawnLoc[11].x, SpawnLoc[11].y);
        EastDistance = m_creature->GetDistance2d(SpawnLoc[12].x, SpawnLoc[12].y);

        if (WestDistance < EastDistance)
            m_creature->GetMotionMaster()->MovePoint(POINT_WEST, SpawnLoc[11].x, SpawnLoc[11].y, SpawnLoc[11].z);
        else
            m_creature->GetMotionMaster()->MovePoint(POINT_EAST, SpawnLoc[12].x, SpawnLoc[12].y, SpawnLoc[12].z);
    }

    void Aggro(Unit *pWho)
    {
        if (!m_pInstance || !pWho)
            return;

        DoCastSpellIfCan(m_creature, SPELL_WINGS_OF_THE_DAMNED, CAST_TRIGGERED);
        //m_creature->AddThreat(pWho, 100.0f);
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bIsCarry && (!m_creature->SelectHostileTarget() || !m_creature->getVictim()))
            return;

        if (!m_bIsCarry && m_creature->CanReachWithMeleeAttack(m_creature->getVictim()) && !m_bInMovement && !m_bIsInCenter)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_VALKYR_CARRY) == CAST_OK)
            {
                m_creature->getVictim()->EnterVehicle(m_creature->GetVehicleKit(), 0);
                m_bIsCarry = true;
            }
        }

        if (m_bIsCarry && !m_bInMovement)
            MoveToClosestPoint();

        if (m_bIsHeroic && !m_bIsInCenter)
        {
            if (m_creature->GetHealthPercent() <= 50)
            {
                //DoCastSpellIfCan(m_creature, SPELL_VALKYR_EJECT);
                if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
                    pVehKit->RemoveAllPassengers();
                m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                SetCombatMovement(false);
                m_creature->SetLevitate(true);
                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMotionMaster()->MovePoint(POINT_CENTER, SpawnLoc[10].x + urand(1, 4), SpawnLoc[10].y + urand (1, 4), SpawnLoc[10].z + urand (1, 4));
            }
        }
        if (m_bIsInCenter)
        {
            if (m_uiLifeSiphonTimer < uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    if (DoCastSpellIfCan(pTarget, SPELL_LIFE_SIPHON) == CAST_OK)
                        m_uiLifeSiphonTimer = 10000;
            }
            else m_uiLifeSiphonTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_valkyr(Creature *pCreature)
{
    return new mob_valkyrAI(pCreature);
}

// Frostmourne phase

struct MANGOS_DLL_DECL mob_terenas_frostmourneAI : public ScriptedAI
{
    mob_terenas_frostmourneAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        pVictim = NULL;
        pSpiritWarden = NULL;
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;
    bool m_bEventStarted;
    bool m_bEventFinished;
    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;
    Player *pVictim;
    Unit *pSpiritWarden;

    void Reset()
    {
        if(!m_pInstance)
            return;

        SetCombatMovement(false);
        m_bEventStarted = false;
        m_bEventFinished = false;
        pSpiritWarden = NULL;
        pVictim = NULL;
        m_uiNextEventTimer = 0;
        m_uiEventStep = 0;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!((Player*)pWho)->isGameMaster() && m_creature->GetDistance2d(pWho) < 20.0f)
            m_creature->SetInCombatWithZone();
        else
            return;
    }

    void Aggro(Unit *pWho)
    {
        if (!m_pInstance || !pWho)
            return;

        m_creature->CastSpell(m_creature, SPELL_LIGHTS_FAVOR, true);

        if (m_bIsHeroic)
            m_creature->CastSpell(m_creature, SPELL_RESTORE_SOUL_HERO, false);
    }

    void JustDied(Unit *pKiller)
    {
        if (pSpiritWarden)
            pSpiritWarden->CastSpell(pVictim, SPELL_DESTROY_SOUL, false);
        if (Creature *pLich = GetClosestCreatureWithEntry(m_creature, NPC_LICH_KING, 500.0f))
        {
            DoScriptText(SAY_FM_PLAYER_DEATH ,pLich, pKiller);
        }
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bIsHeroic)
        {
            if (pSpiritWarden = GetClosestCreatureWithEntry(m_creature, NPC_SPIRIT_WARDEN, 20.0f))
            {
                m_creature->SetInCombatWith(pSpiritWarden);
                pSpiritWarden->SetInCombatWith(m_creature);
                m_creature->AI()->AttackStart(pSpiritWarden);
                m_creature->AddThreat(pSpiritWarden, 100000.0f);
            }
        }

        if (GetPlayerAtMinimumRange(20.0f) && m_bEventStarted)
        {
            NextStep();
            m_bEventStarted = true;
        }

        if (m_bEventStarted && !m_bEventFinished)
        {
            if (m_uiNextEventTimer <= uiDiff)
            {
                switch (m_uiEventStep)
                {
                    case 0:
                        break;
                    case 1:
                        DoScriptText(SAY_FM_TERENAS_AID_1, m_creature);
                        NextStep(13000);
                        break;
                    case 2:
                        DoScriptText(SAY_FM_TERENAS_AID_2, m_creature);
                        NextStep(11000);
                        break;
                    case 3:
                        if (!m_bIsHeroic)
                            DoScriptText(SAY_FM_TERENAS_AID_3, m_creature);
                        NextStep();
                        break;
                    case 4:
                        m_bEventFinished = true;
                        NextStep();
                        break;
                    case 5:
                        break;
                    default:
                        break;
                }
            }
            else
                m_uiNextEventTimer -= uiDiff;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_terenas_frostmourne(Creature *pCreature)
{
    return new mob_terenas_frostmourneAI(pCreature);
}

struct MANGOS_DLL_DECL mob_spirit_wardenAI : public ScriptedAI
{
    mob_spirit_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        pTerenasFrostmourne = NULL;
        pVictim = NULL;
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    uint32 m_uiSoulripTimer;
    uint32 m_uiDestroysoulTimer;

    Creature *pTerenasFrostmourne;
    Player *pVictim;

    void Reset()
    {
        m_uiSoulripTimer = 0;
        m_uiDestroysoulTimer = 60000;
        m_creature->SetRespawnDelay(20000);
        pTerenasFrostmourne = NULL;
        pVictim = NULL;
    }

    void JustDied(Unit *pKiller)
    {
        if (pTerenasFrostmourne)
            pTerenasFrostmourne->CastSpell(pVictim, SPELL_RESTORE_SOUL, false);
        if (Creature *pLich = GetClosestCreatureWithEntry(m_creature, NPC_LICH_KING, 500.0f))
        {
            DoScriptText(SAY_FM_PLAYER_ESCAPE ,pLich, pKiller);
        }
    }

    void Aggro(Unit *pWho)
    {
        if(!m_pInstance)
            return;

        if (pTerenasFrostmourne = GetClosestCreatureWithEntry(m_creature, NPC_TERENAS_FROSTMOURNE, 20.0f))
        {
            m_creature->SetInCombatWith(pTerenasFrostmourne);
            pTerenasFrostmourne->SetInCombatWith(m_creature);
            m_creature->AI()->AttackStart(pTerenasFrostmourne);
            m_creature->AddThreat(pTerenasFrostmourne, 100000.0f);
        }
        m_creature->CastSpell(m_creature, SPELL_DARK_HUNGER, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (pVictim = GetPlayerAtMinimumRange(20.0f))
        {
            // Soul rip
            if (m_uiSoulripTimer < uiDiff)
            {
                if (DoCastSpellIfCan(pTerenasFrostmourne, SPELL_SOULRIP) == CAST_OK)
                    m_uiSoulripTimer = 8000;
            }
            else
                m_uiSoulripTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
        else
            return;
    }
};

CreatureAI* GetAI_mob_spirit_warden(Creature *pCreature)
{
    return new mob_spirit_wardenAI(pCreature);
}

/*struct MANGOS_DLL_DECL mob_terenas_menethilAI : public ScriptedAI
{
    mob_terenas_menethilAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    void Reset()
    {

    }

    void AttackStart(Unit *pWho)
    {
        return;
    }
};

CreatureAI* GetAI_mob_terenas_menethil(Creature *pCreature)
{
    return new mob_terenas_menethilAI(pCreature);
}*/

struct MANGOS_DLL_DECL mob_shambling_horrorAI : public ScriptedAI
{
    mob_shambling_horrorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;

    bool m_bIsHeroic;

    uint32 m_uiEnrageTimer;
    uint32 m_uiShockwaveTimer;

    void Reset()
    {
        m_uiEnrageTimer = 20000;
        m_uiShockwaveTimer = urand(13000, 20000);
    }

    void Aggro(Unit *pWho)
    {
        if (!pWho)
            return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiEnrageTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_HORROR_ENRAGE) == CAST_OK)
                m_uiEnrageTimer = 20000;
        }
        else m_uiEnrageTimer -= uiDiff;

        if (m_uiShockwaveTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHOCKWAVE) == CAST_OK)
                m_uiShockwaveTimer = urand(13000, 20000);
        }
        else m_uiShockwaveTimer -= uiDiff;

        if (m_bIsHeroic)
        {
            if (m_creature->GetHealthPercent() <= 20.0f && !m_creature->HasAura(SPELL_HORROR_FRENZY))
            {
                m_creature->CastSpell(m_creature, SPELL_HORROR_FRENZY, false);
            }
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_shambling_horror(Creature *pCreature)
{
    return new mob_shambling_horrorAI(pCreature);
}

struct MANGOS_DLL_DECL mob_shadow_trapAI : public ScriptedAI
{
    mob_shadow_trapAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiWaitTimer;
    uint32 m_uiDespawnTimer;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        SetCombatMovement(false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, SPELL_SHADOW_TRAP_VISUAL, true);
        m_uiWaitTimer = 3000;
        m_uiDespawnTimer = 30000;
        m_uiCheckTimer = 0;
    }

    void AttackStart(Unit *pWho)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiWaitTimer < uiDiff)
        {
            if (m_uiCheckTimer < uiDiff)
            {
                if (Player *pPlayer = GetPlayerAtMinimumRange(m_creature->GetObjectScale() * 3))
                    if (pPlayer)
                        m_creature->CastSpell(m_creature, SPELL_SHADOW_TRAP, false);

                m_uiCheckTimer = 1000;
            }
            else m_uiCheckTimer -= uiDiff;
        }
        else m_uiWaitTimer -= uiDiff;

        if (m_uiDespawnTimer < uiDiff)
            m_creature->ForcedDespawn();
        else m_uiDespawnTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_shadow_trap(Creature *pCreature)
{
    return new mob_shadow_trapAI(pCreature);
}

void AddSC_boss_lich_king_icc()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_the_lich_king_icc";
    newscript->GetAI = &GetAI_boss_the_lich_king_icc;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_tirion_icc";
    newscript->GetAI = &GetAI_boss_tirion_icc;
    newscript->pGossipHello = &GossipHello_boss_tirion_icc;
    newscript->pGossipSelect = &GossipSelect_boss_tirion_icc;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_ice_sphere_icc";
    newscript->GetAI = &GetAI_mob_ice_sphere_icc;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_defiler_icc";
    newscript->GetAI = &GetAI_mob_defiler_icc;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_strangulate_vehicle";
    newscript->GetAI = &GetAI_mob_strangulate_vehicle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_vile_spirit";
    newscript->GetAI = &GetAI_mob_vile_spirit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_raging_spirit";
    newscript->GetAI = &GetAI_mob_raging_spirit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_valkyr";
    newscript->GetAI = &GetAI_mob_valkyr;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_terenas_frostmourne";
    newscript->GetAI = &GetAI_mob_terenas_frostmourne;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_spirit_warden";
    newscript->GetAI = &GetAI_mob_spirit_warden;
    newscript->RegisterSelf();

    /*newscript = new Script;
    newscript->Name = "mob_terenas_menethil";
    newscript->GetAI = &GetAI_mob_terenas_menethil;
    newscript->RegisterSelf();*/

    newscript = new Script;
    newscript->Name = "mob_shambling_horror";
    newscript->GetAI = &GetAI_mob_shambling_horror;
    newscript->RegisterSelf();
    newscript = new Script;

    newscript->Name = "mob_shadow_trap";
    newscript->GetAI = &GetAI_mob_shadow_trap;
    newscript->RegisterSelf();
};
