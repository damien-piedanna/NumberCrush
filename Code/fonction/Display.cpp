
void  DisplayGrid (const CMat & Grid)
{
    ClearScreen ();
    Couleur(CReset);
    cout << ' ';
    for(unsigned i=0; i < Grid.size(); ++i)
    {
         cout << i << ' ';
    }
    cout << endl;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
         Couleur(CReset);
        cout << i;
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Couleur (to_string(Grid [i][j] + 29));
            if (Grid [i][j] == 0)
                Couleur(CReset);
            cout << Grid [i][j] << ' ';
        }
        cout << endl;
    }
    Couleur(CReset);
}
