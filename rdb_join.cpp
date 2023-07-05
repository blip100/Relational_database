#include<bits/stdc++.h>
#include"rdb.h"


Relation * naturaljoin(Relation * R1,Relation * R2)
{
    Relation* newR2 = new Relation(R2);
    vector <int> inds;
    for(int i=0;i<R2->getnattr();i++) inds.push_back(i);
    for(auto it=R2->getbegin();it!=R2->getend();it++)
    {
        newR2->addrecord(**it,inds);
    }
    R2 = newR2;
    vector <int> dups;
    for(int i=0;i<R1->getnattr();i++)
    {
        for(int j=0;j<R2->getnattr();j++)
        {
            if(R1->getattrname(i)==R2->getattrname(j))
            {
                R2->setattrname(j,R1->getattrname(i)+"#");
                dups.push_back(i);
            }
        }
    }

    Relation * whole = cartesian_product(R1,R2);
    // cout << "Cartesian Product\n";
    // whole->print();

    for(int i=0;i<dups.size();i++)
    {
        DNFformula f;
        for(auto prec=R1->getbegin();prec!=R1->getend();prec++)
        {
            Record * rec = *prec;
            list<tuple<string,char,Attr*>>* andlist = new list<tuple<string,char,Attr*>>;
            tuple<string,char,Attr*>* currtuple = new tuple<string,char,Attr*>;
            tuple<string,char,Attr*>* currtuple2 = new tuple<string,char,Attr*>;
            get<0>(*currtuple) = R1->getattrname(dups[i]); get<0>(*currtuple2) = R1->getattrname(dups[i])+"#";
            get<1>(*currtuple) = '='; get<1>(*currtuple2) = '='; 
            // cout << get<0>(*currtuple) << " = " << get<0>(*currtuple2) << " = ";
            if(R1->gettype(i)==1)
            {
                int data = ((integerAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
                Attr* newattr = (Attr*) new integerAttribute(1,data);
                get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
                // cout<<data<<endl;
            }
            if(R1->gettype(i)==2)
            {
                float data = ((floatAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
                Attr* newattr = (Attr*) new floatAttribute(2,data);
                get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
                // cout<<data<<endl;
            }
            if(R1->gettype(i)==3)
            {
                string data = ((stringAttribute*)rec->getattr(R1->getgivenind(dups[i])))->getdata();
                Attr* newattr = (Attr*) new stringAttribute(3,data);
                get<2> (*currtuple) = newattr; get<2> (*currtuple2) = newattr;
                // cout<<data<<endl;
            }
            andlist->push_back(*currtuple); andlist->push_back(*currtuple2);
            f.ops.push_back(*andlist);
        }
        whole = Union(whole,&f);
        // whole->print();
    }
    list <string> projectattrs;
    for(int i=0;i<whole->getnattr();i++)
    {
        string temp = whole->getattrname(i);
        int test = 1;
        for(int j=0;j<dups.size();j++)
        {
            if(temp == (R1->getattrname(dups[j])+"#")) {test=0;break;}
        }
        if(test) projectattrs.push_back(temp);
    }
    whole = projection(whole,projectattrs);
    return whole;

}