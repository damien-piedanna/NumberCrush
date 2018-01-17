void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction)
{
    switch (Direction)
    {
        case 'z' : if(Pos.first != 0 && Grid[Pos.first-1][Pos.second] != 6 && Grid[Pos.first][Pos.second] != 6)
            {
                swap (Grid[Pos.first-1][Pos.second], Grid[Pos.first][Pos.second]);
            }
        break;
        case 's' : if(Pos.first != Grid.size()-1 && Grid[Pos.first+1][Pos.second] != 6 && Grid[Pos.first][Pos.second] != 6)
            {
                swap (Grid[Pos.first+1][Pos.second], Grid[Pos.first][Pos.second]);
            }
        break;
        case 'd' : if(Pos.second != Grid.size()-1 && Grid[Pos.first][Pos.second+1] != 6 && Grid[Pos.first][Pos.second] != 6)
            {
                swap (Grid[Pos.first][Pos.second+1], Grid[Pos.first][Pos.second]);
            }
        break;
        case 'q' : if(Pos.first != 0 && Grid[Pos.first][Pos.second-1] != 6 && Grid[Pos.first][Pos.second] != 6)
            {
                swap (Grid[Pos.first][Pos.second-1], Grid[Pos.first][Pos.second]);
            }
        break;
        default:
            cout << "Choix incorect, z=haut / q=gauche / s=bas / d=droite" << endl;
            cin >> Direction;
    }
    DisplayGrid(Grid);
}
