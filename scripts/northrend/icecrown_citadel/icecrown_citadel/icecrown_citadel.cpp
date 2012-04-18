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
SDName: icecrown_citadel
SD%Complete: 100%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel - mobs
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"
enum Spells
{
    SPELL_UNDEATH               = 70089,

    // Svalna
    SPELL_AETHER_BURST          = 71468,
    SPELL_AETHER_SHIELD         = 71463,
    SPELL_DIVINE_SURGE          = 71465,
    SPELL_REVIVE_CHAMPION       = 70053,
    SPELL_CARESS_OF_DEATH       = 70078,
    SPELL_IMPALING_SPEAR_NPC    = 70196,
    SPELL_IMPALING_SPEAR_PLAYER = 71443,

    // Crok
    SPELL_DEATH_STRIKE          = 71489,
    SPELL_ICEBOUND_ARMOR        = 70714,
    SPELL_SCOURGE_STRIKE        = 71488,

    // Arnath
    SPELL_FLASH_HEAL_PLAYER     = 71595,
    SPELL_FLASH_HEAL_NPC        = 71782,
    SPELL_SMITE_PLAYER          = 71546,
    SPELL_SMITE_NPC             = 71778,
    SPELL_SHIELD_PLAYER         = 71548,
    SPELL_SHIELD_NPC            = 71780,

    // Brandon
    SPELL_CRUSADER_STRIKE       = 71549,
    SPELL_DIVINE_SHIELD         = 71550,
    SPELL_FORBEARANCE           = 25771,
    SPELL_HAMMER_OF_BETRAYAL    = 71784,
    SPELL_JUDGEMENT_OF_COMMAND  = 71551,

    // Grondel
    SPELL_CHARGE                = 71553,
    SPELL_CONFLAGRATION         = 71785,
    SPELL_MORTAL_STRIKE         = 71552,
    SPELL_SUNDER_ARMOR          = 71554,
    SPELL_SUNDER_ARMOR_WARRIOR  = 7386,

    // Rupert
    SPELL_FEL_IRON_BOMB_PLAYER  = 71592,
    SPELL_FEL_IRON_BOMB_NPC     = 71787,
    SPELL_MACHINE_GUN_PLAYER    = 71594,
    SPELL_MACHINE_GUN_NPC       = 71788,
    SPELL_ROCKET_LAUNCH_PLAYER  = 71590,
    SPELL_ROCKET_LAUNCH_NPC     = 71786,

    // Frostwyrm
    SPELL_FROST_BREATH          = 70116,
    SPELL_BLIZZARD              = 70362,
    SPELL_CLEAVE                = 70361,

    // Frost Giant
    SPELL_STOMP                 = 64652,
    SPELL_ARTIC_BREATH          = 67651,
    SPELL_DEATH_PLAGUE          = 72865,
};

enum Says
{
    // Svalna
    SAY_SVALNA_1                = -1631133,
    SAY_SVALNA_2                = -1631135,
    SAY_SVALNA_3                = -1631134,
    SAY_SVALNA_AGGRO            = -1631136,
    SAY_SVALNA_DEATH            = -1631139,
    SAY_SVALNA_KILL             = -1631138,
    SAY_SVALNA_AETHER           = -1631134,

    SAY_CROK_1                  = -1631130,

    SAY_ARNATH_DEATH_1,
    SAY_ARNATH_DEATH_2,
    SAY_ARNATH_REVIVE,
    SAY_ARNATH_KILL,

    SAY_BRANDON_DEATH_1,
    SAY_BRANDON_DEATH_2,
    SAY_BRANDON_REVIVE,
    SAY_BRANDON_KILL,

    SAY_GRONDEL_DEATH_1,
    SAY_GRONDEL_DEATH_2,
    SAY_GRONDEL_REVIVE,
    SAY_GRONDEL_KILL,

    SAY_RUPERT_DEATH_1,
    SAY_RUPERT_DEATH_2,
    SAY_RUPERT_REVIVE,
};

enum Npcs
{
    NPC_YMIRJAR_DEATHBRINGER    = 38125,
    NPC_YMIRJAR_FROSTBINDER     = 37127,
};

static Locations SpawnLoc[] =
{
    {4356.762910f, 2353.168701f, 351.099884f, 4.71f}, // 0 Crok 1
    {4364.121582f, 2654.478516f, 351.100006f, 4.71f}, // 1 Arnath 1
    {4361.400879f, 2655.604004f, 351.100189f, 4.71f}, // 2 Brandon 1
    {4350.195312f, 2659.611084f, 351.099945f, 4.71f}, // 3 Grondel 1
    {4349.293203f, 2656.468018f, 351.099945f, 4.71f}, // 4 Rupert 1
};

