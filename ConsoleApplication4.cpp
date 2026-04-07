#include <iostream>
#include <vector>

void stalinSort(std::vector<int>& camaradas) {
    if (camaradas.empty()) return;

    // Usamos um iterador para percorrer e remover elementos "traidores"
    // Começamos do segundo elemento (índice 1)
    int valor_referencia = camaradas[0];

    for (auto it = camaradas.begin() + 1; it != camaradas.end(); ) {
        if (*it >= valor_referencia) {
            // O elemento é leal ao regime (é maior ou igual)
            valor_referencia = *it;
            ++it;
        }
        else {
            // "Расстрелять!" (Executar/Remover)
            std::cout << "Elemento " << *it << " eliminado: Inimigo da ordem!\n";
            it = camaradas.erase(it); // remove e retorna o próximo iterador válido
        }
    }
}

void printVector(const std::vector<int>& v) {
    std::cout << "[ ";
    for (int x : v) std::cout << x << " ";
    std::cout << "]\n";
}

int main() {
    std::vector<int> povo = { 3, 1, 4, 1, 5, 9, 2 };

    std::cout << "Antes do expurgo: ";
    printVector(povo);

    stalinSort(povo);

    std::cout << "Depois do expurgo: ";
    printVector(povo); // Deve exibir [3, 4, 5, 9]

    return 0;
}