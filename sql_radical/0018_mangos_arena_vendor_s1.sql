/* NPC */
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(80600, 0, 0, 0, 0, 0, 26391, 0, 0, 0, 'Eustaquio', 'Traficante de armaduras s1', NULL, 0, 80, 80, 40000, 40000, 0, 50000, 50000, 90000, 35, 35, 129, 2.5, 8, 1, 0, 0, 0, 0, 0, 1, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 'arena_vendor');

/* SETS */
-- Warrior 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60000, 0, 0, 2952),   -- pecho
(80600, 60001, 0, 0, 2954),   -- guantes
(80600, 60002, 0, 0, 2949),   -- casco
(80600, 60003, 0, 0, 2953),   -- pantalones 
(80600, 60004, 0, 0, 2948);   -- hombros

-- DK 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60005, 0, 0, 2952),   -- pecho
(80600, 60006, 0, 0, 2954),   -- guantes
(80600, 60007, 0, 0, 2949),   -- casco
(80600, 60008, 0, 0, 2953),   -- pantalones 
(80600, 60009, 0, 0, 2948);   -- hombros

-- Hunter 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60010, 0, 0, 2952),   -- pecho
(80600, 60011, 0, 0, 2954),   -- guantes
(80600, 60012, 0, 0, 2949),   -- casco
(80600, 60013, 0, 0, 2953),   -- pantalones 
(80600, 60014, 0, 0, 2948);   -- hombros

-- Shaman 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60015, 0, 0, 2952),   -- pecho
(80600, 60016, 0, 0, 2954),   -- guantes
(80600, 60017, 0, 0, 2949),   -- casco
(80600, 60018, 0, 0, 2953),   -- pantalones 
(80600, 60019, 0, 0, 2948),   -- hombros

(80600, 60020, 0, 0, 2952),   -- pecho
(80600, 60021, 0, 0, 2954),   -- guantes
(80600, 60022, 0, 0, 2949),   -- casco
(80600, 60023, 0, 0, 2953),   -- pantalones 
(80600, 60024, 0, 0, 2948),   -- hombros

(80600, 60025, 0, 0, 2952),   -- pecho
(80600, 60026, 0, 0, 2954),   -- guantes
(80600, 60027, 0, 0, 2949),   -- casco
(80600, 60028, 0, 0, 2953),   -- pantalones 
(80600, 60029, 0, 0, 2948);   -- hombros

-- Rogue 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60030, 0, 0, 2952),   -- pecho
(80600, 60031, 0, 0, 2954),   -- guantes
(80600, 60032, 0, 0, 2949),   -- casco
(80600, 60033, 0, 0, 2953),   -- pantalones 
(80600, 60034, 0, 0, 2948);   -- hombros

-- Druid 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60035, 0, 0, 2952),   -- pecho
(80600, 60036, 0, 0, 2954),   -- guantes
(80600, 60037, 0, 0, 2949),   -- casco
(80600, 60038, 0, 0, 2953),   -- pantalones 
(80600, 60039, 0, 0, 2948),   -- hombros

(80600, 60040, 0, 0, 2952),   -- pecho
(80600, 60041, 0, 0, 2954),   -- guantes
(80600, 60042, 0, 0, 2949),   -- casco
(80600, 60043, 0, 0, 2953),   -- pantalones 
(80600, 60044, 0, 0, 2948),   -- hombros

(80600, 60045, 0, 0, 2952),   -- pecho
(80600, 60046, 0, 0, 2954),   -- guantes
(80600, 60047, 0, 0, 2949),   -- casco
(80600, 60048, 0, 0, 2953),   -- pantalones 
(80600, 60049, 0, 0, 2948);   -- hombros

-- Mage 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60050, 0, 0, 2952),   -- pecho
(80600, 60051, 0, 0, 2954),   -- guantes
(80600, 60052, 0, 0, 2949),   -- casco
(80600, 60053, 0, 0, 2953),   -- pantalones 
(80600, 60054, 0, 0, 2948);   -- hombros

-- Warlock 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60055, 0, 0, 2952),   -- pecho
(80600, 60056, 0, 0, 2954),   -- guantes
(80600, 60057, 0, 0, 2949),   -- casco
(80600, 60058, 0, 0, 2953),   -- pantalones 
(80600, 60059, 0, 0, 2948);   -- hombros

-- Priest 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80600, 60060, 0, 0, 2952),   -- pecho
(80600, 60061, 0, 0, 2954),   -- guantes
(80600, 60062, 0, 0, 2949),   -- casco
(80600, 60063, 0, 0, 2953),   -- pantalones 
(80600, 60064, 0, 0, 2948),   -- hombros

(80600, 60065, 0, 0, 2952),   -- pecho
(80600, 60066, 0, 0, 2954),   -- guantes
(80600, 60067, 0, 0, 2949),   -- casco
(80600, 60068, 0, 0, 2953),   -- pantalones 
(80600, 60069, 0, 0, 2948);   -- hombros
