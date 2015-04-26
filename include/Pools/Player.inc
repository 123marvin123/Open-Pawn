enum constantvars
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	constantflags:cFlags
};

enum constantflags (<<= 1)
{
	Loggedin = 1
};
new cPlayer[MAX_PLAYERS][constantvars];