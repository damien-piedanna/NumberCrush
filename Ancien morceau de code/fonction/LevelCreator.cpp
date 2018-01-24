bool TestValeurDansString(string & Str, unsigned & GridSize)
{
    if(Str.size() != GridSize) return false;
    for(unsigned i=0;i < Str.size(); ++i)
    {
        if(Str[i] != '0' && Str[i] != '1')
        {
                return false;
        }
    }
    return true;
}// TestValeurDansString ()

void LevelCreator() {
    cout << "Choisissez un nom pour votre niveau (max 20 caracteres et ne pas utiliser deux fois le meme nom ou ne rien saisir)" << endl;
    string NomLevel; // rajouter le test d'existence du fichier
    while(true) {
        bool NoSlash=true;
        NomLevel="reset";
        getline(cin,NomLevel);
        if(NomLevel.size() > 20 || NomLevel.size() == 0) {
            cout << "Respectez les consignes !!!" << endl;
            continue;
        }
        for(unsigned i=0; i < NomLevel.size(); ++i) {
            if(NomLevel[i]=='/') {
                cout << "Les / sont interdits dans les noms de fichier sous linux" << endl;
                NoSlash=false;
                break;
            }
        }
        if(NoSlash)break;
    }
    cout << "Entrez la taille de la grille" << endl;
    unsigned GridSize;
    while(true) {
        cin >> GridSize;
        if(cin.fail() || GridSize >= 20) {
            ClearBuf();
            cout << "Entrez un nombre positif strictement inferieur a 20 (faut pas abuser quand meme)" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez le score a atteindre pour reussir le niveau" << endl;
    unsigned ScoreToWin;
    while(true) {
        cin >> ScoreToWin;
        if(cin.fail()) {
            ClearBuf();
            cout << "Entrez un nombre positif" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez le nombre de valeurs que les cases de la grille peuvent adopter" << endl;
    unsigned NbKandies;
    while(true) {
        cin >> NbKandies;
        if(cin.fail() || NbKandies > 7) {
            ClearBuf();
            cout << "Entrez un nombre positif strictement inferieur à 8 car le terminal ne nous donne acces qu'a 8 couleurs et y'a des murs ! ;{" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez le nombre de coups possibles" << endl;
    unsigned Coups;
    while(true) {
        cin >> Coups;
        if(cin.fail()) {
            ClearBuf();
            cout << "Entrez un nombre positif !" << endl;
            continue;
        }
        break;
    }
    cout << "Entrez les " << GridSize << " lignes de " << GridSize << " chiffres avec un 0 pour les cases ordinaires et" << endl << "un 1 pour les murs (ils peuvent tomber)" << endl;
    vector <string> StockDeVar;
    StockDeVar.resize(GridSize+4);
    StockDeVar[0]=to_string(GridSize);
    StockDeVar[1]=to_string(NbKandies);
    StockDeVar[2]=to_string(Coups);
    StockDeVar[3]=to_string(ScoreToWin);
    //ofs << GridSize << endl << NbKandies << endl << Coups << endl << ScoreToWin << endl;
    for(unsigned i=0; i < GridSize; ++i) {
        string LigneTmp;
        getline(cin,LigneTmp);
        while(!TestValeurDansString(LigneTmp, GridSize)) {
            cout << "Veuillez respecter les indications données" << endl;
            getline(cin,LigneTmp);
        }
        StockDeVar[i+4]=LigneTmp;
    }
    ofstream ofs(NomLevel);
    for(unsigned i=0; i < StockDeVar.size(); ++i) {
        ofs << StockDeVar[i] << endl;
    }
    cout << endl << "Bravo, votre niveau a ete cree avec succes" << endl;
} // LevelCreator ()
