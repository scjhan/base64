#pragma once

#include <functional>
#include <string>
#include <map>

class Testor
{
public:
	typedef std::function<void()> TestType;
	typedef enum
	{
		kOk = 0,
		kIsExisted,
		kNotExist,
		kNullTest
	} TestCode;
public:
	Testor();
	~Testor();

	TestCode RegisterTest(const std::string &test_name, const TestType &test);
	TestCode UnRegisterTest(const std::string &test_name);

	TestCode RunTests();
	TestCode RunTest(const std::string &test_name);
private:
	std::map<std::string, TestType> tests_;
};

