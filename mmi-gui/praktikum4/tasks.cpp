#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

class Address {
private:
    std::string m_street, m_number, m_plz, m_city;

public:
    Address(std::string street, std::string number, std::string plz, std::string city)
        : m_street(street), m_number(number), m_plz(plz), m_city(city) {
    }

    /*Address(std::string street, std::string number, std::string plz, std::string city): m_street(std::move(street)),
                                                                                         m_number(std::move(number)),
                                                                                         m_plz(std::move(plz)),
                                                                                         m_city(std::move(city)) {
    }*/

    /*Address(const std::string &street, const std::string &number, const std::string &plz, const std::string &city)
        : m_street(street), m_number(number), m_plz(plz), m_city(city) {
    }*/

    const std::string &getStreet() const {
        return m_street;
    }

    void setStreet(const std::string &street) {
        m_street = street;
    }

    const std::string &getNumber() const {
        return m_number;
    }

    void setNumber(const std::string &plz) {
        m_number = plz;
    }

    const std::string &getPlz() const {
        return m_plz;
    }

    void setPlz(const std::string &plz) {
        m_plz = plz;
    }

    const std::string &getCity() const {
        return m_city;
    }

    void setCity(const std::string &city) {
        m_city = city;
    }

    friend std::ostream &operator<<(std::ostream &os, const Address &obj) {
        return os
               << "Person(street: " << obj.m_street
               << ", number: " << obj.m_number
               << ", plz: " << obj.m_plz
               << ", city: " << obj.m_city
               << ")";
    }
};

class Date {
private:
    int day, month, year;

public:
    Date(int day, int month, int year)
        : day(day),
          month(month),
          year(year) {
        if (!isValid()) {
            throw std::invalid_argument("Invalid date");
        }
    }

    // 1-31
    int getDay() const {
        return this->day;
    }

    void setDay(int day) {
        this->day = day;
        if (!isValid()) {
            throw std::invalid_argument("Invalid date");
        }
    }

    // 1-12
    int getMonth() const {
        return this->month;
    }

    void setMonth(int month) {
        this->month = month;
        if (!isValid()) {
            throw std::invalid_argument("Invalid date");
        }
    }

    int getYear() const {
        return this->year;
    }

    void setYear(int year) {
        this->year = year;
    }

    void operator+=(int days) {
        this->day += days;

        while (true) {
            int thisMonthLength = monthLength(year, month);
            if (day <= thisMonthLength) {
                break;
            }

            this->day -= thisMonthLength;
            this->month++;

            if (month == 13) {
                this->year += 1;
                this->month = 1;
            }
        }
    }

    void operator-=(int days) {
        this->day -= days;

        while (true) {
            if (day >= 1) {
                break;
            }

            month -= 1;
            if (month == 0) {
                year -= 1;
                month = 12;
            }

            int previousMonthLength = monthLength(year, month);

            //  0 => 30.2.
            // -1 => 29.2.
            // -2 => 28.2.

            day = previousMonthLength + day;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Date &obj) {
        return os << obj.day << "." << obj.month << "." << obj.year;
        /*return os
               << "Date(day: " << obj.day
               << ", month: " << obj.month
               << ", year: " << obj.year
               << ")";*/
    }

    bool isValid() const {
        return this->month >= 1 && this->month <= 12 && this->day >= 1 && this->day <= monthLength(
                   this->year, this->month);
    }

private:
    static int monthLength(int year, int month) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
        int february = isLeapYear ? 29 : 28;

        int lookup[12] = {31, february, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return lookup[month - 1];
    }
};

class Person {
private:
    std::string name;
    Address address;
    Date birthday;

public:
    Person(std::string name, Address address, Date birthday)
        : name(std::move(name)),
          address(std::move(address)),
          birthday(birthday) {
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    const Address &getAddress() const {
        return address;
    }

    void setAddress(const Address &address) {
        this->address = address;
    }

    const Date &getBirthday() const {
        return birthday;
    }

    void setBirthday(const Date &birthday) {
        this->birthday = birthday;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &obj) {
        return os
               << "Person(name: " << obj.name
               << ", address: " << obj.address
               << ", birthday: " << obj.birthday << ")";
    }
};

class ExamResult {
private:
    int grade;
    Person person;

public:
    ExamResult(int result, Person person)
        : grade(result),
          person(std::move(person)) {
    }

    int getGrade() const {
        return grade;
    }

    void setGrade(int grade) {
        this->grade = grade;
    }

