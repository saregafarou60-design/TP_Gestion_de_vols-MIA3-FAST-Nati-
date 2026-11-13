#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// ==========================================
// 1. Classe Passager
// ==========================================
class Passager {
private:
    string idPassager;
    string nom;
    string prenom;
    string email;
    string telephone;

public:
    Passager(string id, string n, string p, string mail, string tel)
        : idPassager(id), nom(n), prenom(p), email(mail), telephone(tel) {}

    string getIdPassager() const { return idPassager; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }

    void afficher() const {
        cout << "Passager [" << idPassager << "] : " << prenom << " " << nom 
             << " | Email: " << email << " | Tel: " << telephone << endl;
    }
};

// ==========================================
// 2. Classe Vol
// ==========================================
class Vol {
private:
    string numeroVol;
    string destination;
    string dateDepart;
    int capacite;
    int placesReservees;
    double prix;

public:
    Vol(string num, string dest, string date, int cap, double p)
        : numeroVol(num), destination(dest), dateDepart(date), capacite(cap), placesReservees(0), prix(p) {}

    string getNumeroVol() const { return numeroVol; }
    string getDestination() const { return destination; }
    int getCapacite() const { return capacite; }
    int getPlacesReservees() const { return placesReservees; }
    double getPrix() const { return prix; }

    bool estComplet() const {
        return placesReservees >= capacite;
    }

    bool ajouterReservationPlace() {
        if (!estComplet()) {
            placesReservees++;
            return true;
        }
        return false;
    }

    void libererPlace() {
        if (placesReservees > 0) {
            placesReservees--;
        }
    }

    void afficher() const {
        cout << "Vol " << numeroVol << " vers " << destination 
             << " | Date: " << dateDepart 
             << " | Prix: " << prix << " €"
             << " | Places dispo: " << (capacite - placesReservees) << "/" << capacite << endl;
    }
};

// ==========================================
// 3. Classe Paiement
// ==========================================
class Paiement {
private:
    string idPaiement;
    double montant;
    string modePaiement; // Carte, Mobile Money, Especes
    bool paye;

public:
    Paiement(string id, double m, string mode)
        : idPaiement(id), montant(m), modePaiement(mode), paye(true) {}

    bool estPaye() const { return paye; }
    double getMontant() const { return montant; }

    void rembourser() {
        paye = false;
        cout << "Remboursement de " << montant << " € effectué via " << modePaiement << "." << endl;
    }

    void afficher() const {
        cout << "Paiement [" << idPaiement << "] - Montant: " << montant << " € - Mode: " << modePaiement << (paye ? " (Validé)" : " (Remboursé)") << endl;
    }
};

// ==========================================
// 4. Classe Reservation
// ==========================================
class Reservation {
private:
    string idReservation;
    string dateReservation;
    string statut; // "Confirmée", "Annulée"
    Passager* passager;
    Vol* vol;
    Paiement* paiement;

public:
    Reservation(string id, string date, Passager* p, Vol* v, Paiement* pai)
        : idReservation(id), dateReservation(date), statut("Confirmée"), passager(p), vol(v), paiement(pai) {}

    string getIdReservation() const { return idReservation; }
    string getStatut() const { return statut; }
    Passager* getPassager() const { return passager; }
    Vol* getVol() const { return vol; }

    void annulerReservation() {
        if (statut == "Confirmée") {
            statut = "Annulée";
            vol->libererPlace();
            if (paiement != nullptr) {
                paiement->rembourser();
            }
            cout << "Réservation " << idReservation << " annulée avec succès." << endl;
        } else {
            cout << "Erreur : La réservation est déjà annulée." << endl;
        }
    }

    void afficher() const {
        cout << "Réservation [" << idReservation << "] | Date: " << dateReservation 
             << " | Statut: " << statut << endl;
        cout << "  -> "; passager->afficher();
        cout << "  -> "; vol->afficher();
        if (paiement != nullptr) {
            cout << "  -> "; paiement->afficher();
        }
        cout << "--------------------------------------------------------" << endl;
    }
};

