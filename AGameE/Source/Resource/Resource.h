#pragma once
#ifndef RESOURCE_H_
#define RESOURCE_H_

#include"..\Common\Utility.h"

class Resource
{
public:
	std::string m_name;
	Resource(const std::string &name)
	{
		m_name = name;
	}
};

#endif // !RESOURCE_H_

