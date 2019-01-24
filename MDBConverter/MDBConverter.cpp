
#include "stdafx.h"
#include "MDBConverter.h"

#include <io.h>


CMDBConverter::CMDBConverter(void)
	: m_nProgressGauge(0)
{
	m_pAccessApp = NULL;
}

CMDBConverter::~CMDBConverter(void)
{
	Release();

	if (m_pAccessApp)
		m_pAccessApp = NULL;
}

bool CMDBConverter::Init()
{
	CLSID clsid;
	if (FAILED(CLSIDFromProgID(L"Access.Application", &clsid))) {
		MessageBox(NULL, _T("Cannot obtain CLSID from ProgID"), L"Failed", MB_OK | MB_ICONSTOP);
	}

	OleInitialize(NULL);

	IUnknown* pUnk = NULL;
	HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (LPVOID*)&pUnk);

	if (SUCCEEDED(hr)) {
		// Get IDispatch interface for Automation...
		IDispatch* pDisp = NULL;
		hr = pUnk->QueryInterface(IID_IDispatch, (void**)&pDisp);
		
		if (SUCCEEDED(hr)) {
			m_pAccessApp = pDisp;

			return true;
		}
	}

	return false;
}

bool CMDBConverter::Convert(wstring path)
{
	vector<wstring> mdbContainer;
	if (!GetMDBFileContainer(path, mdbContainer))
		return false;

	HRESULT hr = S_FALSE;

	for (vector<wstring>::iterator iter = mdbContainer.begin(); iter != mdbContainer.end(); ++iter) {
		wcout << (*iter).c_str() << endl;
		//cout << "Convert MDB to XML... 0%" << '\r';
		cout << "Convert MDB to CSV... 0%" << '\r';

		hr = OpenMDB(const_cast<WCHAR*>((*iter).c_str()));
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Cannot open Access DB"), L"Failed", MB_OK | MB_ICONSTOP);
		}
		else {
			wstring convertPath;
			int delPos = (*iter).rfind(DIRDELIM_STR);
			if (delPos != -1) {
				convertPath = (*iter).substr(0, delPos + 1);
				convertPath.append(L"Convert\\");
			}

			CreateDirectory(convertPath.c_str(), NULL);

			vector<LPOLESTR> vecTableNames;
			if (GetTableNames(vecTableNames) > 0) {
				//hr = ExportXML(acExportTable, vecTableNames, (LPOLESTR)convertPath.c_str());
				hr = ExportCSV(acExportTable, vecTableNames, (LPOLESTR)convertPath.c_str());

				if (FAILED(hr)) {
					//MessageBox(NULL, _T("Cannot convert MDB to XML"), L"Failed", MB_OK | MB_ICONSTOP);
					MessageBox(NULL, _T("Cannot convert MDB to CSV"), L"Failed", MB_OK | MB_ICONSTOP);
				}
				else {
					//cout << "Convert MDB to XML... 100%" << endl;
					cout << "Convert MDB to CSV... 100%" << endl;
				}
			}

			hr = CloseMDB();
		}
		
		m_nProgressGauge = 0;
	}	

	hr = QuitAccess(acQuitSaveNone);

	if (SUCCEEDED(hr))
		return true;

	return false;
}

