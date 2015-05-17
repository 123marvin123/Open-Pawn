/* 
 * ---------------------------------------------------------
 * forwards for mysql querys
 * ---------------------------------------------------------
 */

forward OnPasswordHashed(playerid);
forward OnPlayerAccountCheck(playerid);
forward OnPasswordCheck(playerid, input[]);
forward OnPasswordChecked(playerid);

/* 
 * ---------------------------------------------------------
 * Custom functions for the Loginsystem
 * ---------------------------------------------------------
 */

 forward OnPlayerLogin(playerid);
 forward OnPlayerRegister(playerid);
 forward ShowRegisterDraws(playerid);
 
/* 
 * ---------------------------------------------------------
 * Login System
 * ---------------------------------------------------------
 */
 
public OnPlayerConnect(playerid)
{
	for(new i; i != _:const_struc; i++) cPlayer->const_struc:i[playerid] = 0;
	cPlayer->cFlags[playerid] = const_flags:0; // Turn all Flags off
	
	GetPlayerName(playerid, cPlayer->cName[playerid], MAX_PLAYER_NAME);
	
	SetPlayerVirtualWorld(playerid, playerid + 1);
	#if defined Login_OnPlayerConnect
		return Login_OnPlayerConnect(playerid);
	#else
		return true;
	#endif
}

public OnPlayerRequestClass(playerid, classid)
{
	new str[90];
	mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "SELECT `uID`, `Skin` FROM `User` WHERE `Name` = '%e' LIMIT 1;", cPlayer->cName[playerid]);
	mysql_pquery(ServerVars[MySQLHandle], str, "OnPlayerAccountCheck", "d", playerid);
	
	#if defined Login_OnPlayerRequestClass
		return Login_OnPlayerRequestClass(playerid, classid);
	#else
		return true;
	#endif
}

public OnPlayerLogin(playerid)
{
	if(cPlayer->cFlags[playerid] & Logedin)
	{
		new str[50];
		mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "SELECT * FROM `User` WHERE `uID` = %d LIMIT 1;", cPlayer->uID[playerid]);
		new Cache:result = mysql_query(ServerVars[MySQLHandle], str, true);
		constPlayer[playerid][Cord][0] = cache_get_field_content_float(0, "PosX", ServerVars[MySQLHandle]);
		constPlayer[playerid][Cord][1] = cache_get_field_content_float(0, "PosY", ServerVars[MySQLHandle]);
		constPlayer[playerid][Cord][2] = cache_get_field_content_float(0, "PosZ", ServerVars[MySQLHandle]);
		cache_delete(result);

		SpawnPlayer(playerid);
		SetPlayerPos(playerid, constPlayer[playerid][Cord][0], constPlayer[playerid][Cord][1], constPlayer[playerid][Cord][2]);
		cPlayer->cFlags[playerid] |= LoginDone;
		
		DestroyActor(cPlayer->ActorID[playerid]);
		cPlayer->ActorID[playerid] = INVALID_ACTOR_ID;
		
		SetPlayerVirtualWorld(playerid, 0);
		
		if(cPlayer->cFlags[playerid] & NoSkin)
		{
			HideRegisterDraws(playerid);
			cPlayer->cFlags[playerid] &= ~NoSkin;
		}
		ResetSkinPreview(playerid);
	}
	else
	{
		Kick(playerid);
	}
	return true;
}