struct MANGOS_DLL_DECL mob_svalna_eventAI : public base_icc_bossAI
{
    mob_svalna_eventAI(Creature* pCreature) : base_icc_bossAI(pCreature)
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

    void Reset()
    {
        m_uiStep = 0;
        m_uiEventTimer = 0;
        m_bIsEventStarted = false;
        m_bIsEventFinished = false;
    }

    void NextStep(uint32 uiTimer = 1000)
    {
        m_uiEventTimer = uiTimer;
        ++m_uiStep;
    }

    /*uint32 GetNpcsAlive()
    {
        std::list<Creature*> frostEntryList;
        std::list<Creature*> deathEntryList;
        GetCreatureListWithEntryInGrid(frostEntryList, m_creature, NPC_YMIRJAR_FROSTBINDER, 250.0f);
        GetCreatureListWithEntryInGrid(frostEntryList, m_creature, NPC_YMIRJAR_DEATHBRINGER, 250.0f);

        return frostEntryList.size()-1 + deathEntryList.size()-1;
    }*/

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsEventStarted)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                m_bIsEventStarted = true;
                NextStep();
            }
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void JustDied(Unit *pKiller)
    {
        m_bIsEventFinished = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bIsEventStarted || m_bIsEventFinished)
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            switch (m_uiStep)
            {
                case 0:
                    break;
                case 1:
                    DoScriptText(SAY_SVALNA_1, m_creature);
                    NextStep(12000);
                    break;
                case 2:
                    /*if (Unit* pCrok = m_pInstance->GetSingleCreatureFromStorage(NPC_CROK))
                    {
                        DoScriptText(SAY_CROK_1, pCrok);
                        pCrok->GetMotionMaster()->MovePoint(0, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, SpawnLoc[0].o);
                    }
                    if (Unit* pArnath = m_pInstance->GetSingleCreatureFromStorage(NPC_ARNATH))
                        pArnath->GetMotionMaster()->MovePoint(0, SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, SpawnLoc[1].o);
                    if (Unit* pBrandon = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANDON))
                        pBrandon->GetMotionMaster()->MovePoint(0, SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, SpawnLoc[2].o);
                    if (Unit* pGrondel = m_pInstance->GetSingleCreatureFromStorage(NPC_GRONDEL))
                        pGrondel->GetMotionMaster()->MovePoint(0, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, SpawnLoc[3].o);
                    if (Unit* pRupert = m_pInstance->GetSingleCreatureFromStorage(NPC_RUPERT))
                        pRupert->GetMotionMaster()->MovePoint(0, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, SpawnLoc[4].o);*/
                    NextStep();
                    break;
                case 3:
                    break;
                case 4:
                    DoScriptText(SAY_SVALNA_2, m_creature);
                    NextStep(30000);
                    break;
                case 5:
                    DoScriptText(SAY_SVALNA_3, m_creature);
                    NextStep();
                    break;
                default:
                    break;
            }
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_svalna_event(Creature* pCreature)
{
    return new mob_svalna_eventAI(pCreature);
}

struct MANGOS_DLL_DECL mob_svalnaAI : public mob_svalna_eventAI
{
    mob_svalnaAI(Creature* pCreature) : mob_svalna_eventAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiAetherBurstTimer;
    bool m_bAether1;
    bool m_bAether2;

    void Reset()
    {
        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);

        m_uiAetherBurstTimer = urand(6000, 8000);

        m_bAether1 = false;
        m_bAether2 = false;
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SVALNA, IN_PROGRESS);

        DoScriptText(SAY_SVALNA_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_DIVINE_SURGE, CAST_TRIGGERED);
    }

    void JustDied(Unit *killer)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SVALNA, DONE);

        DoScriptText(SAY_SVALNA_DEATH, m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SVALNA, FAIL);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_SVALNA_KILL, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
            m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);
        else
            m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);

        if (m_uiAetherBurstTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_AETHER_BURST) == CAST_OK)
                m_uiAetherBurstTimer = 15000;
        }
        else
            m_uiAetherBurstTimer -= uiDiff;

        /*if (m_creature->GetHealthPercent() < 70.0f && !m_bAether1)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_AETHER_SHIELD) == CAST_OK)
            {
                DoScriptText(SAY_SVALNA_AETHER, m_creature);
                m_bAether1 = true;
            }
        }

        if (m_creature->GetHealthPercent() < 30.0f && !m_bAether2)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_AETHER_SHIELD) == CAST_OK)
            {
                DoScriptText(SAY_SVALNA_AETHER, m_creature);
                m_bAether2 = true;
            }
        }*/

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_svalna(Creature *pCreature)
{
    return new mob_svalnaAI(pCreature);
}

