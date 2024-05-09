#ifndef UCF_H
#define UCF_H


#include<iostream>
#include<fstream>
#include<stdio.h>
#include<map>
#include<set>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>

using namespace std;
#include "Mysql.h"
const int MAX = 1000;

class UserCF
{
private:
        int k , m ; //k: the most k persons interested in the brand i ; m : choose the former m brands which user u are most interested in
        map< int,int > userid_id;
        map< int,int > id_userid;
        map< int,set<int> > user_brands;
        map< int,set<int> > id_brands;
        map< int,set<int> > brand_ids;
        set<int> brand_all;
        map< int,set<int> > user_brand_rec;
        ifstream fin;
        ofstream fout;
        double sim_mat[MAX][MAX];
        typedef struct sim_idx
        {
            double sim;
            int idx;
            bool operator > (const sim_idx &other) const
            {
                return sim > other.sim;
            }
        }sim_idx;
        typedef struct brand_interest
        {
            double Int; // Int = interest
            int brand;
            bool operator > (const brand_interest &other) const
            {
                return Int > other.Int;
            }
        }brand_interest;

public:
        UserCF(int _k , int _m,CMysql * m_sql);

        void get_sim_mat();

        //brand_ids - brand : userid1,userid2,userid3...
        void get_reverse_table();


        set<int> get_rec_brand_set_by_user(int userid);

        void recommend();

        void print();

        ~UserCF();
public:
        CMysql * m_sql;
};

/*
int main(int argc , char *argv[])
{
    if(argc!=3)
    {
        cout<<"Usage : ./a.out k m"<<endl;
        exit(1);
    }
    int k = atoi(argv[1]) ;
    int m = atoi(argv[2]) ;

    UserCF ucf(k,m);
    ucf.get_sim_mat();
    ucf.recommend();
#if 1
    ucf.print();
#endif
    return 0;
}
*/
#endif // UCF_H
