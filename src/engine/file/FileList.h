// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_FILELIST_H
#define ENGINE_FILE_FILELIST_H

namespace engine {
namespace file {

	// FileList is used to collect file listing from all the package managers.
	// It handles 'overrides' by multiple archive systems.
	class FileList
	{
	public:
		typedef std::vector<String> FileArray;

	private:
		FileArray files;

	public:
		const FileArray &getFiles() const { return files; }

		void addFile(const String &filename) 
		{ 
			for (unsigned i = 0; i < files.size(); ++i)
			{
				if (files[i] == filename)
				{
					files.erase(files.begin() + i);
					break; //remove old file, overwriting!
				}
			}

			files.push_back(filename); 
		}

		const String &operator[] (const unsigned index) const
		{
			assert(index >= 0);
			assert(index < files.size());

			return files[index];
		}
		
		const unsigned getSize() const { return files.size(); }
	};

}
}

#endif