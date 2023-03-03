#include <bits/stdc++.h>

const int MAX_KEY_SIZE = 7;
const int NUMBER_OF_ALPHABETS = 27;
const int LOWER_CASE_CONVERTER_LOWER_LIMIT = 96;
const int LOWER_CASE_CONVERTER_UPPER_LIMIT = 123;

class Encryption_Decryption
{
private:
    std::vector<char> for_punctuations;
    int hasher[NUMBER_OF_ALPHABETS] = {0};
    char table[MAX_KEY_SIZE][MAX_KEY_SIZE];
    std::map<char, std::vector<int>> letter_positions;

public:
    bool Key_checker(std::string key)
    {
        int maker[NUMBER_OF_ALPHABETS] = {0};
        if (key.size() != MAX_KEY_SIZE)
        {
            return false;
        }
        for (int i = 0; i < key.size(); i++)
        {
            if (!(key[i] > LOWER_CASE_CONVERTER_LOWER_LIMIT && key[i] < LOWER_CASE_CONVERTER_UPPER_LIMIT))
            {
                return false;
            }
            maker[key[i] - LOWER_CASE_CONVERTER_LOWER_LIMIT]++;
        }
        for (int i = 0; i < NUMBER_OF_ALPHABETS; i++)
        {
            if (maker[i] > 1)
            {
                return false;
            }
        }
        return true;
    }
    std::string Plain_text_normalizer(std::string plain_text)
    {
        for (int i = 1; i < plain_text.size(); i++)
        {
            if (plain_text[i] == plain_text[i - 1])
            {
                plain_text.insert(i, 1, '@');
            }
        }
        if (plain_text.size() % 2)
        {
            plain_text.append("@");
        }
        return plain_text;
    }
    std::string Cipher_text_processor(std::string cipher)
    {
        for (int i = 0; i < cipher.size(); i++)
        {
            if (cipher[i] == '@')
            {
                cipher.erase(cipher.begin() + i);
            }
        }
        return cipher;
    }
    void Initialize_punctuations()
    {
        for_punctuations.push_back('1');
        for_punctuations.push_back('2');
        for_punctuations.push_back('3');
        for_punctuations.push_back('4');
        for_punctuations.push_back('5');
        for_punctuations.push_back('6');
        for_punctuations.push_back('7');
        for_punctuations.push_back('8');
        for_punctuations.push_back('9');
        for_punctuations.push_back('0');
        for_punctuations.push_back('.');
        for_punctuations.push_back('?');
        for_punctuations.push_back(' ');
        for_punctuations.push_back('!');
        for_punctuations.push_back('@');
        for_punctuations.push_back(',');
        for_punctuations.push_back('/');
        for_punctuations.push_back('(');
        for_punctuations.push_back(')');
        for_punctuations.push_back('%');
        for_punctuations.push_back('+');
        for_punctuations.push_back('-');
        for_punctuations.push_back('*');
    }
    void Initialize_hash_for_key(std::string key)
    {
        for (int i = 0; i < MAX_KEY_SIZE; i++)
        {
            hasher[key[i] - LOWER_CASE_CONVERTER_LOWER_LIMIT]++;
        }
        for (int i = 0; i < MAX_KEY_SIZE; i++)
        {
            table[0][i] = key[i];
        }
        int k = 1;
        int it = 0;
        for (int i = 1; i < MAX_KEY_SIZE; i++)
        {
            int j = 0;
            while (j < MAX_KEY_SIZE)
            {
                if (k >= NUMBER_OF_ALPHABETS)
                {
                    table[i][j] = for_punctuations[it];
                    j++;
                    it++;
                }
                else if (hasher[k] == 0)
                {
                    table[i][j] = k + LOWER_CASE_CONVERTER_LOWER_LIMIT;
                    j++;
                    k++;
                }
                else
                {
                    k++;
                }
            }
        }
    }
    void Initialize_map_for_all_alphabets()
    {
        for (int i = 0; i < MAX_KEY_SIZE; i++)
        {
            for (int j = 0; j < MAX_KEY_SIZE; j++)
            {
                std::vector<int> temp;
                temp.push_back(i);
                temp.push_back(j);
                letter_positions[table[i][j]] = temp;
            }
        }
    }
    std::string Encryption(std::string plain_text, std::string key)
    {
        Initialize_punctuations();
        Initialize_hash_for_key(key);
        Initialize_map_for_all_alphabets();
        plain_text = Plain_text_normalizer(plain_text);
        std::string cipher = "";
        int pointer_for_new_string = 0;
        for (int i = 1; i < plain_text.size(); i += 2)
        {
            std::vector<int> location1 = letter_positions[plain_text[i - 1]];
            std::vector<int> location2 = letter_positions[plain_text[i]];
            if (location1[0] == location2[0])
            {
                int temporary = (location1[1] + 1) % MAX_KEY_SIZE;
                char c = table[location1[0]][temporary];
                cipher.insert(pointer_for_new_string++, 1, c);
                temporary = (location2[1] + 1) % MAX_KEY_SIZE;
                c = table[location1[0]][temporary];
                cipher.insert(pointer_for_new_string++, 1, c);
            }
            else if (location1[1] == location2[1])
            {
                int temporary = (location1[0] + 1) % MAX_KEY_SIZE;
                char c = table[temporary][location1[1]];
                cipher.insert(pointer_for_new_string++, 1, c);
                temporary = (location2[0] + 1) % MAX_KEY_SIZE;
                c = table[temporary][location1[1]];
                cipher.insert(pointer_for_new_string++, 1, c);
            }
            else
            {
                char c = table[location1[0]][location2[1]];
                cipher.insert(pointer_for_new_string++, 1, c);
                c = table[location2[0]][location1[1]];
                cipher.insert(pointer_for_new_string++, 1, c);
            }
        }
        return cipher;
    }
    std::string Decryption(std::string cipher, std::string key)
    {
        Initialize_punctuations();
        Initialize_hash_for_key(key);
        Initialize_map_for_all_alphabets();
        std::string plain_text = "";
        int pointer_for_new_string = 0;
        for (int i = 1; i < cipher.size(); i += 2)
        {
            std::vector<int> location1 = letter_positions[cipher[i - 1]];
            std::vector<int> location2 = letter_positions[cipher[i]];
            if (location1[0] == location2[0])
            {
                int temporary = (((location1[1] - 1) % MAX_KEY_SIZE) + MAX_KEY_SIZE) % MAX_KEY_SIZE;
                char c = table[location1[0]][temporary];
                plain_text.insert(pointer_for_new_string++, 1, c);
                temporary = (((location2[1] - 1) % MAX_KEY_SIZE) + MAX_KEY_SIZE) % MAX_KEY_SIZE;
                c = table[location1[0]][temporary];
                plain_text.insert(pointer_for_new_string++, 1, c);
            }
            else if (location1[1] == location2[1])
            {
                int temporary = (((location1[0] - 1) % MAX_KEY_SIZE) + MAX_KEY_SIZE) % MAX_KEY_SIZE;
                char c = table[temporary][location1[1]];
                plain_text.insert(pointer_for_new_string++, 1, c);
                temporary = (((location2[0] - 1) % MAX_KEY_SIZE) + MAX_KEY_SIZE) % MAX_KEY_SIZE;
                c = table[temporary][location1[1]];
                plain_text.insert(pointer_for_new_string++, 1, c);
            }
            else
            {
                char c = table[location1[0]][location2[1]];
                plain_text.insert(pointer_for_new_string++, 1, c);
                c = table[location2[0]][location1[1]];
                plain_text.insert(pointer_for_new_string++, 1, c);
            }
        }
        plain_text = Cipher_text_processor(plain_text);
        return plain_text;
    }
};

