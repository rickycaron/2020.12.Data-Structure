// 11-散列1 电话聊天狂人 (25 point(s))
// 给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

// 输入格式:
// 输入首先给出正整数N（≤10 
// 5
//  ），为通话记录条数。随后N行，每行给出一条通话记录。简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

// 输出格式:
// 在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

// 输入样例:
// 4
// 13005711862 13588625832
// 13505711862 13088625832
// 13588625832 18087925832
// 15005713862 13588625832
// 结尾无空行
// 输出样例:
// 13588625832 3
#include<bits/stdc++.h>
using namespace std;
int cmp(const pair<string, int>& x, const pair<string, int>& y)
{
    
    return x.second > y.second;
}

void sortMapByValue(map<string, int>& tMap,vector<pair<string, int> >& tVector)
{
    
    for (map<string, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
        tVector.push_back(make_pair(curr->first, curr->second));

    sort(tVector.begin(), tVector.end(), cmp);
}
int main()
{
    
    map<string,int>mp;
    int n;
    cin>>n;
    string s1;
    for(int i=0; i<n*2; i++)
    {
    
        cin>>s1;
        mp[s1]++;
    }
    vector<pair<string,int>> tVector;
    sortMapByValue(mp,tVector);
    int cnt=0;
    for(int i=0;i<tVector.size();i++)
    {
        if(i==0)
        {
            cout<<tVector[i].first<<" "<<tVector[i].second;
            cnt++;
        }
        else
        {
            if(tVector[i].second==tVector[i-1].second)
            {
                cnt++;
            }
            else
            {
                break;
            }
        }
    }
    if(cnt!=1)
    {
        cout<<" "<<cnt<<endl;
    }
    return 0;
}