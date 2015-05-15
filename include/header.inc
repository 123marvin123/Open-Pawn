/*
 * ---------------------------------------------------------
 * Development State Part
 * ---------------------------------------------------------
 */

#define DEBUG				1
#define RELEASE 			2

#define RELEASE_STATE		DEBUG

/*
 * ---------------------------------------------------------
 * Required Stuff
 * ---------------------------------------------------------
 */

#include <a_samp>
#include <a_mysql>
#include <bcrypt>
#include <sscanf2>

/*
 * ---------------------------------------------------------
 * Info Part
 * ---------------------------------------------------------
 */

#include <../../include/Info/mysql_data>
#include <../../include/Info/GlobalStructs>
#include <../../include/Info/Color>

/*
 * ---------------------------------------------------------
 * Stuff to run the Gamemode correctly
 * ---------------------------------------------------------
 */

#include <../../include/preprocess>
#include <../../include/cmdprocess>
#include <../../include/mysql_init>

/*
 * ---------------------------------------------------------
 * Variables / Pools Part
 * ---------------------------------------------------------
 */

#include <../../include/Pools/Player>
#include <../../include/Pools/Actor>

/*
 * ---------------------------------------------------------
 * Hook(s) Part
 * ---------------------------------------------------------
 */

#include <../../include/Hooks/ActorHooks>
#include <../../include/Hooks/PlayerHooks>

/*
 * ---------------------------------------------------------
 * Variables und Info Part
 * ---------------------------------------------------------
 */

#if RELEASE_STATE == DEBUG
	#include <../../include/CMDs/DebugCMDs>
#endif
 
/*
 * ---------------------------------------------------------
 * Systems Part
 * ---------------------------------------------------------
 */
 
#include <../../include/Systems/Login>
#include <../../include/Systems/GlobalTextdrawHandler>

/*
 * ---------------------------------------------------------
 * Saving Part
 * ---------------------------------------------------------
 */
 
#include <../../include/Saveing/PlayerSave>