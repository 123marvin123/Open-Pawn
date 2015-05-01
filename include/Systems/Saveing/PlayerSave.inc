public OnPlayerDisconnect(playerid, reason)
{
	new str[100];
	mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "UPDATE `User` SET `PosX` = %.3f, `PosY` = %.3f, `PosZ` = %.3f WHERE `uID` = %d LIMIT 1;",
															cPlayer->Cord[0][playerid], cPlayer->Cord[1][playerid], cPlayer->Cord[2][playerid], cPlayer->uID[playerid]);
	mysql_tquery(ServerVars[MySQLHandle], str);
	#if defined PlayerSave_OnPlayerDisconnect
		return PlayerSave_OnPlayerDisconnect(playerid, reason);
	#else
		return true;
	#endif
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined PlayerSave_OnPlayerDisconnect
forward PlayerSave_OnPlayerDisconnect(playerid);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect PlayerSave_OnPlayerDisconnect