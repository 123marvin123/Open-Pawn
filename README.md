# Open-Pawn
An Open Source Gamemode for SA:MP

Note: This repository don't include the SAMP software or the plugins to run the server.
Please download them by yourself.


The server currently needs to run:

* SA:MP 0.3.7 RC6(-3) Server (http://team.sa-mp.com/037RC/samp037_svr_RC6-3_win32.zip)
* MySQL Plugin from BlueG R39(-3) (https://github.com/pBlueG/SA-MP-MySQL)
* bycrpt from Lassir 2.2.3 (https://github.com/lassir/bcrypt-samp)
* sscanf 2.8.2 from Y_Less reuploaded by Emmet_ (https://dl.dropboxusercontent.com/u/102595204/sscanf-2.8.2.zip)

-------------------------------------------------------------------------------------------------------------------------

# If you're working on this script:

* Use english for variables and functions, in the comments and commits.
* Use the current struct to keep the code clean
* If you need to add some folders or files e.g. for systems - do it.
* don't upload your local MySQL database or connection informations - for this please use the mysql_data.inc.
You can find it in the folder "include/Info"

When you changed the connection information in mysql_data.inc.

Open the git shell and push this:

`git update-index --assume-unchanged include/Info/mysql_data.inc`

This will stop tracking the mysql_data.inc file in the commits.
