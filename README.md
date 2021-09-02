# Customer-Registry
A little project to understand tcp/ip by implementing a GUI application that sends simple records to an SQL Server via ODBC. (c++)

Apologies with the mess, this is the first time I'm seriously using git and github and trying to upload projects to be somewhat functional off of my computer. if there are any actual looking at this embarrassment, please give tips ;)

Dependencies:
wxwidgets 3.1.4

notes:
- This shouldn't really work since it's simply made to connect to the database on my computer but it can be possible if I simply put sql scripts in the git repo for others to use.
- This application may or may not work as for some other computers it shows errors of missing '.dlls' which I can gather have to be from the visual c++ redistributables. so either they have to be reinstalled or perhaps it didn't work since they didn't have visual studio 2019 and it's c++ development package?
- I will need to find a way to more effectively package this application and it's dependencies, currently have any required in the dependencies folder but it somehow feels wrong. maybe an install wizard is it? or I require a tool that keeps only necessary files? I have no clue.
- Need to find out how licensing works and how to comply with other projects, because I simply shoved wxwidgets built libs in here with no regard...
- Probably should include my odbc functions lib file's project in here.
