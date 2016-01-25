// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_FILESYSTEM_H
#define ENGINE_SYS_FILESYSTEM_H

namespace engine {
namespace sys {

	bool listFilesInDirectory(std::vector<String> &out, const String &path);

	void initializeFilesystem();

	// Wraps the basic fopen / fopen_s functions
	bool fileOpen(FILE **file, const String &fileName, const String &mode);
	void fileClose(FILE *file);

}
}

#endif
