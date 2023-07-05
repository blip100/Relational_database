#include<bits/stdc++.h>
using namespace std;
#define intAttr integerAttribute
#define floatAttr floatAttribute
#define stringAttr stringAttribute


class Attr { //Base class for attributes
// Add operators for different attribute type in derived classes
    int type;
public: 
    Attr(int type_):type(type_){}
    int gettype() const{return type;}
    virtual void print(){}
    virtual bool operator== (const Attr & right) = 0;
    virtual bool operator!= (const Attr & right) = 0;
    virtual bool operator<  (const Attr & right) = 0;
    virtual bool operator<= (const Attr & right) = 0;
    virtual bool operator>  (const Attr & right) = 0;
    virtual bool operator>= (const Attr & right) = 0;
};


class integerAttribute : public Attr
{
    int data;
public:
    auto getdata() {return data;}
    integerAttribute(int type,int data_): Attr(type),data(data_){}
    integerAttribute(integerAttribute& oldattr):Attr(1),data(oldattr.getdata()){}
    bool operator==(const Attr& right)
    {
        if(right.gettype()!=1)return false;
        integerAttribute* newright = (integerAttribute*) &right;
        
        if(newright->getdata() == this->getdata()) return true;
        return false;

    }
    bool operator!=(const Attr& right)
    {
        if(*this==right) return false;
        return true;
    }
    bool operator< (const Attr& right)
    {
        if(right.gettype()!=1)return false;
        integerAttribute* newright = (integerAttribute*) &right;
        
        if(this->getdata() < newright->getdata()) return true;
        return false;
    }
    bool operator<=(const Attr& right)
    {
        if(*this==right) return true;
        if(*this< right) return true;
        return false;
    }
    bool operator> (const Attr& right)
    {
        if(right.gettype()!=1)return false;
        if(*this<=right) return false;
        return true;
    }
    bool operator>=(const Attr& right)
    {
        if(right.gettype()!=1)return false;
        if(*this<right) return false;
        return true;
    }
    void print()
    {
        printf("%15d|",this->getdata());
        // cout << this->getdata() << " ";
    }
};

class floatAttribute : public Attr
{
    float data;
public:
    auto getdata() {return data;}
    floatAttribute(int type,float data_): Attr(type),data(data_){}
    floatAttribute(floatAttribute& oldattr):Attr(2),data(oldattr.getdata()){}
    bool operator==(const Attr& right)
    {
        if(right.gettype()!=2)return false;
        floatAttribute* newright = (floatAttribute*) &right;
        
        if(newright->getdata() == this->getdata()) return true;
        return false;

    }
    bool operator!=(const Attr& right)
    {
        if(*this==right) return false;
        return true;
    }
    bool operator< (const Attr& right)
    {
        if(right.gettype()!=2)return false;
        floatAttribute* newright = (floatAttribute*) &right;
        
        if(this->getdata() < newright->getdata()) return true;
        return false;

    }
    bool operator<=(const Attr& right)
    {
        if(*this==right) return true;
        if(*this< right) return true;
        return false;
    }
    bool operator> (const Attr& right)
    {
        if(right.gettype()!=2)return false;
        if(*this<=right) return false;
        return true;
    }
    bool operator>=(const Attr& right)
    {
        if(right.gettype()!=2)return false;
        if(*this<right) return false;
        return true;
    }
    void print()
    {
        printf("%15f|",this->getdata());
        // cout << this->getdata() << " ";
    }
};

class stringAttribute : public Attr
{
    string data;
public:
    auto getdata() {return data;}
    stringAttribute(int type,string data_): Attr(type),data(data_){}
    stringAttribute(stringAttribute &oldattr): Attr(3),data(oldattr.getdata()){}
    bool operator==(const Attr& right)
    {
        if(right.gettype()!=3)return false;
        stringAttribute* newright = (stringAttribute*) &right;
        
        if(newright->getdata() == this->getdata()) return true;
        return false;
    }
    bool operator!=(const Attr& right)
    {
        if(*this==right) return false;
        return true;
    }
    bool operator< (const Attr& right)
    {
        if(right.gettype()!=3)return false;
        stringAttribute* newright = (stringAttribute*) &right;
        
        if(this->getdata() < newright->getdata()) return true;
        return false;
    }
    bool operator<=(const Attr& right)
    {
        if(*this==right) return true;
        if(*this< right) return true;
        return false;
    }
    bool operator> (const Attr& right)
    {
        if(right.gettype()!=3)return false;
        if(*this<=right) return false;
        return true;
    }
    bool operator>=(const Attr& right)
    {
        if(right.gettype()!=3)return false;
        if(*this<right) return false;
        return true;
    }
    void print()
    {
        cout << this->getdata();
        for(int i=15-this->getdata().size();i>0;i--) printf(" ");
        printf("|");
    }
};



