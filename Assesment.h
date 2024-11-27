
#ifndef ASSESMENT_H
#define ASSESMENT_H

#include <iostream>
#include "Constants.h"
#include "Student.h"

using namespace std;

// Assessment class
class Assessment
{
private:
    int assessmentID;
    string assessmentType;
    string questions[Constants::MAX_QUESTIONS];
    string correctAnswers[Constants::MAX_QUESTIONS];
    string studentAnswers[Constants::MAX_QUESTIONS];
    int score;
    int questionCount;
    int totalMarks;

public:
    // ---------------------Operator overloading-------------------
    bool operator==(const Assessment& obj) const
    {
        return (assessmentID == obj.assessmentID &&
            assessmentType == obj.assessmentType &&
            score == obj.score &&
            questionCount == obj.questionCount &&
            totalMarks == obj.totalMarks);
    }
    Assessment& operator=(const Assessment& obj)
    {
        assessmentID = obj.assessmentID;
        assessmentType = obj.assessmentType;
        score = obj.score;
        questionCount = obj.questionCount;
        totalMarks = obj.totalMarks;
        for (int i = 0; i < questionCount; ++i)
        {
            questions[i] = obj.questions[i];
            correctAnswers[i] = obj.correctAnswers[i];
            studentAnswers[i] = obj.studentAnswers[i];
        }
        return *this;
    }
    friend istream& operator>>(istream& in, Assessment& obj)
    {
        cout << "Enter Assessment ID: ";
        in >> obj.assessmentID;
        cout << "Enter Assessment Type: ";
        in.ignore();
        getline(in, obj.assessmentType);
        cout << "Enter Total Marks: ";
        in >> obj.totalMarks;
        obj.score = 0;
        obj.questionCount = 0;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Assessment& obj)
    {
        out << "Assessment ID: " << obj.assessmentID << endl;
        out << "Assessment Type: " << obj.assessmentType << endl;
        out << "Total Marks: " << obj.totalMarks << endl;
        out << "Score: " << obj.score << endl;
        out << "Questions:" << endl;
        for (int i = 0; i < obj.questionCount; ++i)
        {
            out << "Question " << (i + 1) << ": " << obj.questions[i] << endl;
            out << "Correct Answer: " << obj.correctAnswers[i] << endl;
        }
        return out;
    }
    string operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return to_string(assessmentID);
        case 1:
            return assessmentType;
        case 2:
            return to_string(score);
        case 3:
            return to_string(questionCount);
        case 4:
            return to_string(totalMarks);
        default:
            cout << "Invalid index!!!\n";
            return "";
        }
    }
    string operator()(const string& dataMember) const
    {
        if (dataMember == "assessmentID")
        {
            return to_string(assessmentID);
        }
        else if (dataMember == "assessmentType")
        {
            return assessmentType;
        }
        else if (dataMember == "score")
        {
            return to_string(score);
        }
        else if (dataMember == "questionCount")
        {
            return to_string(questionCount);
        }
        else if (dataMember == "totalMarks")
        {
            return to_string(totalMarks);
        }
        else
        {
            return "Invalid data member!";
        }
    }

    // constructors
    Assessment()
    {
        assessmentID = 0;
        totalMarks = 0;
        score = 0;
        questionCount = 0;
        assessmentType = "";
    }
    Assessment(int id, string type, int marks)
    {
        this->assessmentID = id;
        this->assessmentType = type;
        this->totalMarks = marks;
        score = 0;
        questionCount = 0;
    }
    ~Assessment() {};

    void addQuestion(const string& question, const string& correctAnswer)
    {
        if (questionCount < Constants::MAX_QUESTIONS)
        {
            questions[questionCount] = question;
            correctAnswers[questionCount] = correctAnswer;
            questionCount++;
        }
        else
        {
            cout << "Maximum number of questions reached." << endl;
        }
    }

    void takeAssessment(Student& student)
    {
        score = 0;

        cout << "Taking Assessment: " << assessmentType << " (ID: " << assessmentID << ")" << endl;
        for (int i = 0; i < questionCount; ++i)
        {
            cout << "Question " << (i + 1) << ": " << questions[i] << endl;
            cout << "Your answer: ";
            cin >> studentAnswers[i];

            if (studentAnswers[i] == correctAnswers[i])
            {
                score += totalMarks / questionCount;
            }
        }

        cout << "Assessment completed. Your score is: " << score << " out of " << totalMarks << endl;
        student.addScore(assessmentID, score);
    }

    void viewScore(const Student& student) const
    {
        int studentScore = student.getScore(assessmentID);
        cout << "Assessment ID: " << assessmentID << endl;
        cout << "Assessment Type: " << assessmentType << endl;
        cout << "Total Marks: " << totalMarks << endl;
        cout << "Your Score: " << studentScore << " out of " << totalMarks << endl;
        cout << "Questions and Your Answers:" << endl;
        for (int i = 0; i < questionCount; ++i)
        {
            cout << "Question " << (i + 1) << ": " << questions[i] << endl;
            cout << "Your Answer: " << studentAnswers[i] << endl;
            cout << "Correct Answer: " << correctAnswers[i] << endl;
            cout << "Status: " << (studentAnswers[i] == correctAnswers[i] ? "Correct" : "Incorrect") << endl;
        }
    }

    void displayAssessmentInfo() const
    {
        cout << "Assessment ID: " << assessmentID << endl;
        cout << "Assessment Type: " << assessmentType << endl;
        cout << "Total Marks: " << totalMarks << endl;
        cout << "Questions:" << endl;
        for (int i = 0; i < questionCount; ++i)
        {
            cout << "Question " << (i + 1) << ": " << questions[i] << endl;
            cout << "Correct Answer: " << correctAnswers[i] << endl;
        }
    }
};

#endif