struct MANGOS_DLL_DECL mob_crokAI : public base_icc_bossAI
{
    mob_crokAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiDeathStrikeTimer;
    uint32 m_uiScourgeStrikeTimer;
    uint32 m_uiIceboundArmorTimer;

    void Reset()
    {
        m_uiDeathStrikeTimer = 7000;
        m_uiScourgeStrikeTimer = 10000;
        m_uiIceboundArmorTimer = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiDeathStrikeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_DEATH_STRIKE) == CAST_OK)
                m_uiDeathStrikeTimer = 7000;
        }
        else m_uiDeathStrikeTimer -= uiDiff;

        if (m_uiScourgeStrikeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SCOURGE_STRIKE) == CAST_OK)
                m_uiScourgeStrikeTimer = 7000;
        }
        else m_uiScourgeStrikeTimer -= uiDiff;

        if (m_uiIceboundArmorTimer < uiDiff)
        {
            if (m_creature->GetHealthPercent() < 10.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_ICEBOUND_ARMOR) == CAST_OK)
                    m_uiIceboundArmorTimer = 60000;
            }
        }
        else m_uiIceboundArmorTimer -= uiDiff;

        if (m_creature->HasAura(SPELL_ICEBOUND_ARMOR) && m_creature->GetHealthPercent() >= 15.0f)
            m_creature->RemoveAurasDueToSpell(SPELL_ICEBOUND_ARMOR);

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_crok(Creature *pCreature)
{
    return new mob_crokAI(pCreature);
}

struct MANGOS_DLL_DECL mob_arnathAI : public base_icc_bossAI
{
    mob_arnathAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {

        Reset();
    }

    uint32 m_uiFlashHealTimer;
    uint32 m_uiSmiteTimer;
    uint32 m_uiShieldTimer;
    bool m_bIsFirstDead;

    void Reset()
    {
        m_bIsFirstDead = true;
        m_uiFlashHealTimer = 3000;
        m_uiSmiteTimer = 5000;
        m_uiShieldTimer = 15000;
    }

    void JustDied(Unit *pKiller)
    {
        if (m_bIsFirstDead)
        {
            //DoScriptText(SAY_ARNATH_DEATH_1, m_creature);
            m_bIsFirstDead = false;
        }
        else
        {
            //DoScriptText(SAY_ARNATH_DEATH_2, m_creature);
        }
    }

    bool m_bTargetIsPlayer(Unit *pTarget)
    {
        if (pTarget->GetTypeId() == TYPEID_PLAYER)
            return true;
        else
            return false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFlashHealTimer < uiDiff)
        {
            if (Unit *pTarget = DoSelectLowestHpFriendly(30.0f))
                if (DoCastSpellIfCan(pTarget, m_bTargetIsPlayer(pTarget) ? SPELL_FLASH_HEAL_PLAYER : SPELL_FLASH_HEAL_NPC) == CAST_OK)
                    m_uiFlashHealTimer = 3000;
        }
        else m_uiFlashHealTimer -= uiDiff;

        if (m_uiShieldTimer < uiDiff)
        {
            if (Unit *pTarget = DoSelectLowestHpFriendly(30.0f))
                if (DoCastSpellIfCan(pTarget, m_bTargetIsPlayer(pTarget) ? SPELL_SHIELD_PLAYER : SPELL_SHIELD_NPC) == CAST_OK)
                    m_uiShieldTimer = 15000;
        }
        else m_uiShieldTimer -= uiDiff;

        if (m_uiSmiteTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bTargetIsPlayer(m_creature->getVictim()) ? SPELL_SMITE_PLAYER : SPELL_SMITE_NPC) == CAST_OK)
                m_uiSmiteTimer = 5000;
        }
        else m_uiSmiteTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_arnath(Creature *pCreature)
{
    return new mob_arnathAI(pCreature);
}


struct MANGOS_DLL_DECL mob_brandonAI : public base_icc_bossAI
{
    mob_brandonAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiCrusaderStrikeTimer;
    uint32 m_uiDivineShieldTimer;
    uint32 m_uiHammerOfBetrayalTimer;
    uint32 m_uiJudgementOfCommandTimer;

