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
 * Login System
 * ---------------------------------------------------------
 */
 
public OnPlayerConnect(playerid)
{
	GetPlayerName(playerid, cP->cName[playerid], MAX_PLAYER_NAME);
	cP->cFlags[playerid] &= ~Loggedin; // Turn of the Loginflag
	
	#if defined Login_OnPlayerConnect
		return Login_OnPlayerConnect(playerid);
	#else
		return true;
	#endif
}

public OnPlayerRequestClass(playerid, classid)
{
	//Skip ClassSelection
	SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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
		new str[344];
		#if RELEASE_STATE == DEBUG
		format(str, sizeof(str), "Hallo %s,\n\
								  schön das du zu uns gefunden hast.\n\
								  Da es sich momentan nur um ein Script handelt welches gerade erst begonnen wurde, siehst du diese Textbox.\n\
								  Im Laufe der Zeit wird es sicherlich noch Änderungen geben\n\
								  Schließlich handelt es sich hierbei um ein Open Source Script.", cP->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Willkommen", str, "OK", "");
		#endif
		mysql_format(ServerVars[MySQLHandle], str, sizeof(str), "SELECT `uID`, `Skin` FROM `User` WHERE `Name` = '%e' LIMIT 1;", cP->cName[playerid]);
		mysql_pquery(ServerVars[MySQLHandle], str, "OnPlayerAccountCheck", "d", playerid);
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
			if(cP->uID[playerid])
			{
				format(str, sizeof(str), "Herzlich Willkommen %s,\n\
										  danke, das wir dich erneut ei uns begrüßen dürfen.\n\
										  Um weiter zu spielen brauchst du nur dein Passwort einzutragen\n\
										  und zu bestätigen.", cP->cName[playerid]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Bestätigen", "Ciao");
			}
			else
			{
				
				format(str, sizeof(str), "Herzlich Willkommen %s,\n\
										  danke das du dich für unseren Server entscheiden hast.\n\
										  Allerdings besitzt du aktuell keinen Account bei uns\n\
										  das macht nichts, wenn du im unten stehenden Feld ein Passwort eingibst,\n\
										  registierst du dich völlig automatisch bei uns und kannst jederzeit wiederkommen ohne neu beginnen zu müssen.", cP->cName[playerid]);
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
					format(hash, sizeof(hash), "%s%s", cP->cName[playerid], inputtext);
					bcrypt_hash(hash, 14, "OnPasswordHashed", "d", playerid);
					cP->cFlags[playerid] |= Loggedin;
					return true;
				}
				else
				{
					format(hash, sizeof(hash), "Wir konnten dich nicht registieren.\n\
												Es wurde kein Passwort eingegeben.\n\
												Bitte versuch es erneut.", cP->cName[playerid]);
					ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Willkommen", hash, "Login", "Ciao");
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
				if(cP->uID[playerid])
				{
					new query[120];
					mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "SELECT `Hash` FROM `Password` WHERE `UserID` = %d;", cP->uID[playerid]);
					mysql_pquery(ServerVars[MySQLHandle], query, "OnPasswordCheck", "ds", playerid, inputtext);
				}
				else Kick(playerid);
			}
			else Kick(playerid);
		}
	}
	#if defined Login_OnDialogResponse
		return Login_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
	#else
		return true;
	#endif
}

public OnPasswordHashed(playerid)
{
	new hash[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(hash);
	new query[300];
	
	mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "INSERT INTO `User` (`Name`, `Skin`) VALUES ('%e', 5);", cP->cName[playerid]);
	mysql_pquery(ServerVars[MySQLHandle], query);
	
	mysql_format(ServerVars[MySQLHandle], query, sizeof(query), "INSERT INTO `Password`(`UserID`, `Hash`) VALUES ((SELECT `uID` FROM `User` WHERE `Name` = '%e' LIMIT 1), '%e');", cP->cName[playerid], hash);
	mysql_pquery(ServerVars[MySQLHandle], query);
	return true;
}

public OnPlayerAccountCheck(playerid)
{
	cP->uID[playerid] = cache_get_row_int(0, 0, ServerVars[MySQLHandle]); // 0 = uID
	cP->Skin[playerid] = cache_get_row_int(0, 1, ServerVars[MySQLHandle]); // 1 = Skin
	SetPlayerSkin(playerid, cP->Skin[playerid]);
	
	#if RELEASE_STATE == RELEASE
	new str[300];	
	if(cP->uID[playerid])
	{
		format(str, sizeof(str), "Herzlich Willkommen %s,\n\
								  danke, das wir dich erneut bei uns begrüßen dürfen.\n\
								  Um weiter zu spielen brauchst du nur dein Passwort einzutragen\n\
								  und zu bestätigen.", cP->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Bestätigen", "Ciao");
	}
	else
	{
		format(str, sizeof(str), "Herzlich Willkommen %s,\n\
								  danke das du dich für unseren Server entscheiden hast.\n\
								  Allerdings besitzt du aktuell keinen Account bei uns\n\
								  das macht nichts, wenn du im unten stehenden Feld ein Passwort eingibst,\n\
								  registierst du dich völlig automatisch bei uns und kannst jederzeit wiederkommen ohne neu beginnen zu müssen.", cP->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Willkommen", str, "Login", "Ciao");
	}
	#endif
	return true;
}

public OnPasswordCheck(playerid, input[])
{
	new password[140], DB_Hash[BCRYPT_HASH_LENGTH];
	cache_get_row(0, 0, DB_Hash, ServerVars[MySQLHandle]);
	format(password, sizeof(password), "%s%s", cP->cName[playerid], input);
	bcrypt_check(password, DB_Hash, "OnPasswordChecked", "d", playerid);
	return true;
}

public OnPasswordChecked(playerid)
{
	if(bcrypt_is_equal())
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN_INFO, DIALOG_STYLE_MSGBOX, "Login", "Erfolgreich eingelogt", "OK", "");
	}
	else
	{
		new str[120];
		format(str, sizeof(str), "Wir konnten dich nicht einloggen.\n\
								 Das eingegebene Passwort ist falsch.\n\
								 Bitte versuch es erneut.", cP->cName[playerid]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", str, "Login", "Ciao");
	}
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