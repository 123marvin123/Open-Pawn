#include <../../include/header>

main()
{
	print("\n----------------------------------");
	print(" Open Source Gamemode");
	print(" Source can be found under:");
	print(" https://github.com/Reclusior/Open-Pawn");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	SetGameModeText(MODE);
	UsePlayerPedAnims();
	
	InitRegistrationDraws();
	return true;
}