    void Reset()
    {
        m_uiCrusaderStrikeTimer = 6000;
        m_uiDivineShieldTimer = 5*MINUTE*IN_MILLISECONDS;
        m_uiHammerOfBetrayalTimer = 40000;
        m_uiJudgementOfCommandTimer = 8000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiCrusaderStrikeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CRUSADER_STRIKE) == CAST_OK)
                m_uiCrusaderStrikeTimer = 6000;
        }
        else m_uiCrusaderStrikeTimer -= uiDiff;

        if (m_uiDivineShieldTimer < uiDiff)
        {
            if (m_creature->GetHealthPercent() < 10.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_DIVINE_SHIELD) == CAST_OK)
                {
                    DoCastSpellIfCan(m_creature, SPELL_FORBEARANCE, CAST_TRIGGERED);
                    m_uiDivineShieldTimer = 5*MINUTE*IN_MILLISECONDS;
                }
            }
        }
        else m_uiDivineShieldTimer -= uiDiff;

        if (m_uiHammerOfBetrayalTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_HAMMER_OF_BETRAYAL) == CAST_OK)
                m_uiHammerOfBetrayalTimer = 40000;
        }
        else m_uiHammerOfBetrayalTimer -= uiDiff;

        if (m_uiJudgementOfCommandTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_JUDGEMENT_OF_COMMAND) == CAST_OK)
                m_uiJudgementOfCommandTimer = 8000;
        }
        else m_uiJudgementOfCommandTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_brandon(Creature *pCreature)
{
    return new mob_brandonAI(pCreature);
}

struct MANGOS_DLL_DECL mob_grondelAI : public base_icc_bossAI
{
    mob_grondelAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiChargeTimer;
    uint32 m_uiConflagrationTimer;
    uint32 m_uiMortalStrikeTimer;
    uint32 m_uiSunderArmorTimer;

    void Reset()
    {
        m_uiChargeTimer = 0;
        m_uiConflagrationTimer = 20000;
        m_uiMortalStrikeTimer = 6000;
        m_uiSunderArmorTimer = 4000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiChargeTimer < uiDiff)
        {
            if (m_creature->GetDistance2d(m_creature->getVictim()) > 8.0f && m_creature->GetDistance2d(m_creature->getVictim()) < 25.0f)
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CHARGE) == CAST_OK)
                    m_uiChargeTimer = 15000;
            }
            else m_uiChargeTimer = 2000;
        }
        else m_uiChargeTimer -= uiDiff;

        if (m_uiConflagrationTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CONFLAGRATION) == CAST_OK)
                m_uiConflagrationTimer = 20000;
        }
        else m_uiConflagrationTimer -= uiDiff;

        if (m_uiMortalStrikeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE) == CAST_OK)
                m_uiMortalStrikeTimer = 6000;
        }
        else m_uiMortalStrikeTimer -= uiDiff;

        if (m_uiSunderArmorTimer < uiDiff)
        {
            if (!m_creature->getVictim()->HasAura(SPELL_SUNDER_ARMOR_WARRIOR))
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUNDER_ARMOR) == CAST_OK)
                {
                    if (Unit *pTarget = m_creature->getVictim())
                    {
                        SpellAuraHolderPtr holder = pTarget->GetSpellAuraHolder(SPELL_SUNDER_ARMOR);
                        if (holder)
                        {
                            if (holder->GetStackAmount() >= 5)
                                m_uiSunderArmorTimer = 30000;
                            else
                                m_uiSunderArmorTimer = 2000;
                        }
                        else
                            m_uiSunderArmorTimer = 2000;
                    }
                }
            }
            else
                m_uiSunderArmorTimer = 10000;
        }
        else m_uiSunderArmorTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_grondel(Creature *pCreature)
{
    return new mob_grondelAI(pCreature);
}

struct MANGOS_DLL_DECL mob_rupertAI : public base_icc_bossAI
{
    mob_rupertAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFelIronBombTimer;
    uint32 m_uiMachineGunTimer;
    uint32 m_uiRocketLaunchTimer;

    void Reset()
    {
        m_uiFelIronBombTimer = 10000;
        m_uiMachineGunTimer = 15000;
        m_uiRocketLaunchTimer = 5000;
    }

