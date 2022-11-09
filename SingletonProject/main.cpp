//
//  main.cpp
//  SingletonProject
//
//  Created by Steven Wijaya on 09.11.2022.
//

#include <iostream>

using namespace std;

int NUMBEROFPOPULATION = 10;

class Person {
private:
    string name;
    int age;
    string nationality;
    
public:
    Person() {}
    Person(string name, int age, string nationality) {
        this->name = name;
        this->age = age;
        this->nationality = nationality;
    }
    void introduceYourself(string role) {
        cout << "Hello, my name is " << this->name << ", i'm " << this->age << " , and i'm a/an " << this->nationality << ". And i'm your new " << role << "." << endl;
    }
    int pickAPresident() {
        if ((rand() % 100) % 2 == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    string getNationality() {
        return this->nationality;
    }
};

class Government {
private:
    Government() {};
    Person president;
    Person vicePresident;
    
public:
    static Government& getInstance() {
        static Government instance;
        return instance;
    }
    Government(const Government&) = delete; // For copy constructor
    Government(Government&&) = delete; // For move operator
    Government& operator=(const Government&) = delete; // For copy constructor
    Government& operator=(Government&&) = delete; // For move operator
    
    void election(Person candidate1, Person candidate2, Person* citizen) {
        int voteForCandidate1 = 0;
        int voteForCandidate2 = 0;
        
        for (int i = 0; i < NUMBEROFPOPULATION; i++) {
            if (citizen[i].getNationality() == "Norwegian") {
                continue;
            }
            int selectedCandidate = citizen[i].pickAPresident();
            if (selectedCandidate == 0) {
                voteForCandidate1 += 1;
            } else if (selectedCandidate == 1) {
                voteForCandidate2 += 1;
            }
        }
        
        
        if (voteForCandidate1 > voteForCandidate2) {
            this->president = candidate1;
            this->vicePresident = candidate2;
        } else if (voteForCandidate2 > voteForCandidate1) {
            this->president = candidate2;
            this->vicePresident = candidate1;
        } else {
            int myRand = rand() %100;
            if (myRand % 2 == 0) {
                this->president = candidate1;
                this->vicePresident = candidate2;
            } else {
                this->president = candidate2;
                this->vicePresident = candidate1;
            }
        }
        introduceNewPresidentAndVice();
    }
    
    void introduceNewPresidentAndVice() {
        this->president.introduceYourself("President");
        this->vicePresident.introduceYourself("Vice president");
    }
};

string generateName(int length) {
    char consonents[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
      char vowels[] = {'a','e','i','o','u'};

      string name = "";

      int random = rand() % 2;
      int count = 0;

      for(int i = 0; i < length; i++) {

        if(random < 2 && count < 2) {
          name = name + consonents[rand() % 19];
          count++;
        }
        else {
          name = name + vowels[rand() % 5];
          count = 0;
        }

        random = rand() % 2;

      }

      return name;
}

Person* generateRandomPopulation(int numberOfPerson) {
    Person* population = new Person[numberOfPerson];
    for (int i = 0; i < numberOfPerson; i++) {
        string name = generateName(rand()%10 + 3);
        int age = rand() % 60 + 20;
        string nationality;
        
        if ((rand() % 100) % 2 == 0) {
            nationality = "Icelandic";
        } else {
            nationality = "Norwegian";
        }
        Person newPerson = Person(name, age, nationality);
        population[i] = newPerson;
    }
    
    return population;
}


int main(int argc, const char * argv[]) {
    srand(time(NULL));
    //Initialize government
    Government& myCountryGovernment = Government::getInstance();
    
    //Initialize population in a country
    Person* population = generateRandomPopulation(NUMBEROFPOPULATION);
    // Initialize 2 candidate for presidency
    Person a = Person("Paul", 40, "Icelandic");
    Person b = Person("Roger", 36, "Icelandic");
    
    myCountryGovernment.election(a, b, population);
    
    cout << endl << "Introducing new president and new president for other person." << endl;
    Government& hisCountryGovernment = Government::getInstance();
    hisCountryGovernment.introduceNewPresidentAndVice();


    return 0;
}
