//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <google/protobuf/arena.h>

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Test::RunTests();

	google::protobuf::ShutdownProtobufLibrary();
}

// ---  End of File ---------------
