#include <vector>
#include <iostream>

#include "testor.h"
#include "base/base64.h"

Testor::TestType CreateBase64EncodeTest() {
	std::vector<std::string> encode_text {
		"Hello World",
		"ChenJunhan",
		"Netease"
	};

	Testor::TestType test([=]() {
		for (auto text : encode_text) {
			std::cout << "base64::Encode(" << text << ") : ";
			std::string cipher;
			base64::Base64Code code= base64::Encode(text, &cipher);
			if (code == base64::kOk)
				std::cout << cipher << std::endl;
			else
				std::cout << "base64::Encode error, code = " << base64::Code2String(code) << std::endl;
		}
	});

	return test;
}

Testor::TestType CreateBase64DecodeTest() {
	std::vector<std::string> decode_text{
		"SGVsbG8gV29ybGQ=",
		"Q2hlbkp1bmhhbg==",
		"TmV0ZWFzZQ=="
	};

	Testor::TestType test([=]() {
		for (auto text : decode_text) {
			std::cout << "base64::dncode(" << text << ") : ";
			std::string plain;
			base64::Base64Code code = base64::Decode(text, &plain);
			if (code == base64::kOk)
				std::cout << plain << std::endl;
			else
				std::cout << "base64::Base64Code error, code = " << base64::Code2String(code) << std::endl;
		}
	});

	return test;
}

int main()
{
	Testor testor;

	testor.RegisterTest("Base64EncodeTest", CreateBase64EncodeTest());
	testor.RegisterTest("Base64DecodeTest", CreateBase64DecodeTest());

	testor.RunTests();

	return 0;
}