bool CMDBConverter::GetMDBFileContainer(wstring path, vector<wstring>& container)
{
	// case1: c:\test\test.mdb or c:\test\*.mdb
	// case2: c:\test\

	wstring dirPath = path;
	wstring fullPath;
	if (GetFileAttributes(dirPath.c_str()) == FILE_ATTRIBUTE_DIRECTORY) {
		if (dirPath[dirPath.length() - 1] != DIRDELIM_CHAR)
			dirPath.append(DIRDELIM_STR);

		fullPath.assign(dirPath);
		fullPath.append(L"*.*");
	}
	else {
		int allDotPos = dirPath.rfind(L"*.");
		if (allDotPos == -1 && // path is file path
			(dirPath.substr(dirPath.rfind(DIRDELIM_STR), dirPath.length()).rfind(L".mdb") != -1 || 
			dirPath.substr(dirPath.rfind(DIRDELIM_STR), dirPath.length()).rfind(L".MDB") != -1)) {
			container.push_back(dirPath);
			return true;
		}

		dirPath = dirPath.substr(0, dirPath.rfind(DIRDELIM_STR) + 1);
		
		fullPath.assign(dirPath);
		fullPath.append(L"*.*");
	}

	struct _wfinddata_t fd;
	intptr_t handle = NULL;
	if ((handle = _wfindfirst(fullPath.c_str(), &fd)) == -1L) {
		return false;
	}

	wstring subDirPath;
	do {
		if ((fd.attrib & _A_SUBDIR) && fd.name[0] != L'.') {
			subDirPath.assign(dirPath);
			subDirPath.append(fd.name);
			subDirPath.append(DIRDELIM_STR);

			GetMDBFileContainer(subDirPath, container);
		}
		else {
			_wcsupr_s(fd.name);
			if ((wcsstr(fd.name, L".MDB") != NULL) &&
				(find(container.begin(),container.end(), dirPath + fd.name) == container.end()))
					container.push_back(dirPath + fd.name);
		}
	} while (_wfindnext(handle, &fd) == 0);

	_findclose(handle);

	return true;
}

bool CMDBConverter::Release()
{
	if (m_pAccessApp)
		m_pAccessApp->Release();

	OleUninitialize();

	return false;
}

HRESULT CMDBConverter::OpenMDB(LPOLESTR fullPath)
{
	HRESULT hr = S_FALSE;
	DISPID dispid = NULL;
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };

	// TODO: argsCount, lpszName & invoking logic to param
	auto argsCount = 3;
	OLECHAR* lpszName = L"OpenCurrentDatabase";
	
	VARIANT retVal;
	VariantInit(&retVal);

	hr = m_pAccessApp->GetIDsOfNames(IID_NULL, &lpszName, 1, LOCALE_USER_DEFAULT, &dispid);
	if (SUCCEEDED(hr)) {

		VARIANTARG* pArgs = new VARIANT[argsCount + 1];
		for (auto i = 0; i < argsCount; ++i)
			VariantInit(&pArgs[i]);

		CComVariant cvFilePath(fullPath);
		CComVariant cvExclusive(VARIANT_FALSE);
		// INFO: reverse
		pArgs[2] = cvFilePath;
		pArgs[1] = cvExclusive;

		dispParams.cArgs = argsCount;
		dispParams.rgvarg = pArgs;

		hr = m_pAccessApp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispParams, &retVal, NULL, NULL);

		delete [] pArgs;
	}	

	return hr;
}

HRESULT CMDBConverter::CloseMDB()
{
	HRESULT hr = S_FALSE;
	DISPID dispid = NULL;
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };

	OLECHAR* lpszName = L"CloseCurrentDatabase";
	
	VARIANT retVal;
	VariantInit(&retVal);

	hr = m_pAccessApp->GetIDsOfNames(IID_NULL, &lpszName, 1, LOCALE_USER_DEFAULT, &dispid);
	if (SUCCEEDED(hr))
		hr = m_pAccessApp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispParams, &retVal, NULL, NULL);

	return hr;
}

