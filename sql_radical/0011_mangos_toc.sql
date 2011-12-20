UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `ScriptName` = 'mob_fire_bomb' WHERE `entry` = 34854;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 34800;

UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = 195485;
UPDATE `gameobject` SET `spawnMask` = '15' WHERE `guid` = 2358;

DELETE FROM `creature_template` WHERE `entry` = 34863;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`)
VALUES
	(34863, 0, 0, 0, 0, 0, 19725, 28549, 0, 0, 'Nerubian Burrow Two', '', '', 0, 1, 1, 1, 1, 0, 0, 0, 17, 35, 35, 0, 1, 1.14286, 1, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '');

DELETE FROM `creature_template` WHERE `entry` = 34864;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`)
VALUES
	(34864, 0, 0, 0, 0, 0, 19725, 28549, 0, 0, 'Nerubian Burrow Three', '', '', 0, 1, 1, 1, 1, 0, 0, 0, 17, 35, 35, 0, 1, 1.14286, 1, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '');

DELETE FROM `creature_template` WHERE `entry` = 34865;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`)
VALUES
	(34865, 0, 0, 0, 0, 0, 19725, 28549, 0, 0, 'Nerubian Burrow Four', '', '', 0, 1, 1, 1, 1, 0, 0, 0, 17, 35, 35, 0, 1, 1.14286, 1, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '');

DELETE FROM `creature_template_addon` WHERE `entry` = 34863;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`)
VALUES
	(34863, 0, 0, 1, 0, 0, 0, '66324');

DELETE FROM `creature_template_addon` WHERE `entry` = 34864;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`)
VALUES
	(34864, 0, 0, 1, 0, 0, 0, '66324');
	
DELETE FROM `creature_template_addon` WHERE `entry` = 34865;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`)
VALUES
	(34865, 0, 0, 1, 0, 0, 0, '66324');

DELETE FROM `creature` WHERE `id` = 34862;
DELETE FROM `creature` WHERE `id` = 34863;
DELETE FROM `creature` WHERE `id` = 34864;
DELETE FROM `creature` WHERE `id` = 34865;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES
	(null, 34862, 649, 15, 1, 0, 0, 735.403, 75.3576, 142.202, 2.09439, 180, 0, 0, 1, 0, 0, 0),
	(null, 34863, 649, 15, 1, 0, 0, 692.92, 184.809, 142.203, 5.35816, 180, 0, 0, 1, 0, 0, 0),
	(null, 34864, 649, 15, 1, 0, 0, 688.207, 102.847, 142.202, 0.645772, 180, 0, 0, 1, 0, 0, 0),
	(null, 34865, 649, 15, 1, 0, 0, 740.545, 189.113, 142.197, 3.75246, 180, 0, 0, 1, 0, 0, 0);

UPDATE `creature_template` SET `flags_extra` = '2' WHERE `entry` = 34862;
UPDATE `creature_template` SET `flags_extra` = '2' WHERE `entry` = 34863;
UPDATE `creature_template` SET `flags_extra` = '2' WHERE `entry` = 34864;
UPDATE `creature_template` SET `flags_extra` = '2' WHERE `entry` = 34865;

UPDATE `creature_template` SET `modelid_1` = '17612', `modelid_2` = '0' WHERE `entry` = 5672;

UPDATE `creature_template` SET `minhealth` = '12000', `maxhealth` = '12000' WHERE `entry` = 35458;

UPDATE `creature_template` SET `flags_extra` = '2' WHERE `entry` = 33184;
UPDATE `creature_template` SET `name` = 'Permafrost', `unit_flags` = '0', `faction_A` = '14', `faction_H` = '14', `modelid_1` = '17612' WHERE `entry` = 33184;

UPDATE `creature_template` SET `flags_extra` = '256' WHERE `entry` = 34800;

UPDATE `creature_template` SET `mechanic_immune_mask` = '769605631' WHERE `entry` = 34780;

UPDATE `creature_template` SET `mechanic_immune_mask` = '635387903' WHERE `entry` = 34496;
UPDATE `creature_template` SET `mechanic_immune_mask` = '635387903' WHERE `entry` = 34497;