    bool m_bTargetIsPlayer(Unit *pTarget)
    {
        if (pTarget->GetTypeId() == TYPEID_PLAYER)
            return true;
        else
            return false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFelIronBombTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bTargetIsPlayer(m_creature->getVictim()) ? SPELL_FEL_IRON_BOMB_PLAYER : SPELL_FEL_IRON_BOMB_NPC) == CAST_OK)
                m_uiFelIronBombTimer = 10000;
        }
        else m_uiFelIronBombTimer -= uiDiff;

        if (m_uiMachineGunTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bTargetIsPlayer(m_creature->getVictim()) ? SPELL_MACHINE_GUN_PLAYER : SPELL_MACHINE_GUN_NPC) == CAST_OK)
                m_uiMachineGunTimer = 15000;
        }
        else m_uiMachineGunTimer -= uiDiff;

        if (m_uiRocketLaunchTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bTargetIsPlayer(m_creature->getVictim()) ? SPELL_ROCKET_LAUNCH_PLAYER : SPELL_ROCKET_LAUNCH_NPC) == CAST_OK)
                m_uiRocketLaunchTimer = 10000;
        }
        else m_uiRocketLaunchTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_rupert(Creature *pCreature)
{
    return new mob_rupertAI(pCreature);
}

struct MANGOS_DLL_DECL mob_spire_frostwyrmAI : public ScriptedAI
{
    mob_spire_frostwyrmAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
        Reset();
    }

    uint32 m_uiCleaveTimer;
    uint32 m_uiBlizzardTimer;
    uint32 m_uiFrostBreathTimer;

    void Reset()
    {
        m_uiCleaveTimer = 7000;
        m_uiBlizzardTimer = 20000;
        m_uiFrostBreathTimer = 15000;
        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
        m_creature->SetRespawnDelay(DAY);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
            m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);

        if (m_uiCleaveTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE) == CAST_OK)
                m_uiCleaveTimer = 7000;
        }
        else m_uiCleaveTimer -= uiDiff;

        if (m_uiBlizzardTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_BLIZZARD) == CAST_OK)
                m_uiBlizzardTimer = 25000;
        }
        else m_uiBlizzardTimer -= uiDiff;

        if (m_uiFrostBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROST_BREATH) == CAST_OK)
                m_uiFrostBreathTimer = 20000;
        }
        else m_uiFrostBreathTimer -= uiDiff;

        DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_mob_spire_frostwyrm(Creature* pCreature)
{
    return new mob_spire_frostwyrmAI(pCreature);
}

struct MANGOS_DLL_DECL mob_frost_giantAI : public base_icc_bossAI
{
    mob_frost_giantAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiStompTimer;
    uint32 m_uiDeathPlagueTimer;
    uint32 m_uiArticBreathTimer;

    void Reset()
    {
        m_uiStompTimer = 10000;
        m_uiDeathPlagueTimer = 20000;
        m_uiArticBreathTimer = 15000;
        m_creature->SetRespawnDelay(7*DAY);
    }

    void Aggro(Unit *who)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_FLIGHT_WAR, IN_PROGRESS);
    }

    void JustDied(Unit *killer)
    {
        if(!m_pInstance)
            return;
        if (killer->GetTypeId() == TYPEID_PLAYER || killer->GetCharmerOrOwnerOrSelf()->GetTypeId() == TYPEID_PLAYER )
            m_pInstance->SetData(TYPE_FLIGHT_WAR, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FLIGHT_WAR, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStompTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_STOMP) == CAST_OK)
                m_uiStompTimer = 20000;
        }
        else m_uiStompTimer -= uiDiff;

        if (m_uiDeathPlagueTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_DEATH_PLAGUE) == CAST_OK)
                m_uiDeathPlagueTimer = 20000;
        }
        else m_uiDeathPlagueTimer -= uiDiff;

        if (m_uiArticBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_ARTIC_BREATH) == CAST_OK)
                m_uiArticBreathTimer = 30000;
        }
        else m_uiArticBreathTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_frost_giant(Creature* pCreature)
{
    return new mob_frost_giantAI(pCreature);
}

void AddSC_icecrown_citadel()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "mob_svalna_event";
    pNewScript->GetAI = &GetAI_mob_svalna_event;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_svalna";
    pNewScript->GetAI = &GetAI_mob_svalna;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_crok";
    pNewScript->GetAI = &GetAI_mob_crok;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_arnath";
    pNewScript->GetAI = &GetAI_mob_arnath;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_brandon";
    pNewScript->GetAI = &GetAI_mob_brandon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_grondel";
    pNewScript->GetAI = &GetAI_mob_grondel;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_rupert";
    pNewScript->GetAI = &GetAI_mob_rupert;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_spire_frostwyrm";
    pNewScript->GetAI = &GetAI_mob_spire_frostwyrm;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_frost_giant";
    pNewScript->GetAI = &GetAI_mob_frost_giant;
    pNewScript->RegisterSelf();
}