class Record { //storing data for each record
    vector <Attr *> attrptr;
    int size;
    //methods
    
public:
    int getsize() {return size;}
    Attr* getattr(int idx) {return attrptr[idx];}
    Record():size(0){};
    Record(Record &oldrec):size(0){
        for(int i=0;i<oldrec.getsize();i++)
        {
            if((oldrec.attrptr[i])->gettype()==1)
            {
                addattr(((integerAttribute*)oldrec.attrptr[i])->getdata());
            }
            if((oldrec.attrptr[i])->gettype()==2)
            {
                addattr(((floatAttribute*)oldrec.attrptr[i])->getdata());
            }
            if((oldrec.attrptr[i])->gettype()==3)
            {
                addattr(((stringAttribute*)oldrec.attrptr[i])->getdata());
            }
        }
    }
    Record(Record &oldrec,Record& oldrec2):size(0){
        for(int i=0;i<oldrec.getsize();i++)
        {
            if((oldrec.attrptr[i])->gettype()==1)
            {
                addattr(((integerAttribute*)oldrec.attrptr[i])->getdata());
            }
            if((oldrec.attrptr[i])->gettype()==2)
            {
                addattr(((floatAttribute*)oldrec.attrptr[i])->getdata());
            }
            if((oldrec.attrptr[i])->gettype()==3)
            {
                addattr(((stringAttribute*)oldrec.attrptr[i])->getdata());
            }
        }
        for(int i=0;i<oldrec2.getsize();i++)
        {
            if((oldrec2.attrptr[i])->gettype()==1)
            {
                addattr(((integerAttribute*)oldrec2.attrptr[i])->getdata());
            }
            if((oldrec2.attrptr[i])->gettype()==2)
            {
                addattr(((floatAttribute*)oldrec2.attrptr[i])->getdata());
            }
            if((oldrec2.attrptr[i])->gettype()==3)
            {
                addattr(((stringAttribute*)oldrec2.attrptr[i])->getdata());
            }
        }

    }
    
    Record(Record &oldrec,vector <int> inds):size(0){
        for(int i=0;i<inds.size();i++)
        {
            if((oldrec.attrptr[inds[i]])->gettype()==1)
            {
                addattr(((integerAttribute*)oldrec.attrptr[inds[i]])->getdata());
            }
            if((oldrec.attrptr[inds[i]])->gettype()==2)
            {
                addattr(((floatAttribute*)oldrec.attrptr[inds[i]])->getdata());
            }
            if((oldrec.attrptr[inds[i]])->gettype()==3)
            {
                addattr(((stringAttribute*)oldrec.attrptr[inds[i]])->getdata());
            }
        }
    }
    bool operator==(Record &rec2)
    {
        Record * right = &rec2;
        if(this->getsize()!=right->getsize()) return false;
        for(int i=0;i<this->getsize();i++)
        {
            if(*this->attrptr[i]!=*right->attrptr[i]) return false;
        }
        return true;

    }
    void addattr(int idata)
    {
        integerAttribute* newattr = new integerAttribute(1,idata);
        attrptr.push_back((Attr*)newattr);
        size++;
    }
    void addattr(float fdata)
    {
        floatAttribute* newattr = new floatAttribute(2,fdata);
        attrptr.push_back((Attr*)newattr);
        size++;
    }
    void addattr(string sdata)
    {
        stringAttribute* newattr = new stringAttribute(3,sdata);
        attrptr.push_back((Attr*)newattr);
        size++;
    }
    void print()
    {
        for(int i=0;i<size;i++)
        {
            attrptr[i]->print();
        }
        cout << endl;
    }
    void print(vector <int> inds)
    {
        printf("|");
        for(int i=0;i<size;i++)
        {
            attrptr[inds[i]]->print();
        }
        cout << endl;
    }
};


