# Customer-Registry
A little project to understand tcp/ip by implementing a GUI application that sends simple records to an SQL Server via ODBC. (c++)
A C++ GUI Application.

Main goal was to play around with database connections which is why it's a 'Customer Registry' or registration application.

Build information:
- Built with MSVC v142 - VS 2022 C++ x64/x86 build tools.
- Currently only possible to build wtih x86 release. release or debug.


Dependencies:
wxwidgets 3.1.5 (Shouldn't matter since its within the project)

WTD:
- Need to find out how licensing works and how to comply with other projects, because I simply shoved wxwidgets built libs in here with no regard...
- Want to try and build with multiple compilers so I'll try and figure how that works
- Want to check how to structure a git repo to be organised with source and builds
- Will probably come back at some point to restructure the code.
