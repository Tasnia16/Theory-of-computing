#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>>nfa_table;
vector<vector<int>>states;
vector<vector<vector<int>>>dfa;
queue<vector<int>>q;

void print_dfa(){
	cout<<"  INPUT  ";

	int aa=0;
	for(int i=0;i<dfa[0].size();i++)
        {
		  cout<<"    "<<aa<<"   ";
		  aa++;
	    }
	cout<<endl;
	for(int i=0;i<states.size();i++)
        {
		cout<<"{ ";
		for(int j=0;j<states[i].size();j++)
			cout<<"q"<<states[i][j];
		if(states[i].empty())
            {
			cout<<"eps";
		   }
		cout<<"} ";
		for(int j=0;j<dfa[i].size();j++)
            {
			cout<<"------>";
			for(int k=0;k<dfa[i][j].size();k++)

                {
                    cout<<"q";
				cout<<dfa[i][j][k];

			}
			if(dfa[i][j].empty()){
				cout<<"eps";
			}
		}
		cout<<endl;
	}
}

void print_nfa(){
	cout<<"INPUT"<<"      ";

	int tt=0;
	for(int i=0;i<nfa_table[0].size()-1;i++)
        {
		   cout<<tt<<"    ";
             tt++;
	    }
	//cout<<" eps "<<endl;
	cout<<endl<<endl;
	for(int i=0;i<nfa_table.size();i++)
        {
        cout<<"q"<<i;
		  for(int j=0;j<nfa_table[i].size();j++)
		 {
			cout<<"----->";
			  for(int k=0;k<nfa_table[i][j].size();k++)
			   {
			       cout<<"q";
				  cout<<nfa_table[i][j][k]<<",";

               }

		}
		  cout<<endl;
	}
}

vector<int> closure(int s,vector<vector<vector<int>>>v)
{
    queue<int> q;
	vector<int> t;
	t.push_back(s);
	int a=v[s][v[s].size()-1].size();
	for(int i=0;i<a;i++)
        {
		t.push_back(v[s][v[s].size()-1][i]);
		q.push(t[i]);
	}
	while(!q.empty())
	{
		int a=q.front();
		q.pop();
		if(!v[a][v[a].size()-1].empty()){
			int u=v[a][v[a].size()-1].size();
			for(int i=0;i<u;i++){
				int x=v[a][v[a].size()-1][i];
				if(find(t.begin(),t.end(),x)==t.end()){

					t.push_back(x);
					q.push(x);
				}
			}
		}
	}
return t;
}
int main(void){
	int state_num,input_num;

	cout<<"Enter the number of states in NFA : ";
	cin>>state_num;
	cout<<"Enter number of elements in alphabet : ";
	cin>>input_num;
	for(int i=0;i<state_num;i++)

        {
            vector<vector<int>>sub_table1;

		   cout<<"For state q"<<i<<endl;
		   int tt=0;
		   int output_state,output_num;
		   for(int j=0;j<input_num;j++)
              {
			     vector<int>sub_table2;
			     cout<<"Enter the number of output states for input "<<tt<<" : ";
			     cin>>output_num;
			     cout<<"Enter the output states :"<<endl;
                 for(int i=0;i<output_num;i++)
                      {
				         cin>>output_state;
				         sub_table2.push_back(output_state);
			          }
			      sub_table1.push_back(sub_table2);
                   tt++;
		      }

		 //epsilon control

		vector<int>sub_table2;
		cout<<"Enter no. of output states for input eps : ";
		cin>>output_num;
		cout<<"Enter output states :"<<endl;
		for(int i=0;i<output_num;i++){
			cin>>output_state;
			sub_table2.push_back(output_state);
		}
		sub_table1.push_back(sub_table2);
		nfa_table.push_back(sub_table1);
	}
	cout<<"NFA transition table :"<<endl;
	cout<<"-----------------------"<<endl;
	print_nfa();


	states.push_back(closure(0,nfa_table));
	q.push(states[0]);

	while(!q.empty()){
		vector<int>a=q.front();
		q.pop();
		vector<vector<int>>dfa_sub_table1;
		for(int i=0;i<input_num;i++)
            {
               set<int>s;
			   vector<int>dfa_sub_table2;
			   for(int j=0;j<a.size();j++)
                  {

				  for(int k=0;k<nfa_table[a[j]][i].size();k++)
                      {
					     vector<int> count1= closure(nfa_table[a[j]][i][k],nfa_table);
					      for(int l=0;l<count1.size();l++)
                            {
						      if(s.find(count1[l])==s.end())
						       s.insert(count1[l]);
					        }
				       }

			      }
			for(int m:s)
				dfa_sub_table2.push_back(m);

			dfa_sub_table1.push_back(dfa_sub_table2);

			if(find(states.begin(),states.end(),dfa_sub_table2)==states.end())
			{
				states.push_back(dfa_sub_table2);
				q.push(dfa_sub_table2);
			}
		}

		dfa.push_back(dfa_sub_table1);
	}

	cout<<"DFA transition table :\n";
	cout<<"--------------------\n";
	print_dfa();
}