int main()
{
    std::string PlainText;
    std::string Key;

    Encryption_Decryption obj;
    std::string ans;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

    std::cout << "Hello, welcome to Tushar's Encryption Decryption Cave.\nWhat would you like to do today?\n\n";

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

    std::cout << "Enter 1 for Encryption and 2 for Decryption: ";
    int choice;
    std::cin >> choice;
    std::cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

    if (choice != 1 && choice != 2)
    {
        std::cout << "Oh no!!! it seems like you entered wrong option. Please try again. (*_*)\n";
        std::cout << "Enter any integer to exit\n";

        int random;
        std::cin >> random;
        return 0;
    }

    if (choice == 1)
    {
        std::cout << "Enter the a 7 letter key to be used (all the letter must be unique): ";
        std::cin >> Key;
        std::cin.ignore();

        if (!(obj.Key_checker(Key)))
        {
            std::cout << "Oh no!!! it seems like you entered an invalid key. Please try again. (*_*)\n";
            std::cout << "Enter any integer to exit\n";

            int random;
            std::cin >> random;
            return 0;
        }

        std::cout << "Enter the text to be encrypted: ";
        std::getline(std::cin, PlainText, '\n');

        std::transform(Key.begin(), Key.end(), Key.begin(), ::tolower);
        std::transform(PlainText.begin(), PlainText.end(), PlainText.begin(), ::tolower);

        ans = obj.Encryption(PlainText, Key);
    }

    else
    {
        std::cout << "Enter the a 7 letter key to be used (all the letter must be unique): ";
        std::cin >> Key;
        std::cin.ignore();

        if (!(obj.Key_checker(Key)))
        {
            std::cout << "Oh no!!! it seems like you entered an invalid key. Please try again. (*_*)\n";
            std::cout << "Enter any integer to exit\n";

            int random;
            std::cin >> random;
            return 0;
        }

        std::cout << "Enter the text to be decrypted: ";
        std::getline(std::cin, PlainText, '\n');

        std::transform(Key.begin(), Key.end(), Key.begin(), ::tolower);
        std::transform(PlainText.begin(), PlainText.end(), PlainText.begin(), ::tolower);

        ans = obj.Decryption(PlainText, Key);
    }

    std::cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

    std::cout << "Your resultant text is: " << ans << std::endl;

    std::cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "Enter any integer to exit\n";

    int random;
    std::cin >> random;
    return 0;
}
