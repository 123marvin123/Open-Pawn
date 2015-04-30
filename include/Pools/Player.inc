enum constantvars
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	Float:Cord[3],
	constantflags:cFlags
};

enum constantflags (<<= 1)
{
	Logedin = 1
};
new constPlayer[MAX_PLAYERS][constantvars];