#include "stdafx.h"

#include "AutomaticDisposal.h"

using namespace::AutomaticDisposal;


///////////////////////////////////////////////
// FileDumper
FileDumper::FileDumper(String^ name)
{
	fileStream = nullptr;
	try
	{
		fileStream = gcnew FileStream(name, FileMode::Open);

		streamReader = nullptr;
		try
		{
			streamReader = gcnew StreamReader(fileStream);
			
			// TODO:

		}
		catch (Exception^ e)
		{
			Console::WriteLine("Failed to read file with the following error: " + e->Message);
			
			throw;
		}
		finally
		{
			streamReader->Close();
		}
	}
	catch (Exception^ e)
	{
		Console::WriteLine("Failed to open file with the following error: " + e->Message);
	}
	finally
	{
		fileStream->Close();
	}
}

FileDumper::~FileDumper()
{
	// Free any other managed objects here.
	if (fileStream != nullptr) {
		fileStream->Close();
		fileStream = nullptr;
	}

	if (streamReader != nullptr) {
		streamReader->Close();
		streamReader = nullptr;
	}

	this->!FileDumper();
}

FileDumper::!FileDumper()
{
	// Free any other unmanaged objects here.
}

void FileDumper::Dump()
{
	if (streamReader != nullptr)
		Console::WriteLine(streamReader->ReadToEnd());
}
