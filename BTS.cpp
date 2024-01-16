#include <iostream>
#include<vector>
using namespace std;
template <class K, class V>
class Node
{
public:
    K key;
    V value;
    Node<K,V>* leftChild;
    Node<K,V>* rightChild;

    Node()
    {
        key = 0;
        value =0;
        leftChild = nullptr;
        rightChild = nullptr;
    }
    Node(K key,V value, Node<K,V>* leftChild,    Node<K,V>* rightChild)
    {
        this->key = key;
        this->value = value;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    template<class k, class v>
    friend class specialBST;
    friend class StudentList;

};
template<class K, class V>
class specialBST
{
private:
    Node<K,V> *root = nullptr;
public:
    //--------------------------------------Default constructor-------------------------------------
    specialBST()
    {
        root = nullptr;
    }
    //--------------------------------------------Insertion------------------------------------------
    //Insert Function
    bool insert(K key, V value)    //Wrpper funtion
    {
        insert(key,value,root);
    }
    bool insert(K key, V value,Node<K,V> *&node)
    {
        bool check = isDuplicate(key);
        if(check == true)     // If the key is duplicate then node cannot be inserted and will return false
        {
            cout << "It Is Duplicate, cannot be inserted " << endl;
        }
        else
        {
            cout << "Helo baby "<< endl;
            if(node == nullptr)
            {
                node = new Node<K,V>(key,value, nullptr, nullptr);
                return true;
            }
            else if(node->key > key)
            {
                insert(key,value,node->leftChild);
                rightRotate(node);
            }
            else
            {
                insert(key,value,node->rightChild);
                leftRotate(node);
            }

        }

    }
    // Functions used to bring the inserted node from leaf to root
    // rightRotate will bring from left side
    void rightRotate(Node<K,V>*& child)
    {
        // Orphan nodes are de-attached
        Node<K,V>* orphan = child->leftChild->rightChild;

        Node<K,V>* Y = child->leftChild;
        Y->rightChild = child;

        child->leftChild = orphan;
        child = Y;

    }
    // leftRotate will bring from right side
    void leftRotate(Node<K,V> *& child)
    {
        // Orphan nodes are de-attached
        Node<K,V>* orphan = child->rightChild->leftChild;

        Node<K,V>* y = child->rightChild;
        y->leftChild = child;
        child->rightChild = orphan;
        child = y;
    }
    //Finding the duplicate key
    bool isDuplicate(K key)
    {
        isDuplicate( key, root);
    }
    bool isDuplicate(K key, Node<K,V>*node)
    {
        if(node)
        {
            if(node->key == key)
            {
                return true; // If the key is duplicate
            }
            else if(node->key > key)
            {
                isDuplicate(key,node->leftChild);
            }
            else
            {
                isDuplicate(key,node->rightChild);
            }
            return true;
        }
        else
        {
            return false;     // If not duplicate
        }
    }
    //--------------------------------------------Search------------------------------------------
    Node<K,V> * search(K key)
    {
        return search( key, root);
    }
    Node<K,V> * search(K key, Node<K,V>* &node)
    {
        if(node)
        {
            if(node->key == key)
                return node;
            else if(node->key > key)
                return search(key, node->leftChild);
            else
                return search(key, node->rightChild);
        }
    }
    //--------------------------------------------Search------------------------------------------
    void Inorder()
    {
        Inorder(root);
    }
    void Inorder(Node<K,V> *node)
    {
        if(node!= nullptr)
        {
            Inorder(node->leftChild);
            cout << node->value;
            Inorder(node->rightChild);
        }

    }
    // Getting values in the vector inorder form
    vector<V>* getValuesInOrder()
    {
        //Creating vector element
        vector<V> Vec_Inorder;
        getValuesInOrder(root,Vec_Inorder);
    }
    vector<V>* getValuesInOrder(Node<K,V>*node,vector<V> Vec_Inorder)
    {
        if (node!= nullptr)
        {
            getValuesInOrder(node->leftChild);
            Vec_Inorder.push_back(node->value);
            getValuesInOrder(node->rightChild);
        }
        //Returning Inorder form in vercots
        return Vec_Inorder;

    }


