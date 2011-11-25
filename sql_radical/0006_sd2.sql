SET NAMES UTF8;

-- Oculus Drakos event

DELETE FROM `script_texts` WHERE `entry` = -1578040;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1578040, 'Thank you for freeing us, mortals. Beware, the Blue Flight is alerted to your presence. Even now, Malygos sends Varos Cloudstrider and his ring guardians to defend the Oculus. You will need our help to stand a chance.', NULL, NULL, NULL, NULL, NULL, 'Gracias por liberarnos, mortales. Tened cuidado, el Vuelo Azul ha sido alertado de vuestra presencia. Incluso ahora, Malygos envía a Varos Zancanubes y a sus guardianes del anillo para defender El Oculus. Necesitaréis nuestra ayuda o no tendréis nada que hacer.', 'Gracias por liberarnos, mortales. Tened cuidado, el Vuelo Azul ha sido alertado de vuestra presencia. Incluso ahora, Malygos envía a Varos Zancanubes y a sus guardianes del anillo para defender El Oculus. Necesitaréis nuestra ayuda o no tendréis nada que hacer.', NULL, 0, 0, 0, 0, 'SAY_BELGAR');

-- Brann reacting kills

DELETE FROM `script_texts` WHERE `entry` = -1599072;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599072, 'You winning bread!', NULL, NULL, NULL, NULL, NULL, '¡Os estáis ganando el pan!', '¡Os estáis ganando el pan!', NULL, 14244, 1, 0, 0, 'brann REACTING_KILL_1');

DELETE FROM `script_texts` WHERE `entry` = -1599073;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599073, 'Good work!', NULL, NULL, NULL, NULL, NULL, '¡Seguid adelante, así se hace!', '¡Seguid adelante, así se hace!', NULL, 14245, 1, 0, 0, 'brann REACTING_KILL_2');
	
DELETE FROM `script_texts` WHERE `entry` = -1599074;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599074, 'Too much enemies!', NULL, NULL, NULL, NULL, NULL, '¡Mantened el ritmo! ¡Hay enemigos de sobra!', '¡Mantened el ritmo! ¡Hay enemigos de sobra!', NULL, 14246, 1, 0, 0, 'brann REACTING_KILL_3');