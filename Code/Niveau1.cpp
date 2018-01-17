void Niveau1(CMat & Grid)
{
    InitGrid(Grid, 10, 5);
    for(unsigned i=0; i<5 ;++i)
    {
        Grid[i][0]=6;
        Grid[i][Grid.size()-1]=6;
    }



    for(unsigned i=0; i<5 ;++i)
    {
        for(unsigned j=0 ; j<=i ; ++j)
        {
            Grid[5+i][j]=6;
        }
    }

    for(unsigned i=0; i<5 ;++i)
    {
        for(unsigned j=0 ; j<=i ; ++j)
        {
            Grid[5+i][(Grid.size()-1)-j]=6;
        }
    }
}