public OnPlayerSpawn(playerid)
{
	if(!(cPlayer->cFlags[playerid] & Logedin))
	{
		new str[344];
		#if RELEASE_STATE == DEBUG
		format(str, sizeof(str), "Hallo %s,\n\
								  schön das du zu uns gefunden hast.\n\
								  Da es sich momentan nur um ein Script handelt welches gerade erst begonnen wurde, siehst du diese Textbox.\n\
								  Im Laufe der Zeit wird es sicherlich noch Änderungen geben\n\
								  Schließlich handelt es sich hierbei um ein Open Source Script.", cPlayer->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Willkommen", str, "OK", "");
		#endif
		
		cPlayer->CamObj[playerid] = CreatePlayerObject(playerid, 19300, -2381.091308, 2196.152832, 15.140089, 0.0, 0.0, 0.0);
		TogglePlayerSpectating(playerid, true);
		AttachCameraToPlayerObject(playerid, cPlayer->CamObj[playerid]);
		
		SetPlayerCameraPos(playerid, -2381.091308, 2196.152832, 15.140089);
		SetPlayerCameraLookAt(playerid, -2381.4136, 2212.6426, 12.8594);
		
		return true; // just returning - not calling the other Hooked Callbacks
	}
	#if defined Login_OnPlayerSpawn
		return Login_OnPlayerSpawn(playerid);
	#else
		return true;
	#endif
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		#if RELEASE_STATE == DEBUG
		case DIALOG_INFO:
		{
			new str[344];
			if(cPlayer->uID[playerid])
			{
				format(str, sizeof(str), "Herzlich Willkommen %s,\n\
										  danke, das wir dich erneut bei uns begrüßen dürfen.\n\
										  Um weiter zu spielen brauchst du nur dein Passwort einzutragen\n\
										  und zu bestätigen.", cPlayer->cName[playerid]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Bestätigen", "Ciao");
			}
			else
			{
				
				format(str, sizeof(str), "Herzlich Willkommen %s,\n\
										  danke das du dich für unseren Server entscheiden hast.\n\
										  Allerdings besitzt du aktuell keinen Account bei uns\n\
										  das macht nichts, wenn du im unten stehenden Feld ein Passwort eingibst,\n\
										  registierst du dich völlig automatisch bei uns und kannst jederzeit wiederkommen ohne neu beginnen zu müssen.", cPlayer->cName[playerid]);
				ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Bestätigen", "Nope");
			}
			return true;
		}
		#endif
		case DIALOG_REGISTER:
		{
			if(response)
			{
				new hash[140];
				if(!isnull(inputtext))
				{
					format(hash, sizeof(hash), "%s%s", cPlayer->cName[playerid], inputtext);
					bcrypt_hash(hash, 14, "OnPasswordHashed", "d", playerid);
					// No login
					// cPlayer->cFlags[playerid] |= Logedin;
					SkinSelectZoom(playerid);
					return true;
				}
				else
				{
					format(hash, sizeof(hash), "Wir konnten dich nicht registieren.\n\
												Es wurde kein Passwort eingegeben.\n\
												Bitte versuch es erneut.", cPlayer->cName[playerid]);
					ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Willkommen", hash, "Login", "Ciao");
					return true;
				}
			}
			else
			{
				Kick(playerid);
			}
			return true;
		}
		case DIALOG_LOGIN:
		{
			if(response)
			{
				if(cPlayer->uID[playerid])
				{
					new query[120];
					mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "SELECT `Hash` FROM `Password` WHERE `UserID` = %d;", cPlayer->uID[playerid]);
					mysql_pquery(ServerVars[MySQLHandle], query, "OnPasswordCheck", "ds", playerid, inputtext);
				}
				else Kick(playerid);
			}
			else Kick(playerid);
		}
		case DIALOG_LOGIN_INFO:
		{
			if(response)
			{
				if(cPlayer->cFlags[playerid] & NoSkin)
				{
					SkinSelectZoom(playerid);
				}
				else
				{
					cPlayer->cFlags[playerid] |= Logedin;
					OnPlayerLogin(playerid);
				}
			}
		}
	}
	#if defined Login_OnDialogResponse
		return Login_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return true;
	#endif
}
public OnPlayerDisconnect(playerid, reason)
{
	if(IsValidActor(cPlayer->ActorID[playerid]))
	{
		DestroyActor(cPlayer->ActorID[playerid]);
		cPlayer->ActorID[playerid] = INVALID_ACTOR_ID;
	}
	#if defined LoginOnPlayerDisconnect
		return Login_OnPlayerDisconnect(playerid, reason);
	#else
		return true;
	#endif
}
public OnPasswordHashed(playerid)
{
	new hash[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(hash);
	new query[300];
	
	mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "INSERT INTO `User` (`Name`, `Skin`) VALUES ('%e', -1);", cPlayer->cName[playerid]);
	mysql_tquery(ServerVars[MySQLHandle], query);
	
	mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "INSERT INTO `Password`(`UserID`, `Hash`) VALUES ((SELECT `uID` FROM `User` WHERE `Name` = '%e' LIMIT 1), '%e');", cPlayer->cName[playerid], hash);
	mysql_tquery(ServerVars[MySQLHandle], query);
	return true;
}