class Relation { // storing a relation
 int nattr, nrecs; // number of attributes and records
 vector <string> attrnames; // schema
 vector <int> type;
 vector <int> attrinds; // mapping schema to indices
 vector <int> giveninds;
 list <Record *> recs; // list of records
 // methods

public:
    int getnattr(){return nattr;}
    int getnrecs(){return nrecs;}
    string getattrname(int idx) {return attrnames[idx];}
    void setattrname(int idx,string newname) {attrnames[idx]=newname;}
    int getattrind(int idx) {return attrinds[idx];}
    int getgivenind(int idx) {return giveninds[idx];}
    int gettype(int idx) {return type[idx];}
    Record* getrecord(int _i){
        auto it = recs.begin();
        for(int i=0; i<_i; i++){
            ++it;
        }
        return *it;
    }
    auto getbegin() {return recs.begin();}
    auto getend() {return recs.end();}
    // Record* getrecord(int idx){return recs[idx]};

    
    Relation(vector <string> names,vector <int> type_){
        nattr = names.size(); nrecs=0;
        vector <string> sortednames;
        for(int i=0;i<nattr;i++) 
        {
            type.push_back(type_[i]); 
            attrnames.push_back(names[i]);
            sortednames.push_back(names[i]);
        }

        sort(sortednames.begin(),sortednames.end());
        for(int i=0;i<nattr;i++)
        {
            for(int j=0;j<nattr;j++)
            {
                if(sortednames[i]==names[j]) {attrinds.push_back(j);break;}
            }
        }
        for(int i=0;i<nattr;i++)
        {
            for(int j=0;j<nattr;j++)
            {
                if(names[i]==sortednames[j]) {giveninds.push_back(j);break;}
            }
        }

    }
    
    Relation(Relation * R1)
    {
        // vector <string> attrnames; vector <int> type;
        for(int i=0;i<R1->getnattr();i++) 
        {
            type.push_back(R1->gettype(i));
            attrnames.push_back(R1->getattrname(i));
            giveninds.push_back(R1->getgivenind(i));
            attrinds.push_back(R1->getattrind(i));
        }
        nattr = R1->getnattr(); nrecs = 0;
        // Relation * newR = new Relation(attrnames,type);
    }
    void addrecord()
    {
        Record * newrec = new Record;
        cout << "Enter Record : ";
        for(int i=0;i<type.size();i++)
        {
            if(type[i]==1) 
            {
                int input; cin>>input;
                newrec->addattr(input);
            }
            if(type[i]==2)
            {
                float input; cin>>input;
                newrec->addattr(input);
            }
            if(type[i]==3)
            {
                string input; cin>>input;
                newrec->addattr(input);
            }
        }
        Record * sortednewrec = (Record*) new Record(*newrec,attrinds);
        addrecord(sortednewrec);
    }

    void addrecord(Record * rec)
    {
        recs.push_back(rec);
        nrecs++;
    }

    void addrecord(Record &oldrec,vector <int> inds)
    {
        Record* newrec = new Record(oldrec,inds);
        addrecord(newrec);
    }
    void addrecord(Record &oldrec)
    {
        Record* newrec = new Record(oldrec,attrinds);
        addrecord(newrec);
    }

    void print_horizontal()
    {
        cout << " ";
        for(int i=16*nattr;i>0;i--) cout << "-";
        cout << endl;
    }
    void print()
    {
        // print_horizontal();
        print_schema(12);
        // print_horizontal();
        for(auto i=recs.begin();i!=recs.end();i++)
        {
            (*i)->print(giveninds);
        }
        cout << endl;
        // print_horizontal();
    }
    void print_schema(int len)
    {
        printf("|");
        for(int i=0;i<getnattr();i++)
        {
            cout << getattrname(i) <<"("<<gettype(i)<<")";
            for(int j=len-getattrname(i).size();j>0;j--) printf(" ");
            printf("|");
        }
        cout << endl;
    }
};
typedef struct DNFformula { 
    list <list <tuple <string, char, Attr *> > > ops; 
}DNFformula;

Relation * naturaljoin(Relation * R1,Relation * R2);
Relation* cartesian_product(Relation* R1,Relation* R2);
Relation * projection(Relation * R1, list<string> projectattrs);
bool projection_compatible(Relation * R1,list<string> projectattrs);
Relation * difference(Relation * R1, Relation * R2);
Relation * Union(Relation* R1,DNFformula *f);
Relation * Union(Relation * R1, Relation * R2);
bool set_compatible(Relation* R1,Relation* R2);









