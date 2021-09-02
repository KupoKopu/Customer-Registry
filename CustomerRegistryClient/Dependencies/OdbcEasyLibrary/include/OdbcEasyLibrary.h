#ifndef ODBC_FUNCTIONS
#define ODBC_FUNCTIONS

#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

namespace odbc {
	extern RETCODE rc;

	void initialise(SQLHANDLE& hEnvironment, SQLHANDLE& hConnection);

	//done
	void connect(SQLHANDLE& hConnection, SQLWCHAR* conn);

	//done but not really a functional thing
	//void checkIntegral();

	//done
	void rcCheck(RETCODE& retcode = rc);

	//not done but not really needed
	void getDiagRec(SQLSMALLINT handleType, SQLHANDLE& hStatement, SQLSMALLINT record);

	//done
	void initiateStatement(SQLHANDLE& hConnection, SQLHANDLE& hStatement);

	//done
	void directExecute(SQLHANDLE& hStatement, SQLWCHAR* Statement);

	//void prepareParam();

	//done
	void getColInfo(SQLHANDLE& hStatement, int colPos);

	//done
	void getColNumber(SQLHANDLE& hStatement);


	//done
	void prepareColContainer(SQLHANDLE& hStatement, SQLCHAR& container, int colPos, SQLSMALLINT sqlType, SQLINTEGER bufferLength);

	void prepareColContainer(SQLHANDLE& hStatement, SQLINTEGER* container, int colPos, SQLSMALLINT sqlType);

	//doesnt work? dont bother not needed
	//void setPosition(SQLUSMALLINT row);

	//done
	void fetchCol(SQLHANDLE& hStatement);

	//done
	void freeStatement(SQLHANDLE& hStatement);

	//done
	void disconnect(SQLHANDLE& hConnection);

	//done
	void freeConnection(SQLHANDLE& hConnection);

	//done
	void freeEnv(SQLHANDLE& hEnvironment);

}


#endif // !ODBC_FUNCTIONS
