//Code mẫu tham khảo
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Structure to store symbol and its probability
struct Symbol {
    char c;
    double probability;
};

// Function to calculate cumulative probabilities
vector<double> calculate_cumulative_probabilities(const vector<Symbol>& symbols) {
    vector<double> cumulative_probabilities;
    double sum = 0;
    for (const auto& symbol : symbols) {
        sum += symbol.probability;
        cumulative_probabilities.push_back(sum);
    }
    return cumulative_probabilities;
}

// Arithmetic Encoding (returns a struct instead of a pair)
struct EncodedRange {
    double lower_bound;
    double upper_bound;
};

EncodedRange arithmetic_encode(const string& message, const vector<Symbol>& symbols) {
    vector<double> cumulative_probabilities = calculate_cumulative_probabilities(symbols);
    double lower_bound = 0.0;
    double upper_bound = 1.0;
    double range;

    for (char c : message) {
        range = upper_bound - lower_bound;
        for (size_t i = 0; i < symbols.size(); ++i) {
            if (symbols[i].c == c) {
                upper_bound = lower_bound + range * cumulative_probabilities[i];
                lower_bound = lower_bound + range * (i > 0 ? cumulative_probabilities[i - 1] : 0);
                break;
            }
        }
    }

    return {lower_bound, upper_bound}; // Return the struct
}


// Arithmetic Decoding 
string arithmetic_decode(double encoded_value, const vector<Symbol>& symbols, int message_length) {
    vector<double> cumulative_probabilities = calculate_cumulative_probabilities(symbols);
    string decoded_message = "";
    double lower_bound = 0.0;
    double upper_bound = 1.0;
    double range;

    for (int i = 0; i < message_length; ++i) {
        range = upper_bound - lower_bound;
        for (size_t j = 0; j < symbols.size(); ++j) {
            double upper_limit = lower_bound + range * cumulative_probabilities[j];
            double lower_limit = lower_bound + range * (j > 0 ? cumulative_probabilities[j - 1] : 0);

            if (encoded_value >= lower_limit && encoded_value < upper_limit) {
                decoded_message += symbols[j].c;
                upper_bound = upper_limit;
                lower_bound = lower_limit;
                break;
            }
        }
    }
    return decoded_message;
}


int main() {
    vector<Symbol> symbols = {{'A', 0.6}, {'B', 0.4}};
    string message = "AAABABABBBABAAAABBBB";


    EncodedRange encoded_range = arithmetic_encode(message, symbols);
    double encoded_value = (encoded_range.lower_bound + encoded_range.upper_bound) / 2.0;


    cout << "Encoded Range: [" << encoded_range.lower_bound << ", " << encoded_range.upper_bound << ")" << endl;
    cout << "Encoded Value: " << encoded_value << endl;


    string decoded_message = arithmetic_decode(encoded_value, symbols, message.length()); // Call decode correctly
    cout << "Decoded Message: " << decoded_message << endl;

    return 0;
}