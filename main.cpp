#include <iostream>
#include "sqlite3.h"
#include <string>

class Transport{
    public:
    
    virtual void addatributes(std::string tempName, int tempMaxspeed,int tempHorsepower, int tempSeats, int tempPrice, int tempAge,sqlite3 *db) = 0;

};


class PassengerTransport : Transport
{
protected:
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
    int CountDoors;

public:
    Car() {}

    void addCountDoors(int tempCountDoors)
    {
        CountDoors = tempCountDoors;
    }

    void insertsql(sqlite3 *db)
    {
        char *err = 0;
        std::string SQL = "INSERT INTO car (Name, Maxspeed, Horsepower, Seats, Price, Age,CountDoors) VALUES ('"+ Name+"',"+ std::to_string(Maxspeed) + "," + std::to_string(Horsepower) + "," + std::to_string(Seats) + "," + std::to_string(Price) + "," +std::to_string(Age) + "," +std::to_string(CountDoors)+")";
        sqlite3_exec(db, SQL.c_str(), 0,0,&err);
    }

};

class Plane : public PassengerTransport
{
private:
    int Maxheight;

public:
    Plane() {}
    

    void addMaxheight(int tempMaxheight)
    {
        Maxheight = tempMaxheight;
    }

    void insertsql(sqlite3 *db)
    {
        char *err = 0;
        std::string SQL = "INSERT INTO plane (Name, Maxspeed, Horsepower, Seats, Price, Age,Maxheight) VALUES ('"+ Name+"',"+ std::to_string(Maxspeed) + "," + std::to_string(Horsepower) + "," + std::to_string(Seats) + "," + std::to_string(Price) + "," +std::to_string(Age) + "," +std::to_string(Maxheight)+")";
        sqlite3_exec(db, SQL.c_str(), 0,0,&err);
    }
};

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    try
    {
    for(int i = 0; i < argc; i++)
    {        
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
        std::cout << "request complete";
    }
    std::cout << std::endl;
    }
    catch(...)
    {
        std::cout << "Error executing SQL callback" << std::endl;
    }
    return 0;
}

int main()
{   int rc;
    sqlite3 *db = 0;
    char *err = 0;
    rc = sqlite3_open("db.sqlite3",&db);
  
    // else
    // {
    //     // const char* SQL = "CREATE TABLE IF NOT EXISTS foo(a,b,c)";
    //     // sqlite3_exec(db, SQL, 0,0,&err);
    //     return 0;
    // }
    
    
    while (true)
    {
        int choice;
        std::cout << "Menu: 1.Create object 2.Search object 3.Close" << std::endl;
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
                temp->insertsql(db);
            }
            else if (subchoice == 2)
            {
                int tempMaxheight;
                std::cout << "Enter plane max height: " << std::endl;
                std::cin >> tempMaxheight;
                Plane* temp = new Plane();
                temp->addatributes(tempName,tempMaxspeed,tempHorsepower,tempSeats,tempPrice,tempAge, db);
                temp->addMaxheight(tempMaxheight);
                temp->insertsql(db);
            }
            else
            {
                std::cout << "Net takogo punkta" << std::endl;
            }
            //insert into blalaal
            break;
            }
        case 2:
            {   sqlite3_stmt * pStmt;
                int i, j, coln;
                int b = 1;
                char *err = 0;
                std::string SQL;
                int selectchoice;
                std::cout << "Wto iwete?" << std::endl;
                std::cout << "1. Car" << std::endl;
                std::cout << "2. Plane" << std::endl;
                std::cin >> selectchoice;
                std::cout << "Enter name: " << std::endl;
                std::string tempName;
                std::cin >> tempName;
                if (selectchoice == 1)
                {
                    SQL = "select * from car where  Name= '"+tempName+"'";
                    sqlite3_exec(db, SQL.c_str(), callback, 0,&err);
                }
                else
                {
                    SQL = "select * from plane where  Name= '"+tempName+"'";
                    sqlite3_exec(db, SQL.c_str(), callback, 0,&err);
                }
                break;
            }
         case 3:
            {  
                 exit(0);
            }

        default:
            std::cout << "Error choosing option" << std::endl;
            break;
        }
    }
}

