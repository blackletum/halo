/*
DIALOGUE_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __DIALOGUE_DEFINITIONS_H
#define __DIALOGUE_DEFINITIONS_H
#pragma once

/* ---------- constants */

enum
{
	_speech_priority_none = 0,
	_speech_priority_idle,
	_speech_priority_pain,
	_speech_priority_talk,
	_speech_priority_communicate,
	_speech_priority_shout,
	_speech_priority_script,
	_speech_priority_involuntary,
	_speech_priority_exclaim,
	_speech_priority_scream,
	_speech_priority_death,
	NUMBER_OF_SPEECH_PRIORITIES,
};

enum
{
	_vocalization_idle_noncombat = 0,
	_vocalization_idle_combat,
	_vocalization_idle_flee,
	_vocalization_unused3, /* fake name */
	_vocalization_unused4, /* fake name */
	_vocalization_unused5, /* fake name */
	_vocalization_pain_body_minor,
	_vocalization_pain_body_major,
	_vocalization_pain_shield,
	_vocalization_pain_falling,
	_vocalization_scream_fear,
	_vocalization_scream_pain,
	_vocalization_maimed_limb,
	_vocalization_maimed_head,
	_vocalization_death_quiet,
	_vocalization_death_violent,
	_vocalization_death_falling,
	_vocalization_death_agonizing,
	_vocalization_death_instant,
	_vocalization_death_flying,
	_vocalization_unused20, /* fake name */
	_vocalization_damaged_friend,
	_vocalization_damaged_friend_player,
	_vocalization_damaged_enemy,
	_vocalization_damaged_enemy_cm,
	_vocalization_unused25, /* fake name */
	_vocalization_unused26, /* fake name */
	_vocalization_unused27, /* fake name */
	_vocalization_unused28, /* fake name */
	_vocalization_hurt_friend,
	_vocalization_hurt_friend_re,
	_vocalization_hurt_friend_player,
	_vocalization_hurt_enemy,
	_vocalization_hurt_enemy_re,
	_vocalization_hurt_enemy_cm,
	_vocalization_hurt_enemy_bullet,
	_vocalization_hurt_enemy_needler,
	_vocalization_hurt_enemy_plasma,
	_vocalization_hurt_enemy_sniper,
	_vocalization_hurt_enemy_grenade,
	_vocalization_hurt_enemy_explosion,
	_vocalization_hurt_enemy_melee,
	_vocalization_hurt_enemy_flame,
	_vocalization_hurt_enemy_shotgun,
	_vocalization_hurt_enemy_vehicle,
	_vocalization_hurt_enemy_mountedweapon,
	_vocalization_unused46, /* fake name */
	_vocalization_unused47, /* fake name */
	_vocalization_unused48, /* fake name */
	_vocalization_killed_friend,
	_vocalization_killed_friend_cm,
	_vocalization_killed_friend_player,
	_vocalization_killed_friend_player_cm,
	_vocalization_killed_enemy,
	_vocalization_killed_enemy_cm,
	_vocalization_killed_enemy_player,
	_vocalization_killed_enemy_player_cm,
	_vocalization_killed_enemy_covenant,
	_vocalization_killed_enemy_covenant_cm,
	_vocalization_killed_enemy_floodcombat,
	_vocalization_killed_enemy_floodcombat_cm,
	_vocalization_killed_enemy_floodcarrier,
	_vocalization_killed_enemy_floodcarrier_cm,
	_vocalization_killed_enemy_sentinel,
	_vocalization_killed_enemy_sentinel_cm,
	_vocalization_killed_enemy_bullet,
	_vocalization_killed_enemy_needler,
	_vocalization_killed_enemy_plasma,
	_vocalization_killed_enemy_sniper,
	_vocalization_killed_enemy_grenade,
	_vocalization_killed_enemy_explosion,
	_vocalization_killed_enemy_melee,
	_vocalization_killed_enemy_flame,
	_vocalization_killed_enemy_shotgun,
	_vocalization_killed_enemy_vehicle,
	_vocalization_killed_enemy_mountedweapon,
	_vocalization_killing_spree,
	_vocalization_unused77, /* fake name */
	_vocalization_unused78, /* fake name */
	_vocalization_unused79, /* fake name */
	_vocalization_player_kill_cm,
	_vocalization_player_kill_bullet_cm,
	_vocalization_player_kill_needler_cm,
	_vocalization_player_kill_plasma_cm,
	_vocalization_player_kill_sniper_cm,
	_vocalization_anyone_kill_grenade_cm,
	_vocalization_player_kill_explosion_cm,
	_vocalization_player_kill_melee_cm,
	_vocalization_player_kill_flame_cm,
	_vocalization_player_kill_shotgun_cm,
	_vocalization_player_kill_vehicle_cm,
	_vocalization_player_kill_mountedweapon_cm,
	_vocalization_player_killing_spree_cm,
	_vocalization_unused93, /* fake name */
	_vocalization_unused94, /* fake name */
	_vocalization_unused95, /* fake name */
	_vocalization_friend_died,
	_vocalization_friend_player_died,
	_vocalization_friend_killed_by_friend,
	_vocalization_friend_killed_by_friendly_player,
	_vocalization_friend_killed_by_enemy,
	_vocalization_friend_killed_by_enemy_player,
	_vocalization_friend_killed_by_covenant,
	_vocalization_friend_killed_by_flood,
	_vocalization_friend_killed_by_sentinel,
	_vocalization_friend_betrayed,
	_vocalization_unused106, /* fake name */
	_vocalization_unused107, /* fake name */
	_vocalization_new_combat_alone,
	_vocalization_new_enemy_recent_combat,
	_vocalization_old_enemy_sighted,
	_vocalization_unexpected_enemy,
	_vocalization_dead_friend_found,
	_vocalization_alliance_broken,
	_vocalization_alliance_reformed,
	_vocalization_grenade_throwing,
	_vocalization_grenade_startle,
	_vocalization_grenade_sighted,
	_vocalization_grenade_danger_enemy,
	_vocalization_grenade_danger_self,
	_vocalization_grenade_danger_friend,
	_vocalization_unused121, /* fake name */
	_vocalization_unused122, /* fake name */
	_vocalization_new_combat_group_re,
	_vocalization_nea_combat_nearby_re,
	_vocalization_alert_friend,
	_vocalization_alert_friend_re,
	_vocalization_alert_lost_contact,
	_vocalization_alert_lost_contact_re,
	_vocalization_blocked,
	_vocalization_blocked_re,
	_vocalization_search_start,
	_vocalization_search_query,
	_vocalization_search_query_re,
	_vocalization_search_report,
	_vocalization_search_abandon,
	_vocalization_search_group_abandon,
	_vocalization_uncover_start,
	_vocalization_uncover_start_re,
	_vocalization_advance,
	_vocalization_advance_re,
	_vocalization_retreat,
	_vocalization_retreat_re,
	_vocalization_cover,
	_vocalization_unused144, /* fake name */
	_vocalization_unused145, /* fake name */
	_vocalization_unused146, /* fake name */
	_vocalization_unused147, /* fake name */
	_vocalization_sighted_friend_player,
	_vocalization_shooting,
	_vocalization_shooting_vehicle,
	_vocalization_shooting_berserk,
	_vocalization_shooting_group,
	_vocalization_shooting_traitor,
	_vocalization_taunt,
	_vocalization_taunt_re,
	_vocalization_flee,
	_vocalization_flee_re,
	_vocalization_flee_leader_died,
	_vocalization_attempted_flee,
	_vocalization_attempted_flee_re,
	_vocalization_lost_contact,
	_vocalization_hiding_finished,
	_vocalization_vehicle_entry,
	_vocalization_vehicle_exit,
	_vocalization_vehicle_woohoo,
	_vocalization_vehicle_scared,
	_vocalization_vehicle_collision,
	_vocalization_partially_sighted,
	_vocalization_nothing_there,
	_vocalization_pleading,
	_vocalization_unused171, /* fake name */
	_vocalization_unused172, /* fake name */
	_vocalization_unused173, /* fake name */
	_vocalization_unused174, /* fake name */
	_vocalization_unused175, /* fake name */
	_vocalization_unused176, /* fake name */
	_vocalization_surprise,
	_vocalization_berserk,
	_vocalization_melee_attack,
	_vocalization_dive,
	_vocalization_uncover_leap,
	_vocalization_leap_attack,
	_vocalization_resurrection,
	_vocalization_unused184, /* fake name */
	_vocalization_unused185, /* fake name */
	_vocalization_unused186, /* fake name */
	_vocalization_unused187, /* fake name */
	_vocalization_celebration,
	_vocalization_check_body_enemy,
	_vocalization_check_body_friend,
	_vocalization_shooting_dead_enemy,
	_vocalization_shooting_dead_enemy_player,
	_vocalization_unused193, /* fake name */
	_vocalization_unused194, /* fake name */
	_vocalization_unused195, /* fake name */
	_vocalization_unused196, /* fake name */
	_vocalization_alone,
	_vocalization_unscathed,
	_vocalization_seriously_wounded,
	_vocalization_seriously_wounded_re,
	_vocalization_massacre,
	_vocalization_massacre_re,
	_vocalization_rout,
	_vocalization_rout_re,
	_vocalization_unused205, /* fake name */
	_vocalization_unused206, /* fake name */
	_vocalization_unused207, /* fake name */
	_vocalization_unused208, /* fake name */
	NUMBER_OF_VOCALIZATION_TYPES,
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes/EXAMPLE.C */

short dialogue_get_vocalization_type_by_name(char const *name);
char const *dialogue_get_vocalization_name(short vocalization_type, boolean unknown);

/* ---------- globals */

/* ---------- public code */

#endif // __DIALOGUE_DEFINITIONS_H
