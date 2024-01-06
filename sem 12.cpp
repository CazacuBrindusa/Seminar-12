#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//has a relatie dc avem atribut de tip A in clasa B
//is a relatie dc clasa B e derivata din clasa A
//ex
//din public creste in protected prin mostenire private

class Date
{
    int day = 0;
    int month = 0;
    int year = 0;
public:
    Date() {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};

class Persoana
{
protected:
    string name = "";
    Date birthdate;
    string pin = "";
    string* adress = nullptr;
    int adresscount = 0;
public:
    Persoana() {}
    Persoana(string name, string pin, Date birthdate, string* adress, int adresscount)
    {
        this->name = name;
        this->pin = pin;
        this->birthdate = birthdate;
        this->adresscount = adresscount;
        this->adress = new string[this->adresscount];
        for (int i = 0; i < this->adresscount; i++)
        {
            this->adress[i] = adress[i];
        }
    }
    Persoana(const Persoana& p)
    {
        this->name = p.name;
        this->pin = p.pin;
        this->birthdate = p.birthdate;
        this->adresscount = p.adresscount;
        this->adress = new string[this->adresscount];
        for (int i = 0; i < this->adresscount; i++)
        {
            this->adress[i] = p.adress[i];
        }
    }
    Persoana& operator =(const Persoana& p)
    {
        if (this != &p)
        {
            this->name = p.name;
            this->pin = p.pin;
            this->birthdate = p.birthdate;
            this->adresscount = p.adresscount;
            delete[] this->adress;
            this->adress = new string[this->adresscount];
            for (int i = 0; i < this->adresscount; i++)
            {
                this->adress[i] = p.adress[i];
            }
        }
        return *this;
    }
    virtual string listDetails()
    {
        return "I am a person";
    }
    ~Persoana()
    {
        if (this->adress != NULL)
        {
            delete[] this->adress;
            this->adress = NULL;
        }
    }
};

class Student : public Persoana
{
    int regno = 0;
    double* grades = nullptr;
    int gradescount = 0;
public:
    Student() : Persoana()
    {

    }
    Student(string name, string pin, Date birthdate, string* adress, int adresscount, int regno, double* grades, int gradescount) : Persoana(name, pin, birthdate, adress, adresscount)
    {
        this->regno = regno;
        this->gradescount = gradescount;
        this->grades = new double[this->gradescount];
        for (int i = 0; i < this->gradescount; i++)
        {
            this->grades[i] = grades[i];
        }
    }
    Student(const Student& s) : Persoana(s)
    {
        this->regno = s.regno;
        this->gradescount = s.gradescount;
        this->grades = new double[this->gradescount];
        for (int i = 0; i < this->gradescount; i++)
        {
            this->grades[i] = s.grades[i];
        }
    }
    Student& operator =(const Student& s)
    {
        if (this != &s)
        {
            Persoana::operator=(s);
            this->regno = s.regno;
            this->gradescount = s.gradescount;
            delete[] this->grades;
            this->grades = new double[this->gradescount];
            for (int i = 0; i < this->gradescount; i++)
            {
                this->grades[i] = s.grades[i];
            }
        }
    }
    string listDetails()
    {
        return "I am a student";
    }
    ~Student()
    {
        Persoana::~Persoana(); // este apelat automat
        if (this->grades != NULL)
        {
            delete[] this->grades;
            this->grades = NULL;
        }
    }
};

class Employees : public Persoana
{
protected:
    string salariu;
    string position;
public:
    string listDetails()
    {
        return "I am an employee";
    }
};

class Profesor : public Persoana
{
protected:
    string title="";
public:
    Profesor(){}
    Profesor(string name, string pin, Date birthdate, string* adress, int adresscount, string title) : Persoana(name, pin, birthdate, adress, adresscount), title(title){}
    string listDetails()
    {
        return "I am an profesor";
    }
    ~Profesor(){}
};

class Admin : public Persoana
{
protected:
    string area="";
public:
    Admin() {}
    Admin(string name, string pin, Date birthdate, string* adress, int adresscount, string area) : Persoana(name, pin, birthdate, adress, adresscount), area(area) {}
    string listDetails()
    {
        return "I am an admin";
    }
    ~Admin(){}
};

class University : public Student, public Profesor, public Admin
{
    string name="";
    string city = "";

    Persoana** all=nullptr;
    int allCount=0;
public:
    University(){}
    University(string name, string city): name(name), city(city){}
    void setall(Persoana** all, int allCount)
    {
        this->allCount = allCount;
        //!!!!
        this->all = all;
    }
    void listaDetails()
    {
        for (int i = 0; i < this->allCount; i++)
            cout << this->all[i]->listDetails() << endl;
    }
};

class Product
{
protected:
    string name = "";
    string description = "";
    double price = 0;
public:
    Product(){}
    Product(string name, string description, double price): name(name), description(description), price(price){}
    virtual string details()
    {
        return "Product";
    }
    ~Product(){}
};

class Eloctronics : public Product
{
protected:
    int garantie = 0;
public:
    Eloctronics(){}
    Eloctronics(string name, string description, double price, int garantie): Product(name, description, price), garantie(garantie){}
    string details()
    {
        return "Eloctronics";
    }
    ~Eloctronics(){}
};

class Vehicul: public Product
{
protected:
    int nr_roti;
public:
    Vehicul(){}
    Vehicul(string name, string description, double price, int nr_roti): Product(name, description, price), nr_roti(nr_roti){}
    string details()
    {
        return "Vehicul";
    }
    ~Vehicul(){}
};



int main()
{
    Date d(2, 2, 1900);
    string* adress = new string[3];
    adress[0] = "Bucuresti";
    adress[1] = "Moara Vasiliei";
    adress[2] = "Arad";
    Persoana p("Christescu V", "43327bt871664", d, adress, 3);

    double* grades = new double[5];
    grades[0] = 9;
    grades[1] = 5;
    grades[2] = 6;
    grades[3] = 3;
    grades[4] = 7;
    string* adress2 = new string[2];
    adress2[0] = "Brasov";
    adress2[1] = "Bagheta de sus";
    Date d2(5, 9, 2077);
    Student s1("Christescu V", "43327bt871664", d2, adress, 3, 6536, grades, 5);

    Persoana* person = new Persoana{ "Person", "43327bt871664", d, adress, 3 };
    Persoana* student = new Student{ "Student", "43327bt871664", d2, adress, 3, 6536, grades, 5 };
    Persoana* admin = new Admin{ "Admin", "43327bt871664", d, adress, 3 , "lab" };
    Persoana* prof = new Profesor{ "Profesor", "43327bt871664", d, adress, 3 , "assistent" };
    Persoana** all = new Persoana * [4];
    all[0] = person;
    all[1] = student;
    all[2] = admin;
    all[3] = prof;
    University u1("ASE", "Bucuresti");
    u1.setall(all, 4);
    u1.listaDetails();


    Product* product = new Product{ "Produs", "nou", 1.2 };
    Eloctronics* Eloctronics = new Eloctronics{ "Eloctronics", "nou", 1.2, 3 };
    Vehicul* vehicul = new Vehicul{ "Vehicul", "nou", 1.2, 3 };
    Product** all2 = new product * [3];
    return 0;
}