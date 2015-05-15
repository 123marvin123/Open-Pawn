enum sv // Enum for the Servervariables
{
	MySQLHandle,
	Text:RegisterArrow[2],
	Text:Done[2],
	svFlags:Flags
};

enum svFlags (<<=1)
{
	NoConnectionShutDown = 1,
};
new ServerVars[sv];

enum
{
	#if RELEASE_STATE == DEBUG
	DIALOG_INFO,
	#endif
	
	DIALOG_REGISTER,
	DIALOG_LOGIN,
	DIALOG_LOGIN_INFO
};

enum spawn_struc
{
	Float: sX,
	Float: sY,
	Float: sZ,
	Float: sAngle
};

new Spawns[][spawn_struc] =
{
	{ -2248.2258, 2330.5852, 4.9741, 55.0 },
	{ -2247.9294, 2306.0669, 4.9737, 90.0 },
	{ -2272.1458, 2282.0032, 4.9770,   0.0 }
};