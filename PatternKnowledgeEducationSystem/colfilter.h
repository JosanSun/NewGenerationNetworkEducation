/*
 * CF协同过滤算法实现方法
 *
 * 算法选择 选择了CF——协同过滤之后，我便开始对比User－based算法与Item－based算法，也在网上找了一些参考资料，
 * 通过对比两个Item在不同用户对不同教学案例的测试结果情况，来推荐用户学习的最佳学习案例。
 */
#ifndef COLFILTER_H
#define COLFILTER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <math.h>
using namespace std;


float train_info[950][1501]; //训练集的信息录入，第i位用户对第j部电影的打分，数组值为评分值,默认为0，即没有看过

float sim_matrix[950][950]; //用户i与用户j的相似矩阵（值为相似值sim）

float average_score[950]; //每一位用户的平均分

float knn[950][1501][10];  //knn: 1.人id 2.电影id 3.k值（相似的前k名“邻居”）

float predicting_score[950][1501]; //用户i为电影j的预测打分（用整数表示）

float actual_score[950][1501]; //test测试集中的实际打分(用来最后与predicting_score中的打分对比)

float MAE;

float RMSE;

void init_TrainData(char * fileName,int delLine)
{

    int user_id_buf[delLine];

    int film_id_buf[delLine];

    float score_buf[delLine];

    int time_stamp_buf[delLine];

    ifstream instuf(fileName,ios::in);//读入文件

    instuf.seekg(0,ios::beg);

    if(!instuf)
    {
        cerr<<"File could not be open!"<<endl;
        abort();
    }

    // while(instuf>>user_id>>film_id>>score)
    for(int count=0;count<delLine;count++) //读delLine行数据
    {
        instuf>>user_id_buf[count]>>film_id_buf[count]>>score_buf[count]>>time_stamp_buf[count];

        //cout<<user_id_buf[count]<<'\t'<<film_id_buf[count]<<'\t'<<score_buf[count]<<endl;

        train_info[user_id_buf[count]][film_id_buf[count]]=score_buf[count]; //录入训练集数据（用户i对）
    }


    instuf.close();
}

void init_TestData(char * fileName,int delLine)  //录入测试集
{
    int user_id_buf[delLine];

    int film_id_buf[delLine];

    float score_buf[delLine];

    int time_stamp_buf[delLine];

    ifstream instuf(fileName,ios::in);//读入文件

    instuf.seekg(0,ios::beg);

    if(!instuf)
    {
        cerr<<"File could not be open!"<<endl;
        abort();
    }

    // while(instuf>>user_id>>film_id>>score)
    for(int count=0;count<delLine;count++) //读delLine行数据
    {
        instuf>>user_id_buf[count]>>film_id_buf[count]>>score_buf[count]>>time_stamp_buf[count];

        actual_score[user_id_buf[count]][film_id_buf[count]]=score_buf[count]; //录入测试集数据（用户i对）,该数组用于核对
    }


    instuf.close();



}

void read_TrainData()
{
    for(int i=1;i<=949;i++) //读每行数据
    {
        cout<<"用户:"<<i<<endl;
        for(int j=1;j<=1500;j++)
        {
            if(train_info[i][j]!=0)
            {
                cout<<j<<"--"<<train_info[i][j]<<'\t';
            }
        }
        cout<<"end"<<endl;
    }

}

void read_AverageData()
{
    for(int i=1;i<=949;i++)
    {
        cout<<i<<"   "<<average_score[i]<<endl;
    }
}

void read_sim_matrix()
{
    for(int i=1;i<=949;i++)
    {
        for(int j=1;j<=949;j++)
        {
            if(sim_matrix[i][j]!=0)
            {
                cout<<i<<"   "<<j<<endl;
                cout<<sim_matrix[i][j]<<endl;
            }
        }
    }
}

void calculate_averate()
{

    for(int i=1;i<=949;i++)
    {
        float total_socre=0.0;
        int count=0;//用户i看过的电影数量，用来计算平均值
        for(int j=1;j<=1500;j++)
        {
            if(train_info[i][j]!=0)//如果用户i的矩阵不为0，那么说明他看过这部电影j
            {
                count++;
                total_socre=total_socre+train_info[i][j];
            }
        }
        if(count!=0) //防止分母为0
        {
            average_score[i]=total_socre/count; //计算得到了用户i的平均影评分
        }

    }
}
//获得了每一位用户的平均分，等下用来计算sim_matrix相似矩阵


