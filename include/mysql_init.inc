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

#if defined mysql_OnGameModeInit
forward mysql_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef _ALS_OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit mysql_OnGameModeInit