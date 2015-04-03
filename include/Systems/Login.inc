public OnPlayerConnect(playerid)
{
	GetPlayerName(playerid, cP->cName[playerid], MAX_PLAYER_NAME);
	cP->cFlags[playerid] &= ~Loggedin; // Turn of the Login flag
	
	#if defined Login_OnPlayerConnect
		return Login_OnPlayerConnect(playerid);
	#else
		return true;
	#endif
}

public OnPlayerRequestClass(playerid, classid)
{
	//Skip ClassSelection
	SetSpawnInfo(playerid, 0, 0, 1958.3783, 1343.1572, 15.3746, 270.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	
	#if defined Login_OnPlayerRequestClass
		return Login_OnPlayerRequestClass(playerid, classid);
	#else
		return true;
	#endif
}

public OnPlayerSpawn(playerid)
{
	if(!(cP->cFlags[playerid] & Loggedin))
	{
		new str[300];
		format(str, sizeof(str), "Hallo %s,\n\
								  schön das du zu uns gefunden hast.\n\
								  Da es sich momentan nur um ein Script handelt welches gerade erst begonnen wurde, siehst du diese MessageBox.\n\
								  Im Laufe der Zeit wird es sicherlich noch änderungen geben\n\
								  Schließlich handelt es sich hierbei um ein Open Source Script.", cP->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Willkommen", str, "OK", "");
	}
	#if defined Login_OnPlayerSpawn
		return Login_OnPlayerSpawn(playerid);
	#else
		return true;
	#endif
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined Login_OnPlayerConnect
forward Login_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Login_OnPlayerConnect

#if defined Login_OnPlayerRequestClass
forward Login_OnPlayerRequestClass(playerid, classid);
#endif
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
	#else
		#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass Login_OnPlayerRequestClass

#if defined Login_OnPlayerSpawn
forward Login_OnPlayerSpawn(playerid);
#endif
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
	#else
		#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn Login_OnPlayerSpawn