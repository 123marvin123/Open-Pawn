#define MODE 				"Open Pawn"

#define isnull(%1)  		((%1[0] == 0) || (%1[0] == 1 && %1[1] == 0))

/*
 * ----------------------------------------
 * Variables Restructure
 * ----------------------------------------
 */
 
#define cPlayer->%2[%1] 	constPlayer[%1][%2]
#define Actor->%2[%1] 		Actors[%1][%2]

/*
 * ----------------------------------------
 * For Color.inc
 * ----------------------------------------
 */

#define Color(%0)		((%0 << 8) + 0xFF)
#define ARGB(%0)		(0xFF + (%0))

#define ColorEx(%0, %1)	((%0 << 8) + %1)
#define ARGBEx(%0, %1)	(%1 + (%0))

/*
 * ----------------------------------------
 * Bodyparts
 * ----------------------------------------
 */
 
#define BODY_PART_TORSO 		3
#define BODY_PART_GROIN			4
#define BODY_PART_LEFT_ARM		5
#define BODY_PART_RIGHT_ARM 	6
#define BODY_PART_LEFT_LEG		7
#define BODY_PART_RIGHT_LEG		8
#define BODY_PART_HEAD 			9 