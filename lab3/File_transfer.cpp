#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

class AESCipher {
public:
    AESCipher(const std::string& key) : m_key(key) {}

    std::pair<std::string, std::string> encrypt(const std::string& plaintext) {
        AutoSeededRandomPool prng;
        byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));

        CBC_Mode<AES>::Encryption encryptor((byte*)m_key.data(), m_key.size(), iv);
        
        std::string ciphertext;
        StringSource(plaintext, true, new StreamTransformationFilter(encryptor, new StringSink(ciphertext)));

        return std::make_pair(std::string((const char*)iv, AES::BLOCKSIZE), ciphertext);
    }

    std::string decrypt(const std::string& iv_str, const std::string& ciphertext_str) {
        byte iv[AES::BLOCKSIZE];
        std::memcpy(iv, iv_str.data(), AES::BLOCKSIZE);

        CBC_Mode<AES>::Decryption decryptor((byte*)m_key.data(), m_key.size(), iv);

        std::string decrypted;
        StringSource(ciphertext_str, true, new StreamTransformationFilter(decryptor, new StringSink(decrypted)));

        return decrypted;
    }

private:
    std::string m_key;
};

int main() {
    std::string plaintext, password;
    std::cout << "Enter plaintext: ";
    std::getline(std::cin, plaintext);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    AESCipher cipher(password);
    auto [iv, ciphertext] = cipher.encrypt(plaintext);
    std::string decrypted_plaintext = cipher.decrypt(iv, ciphertext);

    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted plaintext: " << decrypted_plaintext << std::endl;

    return 0;
}
