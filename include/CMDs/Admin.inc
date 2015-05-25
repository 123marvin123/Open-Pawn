Cmd->makeadmin(playerid, params[])
{
	new user, adminrank, string[80];
	
	if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, Color(White), "Du bist kein RCON Administrator!");
	if(sscanf(params, "ui", user, adminrank)) return SendClientMessage(playerid, Color(White), "Verwendung: /makeadmin [Teil des Benutzernames / Benutzerid] [Rank]");
	if(!IsPlayerConnected(user)) return SendClientMessage(playerid, Color(White), "Der Benutzer ist nicht online.");
	
	format(string, sizeof(string), "Du hast dem Benutzer %s den Adminrank %d gegeben!", cPlayer->cName[playerid], adminrank);
	SendClientMessage(playerid, Color(White), string);
	
	format(string, sizeof(string), "Der Benutzer %s hat dir den Adminrank %d gegeben!", cPlayer->cName[user], adminrank);
	SendClientMessage(user, Color(White), string);
	
	cPlayer->AdminRank[user] = adminrank;
	return true;
}