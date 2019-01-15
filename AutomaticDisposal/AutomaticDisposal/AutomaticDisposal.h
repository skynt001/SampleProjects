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

}
