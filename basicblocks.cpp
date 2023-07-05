#include <iostream>
#include "rdb.h"
using namespace std;


bool set_compatible(Relation* R1,Relation* R2)
{
    if(R1->getnattr() != R2->getnattr()) return false;
    int idx1,idx2;
    for(int i=0;i<R1->getnattr();i++)
    {
        idx1 = R1->getattrind(i); idx2 = R2->getattrind(i);
        if(R1->gettype(idx1) != R2->gettype(idx2)) return false;
        if(R1->getattrname(idx1) != R2->getattrname(idx2)) return false;
    }
    return true;
}

Relation * Union(Relation * R1, Relation * R2)
{
    vector <string> attrnames; vector <int> type;
    for(int i=0;i<R1->getnattr();i++) 
    {
        type.push_back(R1->gettype(i));
        attrnames.push_back(R1->getattrname(i));
    }
    Relation * newR = new Relation(attrnames,type);

    for(auto i=R1->getbegin();i!=R1->getend();i++)
    {
        auto j = R2->getbegin();
        for(;j!=R2->getend();j++)
        {
            if(**i == **j) break;
        }
        if(j != R2->getend()) continue;
        newR->addrecord(*i);
    }
    for(auto j=R2->getbegin();j!=R2->getend();j++)
    {
        newR->addrecord(*j);
    }
    return newR;
}

Relation * Union(Relation* R1,DNFformula *f)
{
    int idx;
    vector <int> inds;
    for(int i=0;i<R1->getnattr();i++) inds.push_back(i);
    Relation * newR = new Relation(R1);
    for(auto prec = R1->getbegin();prec!=R1->getend();prec++)
    {
        Record * rec = *prec;
        // cout << "Curr record : ";
        // rec->print();
        for(auto OR=f->ops.begin(); OR!=f->ops.end();OR++)
        {
            int test = 1;
            for(auto AND = OR->begin(); AND!=OR->end() ; AND++)
            {
                // cout << " curr comp : "<<get<0>(*AND)<<get<1>(*AND);
                // get<2>(*AND)->print();
                for(idx=0;idx<R1->getnattr();idx++)
                {
                    if(R1->getattrname(idx) == get<0>(*AND)) break;
                }
                idx = R1->getgivenind(idx);
                // cout << "Attr : "; rec->getattr(idx)->print();
                if(get<1>(*AND) == '=')
                {
                    if(*rec->getattr(idx) != *get<2>(*AND) ) {test=0;break;}
                }
                if(get<1>(*AND) == '<')
                {
                    if(*rec->getattr(idx) >= *get<2>(*AND) ) {test=0;break;}
                }
                if(get<1>(*AND) == '>')
                {
                    if(*rec->getattr(idx) <= *get<2>(*AND) ) {test=0;break;}
                }
            }
            if(test==0) {continue;}
            // cout << "succ";
            newR->addrecord(*rec,inds);
            // cout << "ess";
            break;
        }
    }
    return newR;
}

Relation * difference(Relation * R1, Relation * R2)
{
    vector <string> attrnames; vector <int> type;
    for(int i=0;i<R1->getnattr();i++) 
    {
        type.push_back(R1->gettype(i));
        attrnames.push_back(R1->getattrname(i));
    }
    Relation * newR = new Relation(attrnames,type);

    for(auto i=R1->getbegin();i!=R1->getend();i++)
    {
        auto j = R2->getbegin();
        for(;j!=R2->getend();j++)
        {
            if(**i == **j) break;
        }
        if(j != R2->getend()) continue;
        newR->addrecord(*i);
    }
    return newR;
}

bool projection_compatible(Relation * R1,list<string> projectattrs)
{
    for(auto i=projectattrs.begin();i!=projectattrs.end();i++)
    {
        int test = 0;
        for(int j=0;j<R1->getnattr();j++)
        {
            if(*i==R1->getattrname(j)) {test=1;break;}
        }
        if(test==0) return false;
    }
    return true;
}

Relation * projection(Relation * R1, list<string> projectattrs)
{
    vector <string> newattrnames;
    vector <int> type;
    for(auto i=projectattrs.begin();i!=projectattrs.end();i++)
    {
        newattrnames.push_back(*i);
        for(int j=0;j<R1->getnattr();j++)
        {
            if(*i==R1->getattrname(j)) {type.push_back(R1->gettype(j));break;}
        }
    }

    Relation* newR = new Relation(newattrnames,type);
    sort(newattrnames.begin(),newattrnames.end());
    vector <string> oldattrnames;
    vector <int> inds;
    for(int i=0;i<R1->getnattr();i++)
    {
        string temp = R1->getattrname(R1->getattrind(i));
        oldattrnames.push_back(temp);
        // int j=newattrnames.size()-1;
        // for(;j>-1;j--)
        // {
        //     if(temp==newattrnames[j]) break;
        // }
        // if(j==-1) continue;
        // inds.push_back(R1->getattrind(i));
    }
    for(int i=0;i<newattrnames.size();i++)
    {
        for(int j=0;j<oldattrnames.size();j++)
        {
            if(newattrnames[i]==oldattrnames[j]) 
            {
                inds.push_back(j);
                break;
            }
        }
    }
    cout << "indices : ";
    for(int i=0;i<inds.size();i++) cout <<inds[i] << " ";
    cout << endl;
    for(auto i=R1->getbegin();i!=R1->getend();i++)
    {
        newR->addrecord(**i,inds);
    }
    return newR;
}


