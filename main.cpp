#include "OrderedHashTable.h"
#include <iostream>
#include <string>

int main() {
    OrderedHashTable<std::string, double, 10> commandes;

    // Ajout des commandes
    commandes.insert("CMD001", 25.50);
    commandes.insert("CMD002", 13.99);
    commandes.insert("CMD003", 42.10);
    commandes.insert("CMD004", 7.30);
    commandes.insert("CMD005", 19.99);
    commandes.insert("CMD0016", 5.75);

    std::cout << "Liste des commandes dans l'ordre d'arrivee :" << std::endl;
    commandes.printInOrder();

    std::cout << "\nContenu de la table de hachage :" << std::endl;
    commandes.print();

    // Annulation de la commande CMD002
    std::cout << "\nAnnulation de la commande CMD002..." << std::endl;
    commandes.remove("CMD002");

    // Recherche d'une commande
    double montant = 0;
    if (commandes.search("CMD003", montant)) {
        std::cout << "Montant de la commande CMD003 : " << montant << " EUR" << std::endl;
    }

    std::cout << "\nListe des commandes apres annulation :" << std::endl;
    commandes.printInOrder();

    std::cout << "\nContenu de la table de hachage :" << std::endl;
    commandes.print();

    return 0;
}