// ==========================================
// 5. Classe Gestionnaire / Agence (Application)
// ==========================================
class AgenceVoyage {
private:
    vector<Passager> passagers;
    vector<Vol> vols;
    vector<Reservation> reservations;
    vector<Paiement> paiements;

public:
    void enregistrerPassager() {
        string id, nom, prenom, email, tel;
        cout << "\n--- Enregistrement d'un Passager ---" << endl;
        cout << "ID Passager : "; cin >> id;
        
        // Vérification d'unicité
        for (const auto& p : passagers) {
            if (p.getIdPassager() == id) {
                cout << "Erreur : Cet ID existe déjà !" << endl;
                return;
            }
        }

        cout << "Nom : "; cin >> nom;
        cout << "Prénom : "; cin >> prenom;
        cout << "Email : "; cin >> email;
        cout << "Téléphone : "; cin >> tel;

        passagers.push_back(Passager(id, nom, prenom, email, tel));
        cout << "Succès : Passager enregistré !" << endl;
    }

    void ajouterVol() {
        string num, dest, date;
        int cap;
        double prix;
        cout << "\n--- Ajout d'un Vol ---" << endl;
        cout << "Numéro de vol : "; cin >> num;
        
        for (const auto& v : vols) {
            if (v.getNumeroVol() == num) {
                cout << "Erreur : Ce numéro de vol existe déjà !" << endl;
                return;
            }
        }

        cout << "Destination : "; cin >> dest;
        cout << "Date de départ (JJ/MM/AAAA) : "; cin >> date;
        cout << "Capacité maximale : "; cin >> cap;
        cout << "Prix du billet (€) : "; cin >> prix;

        vols.push_back(Vol(num, dest, date, cap, prix));
        cout << "Succès : Vol ajouté !" << endl;
    }

    void afficherVolsDisponibles() const {
        cout << "\n--- Vols Disponibles ---" << endl;
        if (vols.empty()) {
            cout << "Aucun vol enregistré." << endl;
            return;
        }
        for (const auto& v : vols) {
            if (!v.estComplet()) {
                v.afficher();
            }
        }
    }

    void rechercherVol() const {
        string dest;
        cout << "\n--- Recherche de Vol ---" << endl;
        cout << "Entrez la destination recherchée : "; cin >> dest;
        bool trouve = false;
        for (const auto& v : vols) {
            if (v.getDestination() == dest) {
                v.afficher();
                trouve = true;
            }
        }
        if (!trouve) {
            cout << "Aucun vol trouvé pour cette destination." << endl;
        }
    }

    void effectuerReservation() {
        string idRes, idPass, numVol;
        cout << "\n--- Effectuer une Réservation ---" << endl;
        if (passagers.empty() || vols.empty()) {
            cout << "Erreur : Il faut au moins un passager et un vol enregistrés." << endl;
            return;
        }

        cout << "ID de la réservation : "; cin >> idRes;
        cout << "ID du passager : "; cin >> idPass;
        cout << "Numéro du vol : "; cin >> numVol;

        Passager* passagerTrouve = nullptr;
        for (auto& p : passagers) {
            if (p.getIdPassager() == idPass) {
                passagerTrouve = &p;
                break;
            }
        }

        Vol* volTrouve = nullptr;
        for (auto& v : vols) {
            if (v.getNumeroVol() == numVol) {
                volTrouve = &v;
                break;
            }
        }

        if (passagerTrouve == nullptr) {
            cout << "Erreur : Passager introuvable." << endl;
            return;
        }
        if (volTrouve == nullptr) {
            cout << "Erreur : Vol introuvable." << endl;
            return;
        }

        // Vérification doublon de réservation pour le même passager et vol
        for (const auto& r : reservations) {
            if (r.getPassager()->getIdPassager() == idPass && r.getVol()->getNumeroVol() == numVol && r.getStatut() == "Confirmée") {
                cout << "Erreur : Ce passager a déjà une réservation active pour ce vol !" << endl;
                return;
            }
        }

        if (volTrouve->estComplet()) {
            cout << "Erreur : Désolé, ce vol est complet !" << endl;
            return;
        }

        // Processus de paiement automatique intégré
        double montant = volTrouve->getPrix();
        string mode;
        cout << "Montant à payer : " << montant << " €. Entrez le mode de paiement (Carte/MobileMoney/Espèces) : "; 
        cin >> mode;

        string idPaiement = "PAI_" + idRes;
        paiements.push_back(Paiement(idPaiement, montant, mode));
        Paiement* dernierPaiement = &paiements.back();

        volTrouve->ajouterReservationPlace();
        reservations.push_back(Reservation(idRes, "13/11/2026", passagerTrouve, volTrouve, dernierPaiement));
        cout << "Succès : Réservation et paiement validés avec succès !" << endl;
    }

