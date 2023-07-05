#include <iostream>
#include "rdb.h"
using namespace std;

void greet(string msg)
{
    cout << "********************************************\n";
    cout << "                 " << msg << endl;
    cout << "********************************************\n";
}

void printmenu()
{
    cout << "0) Exit\n";
    cout << "1) Create a new Table\n";
    cout << "2) Add a record to a Table\n";
    cout << "3) Print a Table\n";
    cout << "4) Make Union of 2 Tables\n";
    cout << "5) Make difference of 2 Tables\n";
    cout << "6) Make Cartesian Product of 2 Tables\n";
    cout << "7) Make Projection of a Table\n";
    cout << "8) Make Selection in a Table\n";
    cout << "9) Rename an attribute in Table schema\n";
    cout << "10) Make Natural of 2 Tables\n";
    cout << "11) Delete a Table\n";

}

int main()
{
    greet("Welcome");
    int choice,loop=1,ntables=0;
    Relation* data[1000];
    Relation* newR;
    do{
        cout << "----------------------\n";
        printmenu();
        cout << "Choice : ";
        cin >> choice;
        if(choice == 0)
        {
            loop=0;
        }
        else if(choice == 1)
        {
            vector <int> type; int nattr; int attrtype;
            string attrname; vector <string> attrnames;
            cout << "Enter number of Attributes : ";
            cin >> nattr;
            cout << "Enter Attribute names and types :\n";
            while(nattr--)
            {
                cin >> attrname >> attrtype;
                attrnames.push_back(attrname);
                type.push_back(attrtype);
            }
            newR = new Relation(attrnames,type);
            data[ntables] = newR; ntables++;
            cout << "New Table initialised at index " << ntables-1 << endl;
        }   
        else if(choice == 2)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                continue;
            }
            // cout << "Enter 1 to get Table schema, 0 otherwise : ";
            // int schema; cin >> schema;
            cout << "Schema of table\n";
            data[curr]->print_schema(0);
            data[curr]->addrecord();
            cout << "Record added to Table " << curr << endl;
        }
        else if(choice == 3)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                continue;
            }
            cout << "Printing Table " << curr << endl;
            data[curr]->print();
        }
        else if(choice == 4)
        {
            cout << "Select Tables : ";
            int curr1,curr2; cin >> curr1 >> curr2;
            if(curr1>=ntables)
            {
                cout << "No table at index " << curr1 <<endl;
                continue;
            }
            if(curr2>=ntables)
            {
                cout << "No table at index " << curr2 <<endl;
                continue;
            }
            if(!set_compatible(data[curr1],data[curr2])) 
            {
                cout << "The tables " << curr1<<" and "<<curr2 << " are not Union compatible\n";
                continue;
            }
            newR = Union(data[curr1],data[curr2]);
            data[ntables] = newR; ntables++;
            cout << "Union Table of tables " << curr1<<" and "<<curr2 << " saved at " <<ntables-1<<endl;
            data[ntables-1]->print();
        }
        else if(choice == 5)
        {
            cout << "Select Tables : ";
            int curr1,curr2; cin >> curr1 >> curr2;
            if(curr1>=ntables)
            {
                cout << "No table at index " << curr1 <<endl;
                continue;
            }
            if(curr2>=ntables)
            {
                cout << "No table at index " << curr2 <<endl;
                continue;
            }
            if(!set_compatible(data[curr1],data[curr2])) 
            {
                cout << "The tables " << curr1<<" and "<<curr2 << " are not Difference compatible\n";
                continue;
            }
            newR = difference(data[curr1],data[curr2]);
            data[ntables] = newR; ntables++;
            cout << "Difference Table of tables " << curr1<<" and "<<curr2 << " saved at " <<ntables-1<<endl;
            data[ntables-1]->print();
        }
        else if(choice == 6)
        {
            cout << "Select Tables : ";
            int curr1,curr2; cin >> curr1 >> curr2;
            if(curr1>=ntables)
            {
                cout << "No table at index " << curr1 <<endl;
                continue;
            }
            if(curr2>=ntables)
            {
                cout << "No table at index " << curr2 <<endl;
                continue;
            }
            newR = cartesian_product(data[curr1],data[curr2]);
            data[ntables] = newR; ntables++;
            cout << "Cartesian Product of tables " << curr1<<" and "<<curr2 << " saved at " <<ntables-1<<endl;
            data[ntables-1]->print();

        }
        else if(choice == 7)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                break;
            }
            cout << "Schema of table : \n";
            data[curr]->print_schema(0);
            cout << "Enter number of Columns : ";
            int ncolumns; cin >> ncolumns;
            string newattr;
            list<string> projectattr;
            cout << "Select the columns for projection : ";
            for(int i=0;i<ncolumns;i++)
            {
                cin >> newattr;
                projectattr.push_back(newattr);
            }
            if(!projection_compatible(data[curr],projectattr))
            {
                cout << "The columns selected are not Projection compatible\n";
                continue;
            }
            newR = projection(data[curr],projectattr);
            data[ntables] = newR; ntables++;
            cout << "Projected table saved at " <<ntables-1<<endl;
            data[ntables-1]->print();
        }
        else if(choice == 8)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                continue;
            }
            cout << "Schema of table\n";
            data[curr]->print_schema(0);
            cout << "Enter no of OR conditions : ";
            int nOR; cin >> nOR;
            DNFformula f;
            for(int i=0;i<nOR;i++)
            {
                list<tuple<string,char,Attr*>>* andlist = new list<tuple<string,char,Attr*>>;
                cout << "no of AND conditions for "<< i+1 << " OR :";
                int nAND; cin >> nAND;
                for(int j=0;j<nAND;j++)
                {
                    tuple<string,char,Attr*>* currtuple = new tuple<string,char,Attr*>;
                    cout << "Enter "<<j+1<<" comparison type : ";
                    int type; cin >> type;
                    cout << "Enter " <<j+1<< " comparison : ";
                    string attrname; char comp;
                    cin >> attrname >> comp;
                    get<0>(*currtuple) = attrname; get<1>(*currtuple) = comp;
                    if(type==1)
                    {
                        int input; cin>>input;
                        integerAttribute * newattr = new integerAttribute(1,input);
                        get<2>(*currtuple) = (Attr*)newattr;
                    }
                    if(type==2)
                    {
                        float input; cin>>input;
                        floatAttribute * newattr = new floatAttribute(2,input);
                        get<2>(*currtuple) = (Attr*)newattr;
                    }
                    if(type==3)
                    {
                        string input; cin>>input;
                        stringAttribute * newattr = new stringAttribute(3,input);
                        get<2>(*currtuple) = (Attr*)newattr;
                    }
                    andlist->push_back(*currtuple); 
                }
                f.ops.push_back(*andlist);
            }
            newR = Union(data[curr],&f);
            data[ntables] = newR; ntables++;
            cout << "Selected table saved at " <<ntables-1<<endl;
            data[ntables-1]->print();
            
        }
        else if(choice == 9)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                continue;
            }
            cout << "Schema of table : \n";
            data[curr]->print_schema(0);
            cout << "Select attr index to edit : ";
            int idx; cin >> idx;
            cout << "Enter new name : ";
            string newname; cin >> newname;
            data[curr]->setattrname(idx,newname);
        }
        else if(choice == 10)
        {
            cout << "Select Tables : ";
            int curr1,curr2; cin >> curr1 >> curr2;
            if(curr1>=ntables)
            {
                cout << "No table at index " << curr1 <<endl;
                continue;
            }
            if(curr2>=ntables)
            {
                cout << "No table at index " << curr2 <<endl;
                continue;
            }
            newR = naturaljoin(data[curr1],data[curr2]);
            data[ntables] = newR; ntables++;
            cout << "Natural Join of tables " << curr1<<" and "<<curr2 << " saved at " <<ntables-1<<endl;
            data[ntables-1]->print();
        }
        else if(choice == 11)
        {
            cout << "Select Table : ";
            int curr; cin >> curr;
            if(curr>=ntables)
            {
                cout << "No table at index " << curr <<endl;
                continue;
            }
            Relation* emptyrel = new Relation(data[curr]);
            data[curr] = emptyrel;
            cout << "Table at index "<<curr<<" deleted\n";
        }

    }while(loop);

    greet("Thank You");
    return 0;
}