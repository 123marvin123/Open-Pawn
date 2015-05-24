/* 
 * ---------------------------------------------------------
 * constant PlayerVars
 * ---------------------------------------------------------
 */

enum const_struc
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	Float:Cord[4],
	ActorID,
	CamObj,
	const_flags:cFlags,
	adminRank
};

enum const_flags (<<= 1)
{
	Logedin = 1,
	LoginDone,
	NoSkin,
	SelectZoom,
	LastPosSpawn,
	RegisterSpawn
};
new constPlayer[MAX_PLAYERS][const_struc];

/* 
 * ---------------------------------------------------------
 * variable PlayerVars
 * ---------------------------------------------------------
 */

enum var_struc
{
	var_flags:vFlags
};

enum var_flags (<<= 1)
{
	Spectating = 1,
	Spawned
}

new Player[MAX_PLAYERS][var_struc];