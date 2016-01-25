// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/util/StringUtil.h"

namespace engine {
namespace util {

	void explode(std::vector<String> *result, const String & src, char delim)
	{
		std::istringstream iss(src);

		for(String token; std::getline(iss,token,delim);){
			if(!token.empty()){
				result->push_back(boost::move(token));
			}
		}
	}

}
}