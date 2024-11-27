
#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "Person.h"
#include "Course.h"
#include "Notification.h"
#include "Assignment.h"
#include "Certificate.h"
#include "Submission.h"
#include "Constants.h"
#include "Instructor.h"

using namespace std;
// Derived Admin class
class Admin : private Person
{
private:
    int adminID;
    string department;
    string privileges;
    Course *assignedCourses[Constants::MAX_COURSES];
    Certificate *certificates[Constants::MAX_CERTIFICATES];
    Notification *notifications[Constants::MAX_NOTIFICATIONS]; // Array to store notifications
    int courseCount;
    int certificateCount;
    int notificationCount;

public:
    // ------------------------Operator overloading------------------------
    bool operator==(const Admin &obj) const
    {
        return (adminID == obj.adminID &&
                department == obj.department &&
                privileges == obj.privileges &&
                courseCount == obj.courseCount &&
                certificateCount == obj.certificateCount);
    }
    Admin &operator=(const Admin &obj)
    {
        if (this == &obj)
            return *this;

        adminID = obj.adminID;
        department = obj.department;
        privileges = obj.privileges;
        courseCount = obj.courseCount;
        certificateCount = obj.certificateCount;

        for (int i = 0; i < courseCount; i++)
        {
            assignedCourses[i] = obj.assignedCourses[i];
        }
        for (int i = 0; i < certificateCount; i++)
        {
            certificates[i] = obj.certificates[i];
        }
        return *this;
    }
    friend istream &operator>>(istream &in, Admin &obj)
    {
        cout << reset;
        cout << "Enter Admin ID: ";
        in >> obj.adminID;
        cout << "Enter Department: ";
        in.ignore();
        getline(in, obj.department);
        cout << "Enter Privileges: ";
        getline(in, obj.privileges);
        cout << "Enter Number of Assigned Courses: ";
        in >> obj.courseCount;
        for (int i = 0; i < obj.courseCount; i++)
        {
            // in >> obj.assignedCourses[i];
        }
        cout << "Enter Number of Certificates: ";
        in >> obj.certificateCount;
        for (int i = 0; i < obj.certificateCount; i++)
        {
            // in >> obj.certificates[i];
        }
        return in;
    }
    friend ostream &operator<<(ostream &out, const Admin &obj)
    {
        cout << reset;

        out << "Admin ID: " << obj.adminID << endl;
        out << "Department: " << obj.department << endl;
        out << "Privileges: " << obj.privileges << endl;
        out << "Assigned Courses: " << endl;
        for (int i = 0; i < obj.courseCount; i++)
        {
            out << obj.assignedCourses[i] << endl;
        }
        out << "Certificates: " << endl;
        for (int i = 0; i < obj.certificateCount; i++)
        {
            out << obj.certificates[i] << endl;
        }
        return out;
    }
    string operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return to_string(adminID);
        case 1:
            return department;
        case 2:
            return privileges;
        case 3:
            return to_string(courseCount);
        case 4:
            return to_string(certificateCount);
        default:
            cout << reset;

