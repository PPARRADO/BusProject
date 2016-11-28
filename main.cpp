#include <iostream>
#include <vector>
#include "algo.h"
#include "Base.h"
#include "file_reader.h"

using namespace std;

int main() {
    Base *base = ALGO_File();

    cout << "test : " << base->getHorairHsAtPos(6, 15).getPointDepart() << endl ;
    cout << "test : " << base->getHorairHsAtPos(6, 15).getPointArrivee() << endl ;
    cout << "test : " << base->getHorairHsAtPos(6, 15).getDistance() << endl ;


    std::vector<std::vector<Trajet> > finalSolution;


    executeGlouton(base, finalSolution);
    for(int i=0;i<finalSolution.size();i++)
    {
        cout << "BUS NUMERO " << i << endl;
        for(int j = 0;j<finalSolution[i].size();j++)
        {
            cout << "Point de Départ(" << finalSolution[i][j].getPointDepart() << ") : " << finalSolution[i][j].getHeureDepart() ;
            cout << " == > ";
            cout << "Point de Arrivée(" << finalSolution[i][j].getPointArrivee() << ") : " << finalSolution[i][j].getHeureArrivee() ;
            cout << endl;
        }

    }
    cout <<endl << "Programme Terminé :) !" << endl;
    return 0;
}
