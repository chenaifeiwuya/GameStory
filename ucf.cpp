#include "ucf.h"


UserCF::UserCF(int _k, int _m,CMysql * sql):k(_k),m(_m),m_sql(sql)
{
    {
        //fin.open("user_brand_m123.txt");
        //fout.open("rec_result_by_m123.txt");
        //通过读取数据库获得数据信息
        int res;
        char sqlbuf[1000]="";
        list<string>lstRes;
        sprintf(sqlbuf,"select * from t_user_game;");
        res = m_sql->SelectMysql(sqlbuf,2,lstRes);
        if(!res)
        {
            cout<<"update fail:"<<sqlbuf<<endl;
            return;
        }
        //将u_id和_id添加到user_brands中

        //userid_id , id_userid , user_brands , brand_all
        int userid,brandid,i=0;
        while(!lstRes.empty())
        {
            userid = stoi(lstRes.front());
            lstRes.pop_front();
            if(!lstRes.empty())
            {
                brandid = stoi(lstRes.front());
                lstRes.pop_front();
            }
            if( user_brands[userid].empty())
            {
                userid_id[userid] = i;
                id_userid[i] = userid;
                i++;
            }
            user_brands[userid].insert(brandid);
            brand_all.insert(brandid);
        }

        //id_brands
        map< int,set<int> > :: iterator it = user_brands.begin();
        while( it!=user_brands.end() )
        {
            id_brands[ userid_id[it->first] ] = it->second;
            it++;
        }
        bzero(sim_mat,0);
    }
}



UserCF::~UserCF()
{
    userid_id.clear();
    user_brands.clear();
    id_brands.clear();
    brand_ids.clear();
    brand_all.clear();
    user_brand_rec.clear();
    //fin.close();
    //fout.close();
}





void UserCF::get_sim_mat()    //计算用户和品牌到相似度矩阵
{
    get_reverse_table();
    map< int,set<int> > :: iterator it = brand_ids.begin();
    while(it!=brand_ids.end())
    {
        vector<int> tmp( it->second.begin(),it->second.end() );
        int len = tmp.size();
        //for each brand , traverse all two pair users , sim_mat increment
        for(int i=0;i<len;i++)
            for(int j=i+1;j<len;j++)
            {
                sim_mat[ tmp[i] ][ tmp[j] ]+=1;
                sim_mat[ tmp[j] ][ tmp[i] ]+=1;
            }
            it++;
    }

    int len = id_userid.size();
    for(int i=0;i<len;i++)
        for(int j=0;j<len;j++)
        {
            sim_mat[i][j] /= sqrt( user_brands[ id_userid[i] ].size() * user_brands[ id_userid[j] ].size()  );
            sim_mat[j][i] = sim_mat[i][j];
        }
    cout<<endl;
}


void UserCF::get_reverse_table()
{
    map< int,set<int> > :: iterator it = id_brands.begin();
    while( it!=id_brands.end() )
    {
        set<int> tmp = it->second;
        set<int> :: iterator it2 = tmp.begin();
        while(it2!=tmp.end())
        {
            brand_ids[*it2].insert(it->first);
            it2++;
        }
        it++;
    }
}



set<int> UserCF::get_rec_brand_set_by_user(int userid)
{
    //3.1
    set<int> brand_unused;
    /* set_difference:find different set between two set
     * function : get brand set that userid has never bought before
     */
    set_difference(brand_all.begin(),brand_all.end(),user_brands[userid].begin(),user_brands[userid].end(),inserter( brand_unused , brand_unused.begin() ) );

    sim_idx simidx;
    vector<sim_idx> vec_sim_idx;
    int len = userid_id.size();
    int id = userid_id[userid];
    for(int i=0;i<len;i++)
    {
        simidx.sim=sim_mat[id][i];
        simidx.idx=i;
        vec_sim_idx.push_back(simidx);
    }
    sort( vec_sim_idx.begin(),vec_sim_idx.end(),greater<sim_idx>() ); //order by desc

    //3.2.1
    set<int> rec_ids;
    vector<sim_idx> :: iterator it = vec_sim_idx.begin();
    for(int i=0;i<k;i++)
    {
        rec_ids.insert( (*it).idx );
        it++;
    }

    set<int> rec_brand;
    set<int> :: iterator itt = brand_unused.begin();
    vector<brand_interest> vec_bi; //userid's interest level toward brand
    brand_interest bi;
    while( itt!=brand_unused.end() )
    {
        //3.2.2
        vector<int> newset; // or set<int> newset
        set<int> ids = brand_ids[*itt];
        set_intersection(rec_ids.begin(),rec_ids.end(),ids.begin(),ids.end(),inserter( newset,newset.begin() ));
        if(newset.empty())
        {
            itt++;
            continue;
        }
        double interest = 0.0;
        int len = newset.size();
        for(int i=0;i<len;i++)
        {
            interest += sim_mat[ userid_id[userid] ][ newset[i] ];
        }
        //3.2.3
        bi.brand = *itt;
        bi.Int = interest;
        vec_bi.push_back(bi);
        itt++;
    }//while
                //sort(vec_bi.begin(),vec_bi.end(),greater<brand_interest>() );//感谢@chenyadong的修改建议，这行代码要进行添加
    //3.3
    for(int i=0;i<m&&i<vec_bi.size();i++)
    {
        rec_brand.insert(vec_bi[i].brand);
    }


    return rec_brand;

}


void UserCF::recommend()   //获取推荐
{
    map< int,int > :: iterator it = userid_id.begin();
    while( it!=userid_id.end() )
    {
        user_brand_rec[it->first] = get_rec_brand_set_by_user(it->first);
        it++;
    }
}//recommend

void UserCF::print()
{
    //write recommendation result <user,brand> to file
    cout<<"userCf_print"<<endl;
    map< int,set<int> > :: iterator it = user_brand_rec.begin();
    while( it!=user_brand_rec.end() )
    {
        set<int> tmp = it->second;
        set<int> :: iterator it2 = tmp.begin();
        while(it2!=tmp.end())
        {
            cout<<it->first<<" "<<*it2<<endl;
            it2++;
        }
        it++;
    }

}//print
