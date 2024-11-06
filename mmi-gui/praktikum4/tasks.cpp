#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

class Address {
public:
    /*Address(std::string street, std::string number, std::string plz,
            std::string city): m_street(street), m_number(number), m_plz(plz), m_city(city) {
    }*/

    Address(std::string street, std::string number, std::string plz, std::string city): street(std::move(street)),
        number(std::move(number)),
        plz(std::move(plz)), city(std::move(city)) {
    }

    /*Address(const std::string &street, const std::string &number, const std::string &plz,
            const std::string &city): m_street(street), m_number(number), m_plz(plz), m_city(city) {
    }*/

    const std::string &getStreet() const {
        return street;
    }

    void setStreet(const std::string &street) {
        this->street = street;
    }

    const std::string &getNumber() const {
        return number;
    }

    void setNumber(const std::string &plz) {
        this->number = plz;
    }

    const std::string &getPlz() const {
        return plz;
    }

    void setPlz(const std::string &plz) {
        this->plz = plz;
    }

    const std::string &getCity() const {
        return city;
    }

    void setCity(const std::string &city) {
        this->city = city;
    }

    friend std::ostream &operator<<(std::ostream &os, const Address &obj) {
        return os
               << "Person(street: " << obj.street
               << ", number: " << obj.number
               << ", plz: " << obj.plz
               << ", city: " << obj.city
               << ")";
    }

private:
    std::string street, number, plz, city;
};

class Date {
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
        if (month < 1 || month > 12) {
            throw std::invalid_argument("Invalid date");
        }
    }

    int getYear() const {
        return this->year;
    }

    void setYear(int year) {
        this->year = year;
        throw std::invalid_argument("Invalid date");
    }

    void operator+=(const int &days) {
        this->day += days;

        while (true) {
            int thisMonthLength = monthLength(year, month);
            if (day <= thisMonthLength) {
                return;
            }

            this->day -= thisMonthLength;
            this->month++;

            if (month == 13) {
                this->year += 1;
            }
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
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
            return isLeapYear ? 29 : 28;
        }

        int lookup[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return lookup[month - 1];
    }

    int day, month, year;
};

class Person {
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

private:
    std::string name;
    Address address;
    Date birthday;
};

class ExamResult {
public:
    int getResult() const {
        return result;
    }

    void setResult(int result) {
        this->result = result;
    }

    Person getPerson() const {
        return person;
    }

    void setPerson(const Person &person) {
        this->person = person;
    }

    ExamResult(int result, Person person)
        : result(result),
          person(std::move(person)) {
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
        return this->result <=> other.result;
    }

private:
    int result;
    Person person;
};

class TaxPayer : public Person {
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

private:
    std::string taxId;
};

class TaxPayerManager {
public:
    explicit TaxPayerManager(): people() {
    }

    void add(const TaxPayer &taxPayer) {
        people.push_back(taxPayer);
    }

    void deleteMember(size_t index) {
        people.erase(people.begin() + static_cast<long>(index));
    }

    void clear() {
        people.clear();
    }

    size_t size() const {
        return people.size();
    }

    Person &operator [](size_t index) {
        return people[index];
    }

    const Person &operator [](size_t index) const {
        return people[index];
    }

    TaxPayerManager &operator<<(const TaxPayer &payer) {
        this->add(payer);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const TaxPayerManager &obj) {
        return os << "TaxPayerManager(" << obj.size() << " managed people)";
    }

private:
    std::vector<TaxPayer> people;
};

int main() {
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

    ExamResult examResultA(5, personA);
    ExamResult examResultB(3, personB);

    std::cout << "Person A has better grade than person B: " << (examResultA < examResultB ? "yes" : "no") << std::endl;

    std::cout << std::endl << std::endl;
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

