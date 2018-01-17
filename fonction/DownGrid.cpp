void DownGrid (CMat & Grid)
{
    CPosition Posbis;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            unsigned ibis = i;
            if (Grid [i][j] == 0)
            {
                while (ibis > 0)
                {
                    swap (Grid[ibis-1][j], Grid[ibis][j]);
                    ibis--;
                }
            }
        }
    }
}
