
#pragma once

#include "BaseConverter.h"

#include <vector>
#include <iostream>
using namespace std;


#define DISPID_APPICATION_CURRENTDATA	0x000008a8
#define DISPID_CURRENTDATA_ALLTABLES	0x000008b1
#define DISPID_ALLTABLES_COUNT			0x000007d1
#define DISPID_ALLTABLES_ITEM			0x00000000
#define DISPID_ACCESSOBJECT_NAME		0x80010000

#define DISP_FREEARGS 0x02

/***************************************
	Use with the ExportXML method
***************************************/
#define acQuitPrompt	0	// Displays a dialog box that asks whether you want to save any database objects that have been changed but not saved.
#define acQuitSaveAll	1	// (Default) Saves all objects without displaying a dialog box.
#define acQuitSaveNone	2	// Quits Microsoft Access without saving any objects.

#define acExportForm	2	// Form
#define	acExportFunction	10	// User-defined function (Microsoft Access project only)
#define	acExportQuery	1	// Query
#define	acExportReport	3	// Report
#define	acExportServerView	7	// Server view (Microsoft Access project only)
#define	acExportStoredProcedure	9	// Stored procedure (Microsoft Access project only)
#define	acExportTable	0	// Table

/***************************************
	Use with the ExportCSV method (enum AcTextTransferType)
***************************************/
#define	acImportDelim	0
#define	acImportFixed	1
#define	acExportDelim	2
#define	acExportFixed	3
#define	acExportMerge	4
#define	acLinkDelim		5
#define	acLinkFixed		6
#define	acImportHTML	7
#define	acExportHTML	8
#define	acLinkHTML		9



class CMDBConverter : public BaseConverter
{
public:
	CMDBConverter(void);
	virtual ~CMDBConverter(void);

protected:
	virtual bool Init();
	virtual bool Convert(wstring path);
	virtual bool Release();

private:
	HRESULT OpenMDB(LPOLESTR filepath);
	HRESULT CloseMDB();
	HRESULT ExportCSV(WORD ObjectType, const vector<LPOLESTR>& DataSource, const LPOLESTR DataTarget);
	HRESULT ExportXML(WORD ObjectType, const vector<LPOLESTR>& DataSource, const LPOLESTR DataTarget);
	HRESULT QuitAccess(WORD Options);

	int GetTableNames(vector<LPOLESTR>& tableNames);
	bool GetMDBFileContainer(wstring path, vector<wstring>& container);

private:
	IDispatch* m_pAccessApp;
	WORD m_nProgressGauge;

};