HRESULT CMDBConverter::ExportCSV(WORD ObjectType, const vector<LPOLESTR>& DataSource, const LPOLESTR DataTarget)
{
	HRESULT hr = S_FALSE;
	DISPID doCmdID = NULL;
	DISPID transferTextID = NULL;
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };
	IDispatch* pDoCmd = NULL;

	// TODO: argsCount, lpszName & invoking logic to param
	const auto argsCount = 7;

	VARIANT retVal;
	VariantInit(&retVal);

	OLECHAR* lpszDoCmd = L"DoCmd";
	hr = m_pAccessApp->GetIDsOfNames(IID_NULL, &lpszDoCmd, 1, LOCALE_USER_DEFAULT, &doCmdID);
	if (SUCCEEDED(hr)) {
		hr = m_pAccessApp->Invoke(doCmdID, IID_NULL, LOCALE_USER_DEFAULT, 
			DISPATCH_PROPERTYGET, &dispParams, &retVal, NULL, NULL);
		
		if (SUCCEEDED(hr) && retVal.vt == VT_DISPATCH) {
			hr = retVal.pdispVal->QueryInterface(IID_IDispatch, (void**)&pDoCmd);
			if (SUCCEEDED(hr)) {
				OLECHAR* lpszName = L"TransferText";
				hr = pDoCmd->GetIDsOfNames(IID_NULL, &lpszName, 1, LOCALE_USER_DEFAULT, &transferTextID);
				VariantClear(&retVal);
			}
		}
	}


	if (SUCCEEDED(hr)) {

		VARIANTARG* pArgs = new VARIANT[argsCount + 1];
		for (auto i = 0; i < argsCount; ++i)
			VariantInit(&pArgs[i]);

		vector<LPOLESTR>::const_iterator iter;
		for (iter = DataSource.begin(); iter != DataSource.end(); ++iter, ++m_nProgressGauge) {
			WCHAR wszTarget[_MAX_PATH] = { NULL, };
			wcscpy_s(wszTarget, _MAX_PATH, DataTarget);
			wcscat_s(wszTarget, _MAX_PATH, *iter);
			wcscat_s(wszTarget, _MAX_PATH, L".csv");

			CComVariant cvObjectType(acExportDelim);
			CComVariant cvDataSource(*iter);
			CComVariant cvDataTarget(wszTarget);
			//CComVariant cvHasFieldNames(VARIANT_TRUE);
			// INFO: reverse
			pArgs[6] = cvObjectType; // AcTextTransferType
			// pArgs[5] = // SpecificationName
			pArgs[4] = cvDataSource; // TableName
			pArgs[3] = cvDataTarget; // FileName
			//pArgs[2] = cvHasFieldNames; // HasFieldNames
			// pArgs[1] = // HTMLTableName
			// pArgs[0] = // CodePage

			dispParams.cArgs = argsCount;
			dispParams.rgvarg = pArgs;

			hr = pDoCmd->Invoke(transferTextID, IID_NULL, LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, &dispParams, &retVal, NULL, NULL);

			cout << "Convert MDB to CSV... " << (m_nProgressGauge * 100 / DataSource.size() + 1) << "%" << '\r';
		}

		delete [] pArgs;

		if (!pDoCmd) {
			pDoCmd->Release();
			pDoCmd = NULL;
		}
	}

	return hr;
}

HRESULT CMDBConverter::ExportXML(WORD ObjectType, const vector<LPOLESTR>& DataSource, const LPOLESTR DataTarget)
{
	HRESULT hr = S_FALSE;
	DISPID dispid = NULL;
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };

	// TODO: argsCount, lpszName & invoking logic to param
	auto argsCount = 10;
	OLECHAR* lpszName = L"ExportXML";
	
	VARIANT retVal;
	VariantInit(&retVal);

	hr = m_pAccessApp->GetIDsOfNames(IID_NULL, &lpszName, 1, LOCALE_USER_DEFAULT, 
		&dispid);

	if (SUCCEEDED(hr)) {

		VARIANTARG* pArgs = new VARIANT[argsCount + 1];
		for (auto i = 0; i < argsCount; ++i)
			VariantInit(&pArgs[i]);
		
		vector<LPOLESTR>::const_iterator iter;
		for (iter = DataSource.begin(); iter != DataSource.end(); ++iter, ++m_nProgressGauge) {
			WCHAR wszTarget[_MAX_PATH] = { NULL, };
			wcscpy_s(wszTarget, _MAX_PATH, DataTarget);
			wcscat_s(wszTarget, _MAX_PATH, *iter);
			wcscat_s(wszTarget, _MAX_PATH, L".xml");

			CComVariant cvObjectType(acExportTable);
			CComVariant cvDataSource(*iter);
			CComVariant cvDataTarget(wszTarget);
			// INFO: reverse
			pArgs[9] = cvObjectType;
			pArgs[8] = cvDataSource;
			pArgs[7] = cvDataTarget;

			dispParams.cArgs = argsCount;
			dispParams.rgvarg = pArgs;

			hr = m_pAccessApp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, &dispParams, &retVal, NULL, NULL);

			cout << "Convert MDB to XML... " << (m_nProgressGauge * 100 / DataSource.size() + 1) << "%" << '\r';
		}

		delete [] pArgs;
	}

	return hr;
}

