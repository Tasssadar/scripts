/* Instance_template */
REPLACE INTO `instance_template` (`map`, `parent`, `maxPlayers`, `maxPlayersHeroic`, `reset_delay`, `access_id`, `startLocX`, `startLocY`, `startLocZ`, `startLocO`, `script`) VALUES('37','0','10','10','0','3786',NULL,NULL,NULL,NULL,'instance_azshara_crater');

/* acces_requiement */
REPLACE INTO `access_requirement` (`id`, `level_min`, `heroic_level_min`, `level_max`, `item`, `item2`, `heroic_key`, `heroic_key2`, `quest_done`, `quest_failed_text`, `heroic_quest_done`, `heroic_quest_failed_text`, `comment`) VALUES('3786','75','0','100','0','0','0','0','0',NULL,'0',NULL,'Azshara Crater Raid');

/* areatrigger_teleport */
REPLACE INTO `areatrigger_teleport` (`id`, `name`, `access_id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES('2178','Azshara Crater - Raid','3786','37','0','0','0','0');