    //Level wise ordering
    vector <V>* getValuesLevelWise()
    {
        //Creating vector element
        vector<V> Vec_levelOrder;
        getValuesLevelWise(root, Vec_levelOrder);
    }
    vector <V>* getValuesLevelWise(Node<K,V>* node, vector<V> Vec_levelOrder)
    {
        int lev = 1;
        while(Counting_levels(node, lev,  Vec_levelOrder))
        {
            lev++;
        }
    }
    bool Counting_levels(Node<K,V>* node, int lev, vector<V> Vec_levelOrder)
    {
        if (node == nullptr)
        {
            // Node is empty
            return false;
        }
        else if (lev == 1)
        {
            Vec_levelOrder.push_back(node->value);
            return true;
        }
        bool left = printLevel(node->left, lev - 1);
        bool right = printLevel(node->right, lev - 1);
        return left || right;
    }

    //--------------------------------------------Delete------------------------------------------
    bool Delete(K key)
    {
        if(deleteKey(key, root))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool deleteKey(K key, Node<K,V>* &node)
    {
        if (node)
        {
            if (key > node->key)
            {
                deleteKey(key, node->rightChild);
            }

            else if (key < node->key)
            {
                deleteKey(key, node->leftChild);
            }
            else
            {
                deleteNode(node);
                return true;
            }
        }

    }
    bool deleteNode(Node <K,V> *& node)
    {
        Node <K,V>*temp = node;
        if (node->leftChild == nullptr)
        {
            node = node->rightChild;
            delete temp;
        }
        else if (node->rightChild == nullptr)
        {
            node = node->leftChild;
            delete temp;
        }
        else{
            K key = Predecessor(node->leftChild);
            node->key = key;
            deleteKey(key, node->leftChild);
        }
        return true;
    }
    K Predecessor(Node<K,V>*&node)
    {
        while (node->rightChild != nullptr)
        {
            node = node->rightChild;
        }
        return node->key;
    }
//--------------------------------------------Update the node------------------------------------------
    bool updateNode(K old_key,K new_key, V new_node)
    {
        updateNode(root, old_key,new_key,new_node);
    }
    bool updateNode(Node<K,V> *node, K old_key,K new_key, V new_node)
    {
        deleteKey(old_key,root); // Delete the old keys
        insert(new_key, new_node,root);
        return true;
    }
//--------------------------------------------Destructor------------------------------------------

    ~specialBST()
    {
        Del(root);
    }
    void Del(Node <K,V>*node)
    {
        if (node)
        {
            Del(node->leftChild);
            Del(node->rightChild);
            delete node;
        }
    }
    friend class StudentList;
};

class StudentList
{
private:
    int roll_number;
    string first_name;
    string last_name;
    int batch;
    string department;
    float cgpa;
public:
    specialBST<int,StudentList> s;
    StudentList()
    {
        roll_number = 0;
        first_name = "";
        last_name = "";
        batch = 0;
        department = "";
        cgpa = 0.0;
    }
    StudentList(int roll_number ,string first_name,string last_name,int batch,string department,float cgpa)
    {
        this->roll_number = roll_number;
        this->first_name = first_name;
        this->last_name = last_name;
        this->batch = batch;
        this->department = department;
        this->cgpa = cgpa;
    }
    friend ostream & operator << (ostream &out, const StudentList &obj)
    {
        out << " Roll No : "<<obj.roll_number << endl;
        out << " First Name : " <<obj.first_name << endl;
        out << " Last Name : " <<obj.last_name<< endl;
        out << " Batch : " << obj.batch<< endl;
        out << " Department : " <<obj.department<< endl;
        out << " CGPA : " << obj.cgpa<< endl;
        cout << endl;
        return out;
    }
    void InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
    {
        StudentList Info = StudentList( rollNumber,firstName,lastName, batch, department,cgpa);
        s.insert(rollNumber,Info);
    }
    void Search_by_RollNumber(int &rollNum)
    {

        Node<int ,StudentList> *Searched = s.search(rollNum);
        if(Searched->value.roll_number == rollNum  && Searched)
        {
            cout << " Roll No : "<<Searched->value.roll_number<< endl;
            cout << " First Name : " <<Searched->value.first_name<< endl;
            cout << " Last Name : " <<Searched->value.last_name<< endl;
            cout << " Batch : " << Searched->value.batch<< endl;
            cout << " Department : " << Searched->value.department<< endl;
            cout << " CGPA : " << Searched->value.cgpa<< endl;

        }
        else
        {
            cout << rollNum << " can not be found in the class " << endl;
        }
    }