HRESULT CMDBConverter::QuitAccess(WORD Options)
{
	HRESULT hr = S_FALSE;
	DISPID dispid = NULL;
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };

	// TODO: argsCount, lpszName & invoking logic to param
	int argsCount = 1;
	OLECHAR* lpszName = L"Quit";
	
	VARIANT retVal;
	VariantInit(&retVal);

	hr = m_pAccessApp->GetIDsOfNames(IID_NULL, &lpszName, 1, LOCALE_USER_DEFAULT, &dispid);
	if (SUCCEEDED(hr)) {

		VARIANT* pArgs = new VARIANT[argsCount + 1];
		for(auto i = 0; i < argsCount; ++i)
			VariantInit(&pArgs[i]);

		CComVariant cvOptions(Options);
		pArgs[0] = cvOptions;

		dispParams.cArgs = argsCount;
		dispParams.rgvarg = pArgs;

		hr = m_pAccessApp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispParams, &retVal, NULL, NULL);

		delete [] pArgs;
	}	

	return hr;
}

int CMDBConverter::GetTableNames(vector<LPOLESTR>& tableNames)
{
	IDispatch* pCurrentData = NULL;
	IDispatch* pAllTables = NULL;
	IDispatch* pAccessObject = NULL;
	long nTableCount = 0;
	
	VARIANT retVal;
	VariantInit(&retVal);
	DISPPARAMS dispParams = { NULL, NULL, 0, 0 };

	HRESULT hr = m_pAccessApp->Invoke(DISPID_APPICATION_CURRENTDATA, IID_NULL, LOCALE_USER_DEFAULT, 
		DISPATCH_PROPERTYGET, &dispParams, &retVal, NULL, NULL);

	if (SUCCEEDED(hr)) {
		pCurrentData = retVal.pdispVal;
		hr = pCurrentData->Invoke(DISPID_CURRENTDATA_ALLTABLES, IID_NULL, LOCALE_USER_DEFAULT, 
			DISPATCH_PROPERTYGET, &dispParams, &retVal, NULL, NULL);

		if (SUCCEEDED(hr)) {
			pAllTables = retVal.pdispVal;
			pAllTables->Invoke(DISPID_ALLTABLES_COUNT, IID_NULL, LOCALE_USER_DEFAULT, 
				DISPATCH_PROPERTYGET, &dispParams, &retVal, NULL, NULL);
			nTableCount = retVal.lVal;

			for (auto i = 0; i < nTableCount; ++i) {

				CComVariant cvVar(i);
				VARIANTARG pArg;
				pArg = cvVar;
				dispParams.cArgs = 1;
				dispParams.rgvarg = &pArg;

				hr = pAllTables->Invoke(DISPID_ALLTABLES_ITEM, IID_NULL, LOCALE_USER_DEFAULT, 
					DISPATCH_PROPERTYGET, &dispParams, &retVal, NULL, NULL);

				if (SUCCEEDED(hr)) {
					pAccessObject = retVal.pdispVal;

					DISPPARAMS itemParams = { NULL, NULL, 0, 0 };
					pAccessObject->Invoke(DISPID_ACCESSOBJECT_NAME, IID_NULL, LOCALE_USER_DEFAULT, 
						DISPATCH_PROPERTYGET, &itemParams, &retVal, NULL, NULL);

					CComVariant cvTableName(retVal);
					if (SUCCEEDED(cvTableName.ChangeType(VT_BSTR))) {
						wstring tmpTblName(retVal.bstrVal);
						wstring tmpCompSrc(tmpTblName.substr(0, 3));
						if (tmpCompSrc.compare(L"MSys") == 0)
							continue;

						tableNames.push_back(retVal.bstrVal);
					}
				}
			}
		}
	}

	return nTableCount == tableNames.size() ? nTableCount : 0;
}
