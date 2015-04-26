# Open-Pawn
An Open Source Gamemode for SA:MP

Note: This repository don't include the SAMP software or the plugins to run the server.
Please look for them by yourself.


The server currently needs to run:

SA:MP 0.3.7 RC5 Server
MySQL Plugin from BlueG R39(-3) (https://github.com/pBlueG/SA-MP-MySQL)
bycrpt from Lassir V2.2.3 (https://github.com/lassir/bcrypt-samp)

-------------------------------------------------------------------------------------------------------------------------

If you're working on this script:

Use english for variables and functions, in the comments and commits.

Use the current struct to keep the code clean

If you need to add some folders or files e.g. for systems - do it.

don't upload your local MySQL database or connection informations - for this please use the mysql_data.inc.
You can find it in the folder "include/Info"

When you changed the connection information in mysql_data.inc
Open the git shell and push this: ```git update-index --assume-unchanged include/Info/mysql_data.inc ```
This will stop tracking the mysql_data.inc filefor in the commits.