    void annulerReservation() {
        string idRes;
        cout << "\n--- Annuler une Réservation ---" << endl;
        cout << "Entrez l'ID de la réservation à annuler : "; cin >> idRes;

        bool trouve = false;
        for (auto& r : reservations) {
            if (r.getIdReservation() == idRes) {
                r.annulerReservation();
                trouve = true;
                break;
            }
        }
        if (!trouve) {
            cout << "Erreur : Réservation introuvable." << endl;
        }
    }

    void consulterReservations() const {
        cout << "\n--- Liste de toutes les Réservations ---" << endl;
        if (reservations.empty()) {
            cout << "Aucune réservation enregistrée." << endl;
            return;
        }
        for (const auto& r : reservations) {
            r.afficher();
        }
    }

    void afficherInfosReservationSpecifique() const {
        string idRes;
        cout << "\n--- Afficher les détails d'une réservation ---" << endl;
        cout << "Entrez l'ID de la réservation : "; cin >> idRes;
        bool trouve = false;
        for (const auto& r : reservations) {
            if (r.getIdReservation() == idRes) {
                r.afficher();
                trouve = true;
                break;
            }
        }
        if (!trouve) {
            cout << "Erreur : Réservation introuvable." << endl;
        }
    }

    void lancerMenu() {
        int choix;
        do {
            cout << "\n==============================================" << endl;
            cout << "     AGENCE DE VOYAGE COTONOU - GESTION       " << endl;
            cout << "==============================================" << endl;
            cout << "1. Enregistrer un passager" << endl;
            cout << "2. Ajouter un vol" << endl;
            cout << "3. Afficher les vols disponibles" << endl;
            cout << "4. Rechercher un vol" << endl;
            cout << "5. Effectuer une réservation" << endl;
            cout << "6. Annuler une réservation" << endl;
            cout << "7. Consulter les réservations" << endl;
            cout << "8. Afficher les informations d'une réservation" << endl;
            cout << "9. Quitter" << endl;
            cout << "Votre choix : ";
            
            if (!(cin >> choix)) {
                cout << "Erreur de saisie. Veuillez entrer un nombre valide." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            switch (choix) {
                case 1: enregistrerPassager(); break;
                case 2: ajouterVol(); break;
                case 3: afficherVolsDisponibles(); break;
                case 4: rechercherVol(); break;
                case 5: effectuerReservation(); break;
                case 6: annulerReservation(); break;
                case 7: consulterReservations(); break;
                case 8: afficherInfosReservationSpecifique(); break;
                case 9: cout << "Au revoir !" << endl; break;
                default: cout << "Choix invalide. Réessayez." << endl;
            }
        } while (choix != 9);
    }
};

// ==========================================
// 6. Fonction Principale (main)
// ==========================================
int main() {
    AgenceVoyage agence;
    
    // Données de test pré-enregistrées pour faciliter la démonstration
    // (Optionnel mais pratique)
    
    agence.lancerMenu();

    return 0;
}
