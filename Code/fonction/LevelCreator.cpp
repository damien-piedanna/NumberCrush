void LevelCreator() {
    cout << "Choisissez un nom pour votre niveau (max 20 caracteres et ne pas utiliser deux fois le meme nom)" << endl;
    string NomLevel;
    while(true) {
        cin << NomLevel;
        if(cin.fail() || NomLevel.size() > 20) {
            ClearBuf();
            cout << "Saisissez un maximum de 20 caracteres !!!" << endl;
            continue;
        }
        for(unsigned i=0; i < NomLevel.size(); ++i) {
            if(NomLevel[i]='/') {
                cout << "Les les / sont interdits dans les noms de fichier sous linux" << endl;
                continue;
            }
        }
        break;
    }
    cout << "Entrez la taille de la grille" << endl;
    unsigned GridSize;
    while(true) {
        cin << GridSize;
        if(cin.fail() || GridSize >= 200) {
            ClearBuf();
            cout << "Entrez un nombre positif strictement inferieur a 200 (faut pas abuser quand meme)" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez le nombre de valeurs que les cases de la grille peuvent adopter" << endl;
    unsigned NbKandies;
    while(true) {
        cin << NbKandies;
        if(cin.fail() || NbKandies > 8) {
            ClearBuf();
            cout << "Entrez un nombre positif strictement inferieur à 9 car le terminal ne nous donne acces qu'a 8 couleurs !" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez le nombre de coups possibles" << endl;
    unsigned Coups;
    while(true) {
        cin << Coups;
        if(cin.fail()) {
            ClearBuf();
            cout << "Entrez un nombre positif !" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez les " << GridSize << " lignes de " << GridSize << " chiffres avec un 0 pour les cases ordinaires et un 1 pour les murs (ils peuvent tomber)" << endl;
    ofstream ofs(NomLevel);
    for(unsigned i=0; i < GridSize; ++i) {
        
        cin << 
    }
}
