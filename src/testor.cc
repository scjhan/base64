#include "testor.h"



Testor::Testor()
{
}


Testor::~Testor()
{
}

Testor::TestCode Testor::RegisterTest(const std::string & test_name, const TestType & test)
{
	if (test == nullptr) return kNullTest;
	if (tests_.find(test_name) != tests_.end()) return kIsExisted;

	tests_.insert(std::make_pair(test_name, test));

	return kOk;
}

Testor::TestCode Testor::UnRegisterTest(const std::string & test_name)
{
	if (tests_.find(test_name) == tests_.end()) return kNotExist;

	tests_.erase(test_name);

	return kOk;
}

Testor::TestCode Testor::RunTests()
{
	for (auto test : tests_) {
		test.second();
	}

	return kOk;
}

Testor::TestCode Testor::RunTest(const std::string & test_name)
{
	auto test = tests_.find(test_name);

	if (test == tests_.end()) return kNotExist;

	test->second();

	return kOk;
}
