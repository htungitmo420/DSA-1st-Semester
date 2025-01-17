//Code mẫu tham khảo
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string rle_encode(const string& input) {
    string encoded_string = "";
    if (input.empty()) {
        return encoded_string;
    }

    char current_char = input[0];
    int count = 1;

    for (size_t i = 1; i < input.length(); ++i) {
        if (input[i] == current_char) {
            count++;
        } else {
            encoded_string += to_string(count) + current_char;
            current_char = input[i];
            count = 1;
        }
    }
    encoded_string += to_string(count) + current_char;

    return encoded_string;
}

string rle_decode(const string& input) {
    string decoded_string = "";
    string count_str = "";

    for (char c : input) {
        if (isdigit(c)) {
            count_str += c;
        } else {
            int count = stoi(count_str); 
            for (int i = 0; i < count; ++i) {
                decoded_string += c;
            }
            count_str = "";
        }
    }
    return decoded_string;

}

int main() {
    string input_string = "AAABBBCCCDDDE";
    string encoded_string = rle_encode(input_string);
    string decoded_string = rle_decode(encoded_string);

    cout << "Original string: " << input_string << endl;
    cout << "Encoded string: " << encoded_string << endl;
    cout << "Decoded string: " << decoded_string << endl;



    string input_string2 = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
    string encoded_string2 = rle_encode(input_string2);
    string decoded_string2 = rle_decode(encoded_string2);

    cout << "\nOriginal string: " << input_string2 << endl;
    cout << "Encoded string: " << encoded_string2 << endl;
    cout << "Decoded string: " << decoded_string2 << endl;

        string empty_string = "";
    string encoded_empty_string = rle_encode(empty_string);
    string decoded_empty_string = rle_decode(encoded_empty_string);

    cout << "\nOriginal string: " << empty_string << endl;
    cout << "Encoded string: " << encoded_empty_string << endl;
    cout << "Decoded string: " << decoded_empty_string << endl;


    return 0;
}