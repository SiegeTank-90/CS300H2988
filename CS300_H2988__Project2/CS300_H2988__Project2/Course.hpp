#ifndef _Course_HPP_
#define _Course_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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
        int height; // marker to build a balanced tree to increase search times. 


        Node () {
                this->left = nullptr;
                this->right = nullptr;
                this->height = 1;
                this->data = Course();
        }
        Node(Course new_data){
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
            data = new_data;
        }
    };

    class BinaryCourseTree {

    private:
        Node* addNode(Node *node, Course nCourse);
        void InOrderSortPrint(Node* node);
        vector<string> nDegreePlan;
        vector<string> nCourseList;

        //Balancing Helper Functions 
        int getheight(Node *lowerLevelNode);
        int getBalance(Node *ancestorNode);
        Node *rightRotate(Node *y);
        Node *leftRotate(Node *x);
        
    public:
        Node *root = nullptr;
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
    
    int BinaryCourseTree::getheight(Node *lowerLevelNode) {
        if (lowerLevelNode == NULL) {
            return 0;
        }
        return lowerLevelNode->height;
    }

    int BinaryCourseTree::getBalance(Node *ancestorNode) {
        if (ancestorNode == NULL)
            return 0;
        return getheight(ancestorNode->left) - getheight(ancestorNode->right);
    }

    inline Node* BinaryCourseTree::rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        //perform rotation  (Look here for Rotational Shifts)
        x->right = y;
        y->left = T2;

        //update heights
        y->height = 1 + max(getheight(y->left), getheight(y->right));
        x->height = 1 + max(getheight(x->left), getheight(x->right));

        return x;
    }

    inline Node* BinaryCourseTree::leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        //perform rotation (Look here for Rotational Shifts)
        y->left = x;
        x->right = T2;

        //update heights
        x->height = 1 + max(getheight(x->left), getheight(x->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        return y;
    }
   

    void BinaryCourseTree::Insert(Course nCourse) {

           
            //**Continue down branches if root is full
            root =  addNode(root, nCourse);

    };

   


    Node* BinaryCourseTree::addNode(Node *node, Course new_Course) {


        // insert node at null if node is empty
        if (node == NULL)  {
            return (new Node(new_Course));
         }

        // if new course is smaller than left current node
        if (node->data.id.compare(new_Course.id) < 0) {
            // if left node is empty insert node there.
         
                node->left = addNode(node->left, new_Course);
         
            // if new course is larger than current node
        }
        else if (node->data.id.compare(new_Course.id) > 0) {
            // if right node is empty insert node there
         
                node->right = addNode(node->right, new_Course);  
        }
        else {
            return node;
        }
        
        // update hieght of this ancestor base on nodes below
       
          node->height = 1 + max(getheight(node->left), getheight(node->right));
  
        int balance = getBalance(node);
        //decide rotation case
        if (balance > 1) {

            //Left Left Case
            if (node->data.id.compare(node->left->data.id) < 0) {
                return rightRotate(node);

            /* Left Right Case  */
            } else if (node->data.id.compare(node->left->data.id) > 0 ) {
                node->left = leftRotate(node->left);
                return rightRotate(node);

            }

        }
        else if (balance < -1 ) {

            // Right Right Case
            if (node->data.id.compare(node->right->data.id) > 0) {
                return leftRotate(node);

                } /* Right Left Case  */
            else if (node->data.id.compare(node->right->data.id) < 0) {
                node->right = rightRotate(node->right);
               return leftRotate(node);

            }

        }

        return node;

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
            InOrderSortPrint(node->left);
            node->data.PrintCourse();
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
        if (course_Id.compare(current->data.getId()) == 0) {
            return current->data;
        // if ID is smaller go left otherwise go right.
        }
        if (course_Id.compare(current->data.getId()) > 0 ){
            current = current->left;
        }if (course_Id.compare(current->data.getId()) < 0 ) {
            current = current->right;
        }
    }

     // No data is found return empty Coursefile
     Course NotFound;
     return NotFound;
}

void BinaryCourseTree::ChooseDegree(string course_Id, BinaryCourseTree dataCatalog) {


    vector<string> PreReqList = {}; // validated duplicates list
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

void BinaryCourseTree::PrintDegree() { //Prints every degree program

      
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

        auto FindDups = find(RemainingCourse.begin(),RemainingCourse.end(), nCourseTaken.at(i)); // find duplicates

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
