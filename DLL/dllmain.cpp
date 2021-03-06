// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#pragma warning( disable : 4290 )

#include <iostream>
using namespace std;

#include "src/zoo.h"
#include "src/zooManager.h"
#include "src/areaManager.h"


int _entry() {
    try
    {
        AreaManager quarantineManager("Meny", 5468, 50000);
        Area quarantineArea("quarantineArea", 4, 4, Animal::eAnimalClass::LAND, &quarantineManager);

        Zoo* myZoo = Zoo::getInstance("My Zoo", 10, quarantineArea);

        ZooManager zooManager(*myZoo);

        int numOfManagers = 3;
        vector<AreaManager*>* managers = &zooManager.createAreaManagers(numOfManagers);

        int numOfAreas = 3;
        vector<Area*>* areas = &zooManager.createAllAreas(numOfAreas, *managers);

        // add all areas
        zooManager.addAreasToZoo(*areas, numOfAreas);

        int numOfKeepers = 3;
        vector<Keeper*>* keepers = &zooManager.createAllKeepers(numOfKeepers);

        // add all the keepers
        zooManager.addKeepersToZoo(*keepers, numOfKeepers);

        int numOfAnimals = 4;

        vector<Animal*>* animals = &zooManager.createAnimals(numOfAnimals);

        // add animals
        zooManager.addAllAnimalsToZoo(*animals, numOfAnimals);


        int numOfVeterinarian = 3;
        vector<Veterinarian*>* vets = &zooManager.createAllVeterinarian(numOfVeterinarian);

        // add all vets
        zooManager.addAllVeterinarianToZoo(*vets, numOfVeterinarian);

        // print the whole zoo
        cout << "My Zoo: \n" << *myZoo << endl << endl;

    }
    catch (const string& message)
    {
        cout << message;
    }
    catch (...)
    {
        cout << "Something went wrong" << endl;
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        _entry();
    case DLL_THREAD_ATTACH:
        _entry();
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}