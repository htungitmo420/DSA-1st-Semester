#include <iostream>

struct chem_element {
    char symbol;
    int number;
    chem_element* next;
    chem_element(char s, int n) : symbol(s), number(n), next(nullptr) {}
};

struct StackNode {
    chem_element* elementlist;
    StackNode* next;
    StackNode(chem_element* el) : elementlist(el), next(nullptr) {}
};

void push(StackNode*& top, chem_element* elementlist) {
    StackNode* newNode = new StackNode(elementlist);
    newNode->next = top;
    top = newNode;
}

chem_element* pop(StackNode*& top) {
    if (top == nullptr) return nullptr;
    StackNode* temp = top;
    chem_element* elementlist = top->elementlist;
    top = top->next;
    delete temp;
    return elementlist;
}

void insert_element(chem_element*& head, char symbol, int number) {
    chem_element* curr = head;
    chem_element* prev = nullptr;
    while (curr != nullptr && curr->symbol < symbol) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr && curr->symbol == symbol) {
        curr->number += number;
    } else {
        chem_element* newElement = new chem_element(symbol, number);
        if (prev == nullptr) {
            newElement->next = head;
            head = newElement;
        } else {
            prev->next = newElement;
            newElement->next = curr;
        }
    }
}

void multiply(chem_element*& head, int multiplier) {
    chem_element* curr = head;
    while (curr != nullptr) {
        curr->number *= multiplier;
        curr = curr->next;
    }
}

bool is_letter(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

chem_element *expand_formula(const std::string& formula, int& index) {
    chem_element* elementlist = nullptr;
    StackNode* stack = nullptr;
    
    while (index < formula.length()) {
        if (is_letter(formula[index])) {
            char symbol = formula[index];
            int number = 1;
            index++;
            if (index < formula.length() && is_number(formula[index])) {
                number = 0;
                while (index < formula.length() && is_number(formula[index])) {
                    number = number * 10 + formula[index] - '0';
                    index++;
                }
            }
            insert_element(elementlist, symbol, number);
        } else if (formula[index] == '(') {
            push(stack, elementlist);
            elementlist = nullptr;
            index++;
        } else if (formula[index] == ')') {
            index++;
            int number = 1;
            if (index < formula.length() && is_number(formula[index])) {
                number = 0;
                while (index < formula.length() && is_number(formula[index])) {
                    number = number * 10 + formula[index] - '0';
                    index++;
                }
            }
            multiply(elementlist, number);
            chem_element* sublist = elementlist;
            elementlist = pop(stack);
            chem_element* curr = sublist;
            while (curr != nullptr) {
                insert_element(elementlist, curr->symbol, curr->number);
                curr = curr->next;
            }
        }
    }
    return elementlist;
}

void print_formula(chem_element* head) {
    chem_element* curr = head;
    while (curr != nullptr) {
        std::cout << curr->symbol;
        if (curr->number > 1) {
            std::cout << curr->number;
        }
        curr = curr->next;
    }
}

void free_elements(chem_element* head) {
    while (head != nullptr) {
        chem_element* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    std::string formula;
    std::cin >> formula;
    int index = 0;
    chem_element* elementlist = expand_formula(formula, index);
    print_formula(elementlist);
    free_elements(elementlist);
    return 0;
}