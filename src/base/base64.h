#pragma once

#include <string>

namespace base64
{
	typedef enum {
		kOk = 0,
		kNullInput,
		kNullOutput,
		kErrorCipherText
	}Base64Code;

	Base64Code Encode(const std::string &plain_text, std::string *cipher_text);

	Base64Code Encode(const char *plain_text, std::string *cipher_text);

	Base64Code Decode(const std::string &cipher_text, std::string *plain_text);

	Base64Code Decode(const char *cipher_text, std::string *plain_text);

	std::string Code2String(Base64Code code);

} // namespace base64