void calculate_sim_matrix()  //计算两两用户之间的相似性(用训练集中的矩阵数据来计算),相似公式
{

    for(int i=1;i<=949;i++) //从第一位用户开始
    {

        for(int j=1;j<=949;j++)
        {


            float numerator=0.0;//分子

            float denominator=0.0;// 分母

            float denominatorLeft=0.0;//左分母

            float denominatorRight=0.0;//右分母

            if(sim_matrix[i][j]==0&&i!=j)//if1:如果没有计算过相似性，那么进入计算
            {
                for(int k=1;k<=1500;k++)
                {

                    float subNumeratorLeft=0.0;//左分子

                    float subNumeratorRight=0.0;//右分子

                    float subDenominatorLeft=0.0;//左分母

                    float subDenominatorRight=0.0;//右分母

                    if(train_info[i][k]!=0&&train_info[j][k]!=0)//if2:i和j都看过这部电影k(不等于0)如果i和j都看过k电影的话，计算
                    {
                        subNumeratorLeft=(train_info[i][k]-average_score[i]);

                        subNumeratorRight=(train_info[j][k]-average_score[j]);


                        subDenominatorLeft=subNumeratorLeft*subNumeratorLeft;

                        subDenominatorRight=subNumeratorRight*subNumeratorRight;


                        numerator=numerator+subNumeratorLeft*subNumeratorRight; //叠加对于所有用户i、j看过的电影的相似性sim分子

                        denominatorLeft=denominatorLeft+subDenominatorLeft; //左边的部分叠加（需要开根号）

                        denominatorRight=denominatorRight+subDenominatorRight;


                    }// if2end

                }//i与j对k的分析结束，转入k＋1
                //所有电影k循环后，可以开始进行i与j的相似性计算

                denominator=sqrtf(denominatorLeft)*sqrtf(denominatorRight);//相似性公式分母
                if(denominator!=0)
                {
                    sim_matrix[i][j]=numerator/denominator;
                }


            }//if1end

            else
            {
                if(i==j){sim_matrix[i][j]=1;}
            }


            sim_matrix[j][j]=sim_matrix[i][j];//i与j的相似性性满足交换性

        }//i与j的相似性计算完成，转入i与j＋1的相似性计算

    }//i与j的相似性计算完成，转入i＋1与j的相似性计算

}

void calculate_predictingScore(float accuracy,float accuracySecond)//找到用户i对于j将评测电影的k个“邻居”
{
    int c=0;


    for(int i=1;i<=949;i++) //用户i
    {


        for(int k=1;k<=1500;k++)//电影k
        {
            float pre_numerator=0.0;

            float pre_denominator=0.0;

            int firstFloat=0;

            int intary;

            int q;

            float temp=0.0;
            if(predicting_score[i][k]==-1.0)//如果用户i标识为需要对电影k测评（评分为－1）k的话，开始预测
            {
                // 利用相似矩阵来寻找邻居
                //sim_matrix[i][j];
                for(int j=1;j<949;j++)
                {
                    if(sim_matrix[i][j]>=accuracy&&sim_matrix[i][j]<1&&train_info[j][k]!=0&&i!=j)
                    {
                        pre_numerator=sim_matrix[i][j]*train_info[j][k]+pre_numerator;
                        pre_denominator=pre_denominator+sim_matrix[i][j];
                    }

                }

                if(pre_denominator==0)
                {
                    pre_numerator=1;



                c++;//cout<<i<<"  "<<k<<" asd  "<<pre_numerator<<"  asd "<<pre_denominator<<endl;
                }

                else
                {
                temp=pre_numerator/pre_denominator;//error!!!!

                temp=temp+0.10;

                temp=temp*10;

                q=int(temp);//

                firstFloat=q%10;

                intary=q/10;

                if(firstFloat>=5)
                {predicting_score[i][k]=abs(intary)+1;}
                else
                {predicting_score[i][k]=abs(intary);}
                }

                // cout<<"   "<<temp<<"   "<<q<<"    "<<intary<<"   "<<firstFloat<<"   "<<predicting_score[i][k]<<endl;
            }

            else{predicting_score[i][k]=0;}
            //若是跳过if中内容，那么说明用户i已经看过了j电影，无需预测
        }

    }
   // cout<<"有"<<c<<"个用户没算预测分"<<endl;
}

void read_predictingScore()
{
    int count=0;
    for(int i=1;i<=949;i++) //读每行数据
    {
        for(int j=1;j<=1500;j++)
        {
            if(predicting_score[i][j]!=0&&predicting_score[i][j]!=-1)
            {
            cout<<i<<"    "<<j<<endl;
            cout<<predicting_score[i][j]<<endl;
                count++;
            }
        }
    }

    cout<<count<<endl;
}

