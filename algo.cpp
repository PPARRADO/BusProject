//
// Created by pascal on 25/11/16.
//

#include "Trajet.h"
#include "Base.h"
#include <vector>
#include <clocale>
#include <iostream>


void executeGlouton(Base* mBase, std::vector<std::vector<Trajet> > &finalSolution)
{

    int N_INDIVIDU = 14;
    std::vector<Trajet> horEnService = (*mBase).getHorairEs();
    std::vector<Trajet> horHorsService = (*mBase).getHorairHs();
    std::vector<Trajet> busTravel;
    Trajet* Depart;

    while(horEnService.size() > 0)
    {
        int dist = 999999999;
        int time = 999999999;
        int position = 0;
        //Point de départ
        busTravel.clear();
        for(int i=0;i<horEnService.size();i++)
        {
            if(horEnService[i].getTemps() < time && horEnService[i].getDistance() < dist)
            {
                Depart = &horEnService[i];
                position = i;
                time = horEnService[i].getTemps();
                dist = horEnService[i].getDistance();
            }
        }
        horEnService.erase(horEnService.begin() + position);
        busTravel.push_back(*Depart);


        Trajet* Next;
        do
        {
            //Choix du prochain trajet
            dist = 999999999;
            time = 999999999;
            int position = 0;
            Next = NULL;
            for(int i =0;i<horEnService.size();i++)
            {
                if(horEnService[i].getPointDepart() == busTravel[busTravel.size()-1].getPointArrivee())
                {
                    int timeTemp = 0;
                    int distTemp = 0;
                    timeTemp = horEnService[i].getHeureDepart() - busTravel[busTravel.size()-1].getHeureArrivee();
                    distTemp = horEnService[i].getDistance();
                    if(timeTemp > 5 && timeTemp < time && distTemp < dist)
                    {
                        Next = &horEnService[i];
                        position = i;
                    }
                }
            }
            if(Next != NULL)
            {
                busTravel.push_back(*Next);
                horEnService.erase(horEnService.begin() + position);
            }
        }
        while(Next != NULL);


        //Choix du trajet entre deux terminus
        dist = 999999999;
        time = 999999999;
        Next = NULL;
        for(int i =0;i<horHorsService.size();i++)
        {
            if(horHorsService[i].getPointDepart() == busTravel[busTravel.size()-1].getPointArrivee())
            {
                int timeTemp = 0;
                int distTemp = 0;
                timeTemp = horHorsService[i].getHeureDepart() - busTravel[busTravel.size()-1].getHeureArrivee();
                distTemp = horHorsService[i].getDistance();
                if(timeTemp > 5 && timeTemp < time && distTemp < dist)
                {
                    Next = &horHorsService[i];
                }
            }
        }
        if(Next != NULL)
        {
            busTravel.push_back(*Next);
        }
        finalSolution.push_back(busTravel);
    }



}
