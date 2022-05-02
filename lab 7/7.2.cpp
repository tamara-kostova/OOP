    #include<iostream>
    #include <cstring>
    using namespace std;

    class Number {
        public:
        virtual double doubleValue() =0 ;
        virtual int intValue() = 0;
        virtual void print() = 0;
    };

        bool operator ==(Number *n1,Number &n2){
            return (n1->doubleValue() == n2.doubleValue() && n1->intValue() == n2.intValue());
        }

    class Integer : public Number {
        private:
        int broj;

        public:
        Integer (int broj=0){
            this->broj=broj;
        }
        double doubleValue(){
            return (double)broj;
        }
        int intValue(){
            return broj;
        }
        void print(){
            cout<<"Integer: "<<broj<<endl;
        }
    };

    class Double : public Number{
        private:
        double broj;

        public:
        Double (double broj=0){
            this->broj=broj;
        }
        double doubleValue(){
            return broj;
        }
        int intValue(){
            return (int)broj;
        }
        void print(){
            cout<<"Double: "<<broj<<endl;
        }
    };

    class Numbers{
        private:
        int broj;
        Number **broevi;
        void copy (const Numbers &n){
            broj=n.broj;
            broevi = new Number *[broj];
            for (int i=0; i<broj; i++)
                broevi[i]=n.broevi[i];
        }
        public:
        Numbers(){
            broj=0;
            broevi = new Number*[0];
        }

        Numbers(const Numbers &n){
            copy(n);
        }

        Numbers operator = (const Numbers &n){
            if (this!=&n){
                delete [] broevi;
                copy (n);
            }
            return *this;
        }

        ~Numbers(){
            delete [] broevi;
        }

        Numbers &operator += (Number *n){
            for (int i=0; i<broj; i++)
                if (broevi[i]==*n)
                    return *this;
            Number ** tmp = new Number*[broj+1];
            for (int i=0; i<broj; i++)
                tmp[i]=broevi[i];
            tmp[broj++]=n;
            delete [] broevi;
            broevi=tmp;
            return *this;
        }

        void statistics() {
            cout<<"Count of numbers: "<<broj<<endl;
            double suma=0;
            for (int i=0; i<broj; i++)
                suma+=broevi[i]->doubleValue();
            cout<<"Sum of all numbers: "<<suma<<endl;
            int brojint=0,brojdouble=0,sumaint=0;
            double sumadouble=0;
            for(int i=0; i<broj; i++)
            {
                Integer *in = dynamic_cast <Integer *> (broevi[i]);
                if(in != 0)
                {
                    brojint++;
                    sumaint+=broevi[i]->intValue();
                }
                Double *d=dynamic_cast<Double *>(broevi[i]);
                if(d != 0)
                {
                    brojdouble++;
                    sumadouble+=broevi[i]->doubleValue();
                }
            }
            cout<<"Count of integer numbers: "<<brojint<<endl;
            cout<<"Sum of integer numbers: "<<sumaint<<endl;
            cout<<"Count of double numbers: "<<brojdouble<<endl;
            cout<<"Sum of double numbers: "<<sumadouble<<endl;
        }
        void integersLessThan (Integer n){
            int brojac=0;
            for(int i=0; i<broj; i++)
            {
                Integer *in=dynamic_cast<Integer *>(broevi[i]);
                if(in)
                    if(broevi[i]->intValue() < n.intValue())
                    {
                        broevi[i]->print();
                        brojac++;
                    }
            }
            if(!brojac) cout<<"None"<<endl;
        }
        void doublesBiggerThan (Double n){
            int brojac=0;
            for(int i=0; i<broj; i++)
            {
                Double *d=dynamic_cast<Double *>(broevi[i]);
                if (d)
                    if(broevi[i]->doubleValue() > n.doubleValue())
                    {
                        broevi[i]->print();
                        brojac++;
                    }
            }
            if(!brojac) cout<<"None"<<endl;
        }
    };

    int main() {

        int n;
        cin>>n;
        Numbers numbers;
        for (int i=0;i<n;i++){
            int type;
            double number;
            cin>>type>>number;
            if (type==0){//Integer object
                Integer * integer = new Integer((int) number);
                numbers+=integer;
            }
            else {
                Double * doublee = new Double(number);
                numbers+=doublee;
            }
        }

        int lessThan;
        double biggerThan;

        cin>>lessThan;
        cin>>biggerThan;

        cout<<"STATISTICS FOR THE NUMBERS\n";
        numbers.statistics();
        cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
        numbers.integersLessThan(Integer(lessThan));
        cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
        numbers.doublesBiggerThan(Double(biggerThan));

        return 0;
    }
