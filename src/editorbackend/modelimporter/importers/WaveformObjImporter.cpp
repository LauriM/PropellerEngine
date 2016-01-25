// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/modelimporter/importers/WaveformObjImporter.h"
#include <fstream>
#include "engine/util/StringUtil.h"

#include <boost/lexical_cast.hpp>

#include "editorbackend/modelimporter/AbstractModelImporter.h"
#include "engine/stream/BufferedOutputStream.h"
#include "engine/renderer/PropellerModelVersionIdentifier.h"

/**

 .obj format
 triangles  ! not quads

*/

namespace editor {

	bool WaveformObjImporter::convertToPropellerModel(String filename, ModelStream &stream)
	{
		struct Float3
		{
			float v[3];
		};

		struct FaceData
		{
			FaceData() {}
			FaceData(unsigned vertexIndex, unsigned texCoordIndex, unsigned normalIndex)
				: vertexIndex(vertexIndex)
				, texCoordIndex(texCoordIndex)
				, normalIndex(normalIndex)
			{ }

			unsigned vertexIndex;
			unsigned texCoordIndex;
			unsigned normalIndex;
		};

		struct Face
		{
			FaceData v[3];
		};

		LOG_INFO("importing file from .obj!");

		std::ifstream file(filename); //HACK: Editor is windows only, not using wrappers

		if (!file.is_open())
			return false;

		std::vector<Float3> objVertices;
		std::vector<Float3> objTexCoords;
		std::vector<Float3> objNormals;
		std::vector<Face> objFaces;

		String line;
		while (std::getline(file, line))
		{
			if (line.substr(0, 1) == "#")
				continue; // comment

			if (line.substr(0, 2) == "v ")
			{
				std::vector<String> parts;
				engine::util::explode(&parts, line, ' ');

				Float3 f3;


				f3.v[0] = boost::lexical_cast<float>(parts[1]);
				f3.v[1] = boost::lexical_cast<float>(parts[2]);
				f3.v[2] = boost::lexical_cast<float>(parts[3]);

				objVertices.push_back(f3);
				continue;
			}

			if (line.substr(0, 3) == "vn ")
			{
				std::vector<String> parts;
				engine::util::explode(&parts, line, ' ');

				Float3 f3;

				f3.v[0] = boost::lexical_cast<float>(parts[1]);
				f3.v[1] = boost::lexical_cast<float>(parts[2]);
				f3.v[2] = boost::lexical_cast<float>(parts[3]);

				objNormals.push_back(f3);
				continue;
			}

			if (line.substr(0, 3) == "vt ")
			{
				std::vector<String> parts;
				engine::util::explode(&parts, line, ' ');

				Float3 f3;

				f3.v[0] = boost::lexical_cast<float>(parts[1]);
				f3.v[1] = boost::lexical_cast<float>(parts[2]);
				f3.v[2] = boost::lexical_cast<float>(parts[3]);

				objTexCoords.push_back(f3);
				continue;
			}

			if (line.substr(0, 2) == "f ")
			{
				std::vector<String> parts;
				engine::util::explode(&parts, line, ' ');

				String faceStrings[3];

				faceStrings[0] = parts[1];
				faceStrings[1] = parts[2];
				faceStrings[2] = parts[3];

				Face face;

				for (unsigned i = 0; i < 3; ++i)
				{
					std::vector <String> parts;
					engine::util::explode(&parts, faceStrings[i], '/');

					face.v[i] = FaceData(boost::lexical_cast<unsigned>(parts[0]), boost::lexical_cast<unsigned>(parts[1]), boost::lexical_cast<unsigned>(parts[2]));
				}

				objFaces.push_back(face);

				continue;
			}

			DEBUG_PRINT("Line ignored: " << line);
		}

		LOG_INFO("Reading data from .obj file done.");

		// .PropellerModel header
		stream.write(PROPELLER_MODEL_IDENTIFIER, PROPELLER_MODEL_IDENTIFIER_SIZE);
		stream.write(unsigned(2)); //This is version 1 writer

		// face is one vertex, vertex has 3 floats, 3 normal and 3 texCoords floats(4bit).
		//   3 * 9 -> 27
		stream.write(unsigned(objFaces.size() * 27)); 
		

		for (unsigned i = 0; i < objFaces.size(); ++i)
		{
			// vertex 3 + normal + 3  (float)
			//DEBUG_PRINT("write > face: " << i << "vertexIndex:" << objFaces[i].v[0].vertexIndex);
			stream.write(objVertices[objFaces[i].v[0].vertexIndex - 1].v[0]);
			stream.write(objVertices[objFaces[i].v[0].vertexIndex - 1].v[1]);
			stream.write(objVertices[objFaces[i].v[0].vertexIndex - 1].v[2]);

			//DEBUG_PRINT("write > texCoord: " << i << "texCoordIndex:" << objFaces[i].v[0].texCoordIndex);
			stream.write(objTexCoords[objFaces[i].v[0].texCoordIndex - 1].v[0]);
			stream.write(objTexCoords[objFaces[i].v[0].texCoordIndex - 1].v[1]);
			stream.write(objTexCoords[objFaces[i].v[0].texCoordIndex - 1].v[2]);

			//DEBUG_PRINT("write > normal: " << i << "normalIndex:" << objFaces[i].v[0].normalIndex);
			stream.write(objNormals[objFaces[i].v[0].normalIndex - 1].v[0]);
			stream.write(objNormals[objFaces[i].v[0].normalIndex - 1].v[1]);
			stream.write(objNormals[objFaces[i].v[0].normalIndex - 1].v[2]);

			//#

			//DEBUG_PRINT("write > face: " << i << "vertexIndex:" << objFaces[i].v[1].vertexIndex);
			stream.write(objVertices[objFaces[i].v[1].vertexIndex - 1].v[0]);
			stream.write(objVertices[objFaces[i].v[1].vertexIndex - 1].v[1]);
			stream.write(objVertices[objFaces[i].v[1].vertexIndex - 1].v[2]);


			//DEBUG_PRINT("write > texCoord: " << i << "texCoordIndex:" << objFaces[i].v[1].texCoordIndex);
			stream.write(objTexCoords[objFaces[i].v[1].texCoordIndex - 1].v[0]);
			stream.write(objTexCoords[objFaces[i].v[1].texCoordIndex - 1].v[1]);
			stream.write(objTexCoords[objFaces[i].v[1].texCoordIndex - 1].v[2]);

			//DEBUG_PRINT("write > normal: " << i << "normalIndex:" << objFaces[i].v[1].normalIndex);
			stream.write(objNormals[objFaces[i].v[1].normalIndex - 1].v[0]);
			stream.write(objNormals[objFaces[i].v[1].normalIndex - 1].v[1]);
			stream.write(objNormals[objFaces[i].v[1].normalIndex - 1].v[2]);

			//#

			//DEBUG_PRINT("write > face: " << i << "vertexIndex:" << objFaces[i].v[2].vertexIndex);
			stream.write(objVertices[objFaces[i].v[2].vertexIndex - 1].v[0]);
			stream.write(objVertices[objFaces[i].v[2].vertexIndex - 1].v[1]);
			stream.write(objVertices[objFaces[i].v[2].vertexIndex - 1].v[2]);


			//DEBUG_PRINT("write > texCoord: " << i << "texCoordIndex:" << objFaces[i].v[2].texCoordIndex);
			stream.write(objTexCoords[objFaces[i].v[2].texCoordIndex - 1].v[0]);
			stream.write(objTexCoords[objFaces[i].v[2].texCoordIndex - 1].v[1]);
			stream.write(objTexCoords[objFaces[i].v[2].texCoordIndex - 1].v[2]);

			//DEBUG_PRINT("write > normal: " << i << "normalIndex:" << objFaces[i].v[2].normalIndex);
			stream.write(objNormals[objFaces[i].v[2].normalIndex - 1].v[0]);
			stream.write(objNormals[objFaces[i].v[2].normalIndex - 1].v[1]);
			stream.write(objNormals[objFaces[i].v[2].normalIndex - 1].v[2]);
		}

		// INDICES ARE JUST LIST FROM 0 TO FACECOUNT
		// CONSIDER DROPPING/OPTIMIZING THESE
		stream.write(unsigned(objFaces.size() * 3));

		for (unsigned i = 0; i < (objFaces.size() * 3); ++i)
			stream.write(uint16_t(i));

		return true; 
	}

}