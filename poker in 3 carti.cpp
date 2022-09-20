#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>

using namespace std;


char tip_name[4][15]={"Inima Rosie ", "Inima Neagra", "Romb        ", "Trefla      "};
char nr_name[15][7]={" ", "As","Doi","Trei","Patru","Cinci","Sase","Sapte","Opt",
                    "Noua","Zece"," ","Juvete","Regina","Rege"};
struct carti
{
   int tip, nr, val;
};
struct nod
{
    carti carte;
    nod *leg;
};

nod *creare_pachet()
{
    int v[52], nr_carti_ramase=3, x;
    nod *q, *p=NULL;
    for(int i=0;i<52;i++)
    {
        v[i]=0;
    }
    while(nr_carti_ramase)
    {
        x=rand()%52;
        if(v[x]==0)
        {
            v[x]=1;
            nr_carti_ramase--;
            q=new nod;
            q->carte.tip=x/13;
            q->carte.nr=x%13<10?x%13+1:x%13+2;
            q->carte.val=q->carte.nr==1?15:q->carte.nr;
            q->leg=p;
            p=q;
        }
    }
    return p;
}
void schimb(nod *a,nod *b)
{
    carti aux=a->carte;
    a->carte=b->carte;
    b->carte=aux;
}
void sortare(nod *p)
{
    int ok, i;
    nod *q,*u=NULL;

    if (p==NULL)
        return;
    do
    {
        ok=0;
        q=p;

        while (q->leg!=u)
        {
            if (q->carte.val<q->leg->carte.val)
            {
                schimb(q,q->leg);
                ok=1;
            }
            q=q->leg;
        }
        u=q;
    }
    while (ok);
}



