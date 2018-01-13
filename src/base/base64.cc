#include "base64.h"

namespace base64
{
	static const std::string kBase64EncodeHash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	static const int8_t kBase64DecodeHash[128]{
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
		-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
		-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	};

	Base64Code Encode(const std::string & plain_text, std::string * cipher_text)
	{
		if (cipher_text == nullptr) return kNullOutput;

		std::string cipher;
		int8_t ascii(0), prev_ascii(0), mod(0);
		for (size_t i = 0; i < plain_text.length(); ++i) {
			ascii = plain_text[i];
			mod = i % 3;

			switch (mod)
			{
			case 0:
				cipher.push_back(kBase64EncodeHash[ascii >> 2]);
				break;
			case 1:
				cipher.push_back(kBase64EncodeHash[(prev_ascii & 0x03) << 4 | ascii >> 4]);
				break;
			case 2:
				cipher.push_back(kBase64EncodeHash[(prev_ascii & 0x0f) << 2 | ascii >> 6]);
			 	cipher.push_back(kBase64EncodeHash[ascii & 0x3f]);
				break;
			}

			prev_ascii = ascii;
		}

		if (mod == 0) {
			cipher.push_back(kBase64EncodeHash[(prev_ascii & 0x03) << 4]);
			cipher.push_back('=');
			cipher.push_back('=');
		}
		else if (mod == 1) {
			cipher.push_back(kBase64EncodeHash[(prev_ascii & 0x0f) << 2]);
			cipher.push_back('=');
		}

		cipher_text->swap(cipher);

		return kOk;
	}

	Base64Code Encode(const char * plain_text, std::string * cipher_text)
	{
		if (plain_text == nullptr) return kNullInput;
		if (cipher_text == nullptr) return kNullOutput;

		return Encode(std::string(plain_text), cipher_text);
	}

	Base64Code Decode(const std::string & cipher_text, std::string * plain_text)
	{
		if (plain_text == nullptr) return kNullOutput;
		if (cipher_text.length() % 4 != 0) return kErrorCipherText;

		std::string plain;
		int8_t value(0), prev_value(0), mod(0);
		for (size_t i = 0; i < cipher_text.length(); ++i) {
			value = kBase64DecodeHash[cipher_text[i]];

			if (value == -1) continue;

			mod = i % 4;

			switch (mod)
			{
			case 0:
				break;
			case 1:
				plain.push_back(prev_value << 2 | value >> 4);
				break;
			case 2:
				plain.push_back((prev_value & 0x0f) << 4 | value >> 2);
				break;
			case 3:
				plain.push_back((prev_value & 0x03) << 6 | value);
				break;
			}

			prev_value = value;
		}

		plain_text->swap(plain);

		return kOk;
	}

	Base64Code Decode(const char * cipher_text, std::string * plain_text)
	{
		if (cipher_text == nullptr) return kNullInput;
		if (plain_text == nullptr) return kNullOutput;

		return Decode(std::string(cipher_text), plain_text);
	}

	std::string Code2String(Base64Code code)
	{
		std::string str;

		switch (code)
		{
		case kOk:
			str = "Success";
			break;
		case kNullInput:
			str = "Input source is null address";
			break;
		case kNullOutput:
			str = "Ouput destination is null address";
			break;
		case kErrorCipherText:
			str = "Invalid base64 cipher text";
			break;
		}

		return str;
	}

} // namespace base64