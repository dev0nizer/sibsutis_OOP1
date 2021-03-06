#include <iostream>
#include "sqlite3.h"
#include <string>

class Transport{
    public:
    
    virtual void addatributes(std::string tempName, int tempMaxspeed,int tempHorsepower, int tempSeats, int tempPrice, int tempAge,sqlite3 *db) = 0;

};


class PassengerTransport : Transport
{
private:
    std::string Name;
    int Maxspeed;
    int Horsepower;
    int Seats;
    int Price;
    int Age;

public:
    PassengerTransport() {}
    PassengerTransport(std::string Tempname)
    {
        Name = Tempname;
    }

    void addatributes(std::string tempName, int tempMaxspeed,int tempHorsepower, int tempSeats, int tempPrice, int tempAge,sqlite3 *db)
    {
        Name = tempName;
        Maxspeed = tempMaxspeed;
        Horsepower = tempHorsepower;
        Seats = tempSeats;
        Price = tempPrice;
        Age = tempAge;
    }

    
};

class Car : public PassengerTransport
{
private:
    std::string Name;
    int Maxspeed;
    int Horsepower;
    int Seats;
    int Price;
    int Age;
    int CountDoors;

public:
    Car(){}

    Car(std::string tempName)
    {
        Name = tempName;
    }

    void addCountDoors(int tempCountDoors)
    {
        CountDoors = tempCountDoors;
    }

    void insertsql(std::string Name, int Maxspeed, int Horsepower, int Seats, int Price, int Age, int CountDoors,sqlite3 *db)
    {
        char *err = 0;
        std::string SQL = "INSERT INTO transport (Name, Maxspeed, Horsepower, Seats, Price, Age,CountDoors) VALUES ('"+ Name+"',"+ std::to_string(Maxspeed) + "," + std::to_string(Horsepower) + "," + std::to_string(Seats) + "," + std::to_string(Price) + "," +std::to_string(Age) + "," +std::to_string(CountDoors)+")";
        sqlite3_exec(db, SQL.c_str(), 0,0,&err);
    }

};

class Plane : public PassengerTransport
{
private:
    std::string Name;
    int Maxspeed;
    int Horsepower;
    int Seats;
    int Price;
    int Age;
    int Maxheight;

public:
    Plane() {}
    
    Plane (std::string tempName)
    {
        Name = tempName;
    }

    void addMaxheight(int tempMaxheight)
    {
        Maxheight = tempMaxheight;
    }
};


int main()
{
    sqlite3 *db = 0;
    char *err = 0;
    std::cout << "test";
    if (sqlite3_open("db.sqlite3",&db))
    {
        std::cout << "SQL Error!" << std::endl;
        return 0;
    }
    // else
    // {
    //     // const char* SQL = "CREATE TABLE IF NOT EXISTS foo(a,b,c)";
    //     // sqlite3_exec(db, SQL, 0,0,&err);
    //     return 0;
    // }
    
    
    while (true)
    {
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1: //create new object
            {
            int subchoice;
            std::cout << "Choose type: 1.Car 2.Plane" << std::endl;
            std::cin >> subchoice;
            std::string tempName;
            int tempMaxspeed, tempHorsepower, tempSeats, tempPrice, tempAge;
            std::cout << "Enter name:" << std::endl;
            std::cin >> tempName;
            std::cout << "Enter Maxspeed:" << std::endl;
            std::cin >> tempMaxspeed;
            std::cout << "Enter Horsepower:" << std::endl;
            std::cin >> tempHorsepower;
            std::cout << "Enter Seats:" << std::endl;
            std::cin >> tempSeats;
            std::cout << "Enter Price:" << std::endl;
            std::cin >> tempPrice;
            std::cout << "Enter Age:" << std::endl;
            std::cin >> tempAge;
            
            if (subchoice == 1)
            {
                int tempdoors;
                std::cout << "Enter doors number" << std::endl;
                std::cin >> tempdoors;
                Car* temp = new Car();
                temp->addatributes(tempName,tempMaxspeed,tempHorsepower,tempSeats,tempPrice,tempAge, db);
                temp->addCountDoors(tempdoors);
                std::cout << tempMaxspeed;
                temp->insertsql(tempName,tempMaxspeed,tempHorsepower,tempSeats,tempPrice,tempAge, tempdoors, db);
                std::cout << tempName;
            }
            else if (subchoice == 2)
            {
                int tempMaxheight;
                std::cout << "Enter plane max height: " << std::endl;
                std::cin >> tempMaxheight;
                Plane* temp = new Plane();
                temp->addatributes(tempName,tempMaxspeed,tempHorsepower,tempSeats,tempPrice,tempAge, db);
                temp->addMaxheight(tempMaxheight);
            }
            else
            {
                std::cout << "Net takogo punkta" << std::endl;
            }
            //insert into blalaal
            break;
            }
        case 2:
            { // select from db.table
                std::cout << "Enter name: " << std::endl;
                std::string tempName;
                std::cin >> tempName;
                //select
                //if select is 0
                break;
            }
            

        default:
            
            break;
        }
    }
}