    Person getPerson() const {
        return person;
    }

    void setPerson(const Person &person) {
        this->person = person;
    }

    friend std::ostream &operator<<(std::ostream &os, const ExamResult &obj) {
        return os
               << "ExamResult(person: " << obj.person
               << ", grade: " << obj.grade
               << ")";
    }

    /*bool operator<(const ExamResult &other) const {
        return this->result < other.result;
    }

    bool operator>(const ExamResult &other) const {
        return this->result > other.result;
    }

    bool operator==(const ExamResult &other) const {
        return this->result == other.result;
    }

    bool operator>=(const ExamResult &other) const {
        return this->result >= other.result;
    }

    bool operator<=(const ExamResult &other) const {
        return this->result >= other.result;
    }

    bool operator!=(const ExamResult &other) const {
        return this->result != other.result;
    }*/

    std::weak_ordering operator<=>(const ExamResult &other) const {
        return other.grade <=> this->grade;
    }
};

class TaxPayer : public Person {
private:
    std::string taxId;

public:
    TaxPayer(const std::string &name, const Address &address, const Date &birthday, const std::string &tax_id)
        : Person(name, address, birthday),
          taxId(tax_id) {
    }

    TaxPayer(const Person &person, const std::string &tax_id)
        : Person(person),
          taxId(tax_id) {
    }

    std::string getTaxId() const {
        return taxId;
    }

    void setTaxId(const std::string &tax_id) {
        taxId = tax_id;
    }

    friend std::ostream &operator<<(std::ostream &os, const TaxPayer &obj) {
        return os
               << "TaxPayer(person: " << static_cast<const Person &>(obj)
               << ", taxId: " << obj.taxId << ")";
    }
};

class TaxPayerManager {
private:
    std::vector<TaxPayer> people;

public:
    TaxPayerManager() : people() {
    }

    void add(const TaxPayer &taxPayer) {
        people.push_back(taxPayer);
    }

    void remove(size_t index) {
        people.erase(people.begin() + index);
    }

    void clear() {
        people.clear();
    }

    size_t size() const {
        return people.size();
    }

    Person &operator[](size_t index) {
        return people[index];
    }

    const Person &operator[](size_t index) const {
        return people[index];
    }

    TaxPayerManager &operator<<(const TaxPayer &payer) {
        this->add(payer);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const TaxPayerManager &obj) {
        return os << "TaxPayerManager(" << obj.size() << " managed people)";
    }
};

int main() {
    std::cout << "-- Testing Date -- " << std::endl;
    Date testDate(1, 3, 2000);
    std::cout << testDate << std::endl;
    std::cout << " -1" << std::endl;
    testDate -= 1;
    std::cout << testDate << std::endl;
    std::cout << " -29" << std::endl;
    testDate -= 29;
    std::cout << testDate << std::endl;
    std::cout << " +30" << std::endl;
    testDate += 30;
    std::cout << testDate << std::endl;
    std::cout << " -35" << std::endl;
    testDate -= 35;
    std::cout << testDate << std::endl;
    std::cout << " -26" << std::endl;
    testDate -= 26;
    std::cout << testDate << std::endl;
    std::cout << "-- Testing Date done -- " << std::endl
            << std::endl;

    // TASK 1
    Address address("Some street", "13a", "45193", "City");
    Date birthday(27, 3, 1996);
    Person personA("John Doe", address, birthday);

    Person personB = personA;
    personB.setName("Jane Doe");
    Date bday = personA.getBirthday();
    bday += 5;
    personB.setBirthday(bday);

    std::cout << personA << std::endl;
    std::cout << personB << std::endl;

    ExamResult examResultA(1, personA);
    ExamResult examResultB(2, personB);

    std::cout << "Person A has better grade than person B: " << (examResultA > examResultB ? "yes" : "no") << std::endl;

    std::cout << std::endl
            << std::endl;
    // TASK 2

    TaxPayer taxPayerA(personB, "81036591749");
    TaxPayer taxPayerB(personB, "73514280584");
    std::cout << taxPayerA << std::endl;
    std::cout << taxPayerB << std::endl;

    TaxPayerManager taxPayerManager;
    taxPayerManager << taxPayerA;
    taxPayerManager.add(taxPayerB);

    // taxPayerManager.deleteMember(1);
    // std::cout << taxPayerManager.size() << std::endl; // -> 1
    // taxPayerManager.add(taxPayerB);

    std::cout << taxPayerManager << std::endl;
}
