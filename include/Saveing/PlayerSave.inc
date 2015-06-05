public OnPlayerDisconnect(playerid, reason)
{
	if(!cPlayer->uID[playerid])
	{
		#if defined PlayerSave_OnPlayerDisconnect
			return PlayerSave_OnPlayerDisconnect(playerid, reason);
		#else
			return true;
		#endif
	}
	if(cPlayer->cFlags[playerid] & Logedin && cPlayer->cFlags[playerid] & LoginDone)
	{
		new str[150];
		mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "UPDATE `User` SET `PosX` = %.3f, `PosY` = %.3f, `PosZ` = %.3f, `Angle` = %.3f, `Adminrank` = %d WHERE `uID` = %d LIMIT 1;",
																cPlayer->Cord[0][playerid], 
																cPlayer->Cord[1][playerid], 
																cPlayer->Cord[2][playerid], 
																cPlayer->Cord[3][playerid], 
																cPlayer->AdminRank[playerid],
																cPlayer->uID[playerid]);
		mysql_tquery(ServerVars[MySQLHandle], str);
	}
	#if defined PlayerSave_OnPlayerDisconnect
		return PlayerSave_OnPlayerDisconnect(playerid, reason);
	#else
		return true;
	#endif
}

public OnGameModeExit()
{
	for(new i, j = GetPlayerPoolSize(); i != j; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		OnPlayerDisconnect(i, 3);
	}
	#if defined PlayerSave_OnGameModeExit
		return PlayerSave_OnGameModeExit();
	#else
		return true;
	#endif
}

public OnPlayerUpdate(playerid)
{
	if((cPlayer->cFlags[playerid] & Logedin) && (cPlayer->cFlags[playerid] & LoginDone) && !IsPlayerSpectating(playerid) && IsPlayerSpawned(playerid))
	{
		GetPlayerPos(playerid, cPlayer->Cord[0][playerid], cPlayer->Cord[1][playerid], cPlayer->Cord[2][playerid]);
		GetPlayerFacingAngle(playerid, cPlayer->Cord[3][playerid]);
	}
	#if defined PlayerSave_OnPlayerUpdate
		return PlayerSave_OnPlayerUpdate(playerid);
	#else
		return true;
	#endif
}

SaveSkin(playerid)
{
	if(cPlayer->uID[playerid])
	{
		new str[60];
		mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "UPDATE `User` SET `Skin` = %d WHERE `uID` = %d LIMIT 1;",
																cPlayer->Skin[playerid], cPlayer->uID[playerid]);
		mysql_tquery(ServerVars[MySQLHandle], str);
	}
	else
	{
		printf("No uID for %s", cPlayer->cName[playerid]);
	}
	return true;
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined PlayerSave_OnPlayerDisconnect
forward PlayerSave_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect PlayerSave_OnPlayerDisconnect

#if defined PlayerSave_OnPlayerUpdate
forward PlayerSave_OnPlayerUpdate(playerid);
#endif
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
	#else
		#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate PlayerSave_OnPlayerUpdate

#if defined PlayerSave_OnGameModeExit
forward PlayerSave_OnGameModeExit();
#endif
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit PlayerSave_OnGameModeExit