// "helloworld.cpp": Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>

#include <nlohmann\json.hpp>

using json = nlohmann::json;

#define DECLARE_JSON_VALUE(type,var,value)                            \
						private: type var##_ {setValue(#var,value)};  \
						public:  auto& var() { return getValue(#var);}

#define DECLARE_JSON_ARRAY(type,var,size,value)                       \
						private:	type var##_ {setValueA(#var,size,value)};\
						public:  auto& var() { return getValue(#var);}
class JsonReflect
{
public:
	template <typename T>
	T setValue(const std::string& key, T value)
	{
		m_map[key] = value;
		return value;
	}

	template <typename T>
	T setValueA(const std::string& key, int size, T value)
	{
		std::vector<T> v{value};
		v.reserve(size);
		m_map[key] = v;
		for (int i=0;i<size;i++)
			m_map[key][i] = value;
		return value;
	}

	auto & getValue(const std::string& key)
	{
		return m_map[key];
	}

	void writeJson()
	{
		std::cout << m_map << std::endl;
	}

private:
	json m_map;
};

class Proba : public JsonReflect
{
	
	DECLARE_JSON_VALUE(int,		var1,		0);
	DECLARE_JSON_VALUE(const char*, VAR2,		"doof");
	DECLARE_JSON_VALUE(double,	variable88, 	.4);
	DECLARE_JSON_VALUE(bool,	var,		true);
	DECLARE_JSON_VALUE(std::string, vars,		"hello");
	
	json j2;
	DECLARE_JSON_VALUE(json, varj, j2);
	DECLARE_JSON_ARRAY(int, ia, 8, 14);
	DECLARE_JSON_ARRAY(std::string, sa, 3, "empty");
};

int main()
{
	Proba proba;
	proba.writeJson();
	
	proba.var()		= 8;
	proba.VAR2()		= "no doof";
	proba.variable88()	= 1.4;
	proba.var()		= false;
	proba.vars()		= "bye";
	proba.varj()["int"]	= 4;
	proba.varj()["bool"] 	= true;

	proba.ia()[0] 		= 1;
	proba.ia()[4] 		= 2;

	std::cout << std::endl;
	proba.writeJson();

    return 0;
}
