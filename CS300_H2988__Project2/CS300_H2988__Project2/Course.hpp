#ifndef _Course_HPP_
#define _Course_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// Course countains, a course id, name, and PreRequisites and Print Methods for all three attributes
class Course {
public:
    string id;
    string name;
    vector<string> PreReq;
// constructors
    Course();
    Course(string id, string name, vector<string> PreReq );
    ~Course();
// Print methods
    void PrintCourse();
    void Prerequisites();
// Get Methods
    vector<string> getPreReq();
    string getName();
    string getId();
};

Course::Course() {
    id = "";
    name = "";
    PreReq = {};
}

Course::Course(string nId, string nName, vector<string> nPreReq = {} )
{
    this->id=nId;
    this->name=nName;
    this->PreReq=nPreReq;
}

Course::~Course()
{
}

void Course::PrintCourse() {

    cout <<  this->id  << ", " << this->name;
    cout << endl;
}
void Course::Prerequisites() {

    cout << "Prerequisites: ";
    for (unsigned i = 0; i < PreReq.size() ; i++) {
         cout <<PreReq[i];
         if ( i+1 == PreReq.size()) {
            break;
         }
         else {
             cout << ", ";
         }
     }
     cout << endl;

}
// Adding getter methods
string Course::getId() {
    return this->id;
}

string Course::getName() {
    return this->name;
}

vector<string> Course::getPreReq() {
    return this->PreReq;
}


// Structure for a node
struct Node
        {
        Course data;
        Node *left;
        Node *right;

        Node () {
                this->left = nullptr;
                this->right = nullptr;
        }
        Node(Course new_data){
            this->left = nullptr;
            this->right = nullptr;
            data = new_data;
        }
    };

    class BinaryCourseTree {

    private:
        void addNode(Node* node, Course nCourse);
        void InOrderSortPrint(Node* node);
        vector<string> nDegreePlan;
        vector<string> nCourseList;


    public:
        Node* root = nullptr;
        void Insert(Course nCourse);
        Course FindCourse(string course_Id);
        //Degree functions
        void ChooseDegree(string course_Id, BinaryCourseTree nCourseCatalog);
        void CompareDegreePlans(vector<string> nCourseTaken);
        void getAllCourseById(Node* node); // gets every course Id

        //setters/getters
        vector<string> getIdList();
        vector<string> getDegree();
        void setDegree(vector<string> newDegree);
        void PrintAll();
        void PrintDegree();
    };



    void BinaryCourseTree::setDegree(vector<string> newDegree) {
        this->nDegreePlan = newDegree;
    }

    vector<string> BinaryCourseTree::getDegree() {
        return nDegreePlan;
    }


    void BinaryCourseTree::Insert(Course nCourse) {

        // insert node at null if node is empty
        if (root == nullptr) {
            root = new Node(nCourse);
        }
        else {
            //**Continue donw branches if root is full
            this->addNode(root, nCourse);
        }
    };

    void BinaryCourseTree::addNode(Node* node, Course new_Course) {

        // if new course is smaller than left current node

        if (node != nullptr && node->data.id.compare(new_Course.id) > 0) {
            // if left node is empty insert node there.
            if (node->left == nullptr) {
                node->left = new Node(new_Course);
                return;
                // else left node is full check that node
            }
            else {
                this->addNode(node->left, new_Course);
            }
            // if new course is larger than current node
        }
        else if (node != nullptr && node->data.id.compare(new_Course.id) < 0) {
            // if right node is empty insert node there
            if (node->right == nullptr) {
                node->right = new Node(new_Course);
                return;
                // else right node is full then check versus that node
            }
            else {
                this->addNode(node->right, new_Course);
            }
        }
        //**TEST PRINTS
    }

    void BinaryCourseTree::PrintAll() {
        // verifys that root is not empty
        if (root != nullptr) {
            InOrderSortPrint(root);
        }
        else {
            cout << "No Data in Tree" << endl << endl;
        }
    }

    void BinaryCourseTree::InOrderSortPrint(Node* node) {

        if (node != nullptr) {
            // left to right order, recursively
            // If left go left
            InOrderSortPrint(node->left);
            // if no left print
            node->data.PrintCourse();
            // if right go right
            InOrderSortPrint(node->right);
        }

    };
    void BinaryCourseTree::getAllCourseById(Node* node) {
     

    if (node != nullptr) {
        //left to right order recusively.
        getAllCourseById(node->left); //go left

        nCourseList.push_back(node->data.getId()); //if no left get id

        getAllCourseById(node->right); //go right
    }
}
    vector<string> BinaryCourseTree::getIdList() {


        if (root != nullptr) {
            getAllCourseById(root);
        } else {
            cout << "No Data in Tree" << endl << endl;
        }
        return nCourseList;

    }

