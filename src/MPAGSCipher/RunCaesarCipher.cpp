#include "RunCaesarCipher.hpp"

std::string transform_char(const char in_char);

std::string runCaesarCipher(const std::string& inputText, size_t key, const bool encrypt)
{
    // Create the alphabet container and output string
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::string outputText{""};
    std::string transformed_str{""};

    // Transform the input text: convert all letters to capitals and replace numbers with letters
    for (int i = 0; i < int(inputText.length()); i++)
    {   
        char character{inputText[i]};
        transformed_str += transform_char(character);
    }

    for (int i = 0; i < int(transformed_str.length()); i++)
    {   
        // Loop over the transformed string
        char character{transformed_str[i]};
        int index{-1};

        // For each character find the corresponding position in the alphabet
        index = alphabet.find(character);
        
        // For each character find the corresponding position in the alphabet
        int new_index{-1};
        
        // Apply the shift (depending on encrypt/decrypt value)
        if (encrypt) {
            new_index = index + key;
            // Handling wrap-around for encryption
            if (new_index > int(alphabet.length()-1)) {
                new_index = new_index % alphabet.length();
            }
        }
        else if (!encrypt) {
            new_index = index - key;
            // Handling wrap-around for decryption
            if (new_index < 0) {
                new_index = alphabet.length() + new_index;
            }
        }
        
        // Determine the new character and add it to the output string
        char corr_char{' '};
        corr_char = alphabet[new_index];
        outputText += corr_char;

        // std::cout << character << " " << index << "          " << corr_char << " " <<  new_index << std::endl;  // line for testing characters
    }

    // Return the output string
    return outputText;
}













std::string transform_char( const char in_char )
{
    std::string inputText{""};

    // Uppercase alphabetic characters
    if (std::isalpha(in_char)) {
        inputText += std::toupper(in_char);
    }

    // Transliterate digits to English words
    switch (in_char) {
        case '0':
            inputText += "ZERO";
            break;
        case '1':
            inputText += "ONE";
            break;
        case '2':
            inputText += "TWO";
            break;
        case '3':
            inputText += "THREE";
            break;
        case '4':
            inputText += "FOUR";
            break;
        case '5':
            inputText += "FIVE";
            break;
        case '6':
            inputText += "SIX";
            break;
        case '7':
            inputText += "SEVEN";
            break;
        case '8':
            inputText += "EIGHT";
            break;
        case '9':
            inputText += "NINE";
            break;
    }
    // If the character isn't alphabetic or numeric, DONT add it
    return inputText;

}