#pragma once

using namespace System;
using namespace System::IO;

namespace AutomaticDisposal {

	///////////////////////////////////////////////
	// FileDumper
	public ref class FileDumper
	{
	public:
		explicit FileDumper(String^ name);
		~FileDumper(); // virtual void Dispose();
		!FileDumper(); // GC::Finalizer

		void Dump();
	
	private:
		FileStream^ fileStream;
		StreamReader^ streamReader;
	};

	///////////////////////////////////////////////
	// DisposedFlag
	ref class DisposedFlag
	{
	public:
		explicit DisposedFlag(String^ objectName);
		~DisposedFlag();
		!DisposedFlag();

		operator bool();

		void EnsureObjectIsNotDisposed();

	private:
		bool isDisposed;
		String^ objectName;
	};

	///////////////////////////////////////////////
	// SmartFileDumper
	public ref class SmartFileDumper
	{
	public:
		explicit SmartFileDumper(String^ name);

		void Dump();
		void CheckDisposed();

	private:
		DisposedFlag disposedFlag;

		FileStream^ fileStream;
		StreamReader^ streamReader;
	};

}
