#include <iostream>
#include <vector>
#include <string>

int calcularSomaMagica(const std::vector<int>& numeros) {
    int soma_final = 0;

    for (int n : numeros) {
        
        if (n % 2 != 0) {
            
            std::string str_n = std::to_string(std::abs(n));
            if (str_n.find('3') != std::string::npos) {
                soma_final += n;
            }
        }
    }

    return soma_final;
}

int main() {
    std::vector<int> teste = { 11, 12, 5, 7, 3, 12 };
    std::cout << "Resultado: " << calcularSomaMagica(teste) << std::endl; // Saída: 16
    return 0;
}