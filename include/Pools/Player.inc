enum const_struc
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	Float:Cord[3],
	ActorID,
	CamObj,
	const_flags:cFlags
};

enum const_flags (<<= 1)
{
	Logedin = 1,
	LoginDone,
	NoSkin,
	SelectZoom
};
new constPlayer[MAX_PLAYERS][const_struc];