Course BinaryCourseTree::FindCourse(string course_Id) {
    Node *current = root;
    // start w/ Root

    // while not empty, search down tree
    while ( current != nullptr) {
        if (current->data.id.compare(course_Id) == 0) {
            return current->data;
        // if ID is smaller go left otherwise go right.
        }else if (course_Id.compare(current->data.id) <0 ){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Course Not Found;" << endl;

     // No data is found return empty Coursefile
     Course NotFound;
     return NotFound;
}

void BinaryCourseTree::ChooseDegree(string course_Id, BinaryCourseTree dataCatalog) {


    vector<string> PreReqList = {}; // No duplicates list
    vector<string> PreReqValdiationList = {}; //entries to be validated before entry
    int PreReqListPos = 0;
    Course currCourse = dataCatalog.FindCourse(course_Id);

    PreReqList.push_back(currCourse.getId()); // place starting class in list
    PreReqValdiationList = currCourse.getPreReq(); //place inital courses in validation loop

    while (PreReqList.size() > PreReqListPos ) { // 
        for (unsigned i = 0; i  < PreReqValdiationList.size(); i++) { 

            auto FindDups = find(PreReqList.begin(), PreReqList.end(), PreReqValdiationList.at(i)); // find 

            if (FindDups == PreReqList.end()) { // searches list if it finds reaches the end without dupblicating add to list 
                PreReqList.push_back(PreReqValdiationList.at(i));
            }
            
        }
            PreReqListPos = PreReqListPos +1 ;
            if (PreReqList.size() == PreReqListPos) {
                break;
            }
            currCourse = dataCatalog.FindCourse(PreReqList.at(PreReqListPos)); 
            PreReqValdiationList = currCourse.getPreReq(); // Sets next group of items to be validated starting at next position.
                        
        
    }
    //Print Out Results of Loops
    this->nDegreePlan = PreReqList;
}

void BinaryCourseTree::PrintDegree() {

      
    for (unsigned i = 0; i < this->nDegreePlan.size(); i++) {
        cout << this->nDegreePlan.at(i);
        if (i + 1 < this->nDegreePlan.size()) {
            cout << ",";
        }
    }

}

void BinaryCourseTree::CompareDegreePlans(vector<string> nCourseTaken) {
    vector<string> RemainingCourse = this->nDegreePlan;// Making a copy of degree plan as not to manipulate orignal choice. 
     for (unsigned i = 0; i < nCourseTaken.size(); i++) {

        auto FindDups = find(RemainingCourse.begin(),RemainingCourse.end(), nCourseTaken.at(i)); // find 

        if (FindDups != RemainingCourse.end()) { // 
            RemainingCourse.erase(FindDups);
        }

    }

    //Printing the List 
    for (unsigned i = 0; i < RemainingCourse.size(); i++) {
        cout << RemainingCourse.at(i);
        if (i + 1 < RemainingCourse.size()) {
            cout << ",";
        }
    }

}







#endif /*!_Course_HPP_*/
