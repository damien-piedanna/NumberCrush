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




void Niveau2(CMat & Grid)
{
    InitGrid(Grid, 10, 5);

    for(unsigned i=0; i <= 5; ++i)
    {
        for(unsigned j = i; j <= Grid.size()-1-i; ++j)
        {
            Grid[Grid.size()-1-i][j] = 6;
        }
    }
    for(unsigned i=0; i < 3; ++i)
    {
        Grid[2+i][4] = 6;
         Grid[2+i][5] = 6;
    }
    DisplayGrid(Grid);
}




void Niveau3(CMat & Grid)
{
    InitGrid(Grid, 15, 5);

    for(unsigned i =0; i < 12; ++i)
    {
        Grid[Grid.size()-1-i][11] = 6;
        Grid[Grid.size()-1-i][7] = 6;
        Grid[Grid.size()-1-i][3] = 6;
    }
    DisplayGrid(Grid);
}



void Niveau4(CMat & Grid)
{
    InitGrid(Grid, 20, 5);

    for(unsigned i=0; i < 3 ; ++i)
    {
        for(unsigned j=i ; j < 5-i ; ++j)
        {
            Grid[Grid.size()-1-i][j]=6;
            Grid[Grid.size()-1-i][5+j]=6;
            Grid[Grid.size()-1-i][10+j]=6;
            Grid[Grid.size()-1-i][15+j]=6;

        }
    }

    DisplayGrid(Grid);
}




void Niveau5(CMat & Grid)
{
    InitGrid(Grid, 20, 5);

    for(unsigned i=0; i < 3 ; ++i)
    {
        for(unsigned j=i ; j < 5-i ; ++j)
        {
            Grid[Grid.size()-1-i][j]=6;


            Grid[Grid.size()-1-i][15+j]=6;

        }
    }

    for(unsigned i=0; i < 15 ; ++i )
    {
       Grid[Grid.size()-1-i][5]=6;
       Grid[Grid.size()-1-i][14]=6;
    }

    DisplayGrid(Grid);
}