    bool Delete_Student(int roll_number)
    {
        if(s.Delete(roll_number))
        {
            cout << "\n Student Deleted Successfully,\n" << endl;
        }
        else
        {
            cout << "\n Student of this Roll Number donot found\n " << endl;
        }
    }

    void print()
    {
        s.Inorder();
    }


    bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
    {

        StudentList Info = StudentList(newRollNumber,newFirstName,newLastName, newBatch, newDepartment,newCgpa);
        s.updateNode(oldRollNumber,newRollNumber,Info);
        cout << "-Updeated-" << endl;

    }
};



int main()
{
    /* specialBST<int,int>s;
     s.insert(13,13);
     s.insert(7,7);
     s.insert(25,25);
     s.insert(13,13);
     s.insert(14,14);
     s.insert(39,39);
     s.insert(17,17);
     s.Inorder();
     s.search(15);
     s.search(25);
     s.search(4);*/

    StudentList S;
    char Char ='e';
    int roll_number, batch;
    string first_name ,last_name,department;
    float cgpa;
    while(Char !='E')
    {
        cout << "************ Menue **************"<< endl;
        cout << "---Press I to insert a new student" << endl;
        cout << "---Press D to delete a student" << endl;
        cout << "---Press S to search a student by roll number" << endl;
        cout << "---Press U to update the data of a student" << endl;
        cout << "---Press P to print all students sorted by roll number" << endl;
        cout << "---Press E to exit" << endl;
        cout << "Please enter the option : ";
        cin >> Char;

        if (Char == 'I' || Char == 'i') {
            cout << " Please enter the data of student " << endl;
            cout << " Roll Number : ";
            cin >> roll_number;
            cout << " First Name : ";
            cin >> first_name;
            cout << " Last Name : ";
            cin >> last_name;
            cout << " Batch : ";
            cin >> batch;
            cout << " Department : ";
            cin >> department;
            cout << " CGPA : ";
            cin >> cgpa;
            S.InsertNewStudent(roll_number, first_name, last_name, batch, department, cgpa);
        }
        else if (Char == 'S' || Char == 's') {
            int roll;
            cout << "\n Please enter the roll number of the student that you want to search : ";
            cin >> roll;
            S.Search_by_RollNumber(roll);
        }
        else if (Char == 'D' || Char == 'd') {
            cout << "\n Please enter the roll number of the student that you want to delete : ";
            cin >> roll_number;
            S.Delete_Student(roll_number);
        }
        else if (Char == 'U' || Char == 'u')
        {
            int old_roll_number;
            cout << " Please enter the data of new student " << endl;
            cout << "Old Roll Number : ";
            cin >> roll_number;
            cout << "New Roll Number : ";
            cin >> old_roll_number;
            cout << "New First Name : ";
            cin >> first_name;
            cout << "New Last Name : ";
            cin >> last_name;
            cout << "New Batch : ";
            cin >> batch;
            cout << "New Department : ";
            cin >> department;
            cout << "New CGPA : ";
            cin >> cgpa;
            S.updateStudent(old_roll_number,roll_number, first_name, last_name, batch, department, cgpa);
        }
        else if (Char == 'P' || Char == 'p')
        {
            S.print();
        }
    }

    return 0;
}