void afisarecomb(nod *p,int &ante,int &pairplus,int &val)
{
        nod *u;
        u=p;
        val=-1;
        if(u->carte.val==u->leg->carte.val || u->leg->carte.val==u->leg->leg->carte.val ||u->carte.val==u->leg->leg->carte.val)
        {
            cout<<"Aveti o pereche!"<<endl;
            cout<<"Nu ati primit bonus pentru ca nu aveti cel putin un flush sau mai bun."<<endl;
            val=2;

        }
        else if((u->carte.nr+1==u->leg->carte.nr && u->carte.nr+2==u->leg->carte.nr) && (u->carte.tip==u->leg->carte.tip &&
                            u->leg->carte.tip==u->leg->leg->carte.tip && u->carte.tip==u->leg->leg->carte.tip))
        {
            cout<<"Aveti o tripla royala!"<<endl;
            ante=5*ante;
            pairplus=40*pairplus;
            cout<<"Ati primit un bonus de "<<pairplus<<" de euro pentru ca aveti o tripla royala."<<endl;
            val=6;
        }
        else if(u->carte.tip==u->leg->carte.tip && u->leg->carte.tip==u->leg->leg->carte.tip && u->carte.tip==u->leg->leg->carte.tip)
        {
            cout<<"Aveti un flush!"<<endl;
            pairplus*=4;
            cout<<"Ati primit un bonus de "<<pairplus<<" de euro pentru ca aveti un flush."<<endl;
            val=3;
        }
        else if(u->carte.nr-1==u->leg->carte.nr && u->carte.nr-2==u->leg->carte.nr)
        {
            cout<<"Aveti o tripla!"<<endl;
            pairplus*=6;
            cout<<"Ati primit un bonus de "<<pairplus<<" de euro pentru ca aveti o tripla."<<endl;
            val=4;

        }
        else if(u->carte.val==u->leg->carte.val && u->carte.val==u->leg->leg->carte.val)
        {
            cout<<"Aveti 3 de acelasi tip!"<<endl;
            ante=4*ante;
            pairplus*=30;
            cout<<"Ati primit un bonus de "<<pairplus<<" de euro pentru ca aveti 3 carti de acelasi tip."<<endl;
            val=5;
        }
        else if(u->carte.val>=11 || u->leg->carte.val>=11 || u->leg->leg->carte.val>=11)
        {
            cout<<"Aveti carte mare!"<<endl;
            cout<<"Nu ati primit bonus pentru ca nu aveti cel putin flush sau mai bun."<<endl;
            val=1;
        }
        else if(val==-1)
        {
            cout<<"Nu ati primit bonus pentru ca nu aveti cel putin flush sau mai bun."<<endl;
            cout<<endl;
        }


}
int combdilar(nod *p)
{

        nod *u;
        u=p;
        if(u->carte.val<11 && u->leg->carte.val<11 && u->leg->leg->carte.val<11)
        {
            return 0;
        }
        else if(u->carte.val==u->leg->carte.val || u->leg->carte.val==u->leg->leg->carte.val ||u->carte.val==u->leg->leg->carte.val)
        {

            return 2;

        }
        else if(((u->carte.nr+1==u->leg->carte.nr && u->carte.nr+2==u->leg->carte.nr)) && (u->carte.tip==u->leg->carte.tip && u->leg->carte.tip==u->leg->leg->carte.tip && u->carte.tip==u->leg->leg->carte.tip))
        {

            return 6;
        }
        else if(u->carte.tip==u->leg->carte.tip && u->leg->carte.tip==u->leg->leg->carte.tip && u->carte.tip==u->leg->leg->carte.tip)
        {

            return 3;
        }
        else if(u->carte.nr-1==u->leg->carte.nr && u->carte.nr-2==u->leg->carte.nr)
        {

            return 4;

        }
        else if(u->carte.val==u->leg->carte.val && u->carte.val==u->leg->leg->carte.val)
        {

            return 5;
        }
        else if(u->carte.val>=11 || u->leg->carte.val>=11 || u->leg->leg->carte.val>=11)
        {
            return 1;

        }
        else return -1;
}
int maxim(nod *p)
{
    nod *q;
    int maxim=-1;
    q=p;
    while(q)
    {
       if(q->carte.val>maxim)
       {
           maxim=q->carte.val;
       }
       q=q->leg;
    }
    return maxim;

}
void afisare(nod *p)
{
    nod *q=p;
    cout<<endl;
    while(q)
    {
        cout<<setw(22)<<nr_name[q->carte.nr]<<" de "<<tip_name[q->carte.tip]<<endl;
        q=q->leg;
    }
    cout<<endl;
}
void stergerelista(nod *&p)
{
    nod *q=p,*u;
    while(q!=NULL)
    {
      u=q->leg;
      free(q);
      q=u;
    }
    p=NULL;

}
void joc()
{
     nod *jucator=NULL,*dilar=NULL;
     int ante,pariu,pairplus,x;
     srand(time(NULL));
     cout<<setw(70)<<"********************* Poker in 3 Carti *********************"<<endl;
     cout<<"\nIntroduceti ante-ul:";
     cin>>ante;
     cout<<"Introduceti bonusul pentru perechi+:";
     cin>>pairplus;
     cout<<endl;
     jucator=creare_pachet();
     sortare(jucator);
     cout<<"Mana dumneavoastra:"<<endl;
     afisare(jucator);
     afisarecomb(jucator,ante,pairplus,x);
     cout<<"\nApasati ENTER pentru a continua..."<<endl;
     system("pause>nul");
     cout<<endl;
     dilar=creare_pachet();
     sortare(dilar);
     if(!combdilar(dilar))
     {
         cout<<"Mana dilarului:"<<endl;
         afisare(dilar);
         cout<<"Ati castigat "<<ante+pairplus<<" euro deoarece dilaru nu are o carte mai mare de regina."<<endl;
         stergerelista(jucator);
         stergerelista(dilar);
         return;
     }
     else
     {
        cout<<"\nIntroduceti pariul:";
        cin>>pariu;
        cout<<"\nApasati ENTER pentru a continua..."<<endl;
        system("pause>nul");
        cout<<endl;
        int m=combdilar(dilar);
        if(x<m)
        {
            cout<<"Mana dilarului:"<<endl;
            afisare(dilar);
            cout<<"Ati pierdut "<<ante+pairplus+pariu<<" euro."<<endl;
            stergerelista(jucator);
            stergerelista(dilar);
            return;
        }
        else if(x>m)
        {
            cout<<"Mana dilarului:"<<endl;
            afisare(dilar);
            cout<<"Ati castigat "<<ante+pairplus+pariu<<" euro."<<endl;
            stergerelista(jucator);
            stergerelista(dilar);
            return;
        }
        else if(x==m)
        {
            int a,b;
            a=maxim(jucator);
            b=maxim(dilar);
            if(a>b)
            {
                cout<<"Mana dilarului:"<<endl;
                afisare(dilar);
                cout<<"Ati castigat "<<ante+pairplus+pariu<<" euro."<<endl;
                stergerelista(jucator);
                stergerelista(dilar);
                return;
            }
           else if(a<b)
            {
                cout<<"Mana dilarului:"<<endl;
                afisare(dilar);
                cout<<"Ati pierdut "<<ante+pairplus+pariu<<" euro."<<endl;
                stergerelista(jucator);
                stergerelista(dilar);
                return;
            }
            else if(a==b)
            {
                cout<<"Mana dilarului:"<<endl;
                afisare(dilar);
                cout<<"Egalitate.";
                cout<<"Ati primit inapoi "<<ante+pairplus+pariu<<" euro."<<endl;
                stergerelista(jucator);
                stergerelista(dilar);
                return;
            }
        }

     }

}

int main()
{
    char y[3];
    joc();
    cout<<"\nDoriti sa reincercati?"<<endl;
    cin>>y;
    if(!strcmp(y,"NU") ||!strcmp(y,"Nu") ||!strcmp(y,"nU") || !strcmp(y,"nu"))
    {
       return 0;
    }
    while(!strcmp(y,"Da") ||!strcmp(y,"DA") ||!strcmp(y,"dA") || !strcmp(y,"da"))
    {
            system("cls");
            joc();
            cout<<"\nDoriti sa reincercati?"<<endl;
            cin>>y;
    }

    return 0;

}