void init_predictingScore(char * fileName,int delLine) //计算预测分
{

    int user_id_buf[delLine];

    int film_id_buf[delLine];

    float score_buf[delLine];

    int time_stamp_buf[delLine];

    ifstream instuf(fileName,ios::in);//读入文件

    instuf.seekg(0,ios::beg);

    if(!instuf)
    {
        cerr<<"File could not be open!"<<endl;
        abort();
    }


    for(int count=0;count<delLine;count++) //读delLine行数据
    {

        instuf>>user_id_buf[count]>>film_id_buf[count]>>score_buf[count]>>time_stamp_buf[count];


        predicting_score[user_id_buf[count]][film_id_buf[count]]=-1.0; //录入测试集数据（用户i对）


        //cout<<user_id_buf[count]<<"  "<<film_id_buf[count]<<"  "<<predicting_score[user_id_buf[count]][film_id_buf[count]]<<endl;
    }


    instuf.close();
}


void calculate_MAE_and_RMSE(int m)
{
    float MAE_numerator=0.0;
    float RMSE_numerator=0.0;
    for(int i=1;i<=949;i++)
    {
        for(int j=1;j<=1501;j++)
        {
            if(predicting_score[i][j]!=0&&predicting_score[i][j]!=-1)
            {
                MAE_numerator=MAE_numerator+fabsf(predicting_score[i][j]-actual_score[i][j]);
                RMSE_numerator=RMSE_numerator+(predicting_score[i][j]-actual_score[i][j])*(predicting_score[i][j]-actual_score[i][j]);
            }
        }
    }
    MAE=MAE_numerator/m;
    RMSE=sqrtf(RMSE_numerator/m);
}

void find_bestAccuracy()
{
    float accuracy=0.2;
    float accuracySecond=0.2;
    float tempMAE=1.0;
    float tempAccuracy=0;
    for(;accuracy<0.6;accuracy=accuracy+0.002)
    {


    calculate_predictingScore(accuracy,accuracySecond);
    calculate_MAE_and_RMSE(20000);
        if(MAE<tempMAE&&MAE!=0&&tempMAE!=0){tempMAE=MAE;tempAccuracy=accuracy;}
    }
     cout<<tempMAE<<"   "<<tempAccuracy;
}

void writeToTxt(char * fileName1,char * fileName2,int delLine)
{

    int user_id_buf[delLine];

    int film_id_buf[delLine];

    float score_buf[delLine];

    int time_stamp_buf[delLine];

    ifstream instuf(fileName2,ios::in);//读入文件

    instuf.seekg(0,ios::beg);


    fstream in;

    in.open(fileName1,ios::app);

    in.seekg(0,ios::beg);

    if(!instuf)
    {
        cerr<<"File could not be open!"<<endl;
        abort();
    }


    for(int count=0;count<delLine;count++) //读delLine行数据
    {

        instuf>>user_id_buf[count]>>film_id_buf[count]>>score_buf[count]>>time_stamp_buf[count];


        in<<user_id_buf[count]<<"\t\t"<<film_id_buf[count]<<"\t\t"<<predicting_score[user_id_buf[count]][film_id_buf[count]]<<"\t\t"<<actual_score[user_id_buf[count]][film_id_buf[count]]<<endl;


        //cout<<user_id_buf[count]<<"  "<<film_id_buf[count]<<"  "<<predicting_score[user_id_buf[count]][film_id_buf[count]]<<endl;
    }


    instuf.close();
    in.close();

}

int mainFun(int aTest, const char * bTest[])
{

    init_TrainData("/Users/pro/Desktop/data-rs/80train.txt",80000);
    init_TestData("/Users/pro/Desktop/data-rs/test.txt", 20000);
    init_predictingScore("/Users/pro/Desktop/data-rs/test.txt", 20000);
    calculate_averate();
    calculate_sim_matrix();
    //find_bestAccuracy();
    calculate_predictingScore(0.5,0.2);
    calculate_MAE_and_RMSE(20000);
    //writeToTxt("/Users/pro/Desktop/output.txt","/Users/pro/Desktop/data-rs/test.txt",20000);
    //read_predictingScore();
    //read_AverageData();
    //read_TrainData();
    //read_sim_matrix();
    cout<<MAE<<"   "<<RMSE;
    return 0;
}

#endif // COLFILTER_H
