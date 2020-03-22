#include <string>
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>

std::vector<char> generate_key(){
    // contains every sign wanted in text
    std::vector<char> signs = {'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                             'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                             '1','2','3','4','5','6','7','8','9','0',' ','!','?','.', ','};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(signs.begin(), signs.end(), g);

    return signs;
}

std::string encrypt(std::string& message, std::vector<char>& key){
    static int depth_of_recursion = 0;
    static std::string encrypted_string;

    if(message.size() > depth_of_recursion) {
        encrypted_string +=  *(std::find(std::begin(key), std::end(key),
                (char)(message[depth_of_recursion])) + 1 % std::size(key));
        depth_of_recursion++;
        return encrypt(message, key);
    }
    else{
        return encrypted_string;
    }

}

std::string decrypt(std::string& message, std::vector<char>& key){
    static int depth_of_recursion = 0;
    static std::string decrypted_string;

    if(message.size() > depth_of_recursion) {
        decrypted_string += *(std::find(std::begin(key), std::end(key),
                    (char)(message[depth_of_recursion])) - 1);
        depth_of_recursion++;
        return decrypt(message, key);
    }
    else{
        return decrypted_string;
    }
}

int main() {

    std::string message = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,!?.";

    auto key = generate_key();
    auto cypher = encrypt(message, key);
    auto result = decrypt(cypher, key);

    std::cout << "Message: " << message << '\n';
    std::cout << "Cypher:  " << cypher << '\n';
    std::cout << "Result:  " << result << '\n';

    assert(message == result);
    return 0;
}