            cout << "Invalid index!!!\n";
            return "";
        }
    }
    string operator()(const string &dataMember) const
    {
        if (dataMember == "adminID")
        {
            return to_string(adminID);
        }
        else if (dataMember == "department")
        {
            return department;
        }
        else if (dataMember == "privileges")
        {
            return privileges;
        }
        else if (dataMember == "courseCount")
        {
            return to_string(courseCount);
        }
        else if (dataMember == "certificateCount")
        {
            return to_string(certificateCount);
        }
        else
        {
            cout << reset;

            return "Invalid data member!";
        }
    }
    // constructors
    Admin() : Person()
    {
        adminID = 0;
        department = "";
        privileges = "";
        courseCount = 0;
        certificateCount = 0;
        notificationCount = 0;
    }
    Admin(string n, int id, string e, int aid, string dept, string priv)
        : Person(n, id, e)
    {
        adminID = aid;
        department = dept;
        privileges = priv;
        courseCount = 0;
        certificateCount = 0;
        notificationCount = 0;
    }

    ~Admin() {}

    // functions

    void displayInfo() override
    {
        cout << reset;
        cout << "Admin Name: " << name << endl;
        cout << "Admin ID: " << adminID << endl;
        cout << "Email: " << email << endl;
        cout << "Privileges: " << privileges << endl;
        cout << "Department: " << department << endl;
    }
    string getRole() override
    {
        cout << reset;
        return "Admin";
    }

    string addCourse(string courseTitle, int courseCode, string description, int mcount)
    {
        if (courseCount < Constants::MAX_COURSES)
        {
            assignedCourses[courseCount] = new Course(courseTitle, courseCode, description);
            courseCount++;
            cout << reset;

            return "Course added successfully";
        }
        else
        {
            cout << reset;

            return "Maximum number of courses reached";
        }
    }

    string removeCourse(int courseCode)
    {
        for (int i = 0; i < courseCount; i++)
        {
            if (assignedCourses[i]->getCourseCode() == courseCode)
            {
                delete assignedCourses[i];
                assignedCourses[i] = nullptr;
                // removing deleted course from by shifting courses after deleted courses to next ind
                for (int j = i; j < courseCount - 1; j++)
                {
                    assignedCourses[j] = assignedCourses[j + 1];
                }
                assignedCourses[courseCount - 1] = nullptr;
                courseCount--;
                cout << reset;
                return "Course removed successfully";
            }
        }
        cout << reset;

        return "Course not found";
    }

    void generateReport()
    {
        cout << reset;
        cout << "Generating report for Admin: " << name << endl;
        cout << "Admin ID: " << adminID << endl;
        cout << "Department: " << department << endl;
        cout << "Privileges: " << privileges << endl;
        cout << "Assigned Courses: " << endl;
        if (courseCount == 0)
        {
            cout << "No assigned courses yet!\n";
        }

        for (int i = 0; i < courseCount; i++)
        {
            if (assignedCourses[i] != nullptr)
            {
                assignedCourses[i]->displayCourseInfo();
            }
        }
    }

    string assignInstructor(int courseCode, Instructor *instructor)
    {
        for (int i = 0; i < courseCount; i++)
        {
            if (assignedCourses[i]->getCourseCode() == courseCode)
            {
                instructor->addCourse(assignedCourses[i]);
                cout << reset;
                return "Instructor assigned successfully.";
            }
        }
        cout << reset;
        return "Course not found.";
    }

    void manageCertificates()
    {
        cout << reset;

        cout << "Managing certificates for Admin: " << name << endl;
        cout << "Certificates: " << endl;
        if (certificateCount == 0)
        {
            cout << reset;
            cout << "Admin '" << name << "' has no certificate yet...\n";
        }

        for (int i = 0; i < certificateCount; i++)
        {
            if (certificates[i] != nullptr)
            {
                certificates[i]->displayCertificateInfo();
            }
        }
    }

    void addCertificate(Certificate *certificate)
    {
        if (certificateCount < Constants::MAX_CERTIFICATES)
        {
            certificates[certificateCount] = certificate;
            certificateCount++;
            cout << reset;
            cout << "Certificate added successfully with details :\n";
            certificate->displayCertificateInfo();
        }
        else
        {
            cout << reset << "Maximum number of certificates reached\n";
        }
    }

    void removeCertificate(int certificateID)
    {
        for (int i = 0; i < certificateCount; i++)
        {
            if (certificates[i]->getCertificateID() == certificateID)
            {
                // delete certificates[i];
                // certificates[i] = nullptr;
                // Shift the remaining certificates to fill the gap
                for (int j = i; j < certificateCount - 1; j++)
                {
                    certificates[j] = certificates[j + 1];
                }
                certificates[certificateCount - 1] = nullptr;
                certificateCount--;
                cout << reset;

                cout << "Certificate removed successfully \n";
                return;
            }
        }
        cout << reset;

        cout << "Certificate not found\n";
    }

    bool sendNotification(const Notification &notification) override
    {
        cout << reset;
        cout << "Sending Notification: \n";
        cout << "ID: " << notification.getNotificationId() << endl;
        cout << "Message: " << notification.getMessage() << endl;
        cout << "Date: " << notification.getDateSent() << endl;
        return true;
    }
};

#endif