public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart)
{
	if(IsValidActor(damaged_actorid))
	{
		new Float:Health;
		GetActorHealth(damaged_actorid, Health);
		if(Health < 1) RespawnActor(damaged_actorid);
	}
	#if defined AHandle_OnPlayerGiveDamageActor
		return AHandle_OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
	#else
		return true;
	#endif
}

#if defined AHandle_OnPlayerGiveDamageActor
forward AHandle_OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);
#endif
#if defined _ALS_OnPlayerGiveDamageActor
	#undef OnPlayerGiveDamageActor
	#else
		#define _ALS_OnPlayerGiveDamageActor
#endif
#define OnPlayerGiveDamageActor AHandler_OnPlayerGiveDamageActor