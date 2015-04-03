public OnGameModeInit()
{
	print("Initializing MySQL Connection\n");
	
	mysql_log(LOG_ALL);
	
	ServerVars[MySQLHandle] = mysql_connect(HOST, USER, DB, PASS);
	
	if(ServerVars[MySQLHandle]) print("Connection successfull");
	else
	{
		print("Connection failed\nretrying...");
		ServerVars[MySQLHandle] = mysql_connect(HOST, USER, DB, PASS);
		if(ServerVars[MySQLHandle]) print("Connection successfull");
		else
		{
			print("Couldn't reach the MySQL Server.\nServer shooting down");
			return true;
		}
	}
	
	mysql_log(LOG_ALL);
	print("\nMySQL Connection initialized\n");
	
	#if defined mysql_OnGameModeInit
		return mysql_OnGameModeInit();
	#else
		return true;
	#endif
}

public OnGameModeExit()
{
	mysql_close(ServerVars[MySQLHandle]);

	#if defined mysql_OnGameModeExit
		return mysql_OnGameModeExit();
	#else
		return true;
	#endif
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined mysql_OnGameModeInit
forward mysql_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit mysql_OnGameModeInit

#if defined mysql_OnGameModeExit
forward mysql_OnGameModeExit();
#endif
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit mysql_OnGameModeExit