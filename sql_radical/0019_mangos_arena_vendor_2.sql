/* NPC */
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(80601, 0, 0, 0, 0, 0, 6380, 0, 0, 0, 'Godofredo', 'Traficante de armaduras s2', NULL, 0, 80, 80, 40000, 40000, 0, 50000, 50000, 90000, 35, 35, 129, 2.5, 8, 1, 0, 0, 0, 0, 0, 1, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 'arena_vendor');

/* SETS */
-- Warrior 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60100, 0, 0, 2952),   -- pecho
(80601, 60101, 0, 0, 2954),   -- guantes
(80601, 60102, 0, 0, 2949),   -- casco
(80601, 60103, 0, 0, 2953),   -- pantalones 
(80601, 60104, 0, 0, 2948);   -- hombros

-- DK 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60105, 0, 0, 2952),   -- pecho
(80601, 60106, 0, 0, 2954),   -- guantes
(80601, 60107, 0, 0, 2949),   -- casco
(80601, 60108, 0, 0, 2953),   -- pantalones 
(80601, 60109, 0, 0, 2948);   -- hombros

-- Paladin
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60170, 0, 0, 2952),   -- pecho
(80601, 60171, 0, 0, 2954),   -- guantes
(80601, 60172, 0, 0, 2949),   -- casco
(80601, 60173, 0, 0, 2953),   -- pantalones 
(80601, 60174, 0, 0, 2948),   -- hombros

(80601, 60175, 0, 0, 2952),   -- pecho
(80601, 60176, 0, 0, 2954),   -- guantes
(80601, 60177, 0, 0, 2949),   -- casco
(80601, 60178, 0, 0, 2953),   -- pantalones 
(80601, 60179, 0, 0, 2948);   -- hombros

-- Hunter 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60110, 0, 0, 2952),   -- pecho
(80601, 60111, 0, 0, 2954),   -- guantes
(80601, 60112, 0, 0, 2949),   -- casco
(80601, 60113, 0, 0, 2953),   -- pantalones 
(80601, 60114, 0, 0, 2948);   -- hombros

-- Shaman 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60115, 0, 0, 2952),   -- pecho
(80601, 60116, 0, 0, 2954),   -- guantes
(80601, 60117, 0, 0, 2949),   -- casco
(80601, 60118, 0, 0, 2953),   -- pantalones 
(80601, 60119, 0, 0, 2948),   -- hombros

(80601, 60120, 0, 0, 2952),   -- pecho
(80601, 60121, 0, 0, 2954),   -- guantes
(80601, 60122, 0, 0, 2949),   -- casco
(80601, 60123, 0, 0, 2953),   -- pantalones 
(80601, 60124, 0, 0, 2948),   -- hombros

(80601, 60125, 0, 0, 2952),   -- pecho
(80601, 60126, 0, 0, 2954),   -- guantes
(80601, 60127, 0, 0, 2949),   -- casco
(80601, 60128, 0, 0, 2953),   -- pantalones 
(80601, 60129, 0, 0, 2948);   -- hombros

-- Rogue 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60130, 0, 0, 2952),   -- pecho
(80601, 60131, 0, 0, 2954),   -- guantes
(80601, 60132, 0, 0, 2949),   -- casco
(80601, 60133, 0, 0, 2953),   -- pantalones 
(80601, 60134, 0, 0, 2948);   -- hombros

-- Druid 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60135, 0, 0, 2952),   -- pecho
(80601, 60136, 0, 0, 2954),   -- guantes
(80601, 60137, 0, 0, 2949),   -- casco
(80601, 60138, 0, 0, 2953),   -- pantalones 
(80601, 60139, 0, 0, 2948),   -- hombros

(80601, 60140, 0, 0, 2952),   -- pecho
(80601, 60141, 0, 0, 2954),   -- guantes
(80601, 60142, 0, 0, 2949),   -- casco
(80601, 60143, 0, 0, 2953),   -- pantalones 
(80601, 60144, 0, 0, 2948),   -- hombros

(80601, 60145, 0, 0, 2952),   -- pecho
(80601, 60146, 0, 0, 2954),   -- guantes
(80601, 60147, 0, 0, 2949),   -- casco
(80601, 60148, 0, 0, 2953),   -- pantalones 
(80601, 60149, 0, 0, 2948);   -- hombros

-- Mage 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60150, 0, 0, 2952),   -- pecho
(80601, 60151, 0, 0, 2954),   -- guantes
(80601, 60152, 0, 0, 2949),   -- casco
(80601, 60153, 0, 0, 2953),   -- pantalones 
(80601, 60154, 0, 0, 2948);   -- hombros

-- Warlock 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60155, 0, 0, 2952),   -- pecho
(80601, 60156, 0, 0, 2954),   -- guantes
(80601, 60157, 0, 0, 2949),   -- casco
(80601, 60158, 0, 0, 2953),   -- pantalones 
(80601, 60159, 0, 0, 2948);   -- hombros

-- Priest 
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(80601, 60160, 0, 0, 2952),   -- pecho
(80601, 60161, 0, 0, 2954),   -- guantes
(80601, 60162, 0, 0, 2949),   -- casco
(80601, 60163, 0, 0, 2953),   -- pantalones 
(80601, 60164, 0, 0, 2948),   -- hombros

(80601, 60165, 0, 0, 2952),   -- pecho
(80601, 60166, 0, 0, 2954),   -- guantes
(80601, 60167, 0, 0, 2949),   -- casco
(80601, 60168, 0, 0, 2953),   -- pantalones 
(80601, 60169, 0, 0, 2948);   -- hombros