Relation* cartesian_product(Relation* R1,Relation* R2)
{
    vector <string> sattrnames1, sattrnames2;
    for(int i=0;i<R1->getnattr();i++) sattrnames1.push_back(R1->getattrname(R1->getattrind(i)));
    for(int i=0;i<R2->getnattr();i++) sattrnames2.push_back(R2->getattrname(R2->getattrind(i)));

    vector <int> inds1, inds2;
    for(int i=0;i<R1->getnattr();i++)
    {
        string temp = R1->getattrname(i);
        for(int j=0;j<R1->getnattr();j++)
        {
            if(sattrnames1[j]==temp) inds1.push_back(j);
        }
    }
    for(int i=0;i<R2->getnattr();i++)
    {
        string temp = R2->getattrname(i);
        for(int j=0;j<R2->getnattr();j++)
        {
            if(sattrnames2[j]==temp) inds2.push_back(j);
        }
    }
    vector <string> attrnames,sortedattrnames; //vector <int> attrinds;
    vector <int> type;
    for(int i=0;i<R1->getnattr();i++) 
    {
        attrnames.push_back(R1->getattrname(i));
        type.push_back(R1->gettype(i));
        // sortedattrnames.push_back(R1->getattrname(i));
    }
    for(int i=0;i<R2->getnattr();i++)
    {
        attrnames.push_back(R2->getattrname(i));
        type.push_back(R2->gettype(i));
        // sortedattrnames.push_back(R2->getattrname(i));
    }
    // sort(sortedattrnames.begin(),sortedattrnames.end());
    
    // for(int i=0;i<sortedattrnames.size();i++)
    // {
    //     for(int j=0;j<attrnames.size();j++)
    //     {
    //         if(sortedattrnames[i]==attrnames[j]) attrinds.push_back(j);
    //     }
    // }

    Relation* newR = new Relation(attrnames,type);
    for(auto i=R1->getbegin();i!=R1->getend();i++)
    {
        Record * record1 = new Record(**i,inds1);
        for(auto j=R2->getbegin();j!=R2->getend();j++)
        {
            Record * record2 = new Record(**j,inds2);
            // cout << "Record 1 :"; record1->print();
            // cout << "Record 2 :"; record2->print();
            Record * newrec = new Record(*record1,*record2);
            // cout << "Record 1+2 :"; newrec->print();
            newR->addrecord(*newrec);
        }
    }
    return newR;
}




// Relation * naturaljoin(Relation * R1,Relation * R2)
// {
//     Relation* newR2 = new Relation(R2);
//     vector <int> inds;
//     for(int i=0;i<R2->getnattr();i++) inds.push_back(i);
//     for(auto it=R2->getbegin();it!=R2->getend();it++)
//     {
//         newR2->addrecord(**it,inds);
//     }
//     R2 = newR2;
//     vector <int> dups;
//     for(int i=0;i<R1->getnattr();i++)
//     {
//         for(int j=0;j<R2->getnattr();j++)
//         {
//             if(R1->getattrname(i)==R2->getattrname(j))
//             {
//                 R2->setattrname(j,R1->getattrname(i)+"#");
//                 dups.push_back(i);
//             }
//         }
//     }

//     Relation * whole = cartesian_product(R1,R2);
//     // cout << "Cartesian Product\n";
//     // whole->print();

//     for(int i=0;i<dups.size();i++)
//     {
//         DNFformula f;
//         for(auto prec=R1->getbegin();prec!=R1->getend();prec++)
//         {
//             Record * rec = *prec;
//             list<tuple<string,char,Attr*>>* andlist = new list<tuple<string,char,Attr*>>;
//             tuple<string,char,Attr*>* currtuple = new tuple<string,char,Attr*>;
//             tuple<string,char,Attr*>* currtuple2 = new tuple<string,char,Attr*>;
//             get<0>(*currtuple) = R1->getattrname(dups[i]); get<0>(*currtuple2) = R1->getattrname(dups[i])+"#";
//             get<1>(*currtuple) = '='; get<1>(*currtuple2) = '='; 
//             // cout << get<0>(*currtuple) << " = " << get<0>(*currtuple2) << " = ";
//             if(R1->gettype(i)==1)
//             {
//                 int data = ((integerAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
//                 Attr* newattr = (Attr*) new integerAttribute(1,data);
//                 get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
//                 // cout<<data<<endl;
//             }
//             if(R1->gettype(i)==2)
//             {
//                 float data = ((floatAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
//                 Attr* newattr = (Attr*) new floatAttribute(2,data);
//                 get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
//                 // cout<<data<<endl;
//             }
//             if(R1->gettype(i)==3)
//             {
//                 string data = ((stringAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
//                 Attr* newattr = (Attr*) new stringAttribute(3,data);
//                 get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
//                 // cout<<data<<endl;
//             }
//             andlist->push_back(*currtuple); andlist->push_back(*currtuple2);
//             f.ops.push_back(*andlist);
//         }
//         whole = Union(whole,&f);
//         // whole->print();
//     }
//     list <string> projectattrs;
//     for(int i=0;i<whole->getnattr();i++)
//     {
//         string temp = whole->getattrname(i);
//         int test = 1;
//         for(int j=0;j<dups.size();j++)
//         {
//             if(temp == (R1->getattrname(dups[j])+"#")) {test=0;break;}
//         }
//         if(test) projectattrs.push_back(temp);
//     }
//     whole = projection(whole,projectattrs);
//     return whole;

// }
/*
int main()
{
    vector <int> type;
    vector <string> attrnames;
    attrnames.push_back("Name");attrnames.push_back("RollNo");
    type.push_back(3),type.push_back(1);
    Relation* newR = new Relation(attrnames,type);

    cout << "Choice : ";
    int input; cin>>input;
    while(input)
    {
        if(input==1)
        {
            newR->addrecord();
        }
        if(input==2)
        {
            newR->print();
        }
        cout << "Choice :";
        cin >> input;
    }
    // if(*ptr1 >= *ptr2)
    // {
    //     cout <<">=" <<endl;
    // }
}*/