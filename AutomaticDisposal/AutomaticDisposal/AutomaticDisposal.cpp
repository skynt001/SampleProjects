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


///////////////////////////////////////////////
// DisposedFlag
DisposedFlag::DisposedFlag(String^ objectName)
	: isDisposed(false), objectName(objectName)
{
}

DisposedFlag::~DisposedFlag()
{
	isDisposed = true;
}

DisposedFlag::!DisposedFlag()
{

}

DisposedFlag::operator bool()
{
	return isDisposed;
}

void DisposedFlag::EnsureObjectIsNotDisposed()
{
	if (isDisposed)
		throw gcnew ObjectDisposedException(objectName);
}

///////////////////////////////////////////////
// SmartFileDumper
SmartFileDumper::SmartFileDumper(String^ name)
	: disposedFlag("FileDumper")
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

void SmartFileDumper::Dump()
{
	disposedFlag.EnsureObjectIsNotDisposed();

	if (streamReader != nullptr)
		Console::WriteLine(streamReader->ReadToEnd());
}

void SmartFileDumper::CheckDisposed()
{
	if (disposedFlag)
		Console::WriteLine("FileDumper is disposed");
	else
		Console::WriteLine("FileDumper is not disposed");
}