public OnPlayerAccountCheck(playerid)
{
	cPlayer->uID[playerid] = cache_get_row_int(0, 0, ServerVars[MySQLHandle]); // 0 = uID
	cPlayer->Skin[playerid] = cache_get_row_int(0, 1, ServerVars[MySQLHandle]); // 1 = Skin
	if(cPlayer->Skin[playerid] == -1)
	{
		cPlayer->cFlags[playerid] |= NoSkin;
		cPlayer->Skin[playerid] = 0;
	}
	
	//Skip ClassSelection
	SetSpawnInfo(playerid, 0, cPlayer->Skin[playerid], -2248.2258, 2330.5852, 4.9741, 55.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	
	// Actor stuff
	cPlayer->ActorID[playerid] = CreateActor(cPlayer->Skin[playerid], -2381.4136, 2212.6426, 12.8594, 180.0);
	SetActorVirtualWorld(cPlayer->ActorID[playerid], playerid + 1);
	
	#if RELEASE_STATE == RELEASE
	new str[300];
	if(isnull(cPlayer->cName[playerid])) return Kick(playerid);
	if(cPlayer->uID[playerid])
	{
		format(str, sizeof(str), "Herzlich Willkommen %s,\n\
								  danke, das wir dich erneut bei uns begrüßen dürfen.\n\
								  Um weiter zu spielen brauchst du nur dein Passwort einzutragen\n\
								  und zu bestätigen.", cPlayer->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Bestätigen", "Ciao");
	}
	else
	{
		format(str, sizeof(str), "Herzlich Willkommen %s,\n\
								  danke das du dich für unseren Server entscheiden hast.\n\
								  Allerdings besitzt du aktuell keinen Account bei uns\n\
								  das macht nichts, wenn du im unten stehenden Feld ein Passwort eingibst,\n\
								  registierst du dich völlig automatisch bei uns und kannst jederzeit wiederkommen ohne neu beginnen zu müssen.", cPlayer->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Login", "Ciao");
	}
	#endif
	return true;
}

public OnPasswordCheck(playerid, input[])
{
	new password[140], DB_Hash[BCRYPT_HASH_LENGTH];
	cache_get_row(0, 0, DB_Hash, ServerVars[MySQLHandle]);
	format(password, sizeof(password), "%s%s", cPlayer->cName[playerid], input);
	bcrypt_check(password, DB_Hash, "OnPasswordChecked", "d", playerid);
	return true;
}

public OnPasswordChecked(playerid)
{
	if(bcrypt_is_equal())
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN_INFO, DIALOG_STYLE_MSGBOX, "Login", "Erfolgreich eingeloggt", "OK", "");
	}
	else
	{
		new str[120];
		format(str, sizeof(str), "Wir konnten dich nicht einloggen.\n\
								 Das eingegebene Passwort ist falsch.\n\
								 Bitte versuch es erneut.", cPlayer->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", str, "Login", "Ciao");
	}
	return true;
}

public OnPlayerRegister(playerid)
{
	if(cPlayer->cFlags[playerid] & Logedin)
	{
		ResetSkinPreview(playerid);		
		HideRegisterDraws(playerid);
		
		new rand = random(sizeof(Spawns));
		SetPlayerPos(playerid, Spawns[rand][sX], Spawns[rand][sY], Spawns[rand][sZ]);
		SetPlayerFacingAngle(playerid, Spawns[rand][sAngle]);
		SetCameraBehindPlayer(playerid);		
		
		TextDrawHideForPlayer(playerid, ServerVars[RegisterArrow][0]);
		TextDrawHideForPlayer(playerid, ServerVars[RegisterArrow][1]);
		TextDrawHideForPlayer(playerid, ServerVars[Done][0]);
		TextDrawHideForPlayer(playerid, ServerVars[Done][1]);
	}
	return true;
}

static SkinSelectZoom(playerid)
{
	new Float:Pos[3];
	GetPlayerCameraPos(playerid, Pos[0], Pos[1], Pos[2]);
	InterpolateCameraPos(playerid, Pos[0], Pos[1], Pos[2], Pos[0], Pos[1] + 8.5, Pos[2] - 0.8513, 2000);
	
	SetTimerEx("ShowRegisterDraws", 2000, false, "d", playerid);
	return true;
}

static ResetSkinPreview(playerid)
{
	CancelSelectTextDraw(playerid);
	TogglePlayerSpectating(playerid, false);
	DestroyPlayerObject(playerid, cPlayer->CamObj[playerid]);
	SetCameraBehindPlayer(playerid);
}

static HideRegisterDraws(playerid)
{
	TextDrawHideForPlayer(playerid, ServerVars[RegisterArrow][0]);
	TextDrawHideForPlayer(playerid, ServerVars[RegisterArrow][1]);
	TextDrawHideForPlayer(playerid, ServerVars[Done][0]);
	TextDrawHideForPlayer(playerid, ServerVars[Done][1]);
	return true;
}

public ShowRegisterDraws(playerid)
{
	SelectTextDraw(playerid, Color(Aquamarine));
	TextDrawShowForPlayer(playerid, ServerVars[RegisterArrow][0]);
	TextDrawShowForPlayer(playerid, ServerVars[RegisterArrow][1]);
	TextDrawShowForPlayer(playerid, ServerVars[Done][0]);
	TextDrawShowForPlayer(playerid, ServerVars[Done][1]);
	
	return true;
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

#if defined Login_OnPlayerDisconnect
forward Login_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Login_OnPlayerDisconnect

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

#if defined Login_OnDialogResponse
forward Login_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
	#else
		#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse Login_OnDialogResponse