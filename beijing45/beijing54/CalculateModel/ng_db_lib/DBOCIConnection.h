#pragma once
#ifdef USE_OCILIB
#include "IDBConnection.h"
using namespace NGDBCom;
#include "ocilib.h"

#ifdef _MSC_VER
#pragma comment(lib,"ociliba.lib")
#endif

class DBOCICommand;

class DBOCIConnection :
	public IDBConnection
{
public:
	DBOCIConnection(const char* inuser,const char* inpwd);
	virtual ~DBOCIConnection(void);
protected:
	DBText user;
	DBText pwd;
	OCI_Connection * p_con;
	DBOCICommand *p_cmd;
public:
	virtual bool Open(void);
	virtual bool Close(void);
	virtual IDBCommand* CreateCommand(void);
protected:
	virtual void ClearCommand(void);
};
#endif
