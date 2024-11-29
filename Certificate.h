
#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <iostream>
using namespace std;
// Certificate class
class Certificate
{
private:
    int certificateID;
    string issueDate;
    string courseTitle;
    string recipient;

public:
    //------------------ operator overloading ------------------
    bool operator==(const Certificate &obj) const
    {
        return (certificateID == obj.certificateID &&
                issueDate == obj.issueDate &&
                courseTitle == obj.courseTitle &&
                recipient == obj.recipient);
    }
    Certificate &operator=(const Certificate &obj)
    {
        certificateID = obj.certificateID;
        issueDate = obj.issueDate;
        courseTitle = obj.courseTitle;
        recipient = obj.recipient;
        return *this;
    }
    friend istream &operator>>(istream &in, Certificate &obj)
    {
        cout << "Enter Certificate ID: ";
        in >> obj.certificateID;
        cout << "Enter Issue Date: ";
        in.ignore();
        getline(in, obj.issueDate);
        cout << "Enter Course Title: ";
        getline(in, obj.courseTitle);
        cout << "Enter Recipient: ";
        getline(in, obj.recipient);
        return in;
    }
    friend ostream &operator<<(ostream &out, const Certificate &obj)
    {
        out << "Certificate ID: " << obj.certificateID << endl;
        out << "Issue Date: " << obj.issueDate << endl;
        out << "Course Title: " << obj.courseTitle << endl;
        out << "Recipient: " << obj.recipient << endl;
        return out;
    }
    string operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return to_string(certificateID);
        case 1:
            return issueDate;
        case 2:
            return courseTitle;
        case 3:
            return recipient;
        default:
            cout << "Invalid index!!!\n";
            return "";
        }
    }
    string operator()(const string &dataMember) const
    {
        if (dataMember == "certificateID")
        {
            return to_string(certificateID);
        }
        else if (dataMember == "issueDate")
        {
            return issueDate;
        }
        else if (dataMember == "courseTitle")
        {
            return courseTitle;
        }
        else if (dataMember == "recipient")
        {
            return recipient;
        }
        else
        {
            return "Invalid data member!";
        }
    }
    Certificate() : certificateID(0), issueDate(""), courseTitle(""), recipient("") {}
    Certificate(int id, string date, string title, string recipient)
    {
        this->certificateID = id;
        this->issueDate = date;
        this->courseTitle = title;
        this->recipient = recipient;
    }

    void displayCertificateInfo() const
    {
        cout << "Certificate ID: " << certificateID << endl;
        cout << "Issue Date: " << issueDate << endl;
        cout << "Course Title: " << courseTitle << endl;
        cout << "Recipient: " << recipient << endl;
    }

    int getCertificateID() const
    {
        return certificateID;
    }

    ~Certificate() {}
};

#endif